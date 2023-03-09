#pragma once

#include "GeCore/API/IInspectorItem.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
	class CPhysicalObject;

  //AComponent 是任何组件的基类。
	class AComponent : public API::IInspectorItem
	{
	public:
		AComponent(ECS::Actor& p_owner);

		virtual ~AComponent();

    //当场景在 OnStart 之前开始时调用
		virtual void OnAwake() {}

    // Called when the scene start right after OnAwake
		virtual void OnStart() {}

		//在启用组件时调用（所有者 SetActive 设置为 true）并且在场景中的 OnAwake() 启动后调用
		virtual void OnEnable() {}

		//当组件被禁用时调用（所有者 SetActive 设置为 false），当组件被销毁时在 OnDestroy() 之前调用
		virtual void OnDisable() {}

		//当组件被销毁时调用
		virtual void OnDestroy() {}

		//调用每一帧
		virtual void OnUpdate(float p_deltaTime) {}

		//调用每个物理框架
		virtual void OnFixedUpdate(float p_deltaTime) {}

		//在 OnUpdate 之后调用每一帧
		virtual void OnLateUpdate(float p_deltaTime) {}

		//当此组件的所有者与另一个物理对象发生碰撞时调用
		virtual void OnCollisionEnter(Components::CPhysicalObject& p_otherObject) {}

		//当此组件的所有者与另一个物理对象发生碰撞时调用
		virtual void OnCollisionStay(Components::CPhysicalObject& p_otherObject) {}

		//当此组件的所有者退出与另一个物理对象的碰撞时调用
		virtual void OnCollisionExit(Components::CPhysicalObject& p_otherObject) {}

		//当此组件的所有者使用另一个物理对象进入触发器时调用
		virtual void OnTriggerEnter(Components::CPhysicalObject& p_otherObject) {}

		//当此组件的所有者与另一个物理对象处于触发状态时调用
		virtual void OnTriggerStay(Components::CPhysicalObject& p_otherObject) {}

		//当此组件的所有者使用另一个物理对象退出触发器时调用
		virtual void OnTriggerExit(Components::CPhysicalObject& p_otherObject) {}

		//返回组件的名称
		virtual std::string GetName() = 0;

	public:
		ECS::Actor& owner;
	};
}
