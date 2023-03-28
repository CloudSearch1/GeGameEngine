#pragma once

#include <map>

#include <GeRendering/Core/Renderer.h>
#include <GeRendering/Resources/Mesh.h>
#include <GeRendering/Data/Frustum.h>


#include "GeCore/Resources/Material.h"
#include "GeCore/ECS/Actor.h"
#include "GeCore/ECS/Components/CCamera.h"
#include "GeCore/SceneSystem/Scene.h"

namespace GeCore::ECS
{
  //能够渲染与 ECS 链接的东西的渲染器
	class Renderer : public GeRendering::Core::Renderer
	{
	public:
		using Drawable				= std::tuple<GeMaths::FMatrix4, GeRendering::Resources::Mesh*, GeCore::Resources::Material*, GeMaths::FMatrix4>;
		using OpaqueDrawables		= std::multimap<float, Drawable, std::less<float>>;
		using TransparentDrawables	= std::multimap<float, Drawable, std::greater<float>>;

		Renderer(GeRendering::Context::Driver& p_driver);

		~Renderer();

    //解析一个场景找到主摄像头
		GeCore::ECS::Components::CCamera* FindMainCamera(const GeCore::SceneSystem::Scene& p_scene);

    //用灯光信息填充给定的 FMatrix4 向量
		std::vector<GeMaths::FMatrix4> FindLightMatrices(const GeCore::SceneSystem::Scene& p_scene);

    //用视锥体内的灯光信息填充给定的 FMatrix4 向量
		std::vector<GeMaths::FMatrix4> FindLightMatricesInFrustum(const GeCore::SceneSystem::Scene& p_scene, const GeRendering::Data::Frustum& p_frustum);

    //如果在actor身上找不到材料，则使用给定的默认材料（可选）绘制给定的场景
		void RenderScene
		(
			GeCore::SceneSystem::Scene& p_scene,
			const GeMaths::FVector3& p_cameraPosition,
			const GeRendering::LowRenderer::Camera& p_camera,
			const GeRendering::Data::Frustum* p_customFrustum = nullptr,
			GeCore::Resources::Material* p_defaultMaterial = nullptr
		);

    //通过视锥体剔除从场景中返回不透明和透明的可绘制对象
		std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortFrustumCulledDrawables
		(
			const GeCore::SceneSystem::Scene& p_scene,
			const GeMaths::FVector3& p_cameraPosition,
			const GeRendering::Data::Frustum& p_frustum,
			GeCore::Resources::Material* p_defaultMaterial
		);

    //从场景中返回不透明和透明的可绘制对象
		std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortDrawables
		(
			const GeCore::SceneSystem::Scene& p_scene,
			const GeMaths::FVector3& p_cameraPosition,
			GeCore::Resources::Material* p_defaultMaterial
		);

    //绘制一个Drawable实例
		void DrawDrawable(const Drawable& p_toDraw);

    //使用给定的材质绘制模型（材质将应用于模型的每个子网格）
		void DrawModelWithSingleMaterial(GeRendering::Resources::Model& p_model, GeCore::Resources::Material& p_material, GeMaths::FMatrix4 const* p_modelMatrix, GeCore::Resources::Material* p_defaultMaterial = nullptr);

    //使用给定的材料绘制模型
		void DrawModelWithMaterials(GeRendering::Resources::Model& p_model, std::vector<GeCore::Resources::Material*> p_materials, GeMaths::FMatrix4 const* p_modelMatrix, GeCore::Resources::Material* p_defaultMaterial = nullptr);

    //尝试使用给定的材质绘制网格（如果材质没有附加着色器则失败）
		void DrawMesh(GeRendering::Resources::Mesh& p_mesh, GeCore::Resources::Material& p_material, GeMaths::FMatrix4 const* p_modelMatrix);

    //将给定函数注册为模型矩阵发送方
		void RegisterModelMatrixSender(std::function<void(GeMaths::FMatrix4)> p_modelMatrixSender);

    //将给定函数注册为用户矩阵发送者
		void RegisterUserMatrixSender(std::function<void(GeMaths::FMatrix4)> p_userMatrixSender);

	private:
		std::function<void(GeMaths::FMatrix4)> m_modelMatrixSender;
		std::function<void(GeMaths::FMatrix4)> m_userMatrixSender;
		GeRendering::Resources::Texture* m_emptyTexture = nullptr;
	};
}
