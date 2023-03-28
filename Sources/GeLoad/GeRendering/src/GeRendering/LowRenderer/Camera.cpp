#include <cmath>

#include "GeRendering/LowRenderer/Camera.h"
#include "GeMaths/FMatrix4.h"

GeRendering::LowRenderer::Camera::Camera() :
  m_projectionMode(Settings::EProjectionMode::PERSPECTIVE),
	m_fov(45.0f),
  m_size(5.0f),
	m_near(0.1f),
	m_far(100.f),
	m_clearColor(0.f, 0.f, 0.f),
	m_frustumGeometryCulling(false),
	m_frustumLightCulling(false)
{
}

void GeRendering::LowRenderer::Camera::CacheMatrices(uint16_t p_windowWidth, uint16_t p_windowHeight, const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation)
{
	CacheProjectionMatrix(p_windowWidth, p_windowHeight);
	CacheViewMatrix(p_position, p_rotation);
	CacheFrustum(m_viewMatrix, m_projectionMatrix);
}

void GeRendering::LowRenderer::Camera::CacheProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight)
{
	m_projectionMatrix = CalculateProjectionMatrix(p_windowWidth, p_windowHeight);
}

void GeRendering::LowRenderer::Camera::CacheViewMatrix(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation)
{
	m_viewMatrix = CalculateViewMatrix(p_position, p_rotation);
}

void GeRendering::LowRenderer::Camera::CacheFrustum(const GeMaths::FMatrix4& p_view, const GeMaths::FMatrix4& p_projection)
{
	m_frustum.CalculateFrustum(p_projection * p_view);
}

float GeRendering::LowRenderer::Camera::GetFov() const
{
	return m_fov;
}

float GeRendering::LowRenderer::Camera::GetSize() const
{
    return m_size;
}

float GeRendering::LowRenderer::Camera::GetNear() const
{
	return m_near;
}

float GeRendering::LowRenderer::Camera::GetFar() const
{
	return m_far;
}

const GeMaths::FVector3 & GeRendering::LowRenderer::Camera::GetClearColor() const
{
	return m_clearColor;
}

const GeMaths::FMatrix4& GeRendering::LowRenderer::Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

const GeMaths::FMatrix4& GeRendering::LowRenderer::Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const GeRendering::Data::Frustum& GeRendering::LowRenderer::Camera::GetFrustum() const
{
	return m_frustum;
}

bool GeRendering::LowRenderer::Camera::HasFrustumGeometryCulling() const
{
	return m_frustumGeometryCulling;
}

bool GeRendering::LowRenderer::Camera::HasFrustumLightCulling() const
{
	return m_frustumLightCulling;
}

GeRendering::Settings::EProjectionMode GeRendering::LowRenderer::Camera::GetProjectionMode() const
{
    return m_projectionMode;
}

void GeRendering::LowRenderer::Camera::SetFov(float p_value)
{
	m_fov = p_value;
}

void GeRendering::LowRenderer::Camera::SetSize(float p_value)
{
    m_size = p_value;
}

void GeRendering::LowRenderer::Camera::SetNear(float p_value)
{
	m_near = p_value;
}

void GeRendering::LowRenderer::Camera::SetFar(float p_value)
{
	m_far = p_value;
}

void GeRendering::LowRenderer::Camera::SetClearColor(const GeMaths::FVector3 & p_clearColor)
{
	m_clearColor = p_clearColor;
}

void GeRendering::LowRenderer::Camera::SetFrustumGeometryCulling(bool p_enable)
{
	m_frustumGeometryCulling = p_enable;
}

void GeRendering::LowRenderer::Camera::SetFrustumLightCulling(bool p_enable)
{
	m_frustumLightCulling = p_enable;
}

void GeRendering::LowRenderer::Camera::SetProjectionMode(GeRendering::Settings::EProjectionMode p_projectionMode)
{
    m_projectionMode = p_projectionMode;
}

GeMaths::FMatrix4 GeRendering::LowRenderer::Camera::CalculateProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight) const
{
    using namespace GeMaths;
    using namespace GeRendering::Settings;

    const auto ratio = p_windowWidth / static_cast<float>(p_windowHeight);

    switch (m_projectionMode)
    {
    case EProjectionMode::ORTHOGRAPHIC:
        return FMatrix4::CreateOrthographic(m_size, ratio, m_near, m_far);

    case EProjectionMode::PERSPECTIVE: 
        return FMatrix4::CreatePerspective(m_fov, ratio, m_near, m_far);

    default:
        return FMatrix4::Identity;
    }
}

GeMaths::FMatrix4 GeRendering::LowRenderer::Camera::CalculateViewMatrix(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation) const
{
	const auto& up = p_rotation * GeMaths::FVector3::Up;
	const auto& forward = p_rotation * GeMaths::FVector3::Forward;

	return GeMaths::FMatrix4::CreateView
	(
		p_position.x, p_position.y, p_position.z,												
		p_position.x + forward.x, p_position.y + forward.y, p_position.z + forward.z,			//lookat
		up.x, up.y, up.z																	
	);
}
