#pragma once

#include <sol.hpp>

#include "GeCore/ECS/Components/CPhysicalObject.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //ABehaviour 是任何行为的基类。
  class Behaviour : public AComponent
  {
  public:
    Behaviour(ECS::Actor& p_owner, const std::string& p_name);
    ~Behaviour();

    //返回组件的名称
    virtual std::string GetName() override;

    //注册行为到lua
    bool RegisterToLuaContext(sol::state& p_luaState, const std::string& p_scriptFolder);

    //注册行为到lua
    void UnregisterFromLuaContext();

    //为此行为调用一个 lua 函数
    template<typename... Args>
    void LuaCall(const std::string& p_functionName, Args&&... p_args);

    //返回附加到此行为的 lua 表
    sol::table& GetTable();

    //当场景在 OnStart 之前开始时调用
    virtual void OnAwake() override;

    //当场景在 OnAwake 之后立即开始时调用
    virtual void OnStart() override;

    //启用行为时调用（所有者 SetActive 设置为 true）
    virtual void OnEnable() override;

    //当行为被禁用时调用（所有者 SetActive 设置为 false）
    virtual void OnDisable() override;

    //当行为被破坏时调用
    virtual void OnDestroy() override;

    //调用每一帧
    virtual void OnUpdate(float p_deltaTime) override;

    //调用每个物理框架
    virtual void OnFixedUpdate(float p_deltaTime) override;

    //在 OnUpdate 之后调用每一帧
    virtual void OnLateUpdate(float p_deltaTime) override;

    //当此组件的所有者与另一个物理对象发生碰撞时调用
    virtual void OnCollisionEnter(Components::CPhysicalObject& p_otherObject) override;

    //当此组件的所有者与另一个物理对象发生碰撞时调用
    virtual void OnCollisionStay(Components::CPhysicalObject& p_otherObject) override;

    //当此组件的所有者退出与另一个物理对象的碰撞时调用
    virtual void OnCollisionExit(Components::CPhysicalObject& p_otherObject) override;

    //当此组件的所有者使用另一个物理对象进入触发器时调用
    virtual void OnTriggerEnter(Components::CPhysicalObject& p_otherObject) override;

    //当此组件的所有者与另一个物理对象处于触发状态时调用
    virtual void OnTriggerStay(Components::CPhysicalObject& p_otherObject) override;

    //当此组件的所有者退出与另一个物理对象的触发器时调用
    virtual void OnTriggerExit(Components::CPhysicalObject& p_otherObject) override;

    //序列化行为
    virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //反序列化行为
    virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义应该如何在检查器中绘制行为
    virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

  public:
    static GeUtils::Eventing::Event<Behaviour*> CreatedEvent;
    static GeUtils::Eventing::Event<Behaviour*> DestroyedEvent;

    const std::string name;

  private:
    sol::table m_object = sol::nil;
  };
}

#include "GeCore/ECS/Components/Behaviour.inl"
