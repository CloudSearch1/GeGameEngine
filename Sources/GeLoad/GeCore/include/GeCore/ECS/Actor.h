#pragma once

#include <unordered_map>
#include <memory>

#include <GeUtils/Eventing/Event.h>

#include "GeCore/ECS/Components/AComponent.h"
#include "GeCore/ECS/Components/CTransform.h"
#include "GeCore/ECS/Components/Behaviour.h"
#include "GeCore/API/ISerializable.h"

namespace GeCore::ECS
{
  //Actor是ECS的主类，对应实体，由组件和行为（脚本）组成
	class Actor : public API::ISerializable
	{
	public:
		Actor(int64_t p_actorID, const std::string& p_name, const std::string& p_tag, bool& p_playing);

		virtual ~Actor() override;

    //返回动作的当前姓名
		const std::string& GetName() const;

    //返回actor的当前标签
		const std::string& GetTag() const;

    //为动作定义一个新名字
		void SetName(const std::string& p_name);

    //为动作定义一个新标签
		void SetTag(const std::string& p_tag);

    //启用或禁用actor
		void SetActive(bool p_active);

    //如果actor是活动的，则返回真，忽略他的父母（如果有的话）活动状态
		bool IsSelfActive() const;

    //如果actor和他的递归父母（如果有的话）是活跃的，则返回真
		bool IsActive() const;

    //为actor定义一个新的ID
		void SetID(int64_t p_id);

    //返回actorID
		int64_t GetID() const;

    //设置一个actor作为这个actor的父级
		void SetParent(Actor& p_parent);

    //脱离父级
		void DetachFromParent();

    //如果actor有父母，则返回真
		bool HasParent() const;

    //返回这个actor的父母（如果没有父母，则返回 nullptr）
		Actor* GetParent() const;

    //返回这个actor父级的ID
		int64_t GetParentID() const;

    //返回这个actor的孩子
		std::vector<Actor*>& GetChildren();

    //将 Actor 标记为“已销毁”。 一个“被摧毁”的actor将被场景本身从场景中移除
		void MarkAsDestroy();

    //如果 actor 未被标记为已销毁，则返回 true
		bool IsAlive() const;

    //定义actor是否在睡觉。
    //休眠的actor不会触发OnEnable、OnDisable、OnDestroyed等方法
		void SetSleeping(bool p_sleeping);

    //在场景开始时或在播放模式期间首次启用actor时调用
		void OnAwake();

    //在场景开始时或在播放模式期间首次启用actor时调用
		void OnStart();

    //当 actor 被启用（SetActive 设置为 true）或场景开始时调用，如果 actor 是分层活动的。
		void OnEnable();

    //当 actor 分层活动状态更改为 false 或在分层活动时被销毁时调用
		void OnDisable();

    //如果 actor 被唤醒，则在 actor 被销毁时调用
		void OnDestroy();

    //调用每一帧
		void OnUpdate(float p_deltaTime);

    //调用每个物理框架
		void OnFixedUpdate(float p_deltaTime);

    //在 OnUpdate 之后调用每一帧
		void OnLateUpdate(float p_deltaTime);

    //当actor与另一个物理对象发生碰撞时调用
		void OnCollisionEnter(Components::CPhysicalObject& p_otherObject);

    //当actor与另一个物理对象发生碰撞时调用
		void OnCollisionStay(Components::CPhysicalObject& p_otherObject);

    //当actor退出与另一个物理对象的碰撞时调用
		void OnCollisionExit(Components::CPhysicalObject& p_otherObject);

    //当actor进入触发器与另一个物理对象时调用
		void OnTriggerEnter(Components::CPhysicalObject& p_otherObject);

    //当actor与另一个物理对象触发时调用
		void OnTriggerStay(Components::CPhysicalObject& p_otherObject);

    //当actor退出触发器与另一个物理对象时调用
		void OnTriggerExit(Components::CPhysicalObject& p_otherObject);

    //向 actor 添加一个组件（如果已经存在则返回该组件）
		template<typename T, typename ... Args>
		T& AddComponent(Args&&... p_args);

    //删除给定的组件
		template<typename T>
		bool RemoveComponent();

    //通过引用给定实例移除组件
		bool RemoveComponent(GeCore::ECS::Components::AComponent& p_component);

    //尝试获取给定的组件（失败时返回 nullptr）
		template<typename T>
		T* GetComponent();

    //返回对分量向量的引用
		std::vector<std::shared_ptr<Components::AComponent>>& GetComponents();

    //给actor添加一个行为
		Components::Behaviour& AddBehaviour(const std::string& p_name);

    //通过引用给定实例删除行为
		bool RemoveBehaviour(Components::Behaviour& p_behaviour);

    //通过引用他的名字来删除一个行为
		bool RemoveBehaviour(const std::string& p_name);

    //尝试获得给定的行为（失败时返回 nullptr）
		Components::Behaviour* GetBehaviour(const std::string& p_name);

    //返回对行为向量的引用
		std::unordered_map<std::string, Components::Behaviour>& GetBehaviours();

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_actorsRoot) override;

	private:
    //禁止复制构造函数
		Actor(const Actor& p_actor) = delete;

		void RecursiveActiveUpdate();
		void RecursiveWasActiveUpdate();

	public:
    //actor 实例上发生动作时触发的一些事件
		GeUtils::Eventing::Event<Components::AComponent&>	ComponentAddedEvent;
		GeUtils::Eventing::Event<Components::AComponent&>	ComponentRemovedEvent;
		GeUtils::Eventing::Event<Components::Behaviour&>	BehaviourAddedEvent;
		GeUtils::Eventing::Event<Components::Behaviour&>	BehaviourRemovedEvent;

    //一些当动作发生在任何 actor 上时触发的事件
		static GeUtils::Eventing::Event<Actor&> DestroyedEvent;
		static GeUtils::Eventing::Event<Actor&> CreatedEvent;
		static GeUtils::Eventing::Event<Actor&, Actor&> AttachEvent;
		static GeUtils::Eventing::Event<Actor&> DettachEvent;

	private:
		std::string m_name;
		std::string m_tag;
		bool m_active = true;
		bool& m_playing;

		int64_t	m_actorID;
		bool	m_destroyed = false;
		bool	m_sleeping = true;
		bool	m_awaked = false;
		bool	m_started = false;
		bool	m_wasActive = false;

		int64_t m_parentID = 0;
		Actor* m_parent = nullptr;
		std::vector<Actor*> m_children;

		std::vector<std::shared_ptr<Components::AComponent>> m_components;
		std::unordered_map<std::string, Components::Behaviour> m_behaviours;

	public:
		Components::CTransform& transform;
	};
}

#include "GeCore/ECS/Actor.inl"
