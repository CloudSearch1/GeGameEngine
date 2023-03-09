#pragma once

#include <optional>

#include "GeRendering/Context/Driver.h"
#include "GeRendering/LowRenderer/Camera.h"
#include "GeRendering/Resources/Shader.h"
#include "GeRendering/Resources/Model.h"
#include "GeRendering/Settings/ERenderingCapability.h"
#include "GeRendering/Settings/EPrimitiveMode.h"
#include "GeRendering/Settings/ERasterizationMode.h"
#include "GeRendering/Settings/EComparaisonAlgorithm.h"
#include "GeRendering/Settings/EOperation.h"
#include "GeRendering/Settings/ECullFace.h"
#include "GeRendering/Settings/ECullingOptions.h"
#include "GeRendering/Settings/EPixelDataFormat.h"
#include "GeRendering/Settings/EPixelDataType.h"

namespace GeRendering::Core
{
	/**
  * renderer是GeRendering的核心的类，必须要创建一个
  * 作用是send batches to the GPU
	*/
	class Renderer
	{
	public:
		
		struct FrameInfo
		{
			uint64_t batchCount		= 0;
			uint64_t instanceCount	= 0;
			uint64_t polyCount		= 0;
		};

		Renderer(Context::Driver& p_driver);
		~Renderer() = default;

    //定义clearColor，用于后面的Renderer::Clear方法
		void SetClearColor(float p_red, float p_green, float p_blue, float p_alpha = 1.0f);

    //将屏幕上的颜色设置为单一的颜色，如果调用了setclearcolor方法则使用上个方法设置的颜色
    //否则将采用OpenGL默认的颜色
		void Clear(bool p_colorBuffer = true, bool p_depthBuffer = true, bool p_stencilBuffer = true);

    //用相机的clearcolor来清除屏幕的颜色
		void Clear(GeRendering::LowRenderer::Camera& p_camera, bool p_colorBuffer = true, bool p_depthBuffer = true, bool p_stencilBuffer = true);

    //定义光栅化线宽
		void SetRasterizationLinesWidth(float p_width);

		//定义使用的光栅化模式
		void SetRasterizationMode(Settings::ERasterizationMode p_rasterizationMode);
		
    //通过value设置OpenGL的capabilities
		void SetCapability(Settings::ERenderingCapability p_capability, bool p_value);

    //返回OpenGL的capability是否被启用
		bool GetCapability(Settings::ERenderingCapability p_capability) const;

    //定义比较算法，用于模板缓冲区测试
		void SetStencilAlgorithm(Settings::EComparaisonAlgorithm p_algorithm, int32_t p_reference, uint32_t p_mask);

    //定义比较算法，用于深度缓冲区测试
		void SetDepthAlgorithm(Settings::EComparaisonAlgorithm p_algorithm);

    //控制模板平面各个位的写入。参数指定一个位掩码，以启用和禁用在模具平面中写入单个位。最初，掩码都是1。
		void SetStencilMask(uint32_t p_mask);

		//设置前后模板测试的动作
		void SetStencilOperations(Settings::EOperation p_stencilFail = Settings::EOperation::KEEP, Settings::EOperation p_depthFail = Settings::EOperation::KEEP, Settings::EOperation p_bothPass = Settings::EOperation::KEEP);

		//设置剔除面
		void SetCullFace(Settings::ECullFace p_cullFace);

    //设置是否可以写入深度缓冲区
		void SetDepthWriting(bool p_enable);

    //启用和禁用帧缓冲区颜色分量的写入
		void SetColorWriting(bool p_enableRed, bool p_enableGreen, bool p_enableBlue, bool p_enableAlpha);

    //启用和禁用帧缓冲区颜色分量的写入
		void SetColorWriting(bool p_enable);

    //设置视图参数
		void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    //从帧缓冲区读取一个像素块
		void ReadPixels(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Settings::EPixelDataFormat format,Settings::EPixelDataType type, void* data);

    //返回与给定的gl参数相关的值
		bool GetBool(GLenum p_parameter);

    //返回与给定的gl参数相关的，同时在指定索引处的值
		bool GetBool(GLenum p_parameter, uint32_t p_index);

    //返回与给定的gl参数相关的值
		int GetInt(GLenum p_parameter);

    //返回与给定的gl参数相关的，同时在指定索引处的值
		int GetInt(GLenum p_parameter, uint32_t p_index);

    //返回与给定的gl参数相关的值
		float GetFloat(GLenum p_parameter);

    //返回与给定的gl参数相关的，同时在指定索引处的值
		float GetFloat(GLenum p_parameter, uint32_t p_index);

    //返回与给定的gl参数相关的值
		double GetDouble(GLenum p_parameter);

    //返回与给定的gl参数相关的，同时在指定索引处的值
		double GetDouble(GLenum p_parameter, uint32_t p_index);

    //返回与给定的gl参数相关的值
		int64_t GetInt64(GLenum p_parameter);

    //返回与给定的gl参数相关的，同时在指定索引处的值
		int64_t GetInt64(GLenum p_parameter, uint32_t p_index);

    //返回与给定的gl参数相关的值
		std::string GetString(GLenum p_parameter);

    //返回与给定的gl参数相关的，同时在指定索引处的值
		std::string GetString(GLenum p_parameter, uint32_t p_index);

    //清除帧的信息
		void ClearFrameInfo();

    //根据传入参数的次数绘制给定模型，如果实例数量大于1则渲染实例
		void Draw(Resources::IMesh& p_mesh, Settings::EPrimitiveMode p_primitiveMode = Settings::EPrimitiveMode::TRIANGLES, uint32_t p_instances = 1);

    //返回一个列表，包含一个模型中的需要被渲染的网格列表
		std::vector<std::reference_wrapper<GeRendering::Resources::Mesh>> GetMeshesInFrustum
		(
			const GeRendering::Resources::Model& p_model,
			const GeRendering::Geometry::BoundingSphere& p_modelBoundingSphere,
			const GeMaths::FTransform& p_modelTransform,
			const GeRendering::Data::Frustum& p_frustum,
			GeRendering::Settings::ECullingOptions p_cullingOptions
		);

		//获取并返回实际的OpenGL状态
		uint8_t FetchGLState();

		//应用Mask去修改OpenGL的状态
		void ApplyStateMask(uint8_t p_mask);

    //存储当前渲染状态
		void SetState(uint8_t p_state);

		//返回frameInfo
		const FrameInfo& GetFrameInfo() const;

	private:
		Context::Driver&	m_driver;
		FrameInfo			    m_frameInfo;
		uint8_t				    m_state;
	};
}
