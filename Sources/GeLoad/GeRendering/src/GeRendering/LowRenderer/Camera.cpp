#include <cmath>

#include "GeRendering/LowRenderer/Camera.h"
#include "GeMaths/FMatrix4.h"


namespace GeRendering::LowRenderer
{

  Camera::Camera() :
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

  void Camera::CacheMatrices(uint16_t p_windowWidth, uint16_t p_windowHeight, const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation)
  {
    CacheProjectionMatrix(p_windowWidth, p_windowHeight);
    CacheViewMatrix(p_position, p_rotation);
    CacheFrustum(m_viewMatrix, m_projectionMatrix);
  }

  void Camera::CacheProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight)
  {
    m_projectionMatrix = CalculateProjectionMatrix(p_windowWidth, p_windowHeight);
  }

  void Camera::CacheViewMatrix(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation)
  {
    m_viewMatrix = CalculateViewMatrix(p_position, p_rotation);
  }

  void Camera::CacheFrustum(const GeMaths::FMatrix4& p_view, const GeMaths::FMatrix4& p_projection)
  {
    m_frustum.CalculateFrustum(p_projection * p_view);
  }

  float Camera::GetFov() const
  {
    return m_fov;
  }

  float Camera::GetSize() const
  {
    return m_size;
  }

  float Camera::GetNear() const
  {
    return m_near;
  }

  float Camera::GetFar() const
  {
    return m_far;
  }

  const GeMaths::FVector3& Camera::GetClearColor() const
  {
    return m_clearColor;
  }

  const GeMaths::FMatrix4& Camera::GetProjectionMatrix() const
  {
    return m_projectionMatrix;
  }

  const GeMaths::FMatrix4& Camera::GetViewMatrix() const
  {
    return m_viewMatrix;
  }

  const GeRendering::Data::Frustum& Camera::GetFrustum() const
  {
    return m_frustum;
  }

  bool Camera::HasFrustumGeometryCulling() const
  {
    return m_frustumGeometryCulling;
  }

  bool Camera::HasFrustumLightCulling() const
  {
    return m_frustumLightCulling;
  }

  GeRendering::Settings::EProjectionMode Camera::GetProjectionMode() const
  {
    return m_projectionMode;
  }

  void Camera::SetFov(float p_value)
  {
    m_fov = p_value;
  }

  void Camera::SetSize(float p_value)
  {
    m_size = p_value;
  }

  void Camera::SetNear(float p_value)
  {
    m_near = p_value;
  }

  void Camera::SetFar(float p_value)
  {
    m_far = p_value;
  }

  void Camera::SetClearColor(const GeMaths::FVector3& p_clearColor)
  {
    m_clearColor = p_clearColor;
  }

  void Camera::SetFrustumGeometryCulling(bool p_enable)
  {
    m_frustumGeometryCulling = p_enable;
  }

  void Camera::SetFrustumLightCulling(bool p_enable)
  {
    m_frustumLightCulling = p_enable;
  }

  void Camera::SetProjectionMode(GeRendering::Settings::EProjectionMode p_projectionMode)
  {
    m_projectionMode = p_projectionMode;
  }

  GeMaths::FMatrix4 Camera::CalculateProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight) const
  {
    const auto ratio = p_windowWidth / static_cast<float>(p_windowHeight);

    switch (m_projectionMode)
    {
      case GeRendering::Settings::EProjectionMode::ORTHOGRAPHIC:
        return GeMaths::FMatrix4::CreateOrthographic(m_size, ratio, m_near, m_far);

      case GeRendering::Settings::EProjectionMode::PERSPECTIVE:
        return GeMaths::FMatrix4::CreatePerspective(m_fov, ratio, m_near, m_far);

      default:
        return GeMaths::FMatrix4::Identity;
    }
  }

  GeMaths::FMatrix4 Camera::CalculateViewMatrix(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation) const
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

}
