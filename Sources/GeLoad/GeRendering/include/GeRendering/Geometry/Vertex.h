#pragma once

namespace GeRendering::Geometry
{
  //定义顶点几何的结构体
	struct Vertex
	{
		float position[3];
		float texCoords[2];
		float normals[3];
		float tangent[3];
		float bitangent[3];
	};
}
