#pragma once

#include "GeRendering/Core/Renderer.h"
#include "GeRendering/Resources/Mesh.h"

namespace GeRendering::Core
{
  //渲染基础的图形
	class ShapeDrawer
	{
	public:
    //创建实例
		ShapeDrawer(GeRendering::Core::Renderer& p_renderer);
		~ShapeDrawer();

    //设置绘制时的视图投影
		void SetViewProjection(const GeMaths::FMatrix4& p_viewProjection);

    //在世界空间中绘制线
		void DrawLine(const GeMaths::FVector3& p_start, const GeMaths::FVector3& p_end, const GeMaths::FVector3& p_color, float p_lineWidth = 1.0f);

    //在世界空间中绘制网格
		void DrawGrid(const GeMaths::FVector3& p_viewPos, const GeMaths::FVector3& p_color, int32_t p_gridSize = 50, float p_linear = 0.0f, float p_quadratic = 0.0f, float p_fadeThreshold = 0.0f, float p_lineWidth = 1.0f);

	private:
		GeRendering::Resources::Shader* m_lineShader  = nullptr;
		GeRendering::Resources::Shader* m_gridShader  = nullptr;
		GeRendering::Resources::Mesh*   m_lineMesh    = nullptr;
		GeRendering::Core::Renderer&    m_renderer;
	};
}
