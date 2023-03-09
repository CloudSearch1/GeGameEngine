#pragma once

#include <GeMaths/FTransform.h>
#include <GeMaths/FVector2.h>

#include <GeCore/ECS/Actor.h>

namespace GeEditor::Core
{
	enum class EGizmoOperation
	{
		TRANSLATE,
		ROTATE,
		SCALE
	};

	/* Handle gizmo behaviours */
	class GizmoBehaviour
	{
	public:
		enum class EDirection
		{
			X,
			Y,
			Z
		};
		
		bool IsSnappedBehaviourEnabled() const;

		void StartPicking(GeCore::ECS::Actor& p_target, const GeMaths::FVector3& p_cameraPosition, EGizmoOperation p_operation, EDirection p_direction);

		void StopPicking();

		void ApplyOperation(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize);

		void SetCurrentMouse(const GeMaths::FVector2& p_mousePosition);

		bool IsPicking() const;

		EDirection GetDirection() const;

	private:
		GeMaths::FVector3 GetFakeDirection() const;

		GeMaths::FVector3 GetRealDirection(bool p_relative = false) const;

		GeMaths::FVector2 GetScreenDirection(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const;

		void ApplyTranslation(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const;

		void ApplyRotation(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const;

		void ApplyScale(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const;

	private:
		bool m_firstMouse = true;
		float m_distanceToActor = 0.0f;
		GeCore::ECS::Actor* m_target = nullptr;
		EGizmoOperation m_currentOperation;
		EDirection m_direction;
		GeMaths::FTransform m_originalTransform;
		GeMaths::FVector2 m_originMouse;
		GeMaths::FVector2 m_currentMouse;
		GeMaths::FVector2 m_screenDirection;
	};
}
