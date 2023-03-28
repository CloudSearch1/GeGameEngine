/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "GeEditor/Panels/AView.h"
#include "GeEditor/Core/CameraController.h"

namespace GeEditor::Panels
{
	class AViewControllable : public GeEditor::Panels::AView
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		* @param p_enableFocusInputs
		*/
		AViewControllable
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings,
			bool p_enableFocusInputs = false
		);

		/**
		* Update the controllable view (Handle inputs)
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Returns the camera controller of the controllable view
		*/
		GeEditor::Core::CameraController& GetCameraController();

	protected:
		GeEditor::Core::CameraController m_cameraController;
	};
}