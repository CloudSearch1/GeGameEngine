#include <GeAnalytics/Profiling/ProfilerSpy.h>

#include <GeRendering/Resources/Loaders/TextureLoader.h>
#include <GeRendering/Data/Frustum.h>

#include "GeCore/ECS/Renderer.h"
#include "GeCore/ECS/Components/CModelRenderer.h"
#include "GeCore/ECS/Components/CMaterialRenderer.h"

GeCore::ECS::Renderer::Renderer(GeRendering::Context::Driver& p_driver) :
	GeRendering::Core::Renderer(p_driver),
	m_emptyTexture(GeRendering::Resources::Loaders::TextureLoader::CreateColor
	(
		(255 << 24) | (255 << 16) | (255 << 8) | 255,
		GeRendering::Settings::ETextureFilteringMode::NEAREST,
		GeRendering::Settings::ETextureFilteringMode::NEAREST,
		false
	))
{
}

GeCore::ECS::Renderer::~Renderer()
{
	GeRendering::Resources::Loaders::TextureLoader::Destroy(m_emptyTexture);
}

GeCore::ECS::Components::CCamera* GeCore::ECS::Renderer::FindMainCamera(const GeCore::SceneSystem::Scene& p_scene)
{
	for (GeCore::ECS::Components::CCamera* camera : p_scene.GetFastAccessComponents().cameras)
		if (camera->owner.IsActive())
			return camera;

	return nullptr;
}

std::vector<GeMaths::FMatrix4> GeCore::ECS::Renderer::FindLightMatrices(const GeCore::SceneSystem::Scene& p_scene)
{
	std::vector<GeMaths::FMatrix4> result;

	const auto& facs = p_scene.GetFastAccessComponents();

	for (auto light : facs.lights)
	{
		if (light->owner.IsActive())
		{
			result.push_back(light->GetData().GenerateMatrix());
		}
	}

	return result;
}



std::vector<GeMaths::FMatrix4> GeCore::ECS::Renderer::FindLightMatricesInFrustum(const GeCore::SceneSystem::Scene& p_scene, const GeRendering::Data::Frustum& p_frustum)
{
	std::vector<GeMaths::FMatrix4> result;

	const auto& facs = p_scene.GetFastAccessComponents();

	for (auto light : facs.lights)
	{
		if (light->owner.IsActive())
		{
			const auto& lightData = light->GetData();
			const auto& position = lightData.GetTransform().GetWorldPosition();
			auto effectRange = lightData.GetEffectRange();

			if (std::isinf(effectRange) || p_frustum.SphereInFrustum(position.x, position.y, position.z, lightData.GetEffectRange()))
			{
				result.push_back(lightData.GenerateMatrix());
			}
		}
	}

	return result;
}

void GeCore::ECS::Renderer::RenderScene
(
	GeCore::SceneSystem::Scene& p_scene,
	const GeMaths::FVector3& p_cameraPosition,
	const GeRendering::LowRenderer::Camera& p_camera,
	const GeRendering::Data::Frustum* p_customFrustum,
	GeCore::Resources::Material* p_defaultMaterial
)
{
	OpaqueDrawables	opaqueMeshes;
	TransparentDrawables transparentMeshes;

	if (p_camera.HasFrustumGeometryCulling())
	{
		const auto& frustum = p_customFrustum ? *p_customFrustum : p_camera.GetFrustum();
		std::tie(opaqueMeshes, transparentMeshes) = FindAndSortFrustumCulledDrawables(p_scene, p_cameraPosition, frustum, p_defaultMaterial);
	}
	else
	{
		std::tie(opaqueMeshes, transparentMeshes) = FindAndSortDrawables(p_scene, p_cameraPosition, p_defaultMaterial);
	}

	for (const auto& [distance, drawable] : opaqueMeshes)
		DrawDrawable(drawable);

	for (const auto& [distance, drawable] : transparentMeshes)
		DrawDrawable(drawable);
}

void FindAndSortDrawables
(
	GeCore::ECS::Renderer::OpaqueDrawables& p_opaques,
	GeCore::ECS::Renderer::TransparentDrawables& p_transparents,
	const GeCore::SceneSystem::Scene& p_scene,
	const GeMaths::FVector3& p_cameraPosition,
	GeCore::Resources::Material* p_defaultMaterial
)
{
	for (GeCore::ECS::Components::CModelRenderer* modelRenderer : p_scene.GetFastAccessComponents().modelRenderers)
	{
		if (modelRenderer->owner.IsActive())
		{
			if (auto model = modelRenderer->GetModel())
			{
				float distanceToActor = GeMaths::FVector3::Distance(modelRenderer->owner.transform.GetWorldPosition(), p_cameraPosition);

				if (auto materialRenderer = modelRenderer->owner.GetComponent<GeCore::ECS::Components::CMaterialRenderer>())
				{
					const auto& transform = modelRenderer->owner.transform.GetFTransform();

					const GeCore::ECS::Components::CMaterialRenderer::MaterialList& materials = materialRenderer->GetMaterials();

					for (auto mesh : model->GetMeshes())
					{
						GeCore::Resources::Material* material = nullptr;

						if (mesh->GetMaterialIndex() < MAX_MATERIAL_COUNT)
						{
							material = materials.at(mesh->GetMaterialIndex());
							if (!material || !material->GetShader())
								material = p_defaultMaterial;
						}

						if (material)
						{
							GeCore::ECS::Renderer::Drawable element = { transform.GetWorldMatrix(), mesh, material, materialRenderer->GetUserMatrix() };

							if (material->IsBlendable())
								p_transparents.emplace(distanceToActor, element);
							else
								p_opaques.emplace(distanceToActor, element);
						}
					}
				}
			}
		}
	}
}

std::pair<GeCore::ECS::Renderer::OpaqueDrawables, GeCore::ECS::Renderer::TransparentDrawables> GeCore::ECS::Renderer::FindAndSortFrustumCulledDrawables
(
	const GeCore::SceneSystem::Scene& p_scene,
	const GeMaths::FVector3& p_cameraPosition,
	const GeRendering::Data::Frustum& p_frustum,
	GeCore::Resources::Material* p_defaultMaterial
)
{
	using namespace GeCore::ECS::Components;

	GeCore::ECS::Renderer::OpaqueDrawables opaqueDrawables;
	GeCore::ECS::Renderer::TransparentDrawables transparentDrawables;

	for (CModelRenderer* modelRenderer : p_scene.GetFastAccessComponents().modelRenderers)
	{
		auto& owner = modelRenderer->owner;

		if (owner.IsActive())
		{
			if (auto model = modelRenderer->GetModel())
			{
				if (auto materialRenderer = modelRenderer->owner.GetComponent<CMaterialRenderer>())
				{
					auto& transform = owner.transform.GetFTransform();

					GeRendering::Settings::ECullingOptions cullingOptions = GeRendering::Settings::ECullingOptions::NONE;

					if (modelRenderer->GetFrustumBehaviour() != CModelRenderer::EFrustumBehaviour::DISABLED)
					{
						cullingOptions |= GeRendering::Settings::ECullingOptions::FRUSTUM_PER_MODEL;
					}

					if (modelRenderer->GetFrustumBehaviour() == CModelRenderer::EFrustumBehaviour::CULL_MESHES)
					{
						cullingOptions |= GeRendering::Settings::ECullingOptions::FRUSTUM_PER_MESH;
					}

					const auto& modelBoundingSphere = modelRenderer->GetFrustumBehaviour() == CModelRenderer::EFrustumBehaviour::CULL_CUSTOM ? modelRenderer->GetCustomBoundingSphere() : model->GetBoundingSphere();

					std::vector<std::reference_wrapper<GeRendering::Resources::Mesh>> meshes;

					{
						PROFILER_SPY("Frustum Culling");
						meshes = GetMeshesInFrustum(*model, modelBoundingSphere, transform, p_frustum, cullingOptions);
					}

					if (!meshes.empty())
					{
						float distanceToActor = GeMaths::FVector3::Distance(transform.GetWorldPosition(), p_cameraPosition);
						const GeCore::ECS::Components::CMaterialRenderer::MaterialList& materials = materialRenderer->GetMaterials();

						for (const auto& mesh : meshes)
						{
							GeCore::Resources::Material* material = nullptr;

							if (mesh.get().GetMaterialIndex() < MAX_MATERIAL_COUNT)
							{
								material = materials.at(mesh.get().GetMaterialIndex());
								if (!material || !material->GetShader())
									material = p_defaultMaterial;
							}

							if (material)
							{
								GeCore::ECS::Renderer::Drawable element = { transform.GetWorldMatrix(), &mesh.get(), material, materialRenderer->GetUserMatrix() };

								if (material->IsBlendable())
									transparentDrawables.emplace(distanceToActor, element);
								else
									opaqueDrawables.emplace(distanceToActor, element);
							}
						}
					}
				}
			}
		}
	}

	return { opaqueDrawables, transparentDrawables };
}

std::pair<GeCore::ECS::Renderer::OpaqueDrawables, GeCore::ECS::Renderer::TransparentDrawables> GeCore::ECS::Renderer::FindAndSortDrawables
(
	const GeCore::SceneSystem::Scene& p_scene,
	const GeMaths::FVector3& p_cameraPosition,
	GeCore::Resources::Material* p_defaultMaterial
)
{
	GeCore::ECS::Renderer::OpaqueDrawables opaqueDrawables;
	GeCore::ECS::Renderer::TransparentDrawables transparentDrawables;

	for (GeCore::ECS::Components::CModelRenderer* modelRenderer : p_scene.GetFastAccessComponents().modelRenderers)
	{
		if (modelRenderer->owner.IsActive())
		{
			if (auto model = modelRenderer->GetModel())
			{
				float distanceToActor = GeMaths::FVector3::Distance(modelRenderer->owner.transform.GetWorldPosition(), p_cameraPosition);

				if (auto materialRenderer = modelRenderer->owner.GetComponent<GeCore::ECS::Components::CMaterialRenderer>())
				{
					const auto& transform = modelRenderer->owner.transform.GetFTransform();

					const GeCore::ECS::Components::CMaterialRenderer::MaterialList& materials = materialRenderer->GetMaterials();

					for (auto mesh : model->GetMeshes())
					{
						GeCore::Resources::Material* material = nullptr;

						if (mesh->GetMaterialIndex() < MAX_MATERIAL_COUNT)
						{
							material = materials.at(mesh->GetMaterialIndex());
							if (!material || !material->GetShader())
								material = p_defaultMaterial;
						}

						if (material)
						{
							GeCore::ECS::Renderer::Drawable element = { transform.GetWorldMatrix(), mesh, material, materialRenderer->GetUserMatrix() };

							if (material->IsBlendable())
								transparentDrawables.emplace(distanceToActor, element);
							else
								opaqueDrawables.emplace(distanceToActor, element);
						}
					}
				}
			}
		}
	}

	return { opaqueDrawables, transparentDrawables };
}

void GeCore::ECS::Renderer::DrawDrawable(const Drawable& p_toDraw)
{
	m_userMatrixSender(std::get<3>(p_toDraw));
	DrawMesh(*std::get<1>(p_toDraw), *std::get<2>(p_toDraw), &std::get<0>(p_toDraw));
}

void GeCore::ECS::Renderer::DrawModelWithSingleMaterial(GeRendering::Resources::Model& p_model, GeCore::Resources::Material& p_material, GeMaths::FMatrix4 const* p_modelMatrix, GeCore::Resources::Material* p_defaultMaterial)
{
	if (p_modelMatrix)
		m_modelMatrixSender(*p_modelMatrix);

	for (auto mesh : p_model.GetMeshes())
	{
		GeCore::Resources::Material* material = p_material.GetShader() ? &p_material : p_defaultMaterial;

		if (material)
			DrawMesh(*mesh, *material, nullptr);
	}
}

void GeCore::ECS::Renderer::DrawModelWithMaterials(GeRendering::Resources::Model& p_model, std::vector<GeCore::Resources::Material*> p_materials, GeMaths::FMatrix4 const* p_modelMatrix, GeCore::Resources::Material* p_defaultMaterial)
{
	if (p_modelMatrix)
		m_modelMatrixSender(*p_modelMatrix);

	for (auto mesh : p_model.GetMeshes())
	{
		GeCore::Resources::Material* material = p_materials.size() > mesh->GetMaterialIndex() ? p_materials[mesh->GetMaterialIndex()] : p_defaultMaterial;
		if (material)
			DrawMesh(*mesh, *material, nullptr);
	}
}

void GeCore::ECS::Renderer::DrawMesh(GeRendering::Resources::Mesh& p_mesh, GeCore::Resources::Material& p_material, GeMaths::FMatrix4 const* p_modelMatrix)
{
	using namespace GeRendering::Settings;

	if (p_material.HasShader() && p_material.GetGPUInstances() > 0)
	{
		if (p_modelMatrix)
			m_modelMatrixSender(*p_modelMatrix);

		uint8_t stateMask = p_material.GenerateStateMask();
		ApplyStateMask(stateMask);
		
		p_material.Bind(m_emptyTexture);
		Draw(p_mesh, GeRendering::Settings::EPrimitiveMode::TRIANGLES, p_material.GetGPUInstances());
		p_material.UnBind();
	}
}

void GeCore::ECS::Renderer::RegisterModelMatrixSender(std::function<void(GeMaths::FMatrix4)> p_modelMatrixSender)
{
	m_modelMatrixSender = p_modelMatrixSender;
}

void GeCore::ECS::Renderer::RegisterUserMatrixSender(std::function<void(GeMaths::FMatrix4)> p_userMatrixSender)
{
	m_userMatrixSender = p_userMatrixSender;
}
