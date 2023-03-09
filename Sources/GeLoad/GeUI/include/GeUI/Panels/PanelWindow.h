/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <memory>

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Panels/APanelTransformable.h"
#include "GeUI/Settings/PanelWindowSettings.h"

namespace GeUI::Panels
{
	/**
	* A PanelWindow is a panel that is localized and behave like a window (Movable, resizable...)
	*/
	class PanelWindow : public APanelTransformable
	{
	public:
		/**
		* Creates the PanelWindow
		* @param p_name
		* @param p_opened
		* @param p_panelSettings
		*/
		PanelWindow
		(
			const std::string& p_name = "",
			bool p_opened = true,
			const Settings::PanelWindowSettings& p_panelSettings = Settings::PanelWindowSettings{}
		);

		/**
		* Open (show) the panel
		*/
		void Open();

		/**
		* Close (hide) the panel
		*/
		void Close();

		/**
		* Focus the panel
		*/
		void Focus();

		/**
		* Defines the opened state of the window
		* @param p_value
		*/
		void SetOpened(bool p_value);

		/**
		* Returns true if the panel is opened
		*/
		bool IsOpened() const;

		/**
		* Returns true if the panel is hovered
		*/
		bool IsHovered() const;

		/**
		* Returns true if the panel is focused
		*/
		bool IsFocused() const;

		/**
		* Returns true if the panel is appearing
		*/
		bool IsAppearing() const;

        /**
        * Scrolls to the bottom of the window
        */
        void ScrollToBottom();

        /**
        * Scrolls to the top of the window
        */
        void ScrollToTop();

        /**
        * Returns true if the window is scrolled to the bottom
        */
        bool IsScrolledToBottom() const;

        /**
        * Returns true if the window is scrolled to the bottom
        */
        bool IsScrolledToTop() const;

	protected:
		void _Draw_Impl() override;

	public:
		std::string name;

		GeMaths::FVector2 minSize = { 0.f, 0.f };
		GeMaths::FVector2 maxSize = { 0.f, 0.f };

		bool resizable = true;
		bool closable = false;
		bool movable = true;
		bool scrollable = true;
		bool dockable = false;
		bool hideBackground = false;
		bool forceHorizontalScrollbar = false;
		bool forceVerticalScrollbar = false;
		bool allowHorizontalScrollbar = false;
		bool bringToFrontOnFocus = true;
		bool collapsable = false;
		bool allowInputs = true;
		bool titleBar = true;

		GeUtils::Eventing::Event<> OpenEvent;
		GeUtils::Eventing::Event<> CloseEvent;

	private:
		bool m_opened;
		bool m_hovered;
		bool m_focused;
        bool m_mustScrollToBottom = false;
        bool m_mustScrollToTop = false;
        bool m_scrolledToBottom = false;
        bool m_scrolledToTop = false;
	};
}