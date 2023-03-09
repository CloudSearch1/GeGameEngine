#include "GeEditor/Core/GizmoBehaviour.h"
#include "GeEditor/Core/EditorActions.h"
#include "GeEditor/Settings/EditorSettings.h"

float SnapValue(float p_value, float p_step)
{
	return p_value - std::fmod(p_value, p_step);
}

bool GeEditor::Core::GizmoBehaviour::IsSnappedBehaviourEnabled() const
{
	using namespace GeWindow::Inputs;

	const auto& inputManager = EDITOR_CONTEXT(inputManager);
	return inputManager->GetKeyState(EKey::KEY_LEFT_CONTROL) == EKeyState::KEY_DOWN || inputManager->GetKeyState(EKey::KEY_RIGHT_CONTROL) == EKeyState::KEY_DOWN;
}

void GeEditor::Core::GizmoBehaviour::StartPicking(GeCore::ECS::Actor& p_target, const GeMaths::FVector3& p_cameraPosition, EGizmoOperation p_operation, EDirection p_direction)
{
	m_target = &p_target;
	m_firstMouse = true;
	m_originalTransform = p_target.transform.GetFTransform();
	m_distanceToActor = GeMaths::FVector3::Distance(p_cameraPosition, m_target->transform.GetWorldPosition());
	m_currentOperation = p_operation;
	m_direction = p_direction;
}

void GeEditor::Core::GizmoBehaviour::StopPicking()
{
	m_target = nullptr;
}

GeMaths::FVector3 GeEditor::Core::GizmoBehaviour::GetFakeDirection() const
{
	auto result = GeMaths::FVector3();

	switch (m_direction)
	{
	case GeEditor::Core::GizmoBehaviour::EDirection::X:
		result = GeMaths::FVector3::Right;
		break;
	case GeEditor::Core::GizmoBehaviour::EDirection::Y:
		result = GeMaths::FVector3::Up;
		break;
	case GeEditor::Core::GizmoBehaviour::EDirection::Z:
		result = GeMaths::FVector3::Forward;
		break;
	}

	return result;
}

GeMaths::FVector3 GeEditor::Core::GizmoBehaviour::GetRealDirection(bool p_relative) const
{
	auto result = GeMaths::FVector3();

	switch (m_direction)
	{
	case GeEditor::Core::GizmoBehaviour::EDirection::X:
		result = p_relative ? m_originalTransform.GetWorldRight() : m_originalTransform.GetLocalRight();
		break;
	case GeEditor::Core::GizmoBehaviour::EDirection::Y:
		result = p_relative ? m_originalTransform.GetWorldUp() : m_originalTransform.GetLocalUp();
		break;
	case GeEditor::Core::GizmoBehaviour::EDirection::Z:
		result = p_relative ? m_originalTransform.GetWorldForward() : m_originalTransform.GetLocalForward();
		break;
	}

	return result;
}

GeMaths::FVector2 GeEditor::Core::GizmoBehaviour::GetScreenDirection(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const
{
	auto start = m_originalTransform.GetWorldPosition();
	auto end = m_originalTransform.GetWorldPosition() + GetRealDirection(true) * 0.01f;

	auto start2D = GeMaths::FVector2();
	{
		auto clipSpacePos = p_projectionMatrix * (p_viewMatrix * GeMaths::FVector4{ start.x, start.y, start.z, 1.0f });
		auto ndcSpacePos = GeMaths::FVector3{ clipSpacePos.x, clipSpacePos.y, clipSpacePos.z } / clipSpacePos.w;
		auto windowSpacePos = ((GeMaths::FVector2{ ndcSpacePos.x, ndcSpacePos.y } + 1.0f) / 2.0f);
		windowSpacePos.x *= p_viewSize.x;
		windowSpacePos.y *= p_viewSize.y;
		start2D = windowSpacePos;
	}

	auto end2D = GeMaths::FVector2();
	{
		auto clipSpacePos = p_projectionMatrix * (p_viewMatrix * GeMaths::FVector4{ end.x, end.y, end.z, 1.0f });
		auto ndcSpacePos = GeMaths::FVector3{ clipSpacePos.x, clipSpacePos.y, clipSpacePos.z } / clipSpacePos.w;
		auto windowSpacePos = ((GeMaths::FVector2{ ndcSpacePos.x, ndcSpacePos.y } + 1.0f) / 2.0f);
		windowSpacePos.x *= p_viewSize.x;
		windowSpacePos.y *= p_viewSize.y;
		end2D = windowSpacePos;
	}

	auto result = end2D - start2D;

	result.y *= -1; // Screen coordinates are reversed, so we inverse the Y

	return GeMaths::FVector2::Normalize(result);
}

void GeEditor::Core::GizmoBehaviour::ApplyTranslation(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const
{
	auto unitsPerPixel = 0.001f * m_distanceToActor;
	auto originPosition = m_originalTransform.GetLocalPosition();

	auto screenDirection = GetScreenDirection(p_viewMatrix, p_projectionMatrix, p_viewSize);

	auto totalDisplacement = m_currentMouse - m_originMouse;
	auto translationCoefficient = GeMaths::FVector2::Dot(totalDisplacement, screenDirection) * unitsPerPixel;

	if (IsSnappedBehaviourEnabled())
	{
		translationCoefficient = SnapValue(translationCoefficient, GeEditor::Settings::EditorSettings::TranslationSnapUnit);
	}

	m_target->transform.SetLocalPosition(originPosition + GetRealDirection() * translationCoefficient);
}

void GeEditor::Core::GizmoBehaviour::ApplyRotation(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const
{
	auto unitsPerPixel = 0.2f;
	auto originRotation = m_originalTransform.GetLocalRotation();

	auto screenDirection = GetScreenDirection(p_viewMatrix, p_projectionMatrix, p_viewSize);
	screenDirection = GeMaths::FVector2(-screenDirection.y, screenDirection.x);

	auto totalDisplacement = m_currentMouse - m_originMouse;
	auto rotationCoefficient = GeMaths::FVector2::Dot(totalDisplacement, screenDirection) * unitsPerPixel;

	if (IsSnappedBehaviourEnabled())
	{
		rotationCoefficient = SnapValue(rotationCoefficient, GeEditor::Settings::EditorSettings::RotationSnapUnit);
	}

	auto rotationToApply = GeMaths::FQuaternion(GeMaths::FVector3(GetFakeDirection() * rotationCoefficient));
	m_target->transform.SetLocalRotation(originRotation * rotationToApply);
}

void GeEditor::Core::GizmoBehaviour::ApplyScale(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize) const
{
	auto unitsPerPixel = 0.01f;
	auto originScale = m_originalTransform.GetLocalScale();

	auto screenDirection = GetScreenDirection(p_viewMatrix, p_projectionMatrix, p_viewSize);

	auto totalDisplacement = m_currentMouse - m_originMouse;
	auto scaleCoefficient = GeMaths::FVector2::Dot(totalDisplacement, screenDirection) * unitsPerPixel;

	if (IsSnappedBehaviourEnabled())
	{
		scaleCoefficient = SnapValue(scaleCoefficient, GeEditor::Settings::EditorSettings::ScalingSnapUnit);
	}

	auto newScale = originScale + GetFakeDirection() * scaleCoefficient;

	/* Prevent scale from being negative*/
	newScale.x = std::max(newScale.x, 0.0001f);
	newScale.y = std::max(newScale.y, 0.0001f);
	newScale.z = std::max(newScale.z, 0.0001f);

	m_target->transform.SetLocalScale(newScale);
}

void GeEditor::Core::GizmoBehaviour::ApplyOperation(const GeMaths::FMatrix4& p_viewMatrix, const GeMaths::FMatrix4& p_projectionMatrix, const GeMaths::FVector2& p_viewSize)
{
	switch (m_currentOperation)
	{
	case EGizmoOperation::TRANSLATE:
		ApplyTranslation(p_viewMatrix, p_projectionMatrix, p_viewSize);
		break;

	case EGizmoOperation::ROTATE:
		ApplyRotation(p_viewMatrix, p_projectionMatrix, p_viewSize);
		break;

	case EGizmoOperation::SCALE:
		ApplyScale(p_viewMatrix, p_projectionMatrix, p_viewSize);
		break;
	}
}

void GeEditor::Core::GizmoBehaviour::SetCurrentMouse(const GeMaths::FVector2& p_mousePosition)
{
	if (m_firstMouse)
	{
		m_currentMouse = m_originMouse = p_mousePosition;
		m_firstMouse = false;
	}
	else
	{
		m_currentMouse = p_mousePosition;
	}
}

bool GeEditor::Core::GizmoBehaviour::IsPicking() const
{
	return m_target;
}

GeEditor::Core::GizmoBehaviour::EDirection GeEditor::Core::GizmoBehaviour::GetDirection() const
{
	return m_direction;
}
