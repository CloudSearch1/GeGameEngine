#include <GeCore/ECS/Components/CCamera.h>
#include <GeCore/ECS/Components/CPhysicalBox.h>
#include <GeCore/ECS/Components/CPhysicalSphere.h>
#include <GeCore/ECS/Components/CPhysicalCapsule.h>
#include <GeCore/ECS/Components/CMaterialRenderer.h>
#include <GeCore/ECS/Components/CPointLight.h>
#include <GeCore/ECS/Components/CDirectionalLight.h>
#include <GeCore/ECS/Components/CSpotLight.h>

#include <GeAnalytics/Profiling/ProfilerSpy.h>

#include <GeDebug/Assertion.h>

#include "GeEditor/Core/EditorRenderer.h"
#include "GeEditor/Core/EditorResources.h"
#include "GeEditor/Panels/AView.h"
#include "GeEditor/Panels/GameView.h"
#include "GeEditor/Core/GizmoBehaviour.h"
#include "GeEditor/Settings/EditorSettings.h"

#include "GeEditor/Core/EditorActions.h"

using namespace GeMaths;
using namespace GeRendering::Resources;
using namespace GeCore::Resources;

const GeMaths::FVector3 DEBUG_BOUNDS_COLOR		= { 1.0f, 0.0f, 0.0f };
const GeMaths::FVector3 LIGHT_VOLUME_COLOR		= { 1.0f, 1.0f, 0.0f };
const GeMaths::FVector3 COLLIDER_COLOR			= { 0.0f, 1.0f, 0.0f };
const GeMaths::FVector3 FRUSTUM_COLOR			= { 1.0f, 1.0f, 1.0f };

GeEditor::Core::EditorRenderer::EditorRenderer(Context& p_context) : m_context(p_context)
{
	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::STENCIL_TEST, true);
	m_context.renderer->SetStencilOperations(GeRendering::Settings::EOperation::KEEP, GeRendering::Settings::EOperation::KEEP, GeRendering::Settings::EOperation::REPLACE);
	m_context.renderer->SetStencilAlgorithm(GeRendering::Settings::EComparaisonAlgorithm::ALWAYS, 1, 0xFF);

	InitMaterials();

	m_context.renderer->RegisterModelMatrixSender([this](const GeMaths::FMatrix4 & p_modelMatrix)
	{
		m_context.engineUBO->SetSubData(GeMaths::FMatrix4::Transpose(p_modelMatrix), 0);
	});

	m_context.renderer->RegisterUserMatrixSender([this](const GeMaths::FMatrix4 & p_userMatrix)
	{
		m_context.engineUBO->SetSubData
		(
			p_userMatrix, 

			sizeof(GeMaths::FMatrix4) +
			sizeof(GeMaths::FMatrix4) +
			sizeof(GeMaths::FMatrix4) +
			sizeof(GeMaths::FVector3) +
			sizeof(float)
		);
	});
}

void GeEditor::Core::EditorRenderer::InitMaterials()
{
	m_defaultMaterial.SetShader(m_context.shaderManager[":Shaders\\Standard.glsl"]);
	m_defaultMaterial.Set("u_Diffuse", FVector4(1.f, 1.f, 1.f, 1.f));
	m_defaultMaterial.Set("u_Shininess", 100.0f);
	m_defaultMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);

	m_emptyMaterial.SetShader(m_context.shaderManager[":Shaders\\Unlit.glsl"]);
	m_emptyMaterial.Set("u_Diffuse", FVector4(1.f, 0.f, 1.f, 1.0f));
	m_emptyMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);

	m_gridMaterial.SetShader(m_context.editorResources->GetShader("Grid"));
	m_gridMaterial.SetBlendable(true);
	m_gridMaterial.SetBackfaceCulling(false);
	m_gridMaterial.SetDepthTest(false);

	m_cameraMaterial.SetShader(m_context.shaderManager[":Shaders\\Lambert.glsl"]);
	m_cameraMaterial.Set("u_Diffuse", FVector4(0.0f, 0.3f, 0.7f, 1.0f));
	m_cameraMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);

	m_lightMaterial.SetShader(m_context.editorResources->GetShader("Billboard"));
	m_lightMaterial.Set("u_Diffuse", FVector4(1.f, 1.f, 0.5f, 0.5f));
	m_lightMaterial.SetBackfaceCulling(false);
	m_lightMaterial.SetBlendable(true);
	m_lightMaterial.SetDepthTest(false);

	m_stencilFillMaterial.SetShader(m_context.shaderManager[":Shaders\\Unlit.glsl"]);
	m_stencilFillMaterial.SetBackfaceCulling(true);
	m_stencilFillMaterial.SetDepthTest(false);
	m_stencilFillMaterial.SetColorWriting(false);
	m_stencilFillMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);

	m_textureMaterial.SetShader(m_context.shaderManager[":Shaders\\Unlit.glsl"]);
	m_textureMaterial.Set("u_Diffuse", FVector4(1.f, 1.f, 1.f, 1.f));
	m_textureMaterial.SetBackfaceCulling(false);
	m_textureMaterial.SetBlendable(true);
	m_textureMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);

	m_outlineMaterial.SetShader(m_context.shaderManager[":Shaders\\Unlit.glsl"]);
	m_outlineMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);
	m_outlineMaterial.SetDepthTest(false);

	m_gizmoArrowMaterial.SetShader(m_context.editorResources->GetShader("Gizmo"));
	m_gizmoArrowMaterial.SetGPUInstances(3);
	m_gizmoArrowMaterial.Set("u_IsBall", false);
	m_gizmoArrowMaterial.Set("u_IsPickable", false);

	m_gizmoBallMaterial.SetShader(m_context.editorResources->GetShader("Gizmo"));
	m_gizmoBallMaterial.Set("u_IsBall", true);
	m_gizmoBallMaterial.Set("u_IsPickable", false);

	m_gizmoPickingMaterial.SetShader(m_context.editorResources->GetShader("Gizmo"));
	m_gizmoPickingMaterial.SetGPUInstances(3);
	m_gizmoPickingMaterial.Set("u_IsBall", false);
	m_gizmoPickingMaterial.Set("u_IsPickable", true);

	m_actorPickingMaterial.SetShader(m_context.shaderManager[":Shaders\\Unlit.glsl"]);
	m_actorPickingMaterial.Set("u_Diffuse", FVector4(1.f, 1.f, 1.f, 1.0f));
	m_actorPickingMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);
	m_actorPickingMaterial.SetFrontfaceCulling(false);
	m_actorPickingMaterial.SetBackfaceCulling(false);
}

void GeEditor::Core::EditorRenderer::PreparePickingMaterial(GeCore::ECS::Actor& p_actor, GeCore::Resources::Material& p_material)
{
	uint32_t actorID = static_cast<uint32_t>(p_actor.GetID());

	auto bytes = reinterpret_cast<uint8_t*>(&actorID);
	auto color = FVector4{ bytes[0] / 255.0f, bytes[1] / 255.0f, bytes[2] / 255.0f, 1.0f };

	p_material.Set("u_Diffuse", color);
}

GeMaths::FMatrix4 GeEditor::Core::EditorRenderer::CalculateCameraModelMatrix(GeCore::ECS::Actor& p_actor)
{
	auto translation = FMatrix4::Translation(p_actor.transform.GetWorldPosition());
	auto rotation = FQuaternion::ToMatrix4(p_actor.transform.GetWorldRotation());

	return translation * rotation;
}

void GeEditor::Core::EditorRenderer::RenderScene(const GeMaths::FVector3& p_cameraPosition, const GeRendering::LowRenderer::Camera& p_camera, const GeRendering::Data::Frustum* p_customFrustum)
{
	/* Render the actors */
	m_context.lightSSBO->Bind(0);
	m_context.renderer->RenderScene(*m_context.sceneManager.GetCurrentScene(), p_cameraPosition, p_camera, p_customFrustum, &m_emptyMaterial);
	m_context.lightSSBO->Unbind();
}

void GeEditor::Core::EditorRenderer::RenderSceneForActorPicking()
{
	auto& scene = *m_context.sceneManager.GetCurrentScene();

	/* Render models */
	for (auto modelRenderer : scene.GetFastAccessComponents().modelRenderers)
	{
		auto& actor = modelRenderer->owner;

		if (actor.IsActive())
		{
			if (auto model = modelRenderer->GetModel())
			{
				if (auto materialRenderer = modelRenderer->owner.GetComponent<GeCore::ECS::Components::CMaterialRenderer>())
				{
					const GeCore::ECS::Components::CMaterialRenderer::MaterialList& materials = materialRenderer->GetMaterials();
					const auto& modelMatrix = actor.transform.GetWorldMatrix();

					PreparePickingMaterial(actor, m_actorPickingMaterial);

					for (auto mesh : model->GetMeshes())
					{
						GeCore::Resources::Material* material = nullptr;

						if (mesh->GetMaterialIndex() < MAX_MATERIAL_COUNT)
						{
							material = materials.at(mesh->GetMaterialIndex());
							if (!material || !material->GetShader())
								material = &m_emptyMaterial;
						}

						if (material)
						{
							m_actorPickingMaterial.SetBackfaceCulling(material->HasBackfaceCulling());
							m_actorPickingMaterial.SetFrontfaceCulling(material->HasFrontfaceCulling());
							m_actorPickingMaterial.SetColorWriting(material->HasColorWriting());
							m_actorPickingMaterial.SetDepthTest(material->HasDepthTest());
							m_actorPickingMaterial.SetDepthWriting(material->HasDepthWriting());

							m_context.renderer->DrawMesh(*mesh, m_actorPickingMaterial, &modelMatrix);
						}
					}
				}
			}
		}
	}

	/* Render cameras */
	for (auto camera : m_context.sceneManager.GetCurrentScene()->GetFastAccessComponents().cameras)
	{
		auto& actor = camera->owner;

		if (actor.IsActive())
		{
			PreparePickingMaterial(actor, m_actorPickingMaterial);
			auto& model = *m_context.editorResources->GetModel("Camera");
			auto modelMatrix = CalculateCameraModelMatrix(actor);

			m_context.renderer->DrawModelWithSingleMaterial(model, m_actorPickingMaterial, &modelMatrix);
		}
	}

	/* Render lights */
	if (Settings::EditorSettings::LightBillboardScale > 0.001f)
	{
		m_context.renderer->Clear(false, true, false);

		m_lightMaterial.SetDepthTest(true);
		m_lightMaterial.Set<float>("u_Scale", Settings::EditorSettings::LightBillboardScale * 0.1f);
		m_lightMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", nullptr);

		for (auto light : m_context.sceneManager.GetCurrentScene()->GetFastAccessComponents().lights)
		{
			auto& actor = light->owner;

			if (actor.IsActive())
			{
				PreparePickingMaterial(actor, m_lightMaterial);
				auto& model = *m_context.editorResources->GetModel("Vertical_Plane");
				auto modelMatrix = FMatrix4::Translation(actor.transform.GetWorldPosition());
				m_context.renderer->DrawModelWithSingleMaterial(model, m_lightMaterial, &modelMatrix);
			}
		}
	}
}

void GeEditor::Core::EditorRenderer::RenderUI()
{
	m_context.uiManager->Render();
}

void GeEditor::Core::EditorRenderer::RenderCameras()
{
	using namespace GeMaths;

	for (auto camera : m_context.sceneManager.GetCurrentScene()->GetFastAccessComponents().cameras)
	{
		auto& actor = camera->owner;

		if (actor.IsActive())
		{
			auto& model = *m_context.editorResources->GetModel("Camera");
			auto modelMatrix = CalculateCameraModelMatrix(actor);
			
			m_context.renderer->DrawModelWithSingleMaterial(model, m_cameraMaterial, &modelMatrix);
		}
	}
}

void GeEditor::Core::EditorRenderer::RenderLights()
{
	using namespace GeMaths;

	m_lightMaterial.SetDepthTest(false);
	m_lightMaterial.Set<float>("u_Scale", Settings::EditorSettings::LightBillboardScale * 0.1f);

	for (auto light : m_context.sceneManager.GetCurrentScene()->GetFastAccessComponents().lights)
	{
		auto& actor = light->owner;

		if (actor.IsActive())
		{
			auto& model = *m_context.editorResources->GetModel("Vertical_Plane");
			auto modelMatrix = FMatrix4::Translation(actor.transform.GetWorldPosition());

			GeRendering::Resources::Texture* texture = nullptr;

			switch (static_cast<GeRendering::Entities::Light::Type>(static_cast<int>(light->GetData().type)))
			{
			case GeRendering::Entities::Light::Type::POINT:				texture = m_context.editorResources->GetTexture("Bill_Point_Light");			break;
			case GeRendering::Entities::Light::Type::SPOT:				texture = m_context.editorResources->GetTexture("Bill_Spot_Light");				break;
			case GeRendering::Entities::Light::Type::DIRECTIONAL:		texture = m_context.editorResources->GetTexture("Bill_Directional_Light");		break;
			case GeRendering::Entities::Light::Type::AMBIENT_BOX:		texture = m_context.editorResources->GetTexture("Bill_Ambient_Box_Light");		break;
			case GeRendering::Entities::Light::Type::AMBIENT_SPHERE:	texture = m_context.editorResources->GetTexture("Bill_Ambient_Sphere_Light");	break;
			}

			const auto& lightColor = light->GetColor();
			m_lightMaterial.Set<GeRendering::Resources::Texture*>("u_DiffuseMap", texture);
			m_lightMaterial.Set<GeMaths::FVector4>("u_Diffuse", GeMaths::FVector4(lightColor.x, lightColor.y, lightColor.z, 0.75f));
			m_context.renderer->DrawModelWithSingleMaterial(model, m_lightMaterial, &modelMatrix);
		}
	}
}

void GeEditor::Core::EditorRenderer::RenderGizmo(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation, GeEditor::Core::EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis)
{
	using namespace GeMaths;

	FMatrix4 model = FMatrix4::Translation(p_position) * FQuaternion::ToMatrix4(FQuaternion::Normalize(p_rotation));

	GeRendering::Resources::Model* arrowModel = nullptr;

	if (!p_pickable)
	{
		FMatrix4 sphereModel = model * GeMaths::FMatrix4::Scaling({ 0.1f, 0.1f, 0.1f });
		m_context.renderer->DrawModelWithSingleMaterial(*m_context.editorResources->GetModel("Sphere"), m_gizmoBallMaterial, &sphereModel);
		m_gizmoArrowMaterial.Set("u_HighlightedAxis", p_highlightedAxis);

		switch (p_operation)
		{
		case GeEditor::Core::EGizmoOperation::TRANSLATE:
			arrowModel = m_context.editorResources->GetModel("Arrow_Translate");
			break;
		case GeEditor::Core::EGizmoOperation::ROTATE:
			arrowModel = m_context.editorResources->GetModel("Arrow_Rotate");
			break;
		case GeEditor::Core::EGizmoOperation::SCALE:
			arrowModel = m_context.editorResources->GetModel("Arrow_Scale");
			break;
		}
	}
	else
	{
		arrowModel = m_context.editorResources->GetModel("Arrow_Picking");
	}

	if (arrowModel)
	{
		m_context.renderer->DrawModelWithSingleMaterial(*arrowModel, p_pickable ? m_gizmoPickingMaterial : m_gizmoArrowMaterial, &model);
	}
}

void GeEditor::Core::EditorRenderer::RenderModelToStencil(const GeMaths::FMatrix4& p_worldMatrix, GeRendering::Resources::Model& p_model)
{
	m_context.renderer->SetStencilMask(0xFF);
	m_context.renderer->DrawModelWithSingleMaterial(p_model, m_stencilFillMaterial, &p_worldMatrix);
	m_context.renderer->SetStencilMask(0x00);
}

void GeEditor::Core::EditorRenderer::RenderModelOutline(const GeMaths::FMatrix4& p_worldMatrix, GeRendering::Resources::Model& p_model, float p_width)
{
	m_context.renderer->SetStencilAlgorithm(GeRendering::Settings::EComparaisonAlgorithm::NOTEQUAL, 1, 0xFF);
	m_context.renderer->SetRasterizationMode(GeRendering::Settings::ERasterizationMode::LINE);
	m_context.renderer->SetRasterizationLinesWidth(p_width);
	m_context.renderer->DrawModelWithSingleMaterial(p_model, m_outlineMaterial, &p_worldMatrix);
	m_context.renderer->SetRasterizationLinesWidth(1.f);
	m_context.renderer->SetRasterizationMode(GeRendering::Settings::ERasterizationMode::FILL);
	m_context.renderer->SetStencilAlgorithm(GeRendering::Settings::EComparaisonAlgorithm::ALWAYS, 1, 0xFF);
}

void GeEditor::Core::EditorRenderer::RenderActorOutlinePass(GeCore::ECS::Actor& p_actor, bool p_toStencil, bool p_isSelected)
{
	float outlineWidth = p_isSelected ? 5.0f : 2.5f;

	m_outlineMaterial.Set("u_Diffuse", p_isSelected ? FVector4(1.f, 0.7f, 0.f, 1.0f) : FVector4(1.f, 1.f, 0.f, 1.0f));

	if (p_actor.IsActive())
	{
		/* Render static mesh outline and bounding spheres */
		if (auto modelRenderer = p_actor.GetComponent<GeCore::ECS::Components::CModelRenderer>(); modelRenderer && modelRenderer->GetModel())
		{
			if (p_toStencil)
				RenderModelToStencil(p_actor.transform.GetWorldMatrix(), *modelRenderer->GetModel());
			else
				RenderModelOutline(p_actor.transform.GetWorldMatrix(), *modelRenderer->GetModel(), outlineWidth);

			if (p_isSelected && Settings::EditorSettings::ShowGeometryBounds && !p_toStencil)
			{
				RenderBoundingSpheres(*modelRenderer);
			}
		}

		/* Render camera component outline */
		if (auto cameraComponent = p_actor.GetComponent<GeCore::ECS::Components::CCamera>(); cameraComponent)
		{
			auto model = CalculateCameraModelMatrix(p_actor);

			if (p_toStencil)
				RenderModelToStencil(model, *m_context.editorResources->GetModel("Camera"));
			else
				RenderModelOutline(model, *m_context.editorResources->GetModel("Camera"), outlineWidth);

			if (p_isSelected && !p_toStencil)
			{
				RenderCameraFrustum(*cameraComponent);
			}
		}

		if (p_isSelected && !p_toStencil)
		{
			/* Render the actor collider */
			if (p_actor.GetComponent<GeCore::ECS::Components::CPhysicalObject>())
			{
				RenderActorCollider(p_actor);
			}

			/* Render the actor ambient light */
			if (auto ambientBoxComp = p_actor.GetComponent<GeCore::ECS::Components::CAmbientBoxLight>())
			{
				RenderAmbientBoxVolume(*ambientBoxComp);
			}

			if (auto ambientSphereComp = p_actor.GetComponent<GeCore::ECS::Components::CAmbientSphereLight>())
			{
				RenderAmbientSphereVolume(*ambientSphereComp);
			}

			if (GeEditor::Settings::EditorSettings::ShowLightBounds)
			{
				if (auto light = p_actor.GetComponent<GeCore::ECS::Components::CLight>())
				{
					RenderLightBounds(*light);
				}
			}
		}

		for (auto& child : p_actor.GetChildren())
		{
			RenderActorOutlinePass(*child, p_toStencil, p_isSelected);
		}
	}
}

void DrawFrustumLines(GeRendering::Core::ShapeDrawer& p_drawer,
                      const GeMaths::FVector3& pos,
                      const GeMaths::FVector3& forward,
                      float near,
                      const float far,
                      const GeMaths::FVector3& a,
                      const GeMaths::FVector3& b,
                      const GeMaths::FVector3& c,
                      const GeMaths::FVector3& d,
                      const GeMaths::FVector3& e,
                      const GeMaths::FVector3& f,
                      const GeMaths::FVector3& g,
                      const GeMaths::FVector3& h)
{
    // Convenient lambda to draw a frustum line
    auto draw = [&](const FVector3& p_start, const FVector3& p_end, const float planeDistance)
    {
        auto offset = pos + forward * planeDistance;
        auto start = offset + p_start;
        auto end = offset + p_end;
        p_drawer.DrawLine(start, end, FRUSTUM_COLOR);
    };

    // Draw near plane
    draw(a, b, near);
    draw(b, d, near);
    draw(d, c, near);
    draw(c, a, near);

    // Draw far plane
    draw(e, f, far);
    draw(f, h, far);
    draw(h, g, far);
    draw(g, e, far);

    // Draw lines between near and far planes
    draw(a + forward * near, e + forward * far, 0);
    draw(b + forward * near, f + forward * far, 0);
    draw(c + forward * near, g + forward * far, 0);
    draw(d + forward * near, h + forward * far, 0);
}

void GeEditor::Core::EditorRenderer::RenderCameraPerspectiveFrustum(std::pair<uint16_t, uint16_t>& p_size, GeCore::ECS::Components::CCamera& p_camera)
{
    const auto& owner = p_camera.owner;
    auto& camera = p_camera.GetCamera();

    const auto& cameraPos = owner.transform.GetWorldPosition();
    const auto& cameraRotation = owner.transform.GetWorldRotation();
    const auto& cameraForward = owner.transform.GetWorldForward();

    camera.CacheMatrices(p_size.first, p_size.second, cameraPos, cameraRotation);
    const auto proj = FMatrix4::Transpose(camera.GetProjectionMatrix());
    const auto near = camera.GetNear();
    const auto far = camera.GetFar();

    const auto nLeft = near * (proj.data[2] - 1.0f) / proj.data[0];
    const auto nRight = near * (1.0f + proj.data[2]) / proj.data[0];
    const auto nTop = near * (1.0f + proj.data[6]) / proj.data[5];
    const auto nBottom = near * (proj.data[6] - 1.0f) / proj.data[5];

    const auto fLeft = far * (proj.data[2] - 1.0f) / proj.data[0];
    const auto fRight = far * (1.0f + proj.data[2]) / proj.data[0];
    const auto fTop = far * (1.0f + proj.data[6]) / proj.data[5];
    const auto fBottom = far * (proj.data[6] - 1.0f) / proj.data[5];

    auto a = cameraRotation * FVector3{ nLeft, nTop, 0 };
    auto b = cameraRotation * FVector3{ nRight, nTop, 0 };
    auto c = cameraRotation * FVector3{ nLeft, nBottom, 0 };
    auto d = cameraRotation * FVector3{ nRight, nBottom, 0 };
    auto e = cameraRotation * FVector3{ fLeft, fTop, 0 };
    auto f = cameraRotation * FVector3{ fRight, fTop, 0 };
    auto g = cameraRotation * FVector3{ fLeft, fBottom, 0 };
    auto h = cameraRotation * FVector3{ fRight, fBottom, 0 };

    DrawFrustumLines(*m_context.shapeDrawer, cameraPos, cameraForward, near, far, a, b, c, d, e, f, g, h);
}

void GeEditor::Core::EditorRenderer::RenderCameraOrthographicFrustum(std::pair<uint16_t, uint16_t>& p_size, GeCore::ECS::Components::CCamera& p_camera)
{
    auto& owner = p_camera.owner;
    auto& camera = p_camera.GetCamera();
    const auto ratio = p_size.first / static_cast<float>(p_size.second);

    const auto& cameraPos = owner.transform.GetWorldPosition();
    const auto& cameraRotation = owner.transform.GetWorldRotation();
    const auto& cameraForward = owner.transform.GetWorldForward();

    const auto near = camera.GetNear();
    const auto far = camera.GetFar();
    const auto size = p_camera.GetSize();

    const auto right = ratio * size;
    const auto left = -right;
    const auto top = size;
    const auto bottom = -top;

    const auto a = cameraRotation * FVector3{ left, top, 0 };
    const auto b = cameraRotation * FVector3{ right, top, 0 };
    const auto c = cameraRotation * FVector3{ left, bottom, 0 };
    const auto d = cameraRotation * FVector3{ right, bottom, 0 };

    DrawFrustumLines(*m_context.shapeDrawer, cameraPos, cameraForward, near, far, a, b, c, d, a, b, c, d);
}

void GeEditor::Core::EditorRenderer::RenderCameraFrustum(GeCore::ECS::Components::CCamera& p_camera)
{
    auto& gameView = EDITOR_PANEL(Panels::GameView, "Game View");
    auto gameViewSize = gameView.GetSafeSize();

    if (gameViewSize.first == 0 || gameViewSize.second == 0)
    {
        gameViewSize = { 16, 9 };
    }

    switch (p_camera.GetProjectionMode())
    {
    case GeRendering::Settings::EProjectionMode::ORTHOGRAPHIC:
        RenderCameraOrthographicFrustum(gameViewSize, p_camera);
        break;
    
    case GeRendering::Settings::EProjectionMode::PERSPECTIVE:
        RenderCameraPerspectiveFrustum(gameViewSize, p_camera);
        break;
    }
}

void GeEditor::Core::EditorRenderer::RenderActorCollider(GeCore::ECS::Actor & p_actor)
{
	using namespace GeCore::ECS::Components;
	using namespace GePhysics::Entities;

	bool depthTestBackup = m_context.renderer->GetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST);
	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, false);

	/* Draw the box collider if any */
	if (auto boxColliderComponent = p_actor.GetComponent<GeCore::ECS::Components::CPhysicalBox>(); boxColliderComponent)
	{
		GeMaths::FQuaternion rotation = p_actor.transform.GetWorldRotation();
		GeMaths::FVector3 center = p_actor.transform.GetWorldPosition();
		GeMaths::FVector3 colliderSize = boxColliderComponent->GetSize();
		GeMaths::FVector3 actorScale = p_actor.transform.GetWorldScale();
		GeMaths::FVector3 halfSize = { colliderSize.x * actorScale.x, colliderSize.y * actorScale.y, colliderSize.z * actorScale.z };
		GeMaths::FVector3 size = halfSize * 2.f;
		
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, -halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ -halfSize.x, -halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ -halfSize.x, +halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, -halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ -halfSize.x, +halfSize.y, -halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, -halfSize.y, +halfSize.z }, center	+ rotation * GeMaths::FVector3{ -halfSize.x, +halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ +halfSize.x, -halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, -halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ +halfSize.x, halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, +halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ +halfSize.x, -halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, +halfSize.y, -halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ +halfSize.x, -halfSize.y, +halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, +halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, -halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, -halfSize.y, -halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, +halfSize.y, -halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, +halfSize.y, -halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, -halfSize.y, +halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, -halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * GeMaths::FVector3{ -halfSize.x, +halfSize.y, +halfSize.z }, center	+ rotation * GeMaths::FVector3{ +halfSize.x, +halfSize.y, +halfSize.z }, GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
	}

	/* Draw the sphere collider if any */
	if (auto sphereColliderComponent = p_actor.GetComponent<GeCore::ECS::Components::CPhysicalSphere>(); sphereColliderComponent)
	{
		FVector3 actorScale = p_actor.transform.GetWorldScale();
		GeMaths::FQuaternion rotation = p_actor.transform.GetWorldRotation();
		GeMaths::FVector3 center = p_actor.transform.GetWorldPosition();
		float radius = sphereColliderComponent->GetRadius() * std::max(std::max(std::max(actorScale.x, actorScale.y), actorScale.z), 0.0f);

		for (float i = 0; i <= 360.0f; i += 10.0f)
		{
			m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), sin(i * (3.14f / 180.0f)), 0.f } * radius), center + rotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), sin((i + 10.0f) * (3.14f / 180.0f)), 0.f } * radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
			m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ 0.f, sin(i * (3.14f / 180.0f)), cos(i * (3.14f / 180.0f)) } * radius), center + rotation * (GeMaths::FVector3{ 0.f, sin((i + 10.0f) * (3.14f / 180.0f)), cos((i + 10.0f) * (3.14f / 180.0f)) } * radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
			m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), 0.f, sin(i * (3.14f / 180.0f)) } * radius), center + rotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), 0.f, sin((i + 10.0f) * (3.14f / 180.0f)) } * radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		}
	}

	/* Draw the capsule collider if any */
	if (auto capsuleColliderComponent = p_actor.GetComponent<GeCore::ECS::Components::CPhysicalCapsule>(); capsuleColliderComponent)
	{
		float radius = abs(capsuleColliderComponent->GetRadius() * std::max(std::max(p_actor.transform.GetWorldScale().x, p_actor.transform.GetWorldScale().z), 0.f));
		float height = abs(capsuleColliderComponent->GetHeight() * p_actor.transform.GetWorldScale().y);
		float halfHeight = height / 2;

		FVector3 actorScale = p_actor.transform.GetWorldScale();
		GeMaths::FQuaternion rotation = p_actor.transform.GetWorldRotation();
		GeMaths::FVector3 center = p_actor.transform.GetWorldPosition();

		GeMaths::FVector3 hVec = { 0.0f, halfHeight, 0.0f };
		for (float i = 0; i < 360.0f; i += 10.0f)
		{
			m_context.shapeDrawer->DrawLine(center + rotation * (hVec + GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), 0.f, sin(i * (3.14f / 180.0f)) } *radius), center + rotation * (hVec + GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), 0.f, sin((i + 10.0f) * (3.14f / 180.0f)) } *radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
			m_context.shapeDrawer->DrawLine(center + rotation * (-hVec + GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), 0.f, sin(i * (3.14f / 180.0f)) } *radius), center + rotation * (-hVec + GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), 0.f, sin((i + 10.0f) * (3.14f / 180.0f)) } *radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);

			if (i < 180.f)
			{
				m_context.shapeDrawer->DrawLine(center + rotation * (hVec + GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), sin(i * (3.14f / 180.0f)), 0.f } * radius), center + rotation * (hVec + GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), sin((i + 10.0f) * (3.14f / 180.0f)), 0.f } * radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
				m_context.shapeDrawer->DrawLine(center + rotation * (hVec + GeMaths::FVector3{ 0.f, sin(i * (3.14f / 180.0f)), cos(i * (3.14f / 180.0f)) } * radius), center + rotation * (hVec + GeMaths::FVector3{ 0.f, sin((i + 10.0f) * (3.14f / 180.0f)), cos((i + 10.0f) * (3.14f / 180.0f)) } * radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
			}
			else
			{
				m_context.shapeDrawer->DrawLine(center + rotation * (-hVec + GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), sin(i * (3.14f / 180.0f)), 0.f } * radius), center + rotation * (-hVec + GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), sin((i + 10.0f) * (3.14f / 180.0f)), 0.f } * radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
				m_context.shapeDrawer->DrawLine(center + rotation * (-hVec + GeMaths::FVector3{ 0.f, sin(i * (3.14f / 180.0f)), cos(i * (3.14f / 180.0f)) } * radius), center + rotation * (-hVec + GeMaths::FVector3{ 0.f, sin((i + 10.0f) * (3.14f / 180.0f)), cos((i + 10.0f) * (3.14f / 180.0f)) } * radius), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
			}
		}

		m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ -radius, -halfHeight, 0.f }),	center + rotation * (GeMaths::FVector3{ -radius, +halfHeight, 0.f }), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ radius, -halfHeight, 0.f }),	center + rotation * (GeMaths::FVector3{ radius, +halfHeight, 0.f }), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ 0.f, -halfHeight, -radius }),	center + rotation * (GeMaths::FVector3{ 0.f, +halfHeight, -radius }), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ 0.f, -halfHeight, radius }),	center + rotation * (GeMaths::FVector3{ 0.f, +halfHeight, radius }), GeMaths::FVector3{ 0.f, 1.f, 0.f }, 1.f);
	}

	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, depthTestBackup);
	m_context.renderer->SetRasterizationLinesWidth(1.0f);
}

void GeEditor::Core::EditorRenderer::RenderLightBounds(GeCore::ECS::Components::CLight& p_light)
{
	bool depthTestBackup = m_context.renderer->GetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST);
	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, false);

	auto& data = p_light.GetData();

	GeMaths::FQuaternion rotation = data.GetTransform().GetWorldRotation();
	GeMaths::FVector3 center = data.GetTransform().GetWorldPosition();
	float radius = data.GetEffectRange();

	if (!std::isinf(radius))
	{
		for (float i = 0; i <= 360.0f; i += 10.0f)
		{
			m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), sin(i * (3.14f / 180.0f)), 0.f } *radius), center + rotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), sin((i + 10.0f) * (3.14f / 180.0f)), 0.f } *radius), DEBUG_BOUNDS_COLOR, 1.f);
			m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ 0.f, sin(i * (3.14f / 180.0f)), cos(i * (3.14f / 180.0f)) } *radius), center + rotation * (GeMaths::FVector3{ 0.f, sin((i + 10.0f) * (3.14f / 180.0f)), cos((i + 10.0f) * (3.14f / 180.0f)) } *radius), DEBUG_BOUNDS_COLOR, 1.f);
			m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), 0.f, sin(i * (3.14f / 180.0f)) } *radius), center + rotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), 0.f, sin((i + 10.0f) * (3.14f / 180.0f)) } *radius), DEBUG_BOUNDS_COLOR, 1.f);
		}
	}

	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, depthTestBackup);
}

void GeEditor::Core::EditorRenderer::RenderAmbientBoxVolume(GeCore::ECS::Components::CAmbientBoxLight & p_ambientBoxLight)
{
	bool depthTestBackup = m_context.renderer->GetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST);
	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, false);

	auto& data = p_ambientBoxLight.GetData();

	FMatrix4 model =
		FMatrix4::Translation(p_ambientBoxLight.owner.transform.GetWorldPosition()) *
		FMatrix4::Scaling({ data.constant * 2.f, data.linear * 2.f, data.quadratic * 2.f });

	GeMaths::FVector3 center = p_ambientBoxLight.owner.transform.GetWorldPosition();
	GeMaths::FVector3 size = { data.constant * 2.f, data.linear * 2.f, data.quadratic * 2.f };
	GeMaths::FVector3 actorScale = p_ambientBoxLight.owner.transform.GetWorldScale();
	GeMaths::FVector3 halfSize = size / 2.f;

	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, -halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ -halfSize.x, -halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ -halfSize.x, +halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, -halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ -halfSize.x, +halfSize.y, -halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, -halfSize.y, +halfSize.z }, center + GeMaths::FVector3{ -halfSize.x, +halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ +halfSize.x, -halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, -halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ +halfSize.x, halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, +halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ +halfSize.x, -halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, +halfSize.y, -halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ +halfSize.x, -halfSize.y, +halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, +halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, -halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, -halfSize.y, -halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, +halfSize.y, -halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, +halfSize.y, -halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, -halfSize.y, +halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, -halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);
	m_context.shapeDrawer->DrawLine(center + GeMaths::FVector3{ -halfSize.x, +halfSize.y, +halfSize.z }, center + GeMaths::FVector3{ +halfSize.x, +halfSize.y, +halfSize.z }, LIGHT_VOLUME_COLOR, 1.f);

	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, depthTestBackup);
}

void GeEditor::Core::EditorRenderer::RenderAmbientSphereVolume(GeCore::ECS::Components::CAmbientSphereLight & p_ambientSphereLight)
{
	bool depthTestBackup = m_context.renderer->GetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST);
	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, false);

	auto& data = p_ambientSphereLight.GetData();

	GeMaths::FQuaternion rotation = p_ambientSphereLight.owner.transform.GetWorldRotation();
	GeMaths::FVector3 center = p_ambientSphereLight.owner.transform.GetWorldPosition();
	float radius = data.constant;

	for (float i = 0; i <= 360.0f; i += 10.0f)
	{
		m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), sin(i * (3.14f / 180.0f)), 0.f } *radius), center + rotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), sin((i + 10.0f) * (3.14f / 180.0f)), 0.f } *radius), LIGHT_VOLUME_COLOR, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ 0.f, sin(i * (3.14f / 180.0f)), cos(i * (3.14f / 180.0f)) } *radius), center + rotation * (GeMaths::FVector3{ 0.f, sin((i + 10.0f) * (3.14f / 180.0f)), cos((i + 10.0f) * (3.14f / 180.0f)) } *radius), LIGHT_VOLUME_COLOR, 1.f);
		m_context.shapeDrawer->DrawLine(center + rotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), 0.f, sin(i * (3.14f / 180.0f)) } *radius), center + rotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), 0.f, sin((i + 10.0f) * (3.14f / 180.0f)) } *radius), LIGHT_VOLUME_COLOR, 1.f);
	}

	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, depthTestBackup);
}

void GeEditor::Core::EditorRenderer::RenderBoundingSpheres(GeCore::ECS::Components::CModelRenderer& p_modelRenderer)
{
	using namespace GeCore::ECS::Components;
	using namespace GePhysics::Entities;

	bool depthTestBackup = m_context.renderer->GetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST);
	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, false);

	/* Draw the sphere collider if any */
	if (auto model = p_modelRenderer.GetModel())
	{
		auto& actor = p_modelRenderer.owner;

		GeMaths::FVector3 actorScale = actor.transform.GetWorldScale();
		GeMaths::FQuaternion actorRotation = actor.transform.GetWorldRotation();
		GeMaths::FVector3 actorPosition = actor.transform.GetWorldPosition();

		const auto& modelBoundingsphere = 
			p_modelRenderer.GetFrustumBehaviour() == GeCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_CUSTOM ?
			p_modelRenderer.GetCustomBoundingSphere() :
			model->GetBoundingSphere();

		float radiusScale = std::max(std::max(std::max(actorScale.x, actorScale.y), actorScale.z), 0.0f);
		float scaledRadius = modelBoundingsphere.radius * radiusScale;
		auto sphereOffset = GeMaths::FQuaternion::RotatePoint(modelBoundingsphere.position, actorRotation) * radiusScale;

		GeMaths::FVector3 boundingSphereCenter = actorPosition + sphereOffset;

		for (float i = 0; i <= 360.0f; i += 10.0f)
		{
			m_context.shapeDrawer->DrawLine(boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), sin(i * (3.14f / 180.0f)), 0.f } *scaledRadius), boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), sin((i + 10.0f) * (3.14f / 180.0f)), 0.f } *scaledRadius), DEBUG_BOUNDS_COLOR, 1.f);
			m_context.shapeDrawer->DrawLine(boundingSphereCenter + actorRotation * (GeMaths::FVector3{ 0.f, sin(i * (3.14f / 180.0f)), cos(i * (3.14f / 180.0f)) } *scaledRadius), boundingSphereCenter + actorRotation * (GeMaths::FVector3{ 0.f, sin((i + 10.0f) * (3.14f / 180.0f)), cos((i + 10.0f) * (3.14f / 180.0f)) } *scaledRadius), DEBUG_BOUNDS_COLOR, 1.f);
			m_context.shapeDrawer->DrawLine(boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), 0.f, sin(i * (3.14f / 180.0f)) } *scaledRadius), boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), 0.f, sin((i + 10.0f) * (3.14f / 180.0f)) } *scaledRadius), DEBUG_BOUNDS_COLOR, 1.f);
		}

		if (p_modelRenderer.GetFrustumBehaviour() == GeCore::ECS::Components::CModelRenderer::EFrustumBehaviour::CULL_MESHES)
		{
			const auto& meshes = model->GetMeshes();

			if (meshes.size() > 1) // One mesh would result into the same bounding sphere for mesh and model
			{
				for (auto mesh : meshes)
				{
					auto& meshBoundingSphere = mesh->GetBoundingSphere();
					float scaledRadius = meshBoundingSphere.radius * radiusScale;
					auto sphereOffset = GeMaths::FQuaternion::RotatePoint(meshBoundingSphere.position, actorRotation) * radiusScale;

					GeMaths::FVector3 boundingSphereCenter = actorPosition + sphereOffset;

					for (float i = 0; i <= 360.0f; i += 10.0f)
					{
						m_context.shapeDrawer->DrawLine(boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), sin(i * (3.14f / 180.0f)), 0.f } *scaledRadius), boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), sin((i + 10.0f) * (3.14f / 180.0f)), 0.f } *scaledRadius), DEBUG_BOUNDS_COLOR, 1.f);
						m_context.shapeDrawer->DrawLine(boundingSphereCenter + actorRotation * (GeMaths::FVector3{ 0.f, sin(i * (3.14f / 180.0f)), cos(i * (3.14f / 180.0f)) } *scaledRadius), boundingSphereCenter + actorRotation * (GeMaths::FVector3{ 0.f, sin((i + 10.0f) * (3.14f / 180.0f)), cos((i + 10.0f) * (3.14f / 180.0f)) } *scaledRadius), DEBUG_BOUNDS_COLOR, 1.f);
						m_context.shapeDrawer->DrawLine(boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos(i * (3.14f / 180.0f)), 0.f, sin(i * (3.14f / 180.0f)) } *scaledRadius), boundingSphereCenter + actorRotation * (GeMaths::FVector3{ cos((i + 10.0f) * (3.14f / 180.0f)), 0.f, sin((i + 10.0f) * (3.14f / 180.0f)) } *scaledRadius), DEBUG_BOUNDS_COLOR, 1.f);
					}
				}
			}
		}
	}

	m_context.renderer->SetCapability(GeRendering::Settings::ERenderingCapability::DEPTH_TEST, depthTestBackup);
	m_context.renderer->SetRasterizationLinesWidth(1.0f);
}

void GeEditor::Core::EditorRenderer::RenderModelAsset(GeRendering::Resources::Model& p_model)
{
	FMatrix4 model = GeMaths::FMatrix4::Scaling({ 3.f, 3.f, 3.f });
	m_context.renderer->DrawModelWithSingleMaterial(p_model, m_defaultMaterial, &model);
}

void GeEditor::Core::EditorRenderer::RenderTextureAsset(GeRendering::Resources::Texture & p_texture)
{
	FMatrix4 model = FMatrix4::RotateOnAxisX(FMatrix4::Scaling({ 5.f, 5.f, 5.f }), 90.f * 0.0174f);

	m_textureMaterial.Set<Texture*>("u_DiffuseMap", &p_texture);
	m_context.renderer->DrawModelWithSingleMaterial(*m_context.editorResources->GetModel("Plane"), m_textureMaterial, &model);
}

void GeEditor::Core::EditorRenderer::RenderMaterialAsset(GeCore::Resources::Material & p_material)
{
	FMatrix4 model = GeMaths::FMatrix4::Scaling({ 3.f, 3.f, 3.f });
	m_context.renderer->DrawModelWithSingleMaterial(*m_context.editorResources->GetModel("Sphere"), p_material, &model, &m_emptyMaterial);
}

void GeEditor::Core::EditorRenderer::RenderGrid(const GeMaths::FVector3& p_viewPos, const GeMaths::FVector3& p_color)
{
    constexpr float gridSize = 5000.0f;

    FMatrix4 model = FMatrix4::Translation({ p_viewPos.x, 0.0f, p_viewPos.z }) * FMatrix4::Scaling({ gridSize * 2.0f, 1.f, gridSize * 2.0f });
	m_gridMaterial.Set("u_Color", p_color);
	m_context.renderer->DrawModelWithSingleMaterial(*m_context.editorResources->GetModel("Plane"), m_gridMaterial, &model);

    m_context.shapeDrawer->DrawLine(GeMaths::FVector3(-gridSize + p_viewPos.x, 0.0f, 0.0f), GeMaths::FVector3(gridSize + p_viewPos.x, 0.0f, 0.0f), GeMaths::FVector3(1.0f, 0.0f, 0.0f), 1.0f);
    m_context.shapeDrawer->DrawLine(GeMaths::FVector3(0.0f, -gridSize + p_viewPos.y, 0.0f), GeMaths::FVector3(0.0f, gridSize + p_viewPos.y, 0.0f), GeMaths::FVector3(0.0f, 1.0f, 0.0f), 1.0f);
    m_context.shapeDrawer->DrawLine(GeMaths::FVector3(0.0f, 0.0f, -gridSize + p_viewPos.z), GeMaths::FVector3(0.0f, 0.0f, gridSize + p_viewPos.z), GeMaths::FVector3(0.0f, 0.0f, 1.0f), 1.0f);
}

void GeEditor::Core::EditorRenderer::UpdateLights(GeCore::SceneSystem::Scene& p_scene)
{
	PROFILER_SPY("Light SSBO Update");
	auto lightMatrices = m_context.renderer->FindLightMatrices(p_scene);
	m_context.lightSSBO->SendBlocks<FMatrix4>(lightMatrices.data(), lightMatrices.size() * sizeof(FMatrix4));
}

void GeEditor::Core::EditorRenderer::UpdateLightsInFrustum(GeCore::SceneSystem::Scene& p_scene, const GeRendering::Data::Frustum& p_frustum)
{
	PROFILER_SPY("Light SSBO Update (Frustum culled)");
	auto lightMatrices = m_context.renderer->FindLightMatricesInFrustum(p_scene, p_frustum);
	m_context.lightSSBO->SendBlocks<FMatrix4>(lightMatrices.data(), lightMatrices.size() * sizeof(FMatrix4));
}
