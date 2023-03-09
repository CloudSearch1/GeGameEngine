#pragma once

#include <any>
#include <memory>

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include <GeMaths/FTransform.h>

#include <GeUtils/Eventing/Event.h>


#include "GePhysics/Settings/BodySettings.h"

namespace GePhysics::Core { class PhysicsEngine; }

namespace GePhysics::Entities
{
  //任何物理实体的基类
	class PhysicalObject
	{
	public:
		friend class GePhysics::Core::PhysicsEngine;

    //定义了一些物理对象可以拥有的碰撞检测模式
		enum class ECollisionDetectionMode
		{
			DISCRETE,
			CONTINUOUS
		};
    
    //定义了物理对象可以具有的一些激活状态
		enum class EActivationState
		{
			ACTIVE				    = 1,
			SLEEPING			    = 2,
			LOOKING_FOR_SLEEP	= 3,
			ALWAYS_ACTIVE		  = 4,
			ALWAYS_SLEEPING	  = 5
		};

    //PhysicalObject 构造函数（内部转换管理）
		PhysicalObject();

    //PhysicalObject 构造函数（外部转换管理）
		PhysicalObject(GeMaths::FTransform& p_transform);

    //PhysicalObject 析构函数（如果转换是内部管理的，则释放内存）
		~PhysicalObject();

    //给物理对象加一个力
		void AddForce(const GeMaths::FVector3& p_force);

    //给实物添加冲动
		void AddImpulse(const GeMaths::FVector3& p_impulse);

    //清除力量
		void ClearForces();

    //为实物添加标志
		void AddFlag(btCollisionObject::CollisionFlags p_flag);

    //从物理对象中添加一个标志
		void RemoveFlag(btCollisionObject::CollisionFlags p_flag);

    //返回物理对象的质量
		float GetMass() const;

    //返回物理对象的碰撞检测模式
		const ECollisionDetectionMode& GetCollisionDetectionMode() const;

    //返回物理对象的弹性
		float GetBounciness() const;

    //返回物理对象的摩擦力
		float GetFriction()	const;

    //返回物理对象的线速度
		GeMaths::FVector3 GetLinearVelocity() const;

    //返回物理对象的角度
		GeMaths::FVector3 GetAngularVelocity() const;

    //返回物理对象的线性因子
		GeMaths::FVector3 GetLinearFactor()	const;

    //返回物理对象的角度因子
		GeMaths::FVector3 GetAngularFactor() const;

    //如果物理对象是触发器，则返回 true
		bool IsTrigger() const;

    //如果物理对象是运动的则返回真
		bool IsKinematic() const;

    //返回当前激活状态
		EActivationState GetActivationState() const;

    //返回对物理对象变换的引用
		GeMaths::FTransform& GetTransform();

    //为物理对象定义一个新的质量
		void SetMass(float p_mass);

    //为物理对象定义了一种新的碰撞检测模式
		void SetCollisionDetectionMode(ECollisionDetectionMode p_mode);

    //为物理对象定义一个新的弹性
		void SetBounciness(float p_bounciness);

    //为物理对象定义新的摩擦力
		void SetFriction(float p_friction);

    //为物理对象定义一个新的线速度
		void SetLinearVelocity(const GeMaths::FVector3& p_linearVelocity);

    //为物理对象定义一个新的角速度
		void SetAngularVelocity(const GeMaths::FVector3& p_angularVelocity);

    //为物理对象定义一个新的线性因子
		void SetLinearFactor(const GeMaths::FVector3& p_linearFactor);

    //为物理对象定义一个新的角度因子
		void SetAngularFactor(const GeMaths::FVector3& p_angularFactor);

    //定义物理对象是否应该是触发器
		void SetTrigger(bool p_trigger);

    //定义物理对象是否应该是触发器
		void SetKinematic(bool p_kinematic);

    //为物理对象定义新的激活状态
		void SetActivationState(EActivationState p_activationState);

    //定义是否应启用物理对象
		void SetEnabled(bool p_enabled);

    //如果启用了物理对象，则返回 true
		bool IsEnabled() const;

    //返回与此物理对象实例关联的用户数据
		template <typename T> T		GetUserData() const		{ return std::any_cast<T>(m_userData); }

    //定义与此物理对象实例关联的用户数据
		template <typename T> void	SetUserData(T p_data)	{ m_userData = p_data; }

	protected:
		void Init();
		void RecreateBody();
		void ApplyInertia();
		virtual void SetLocalScaling(const GeMaths::FVector3& p_scaling) = 0;
		void Consider();
		void Unconsider();

	private:
    //内部的
		void CreateBody(const Settings::BodySettings& p_bodySettings);
		Settings::BodySettings DestroyBody();
		btVector3 CalculateInertia() const;

    //物理引擎需要
		btRigidBody& GetBody();
		void UpdateBtTransform();
		void UpdateFTransform();

	public:
		GeUtils::Eventing::Event<PhysicalObject&>			CollisionStartEvent;
		GeUtils::Eventing::Event<PhysicalObject&>			CollisionStayEvent;
		GeUtils::Eventing::Event<PhysicalObject&>			CollisionStopEvent;

		GeUtils::Eventing::Event<PhysicalObject&>			TriggerStartEvent;
		GeUtils::Eventing::Event<PhysicalObject&>			TriggerStayEvent;
		GeUtils::Eventing::Event<PhysicalObject&>			TriggerStopEvent;

	private:
		GeMaths::FTransform* const m_transform;
		const bool m_internalTransform;

		float  m_mass = 1.f;
		bool  m_kinematic = false;
		bool  m_trigger = false;
		bool  m_enabled = true;
		bool  m_considered = false;
		ECollisionDetectionMode m_collisionMode = ECollisionDetectionMode::DISCRETE;

		std::any m_userData;
		GeMaths::FVector3 m_previousScale = { 0.0f, 0.0f, 0.0f };
		static GeUtils::Eventing::Event<PhysicalObject&> CreatedEvent;
		static GeUtils::Eventing::Event<PhysicalObject&> DestroyedEvent;
		static GeUtils::Eventing::Event<btRigidBody&> ConsiderEvent;
		static GeUtils::Eventing::Event<btRigidBody&> UnconsiderEvent;

		std::unique_ptr<btMotionState> m_motion;
		std::unique_ptr<btRigidBody> m_body;

	protected:
		std::unique_ptr<btCollisionShape>	m_shape;
	};
}
