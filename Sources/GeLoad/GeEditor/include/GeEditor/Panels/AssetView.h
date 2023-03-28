/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <variant>

#include <GeCore/Resources/Material.h>

#include "GeEditor/Panels/AViewControllable.h"

namespace GeEditor::Panels
{
	/**
	* Provide a view for assets
	*/
	class AssetView : public GeEditor::Panels::AViewControllable
	{
	public:
		using ViewableResource = std::variant<GeRendering::Resources::Model*, GeRendering::Resources::Texture*, GeCore::Resources::Material*>;

		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		AssetView
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Custom implementation of the render method
		*/
		virtual void _Render_Impl() override;

		/**
		* Defines the resource to preview
		* @parma p_resource
		*/
		void SetResource(ViewableResource p_resource);

		/**
		* Return the currently previewed resource
		*/
		ViewableResource GetResource() const;

	private:
		ViewableResource m_resource;
	};
}