#pragma once

#include <GePhysics/Entities/PhysicalObject.h>

#include "GeCore/ECS/Components/AComponent.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //任何物理对象的基类
	class CPhysicalObject : public AComponent
	{
	public:
		CPhysicalObject(ECS::Actor& p_owner);

    //给刚体加一个力
		void AddForce(const GeMaths::FVector3& p_force);

    //给刚体添加一个冲量
		void AddImpulse(const GeMaths::FVector3& p_impulse);

    //清除力量
		void ClearForces();

    //返回物理对象的质量
		float GetMass() const;

    //返回物理对象的碰撞检测模式
		GePhysics::Entities::PhysicalObject::ECollisionDetectionMode GetCollisionDetectionMode() const;

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
		GePhysics::Entities::PhysicalObject::EActivationState GetActivationState() const;

    //为物理对象定义一个新的质量
		void SetMass(float p_mass);

    //为物理对象定义了一种新的碰撞检测模式
		void SetCollisionDetectionMode(GePhysics::Entities::PhysicalObject::ECollisionDetectionMode p_mode);

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

    //定义物理对象是否应该是运动学的
		void SetKinematic(bool p_kinematic);

    //为物理对象定义新的激活状态
		void SetActivationState(GePhysics::Entities::PhysicalObject::EActivationState p_activationState);

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	protected:
		template <typename T> T& GetPhysicalObjectAs() const { return *static_cast<T*>(m_physicalObject.get()); }
		void Init();
		void BindListener();

	private:
		virtual void OnEnable() override;
		virtual void OnDisable() override;

	public:
		GeUtils::Eventing::Event<CPhysicalObject&> CollisionEnterEvent;
		GeUtils::Eventing::Event<CPhysicalObject&> CollisionStayEvent;
		GeUtils::Eventing::Event<CPhysicalObject&> CollisionExitEvent;

		GeUtils::Eventing::Event<CPhysicalObject&> TriggerEnterEvent;
		GeUtils::Eventing::Event<CPhysicalObject&> TriggerStayEvent;
		GeUtils::Eventing::Event<CPhysicalObject&> TriggerExitEvent;

	protected:
		std::unique_ptr<GePhysics::Entities::PhysicalObject> m_physicalObject;
	};
}
