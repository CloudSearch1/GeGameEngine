#pragma once

#include <GeMaths/FVector3.h>
#include <GeMaths/FMatrix4.h>
#include <GeMaths/FQuaternion.h>

#include <GeUtils/Utils/ReferenceOrValue.h>


#include "GeRendering/Data/Frustum.h"
#include "GeRendering/Settings/EProjectionMode.h"

namespace GeRendering::LowRenderer
{

	class Camera
	{
	public:
		Camera();

    //缓存投影、视图和视锥体矩阵
		void CacheMatrices(uint16_t p_windowWidth, uint16_t p_windowHeight, const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation);
    
    //计算并缓存结果投影矩阵
		void CacheProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight);

    //计算并缓存结果视图矩阵
		void CacheViewMatrix(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation);

    //计算并缓存结果视锥体。
		void CacheFrustum(const GeMaths::FMatrix4& p_view, const GeMaths::FMatrix4& p_projection);

    //返回相机的FOV
		float GetFov() const;

    //返回相机的大小
    float GetSize() const;
    
    //返回相机的near
		float GetNear() const;

    //返回相机的far
    float GetFar() const;

    //返回相机的清除颜色
		const GeMaths::FVector3& GetClearColor() const;

    //返回缓存的投影矩阵
		const GeMaths::FMatrix4& GetProjectionMatrix() const;

	  //返回缓存的视图矩阵
		const GeMaths::FMatrix4& GetViewMatrix() const;

    //返回视图的视锥体
		const GeRendering::Data::Frustum& GetFrustum() const;

		//如果启用几何的视锥体剔除，则返回 true
		bool HasFrustumGeometryCulling() const;

    //如果启用了灯光的视锥体剔除，则返回 true
		bool HasFrustumLightCulling() const;

    //返回当前投影模式
    GeRendering::Settings::EProjectionMode GetProjectionMode() const;

    //设置相机的FOV
		void SetFov(float p_value);

    //设置相机的大小
    void SetSize(float p_value);

    //将相机的near设置为给定值
		void SetNear(float p_value);

		//将相机的far设置为给定值
		void SetFar(float p_value);

    //设置相机的清除颜色
		void SetClearColor(const GeMaths::FVector3& p_clearColor);

    //定义相机是否应该在渲染时对几何体应用视锥体剔除
		void SetFrustumGeometryCulling(bool p_enable);

		//定义相机是否应该在渲染时对灯光应用视锥体剔除
		void SetFrustumLightCulling(bool p_enable);

    //定义相机应采用的投影模式
    void SetProjectionMode(GeRendering::Settings::EProjectionMode p_projectionMode);

	private:
		GeMaths::FMatrix4 CalculateProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight) const;
		GeMaths::FMatrix4 CalculateViewMatrix(const GeMaths::FVector3& p_position, const GeMaths::FQuaternion& p_rotation) const;

	private:
		GeRendering::Data::Frustum m_frustum;
		GeMaths::FMatrix4 m_viewMatrix;
		GeMaths::FMatrix4 m_projectionMatrix;
        GeRendering::Settings::EProjectionMode m_projectionMode;

		float m_fov;
    float m_size;
		float m_near;
		float m_far;

		GeMaths::FVector3 m_clearColor;

		bool m_frustumGeometryCulling;
		bool m_frustumLightCulling;
	};
}
