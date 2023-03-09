#pragma once


#include "GeCore/ECS/Actor.h"
#include "GeCore/API/ISerializable.h"

#include "GeCore/ECS/Components/CModelRenderer.h"
#include "GeCore/ECS/Components/CCamera.h"
#include "GeCore/ECS/Components/CLight.h"

namespace GeCore::SceneSystem
{
  //这个场景是一组actor
	class Scene : public API::ISerializable
	{
	public:
    //包含一组已排序的组件向量。它允许快速操作组件，而无需解析整个场景
		struct FastAccessComponents
		{
			std::vector<ECS::Components::CModelRenderer*>	modelRenderers;
			std::vector<ECS::Components::CCamera*>			cameras;
			std::vector<ECS::Components::CLight*>			lights;
		};

		Scene();

		~Scene();

    //播放场景
		void Play();

    //如果场景正在播放则返回true
		bool IsPlaying() const;

    //更新每个actor
		void Update(float p_deltaTime);

    //每秒钟更新每个actor60帧
		void FixedUpdate(float p_deltaTime);

    //最近更新每个actor
		void LateUpdate(float p_deltaTime);

    //创建一个具有默认名称的参与者，并返回对它的引用。
		ECS::Actor& CreateActor();

    //创建一个具有给定名称的参与者，并返回对它的引用。
		ECS::Actor& CreateActor(const std::string& p_name, const std::string& p_tag = "");

    //摧毁和actor，成功时返回true
		bool DestroyActor(ECS::Actor& p_target);

    //通过移除被摧毁标记的actor来收集垃圾
		void CollectGarbages();

    //返回第一个给定名称的参与者，失败时返回nullptr
		ECS::Actor* FindActorByName(const std::string& p_name);

    //返回由给定标签标识的第一个参与者，失败时返回nullptr
		ECS::Actor* FindActorByTag(const std::string& p_tag);

    //返回指定ID的参与者(失败时返回0)
		ECS::Actor* FindActorByID(int64_t p_id);

    //返回每个给定名称标识的参与者
		std::vector<std::reference_wrapper<ECS::Actor>> FindActorsByName(const std::string& p_name);

    //返回由给定标签标识的每个actor
		std::vector<std::reference_wrapper<ECS::Actor>> FindActorsByTag(const std::string& p_tag);

    //每次在场景的参与者上添加组件时调用回调方法
		void OnComponentAdded(ECS::Components::AComponent& p_compononent);

    //每次在场景的参与者上删除组件时调用回调方法
		void OnComponentRemoved(ECS::Components::AComponent& p_compononent);

    //在参与者地图上返回一个引用
		std::vector<GeCore::ECS::Actor*>& GetActors();

    //返回快速访问组件的数据结构
		const FastAccessComponents& GetFastAccessComponents() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_root) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_root) override;

	private:
		int64_t m_availableID = 1;
		bool m_isPlaying = false;
		std::vector<ECS::Actor*> m_actors;

		FastAccessComponents m_fastAccessComponents;
	};
}
