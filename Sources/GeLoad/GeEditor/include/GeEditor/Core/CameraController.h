#pragma once

#include <queue>

#include <GeWindow/Inputs/InputManager.h>
#include <GeWindow/Window.h>
#include <GeRendering/LowRenderer/Camera.h>

#include "GeEditor/Panels/Hierarchy.h"
#include "GeEditor/Panels/AView.h"

namespace GeEditor::Core
{
  //用于导航到视图的简单相机控制器
	class CameraController
	{
	public:
		CameraController
		(
			GeEditor::Panels::AView& p_view,
			GeRendering::LowRenderer::Camera& p_camera,
			GeMaths::FVector3& p_position,
			GeMaths::FQuaternion& p_rotation,
			bool p_enableFocusInputs = false
		);

		void HandleInputs(float p_deltaTime);

		void MoveToTarget(GeCore::ECS::Actor& p_target);

    void SetSpeed(float p_speed);

		float GetSpeed() const;

		void SetPosition(const GeMaths::FVector3& p_position);

    void SetRotation(const GeMaths::FQuaternion& p_rotation);

		const GeMaths::FVector3& GetPosition() const;

		const GeMaths::FQuaternion& GetRotation() const;

		bool IsRightMousePressed() const;

	private:
		void HandleCameraPanning(const GeMaths::FVector2& p_mouseOffset, bool p_firstMouse);
		void HandleCameraOrbit(const GeMaths::FVector2& p_mouseOffset, bool p_firstMouse);
		void HandleCameraFPSMouse(const GeMaths::FVector2& p_mouseOffset, bool p_firstMouse);

		void HandleCameraZoom();
		void HandleCameraFPSKeyboard(float p_deltaTime);
		void UpdateMouseState();

	private:
		GeWindow::Inputs::InputManager& m_inputManager;
		GeWindow::Window& m_window;
		GeEditor::Panels::AView& m_view;
		GeRendering::LowRenderer::Camera& m_camera;
		GeMaths::FVector3& m_cameraPosition;
		GeMaths::FQuaternion& m_cameraRotation;

		std::queue<std::tuple<GeMaths::FVector3, GeMaths::FQuaternion>> m_cameraDestinations;

		bool m_enableFocusInputs;

		bool m_leftMousePressed = false;
		bool m_middleMousePressed = false;
		bool m_rightMousePressed = false;

		GeMaths::FVector3 m_targetSpeed;
		GeMaths::FVector3 m_currentMovementSpeed;

		GeMaths::FTransform* m_orbitTarget = nullptr;
		GeMaths::FVector3 m_orbitStartOffset;
		bool m_firstMouse = true;
		double m_lastMousePosX = 0.0;
		double m_lastMousePosY = 0.0;
		GeMaths::FVector3 m_ypr;
		float m_mouseSensitivity = 0.12f;
		float m_cameraDragSpeed = 0.03f;
		float m_cameraOrbitSpeed = 0.5f;
		float m_cameraMoveSpeed = 15.0f;
		float m_focusDistance = 15.0f;
		float m_focusLerpCoefficient = 8.0f;
	};
}
