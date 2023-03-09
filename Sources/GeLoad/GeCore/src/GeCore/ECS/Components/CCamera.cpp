#include <GeUI/Widgets/Drags/DragFloat.h>
#include <GeUI/Widgets/Selection/ComboBox.h>
#include <GeUI/Plugins/DataDispatcher.h>

#include "GeCore/ECS/Components/CCamera.h"
#include "GeCore/ECS/Actor.h"

GeCore::ECS::Components::CCamera::CCamera(ECS::Actor& p_owner) : AComponent(p_owner)
{
	SetClearColor({ 0.1921569f, 0.3019608f, 0.4745098f });
}

std::string GeCore::ECS::Components::CCamera::GetName()
{
	return "Camera";
}

void GeCore::ECS::Components::CCamera::SetFov(float p_value)
{
	m_camera.SetFov(p_value);
}

void GeCore::ECS::Components::CCamera::SetSize(float p_value)
{
    m_camera.SetSize(p_value);
}

void GeCore::ECS::Components::CCamera::SetNear(float p_value)
{
	m_camera.SetNear(p_value);
}

void GeCore::ECS::Components::CCamera::SetFar(float p_value)
{
	m_camera.SetFar(p_value);
}

void GeCore::ECS::Components::CCamera::SetFrustumGeometryCulling(bool p_enable)
{
	m_camera.SetFrustumGeometryCulling(p_enable);
}

void GeCore::ECS::Components::CCamera::SetFrustumLightCulling(bool p_enable)
{
	m_camera.SetFrustumLightCulling(p_enable);
}

void GeCore::ECS::Components::CCamera::SetProjectionMode(GeRendering::Settings::EProjectionMode p_projectionMode)
{
    m_camera.SetProjectionMode(p_projectionMode);
}

float GeCore::ECS::Components::CCamera::GetFov() const
{
	return m_camera.GetFov();
}

float GeCore::ECS::Components::CCamera::GetSize() const
{
    return m_camera.GetSize();
}

float GeCore::ECS::Components::CCamera::GetNear() const
{
	return m_camera.GetNear();
}

float GeCore::ECS::Components::CCamera::GetFar() const
{
	return m_camera.GetFar();
}

const GeMaths::FVector3 & GeCore::ECS::Components::CCamera::GetClearColor() const
{
	return m_camera.GetClearColor();
}

bool GeCore::ECS::Components::CCamera::HasFrustumGeometryCulling() const
{
	return m_camera.HasFrustumGeometryCulling();
}

void GeCore::ECS::Components::CCamera::SetClearColor(const GeMaths::FVector3 & p_clearColor)
{
	m_camera.SetClearColor(p_clearColor);
}

bool GeCore::ECS::Components::CCamera::HasFrustumLightCulling() const
{
	return m_camera.HasFrustumLightCulling();
}

GeRendering::Settings::EProjectionMode GeCore::ECS::Components::CCamera::GetProjectionMode() const
{
    return m_camera.GetProjectionMode();
}

GeRendering::LowRenderer::Camera & GeCore::ECS::Components::CCamera::GetCamera()
{
	return m_camera;
}

void GeCore::ECS::Components::CCamera::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	GeCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "fov", m_camera.GetFov());
	GeCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "size", m_camera.GetSize());
	GeCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "near", m_camera.GetNear());
	GeCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "far", m_camera.GetFar());
	GeCore::Helpers::Serializer::SerializeVec3(p_doc, p_node, "clear_color", m_camera.GetClearColor());
	GeCore::Helpers::Serializer::SerializeBoolean(p_doc, p_node, "frustum_geometry_culling", m_camera.HasFrustumGeometryCulling());
	GeCore::Helpers::Serializer::SerializeBoolean(p_doc, p_node, "frustum_light_culling", m_camera.HasFrustumLightCulling());
	GeCore::Helpers::Serializer::SerializeInt(p_doc, p_node, "projection_mode", static_cast<int>(m_camera.GetProjectionMode()));
}

void GeCore::ECS::Components::CCamera::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	m_camera.SetFov(GeCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "fov"));
	m_camera.SetSize(GeCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "size"));
	m_camera.SetNear(GeCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "near"));
	m_camera.SetFar(GeCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "far"));
	m_camera.SetClearColor(GeCore::Helpers::Serializer::DeserializeVec3(p_doc, p_node, "clear_color"));
	m_camera.SetFrustumGeometryCulling(GeCore::Helpers::Serializer::DeserializeBoolean(p_doc, p_node, "frustum_geometry_culling"));
	m_camera.SetFrustumLightCulling(GeCore::Helpers::Serializer::DeserializeBoolean(p_doc, p_node, "frustum_light_culling"));

    //我们必须确保序列化组件中存在“projection_mode”，否则我们不想修改默认设置（Perspective）。
    // 让每个组件在 `OnDeserialize` 中调用 setter 是一种不好的做法，即使没有找到给定属性的 XML 节点也是如此。
    // 我们应该稍后重新设计这个系统。 由于它不在正射投影范围内，所以暂时保留原样。
    if (p_node->FirstChildElement("projection_mode"))
    {
        m_camera.SetProjectionMode(static_cast<GeRendering::Settings::EProjectionMode>(GeCore::Helpers::Serializer::DeserializeInt(p_doc, p_node, "projection_mode")));
    }
}

void GeCore::ECS::Components::CCamera::OnInspector(GeUI::Internal::WidgetContainer& p_root)
{
    auto currentProjectionMode = GetProjectionMode();

	GeCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Field of view", std::bind(&CCamera::GetFov, this), std::bind(&CCamera::SetFov, this, std::placeholders::_1));
    auto& fovWidget = *p_root.GetWidgets()[p_root.GetWidgets().size() - 1].first;
    auto& fovWidgetLabel = *p_root.GetWidgets()[p_root.GetWidgets().size() - 2].first;
    fovWidget.enabled = fovWidgetLabel.enabled = currentProjectionMode == GeRendering::Settings::EProjectionMode::PERSPECTIVE;

	GeCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Size", std::bind(&CCamera::GetSize, this), std::bind(&CCamera::SetSize, this, std::placeholders::_1));
    auto& sizeWidget = *p_root.GetWidgets()[p_root.GetWidgets().size() - 1].first;
    auto& sizeWidgetLabel = *p_root.GetWidgets()[p_root.GetWidgets().size() - 2].first;
    sizeWidget.enabled = sizeWidgetLabel.enabled = currentProjectionMode == GeRendering::Settings::EProjectionMode::ORTHOGRAPHIC;

	GeCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Near", std::bind(&CCamera::GetNear, this), std::bind(&CCamera::SetNear, this, std::placeholders::_1));
	GeCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Far", std::bind(&CCamera::GetFar, this), std::bind(&CCamera::SetFar, this, std::placeholders::_1));
	GeCore::Helpers::GUIDrawer::DrawColor(p_root, "Clear color", [this]() {return reinterpret_cast<const GeUI::Types::Color&>(GetClearColor()); }, [this](GeUI::Types::Color p_color) { SetClearColor({ p_color.r, p_color.g, p_color.b }); }, false);
	GeCore::Helpers::GUIDrawer::DrawBoolean(p_root, "Frustum Geometry Culling", std::bind(&CCamera::HasFrustumGeometryCulling, this), std::bind(&CCamera::SetFrustumGeometryCulling, this, std::placeholders::_1));
	GeCore::Helpers::GUIDrawer::DrawBoolean(p_root, "Frustum Light Culling", std::bind(&CCamera::HasFrustumLightCulling, this), std::bind(&CCamera::SetFrustumLightCulling, this, std::placeholders::_1));

    Helpers::GUIDrawer::CreateTitle(p_root, "Projection Mode");
    auto& projectionMode = p_root.CreateWidget<GeUI::Widgets::Selection::ComboBox>(static_cast<int>(GetProjectionMode()));
    projectionMode.choices.emplace(0, "Orthographic");
    projectionMode.choices.emplace(1, "Perspective");
    projectionMode.ValueChangedEvent += [this, &fovWidget, &fovWidgetLabel, &sizeWidget, &sizeWidgetLabel](int p_choice)
    {
        const auto newProjectionMode = static_cast<GeRendering::Settings::EProjectionMode>(p_choice);
        SetProjectionMode(newProjectionMode);
        fovWidget.enabled = fovWidgetLabel.enabled = newProjectionMode == GeRendering::Settings::EProjectionMode::PERSPECTIVE;
        sizeWidget.enabled = sizeWidgetLabel.enabled = newProjectionMode == GeRendering::Settings::EProjectionMode::ORTHOGRAPHIC;
    };
}
