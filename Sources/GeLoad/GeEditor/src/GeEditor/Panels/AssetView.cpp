/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <GeUtils/Utils/PathParser.h>
#include <GeUI/Plugins/DDTarget.h>

#include "GeEditor/Core/EditorRenderer.h"
#include "GeEditor/Core/EditorActions.h"
#include "GeEditor/Panels/AssetView.h"


GeEditor::Panels::AssetView::AssetView
(
	const std::string& p_title,
	bool p_opened,
	const GeUI::Settings::PanelWindowSettings& p_windowSettings
) : AViewControllable(p_title, p_opened, p_windowSettings)
{
	m_camera.SetClearColor({ 0.098f, 0.098f, 0.098f });
	m_camera.SetFar(5000.0f);

	m_resource = static_cast<GeRendering::Resources::Model*>(nullptr);
	m_image->AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [this](auto p_data)
	{
		std::string path = p_data.first;

		switch (GeUtils::Utils::PathParser::GetFileType(path))
		{
		case GeUtils::Utils::PathParser::EFileType::MODEL:
			if (auto resource = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::ModelManager>().GetResource(path); resource)
				m_resource = resource;
			break;
		case GeUtils::Utils::PathParser::EFileType::TEXTURE:
			if (auto resource = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::TextureManager>().GetResource(path); resource)
				m_resource = resource;
			break;

		case GeUtils::Utils::PathParser::EFileType::MATERIAL:
			if (auto resource = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::MaterialManager>().GetResource(path); resource)
				m_resource = resource;
			break;
		}
	};
}

void GeEditor::Panels::AssetView::_Render_Impl()
{
	PrepareCamera();

	auto& baseRenderer = *EDITOR_CONTEXT(renderer).get();

	m_fbo.Bind();

	baseRenderer.SetStencilMask(0xFF);
	baseRenderer.Clear(m_camera);
	baseRenderer.SetStencilMask(0x00);

	uint8_t glState = baseRenderer.FetchGLState();
	baseRenderer.ApplyStateMask(glState);

	m_editorRenderer.RenderGrid(m_cameraPosition, m_gridColor);

	if (auto pval = std::get_if<GeRendering::Resources::Model*>(&m_resource); pval && *pval)
		m_editorRenderer.RenderModelAsset(**pval);
	
	if (auto pval = std::get_if<GeRendering::Resources::Texture*>(&m_resource); pval && *pval)
		m_editorRenderer.RenderTextureAsset(**pval);
	
	if (auto pval = std::get_if<GeCore::Resources::Material*>(&m_resource); pval && *pval)
		m_editorRenderer.RenderMaterialAsset(**pval);

	baseRenderer.ApplyStateMask(glState);

	m_fbo.Unbind();
}

void GeEditor::Panels::AssetView::SetResource(ViewableResource p_resource)
{
	m_resource = p_resource;
}

GeEditor::Panels::AssetView::ViewableResource GeEditor::Panels::AssetView::GetResource() const
{
	return m_resource;
}
