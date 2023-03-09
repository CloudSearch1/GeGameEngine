#pragma once

#include <GeRendering/LowRenderer/Camera.h>

#include <GeCore/ECS/Actor.h>
#include <GeCore/SceneSystem/SceneManager.h>
#include <GeCore/ECS/Components/CModelRenderer.h>
#include <GeCore/Resources/Material.h>
#include <GeCore/ECS/Components/CAmbientBoxLight.h>
#include <GeCore/ECS/Components/CAmbientSphereLight.h>

#include "GeEditor/Core/Context.h"

namespace GeEditor::Core { enum class EGizmoOperation; }
namespace GeEditor::Panels { class AView; }

namespace GeEditor::Core
{
	class EditorRenderer
	{
	public:
		EditorRenderer(Context& p_context);

		void InitMaterials();

		void PreparePickingMaterial(GeCore::ECS::Actor& p_actor, GeCore::Resources::Material& p_material);

		GeMaths::FMatrix4 CalculateCameraModelMatrix(GeCore::ECS::Actor& p_actor);

		void RenderScene(const GeMaths::FVector3& p_cameraPosition, const GeRendering::LowRenderer::Camera& p_camera, const GeRendering::Data::Frustum* p_customFrustum = nullptr);

		void RenderSceneForActorPicking();

		void RenderUI();

		void RenderCameras();

		void RenderLights();

		void RenderGizmo(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation, GeEditor::Core::EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis = -1);

		void RenderModelToStencil(const GeMaths::FMatrix4& p_worldMatrix, GeRendering::Resources::Model& p_model);

		void RenderModelOutline(const GeMaths::FMatrix4& p_worldMatrix, GeRendering::Resources::Model& p_model, float p_width);

		void RenderActorOutlinePass(GeCore::ECS::Actor& p_actor, bool p_toStencil, bool p_isSelected = false);

    void RenderCameraPerspectiveFrustum(std::pair<uint16_t, uint16_t>& p_size, GeCore::ECS::Components::CCamera& p_camera);

    void RenderCameraOrthographicFrustum(std::pair<uint16_t, uint16_t>& p_size, GeCore::ECS::Components::CCamera& p_camera);

		void RenderCameraFrustum(GeCore::ECS::Components::CCamera& p_camera);

		void RenderActorCollider(GeCore::ECS::Actor& p_actor);

		void RenderLightBounds(GeCore::ECS::Components::CLight& p_light);

		void RenderAmbientBoxVolume(GeCore::ECS::Components::CAmbientBoxLight& p_ambientBoxLight);

		void RenderAmbientSphereVolume(GeCore::ECS::Components::CAmbientSphereLight& p_ambientSphereLight);

		void RenderBoundingSpheres(GeCore::ECS::Components::CModelRenderer& p_modelRenderer);

		void RenderModelAsset(GeRendering::Resources::Model& p_model);

		void RenderTextureAsset(GeRendering::Resources::Texture& p_texture);

		void RenderMaterialAsset(GeCore::Resources::Material& p_material);

		void RenderGrid(const GeMaths::FVector3& p_viewPos, const GeMaths::FVector3& p_color);

		void UpdateLights(GeCore::SceneSystem::Scene& p_scene);

		void UpdateLightsInFrustum(GeCore::SceneSystem::Scene& p_scene, const GeRendering::Data::Frustum& p_frustum);

	private:
		Context& m_context;

		GeCore::Resources::Material m_gridMaterial;
		GeCore::Resources::Material m_stencilFillMaterial;
		GeCore::Resources::Material m_textureMaterial;
		GeCore::Resources::Material m_outlineMaterial;
		GeCore::Resources::Material m_emptyMaterial;
		GeCore::Resources::Material m_defaultMaterial;
		GeCore::Resources::Material m_cameraMaterial;
		GeCore::Resources::Material m_lightMaterial;
		GeCore::Resources::Material m_gizmoArrowMaterial;
		GeCore::Resources::Material m_gizmoBallMaterial;
		GeCore::Resources::Material m_gizmoPickingMaterial;
		GeCore::Resources::Material m_actorPickingMaterial;
	};
}
