#pragma once

#include <vector>

#include "GeRendering/Buffers/VertexArray.h"

namespace GeRendering::Resources
{
  //任意网格的接口
	class IMesh
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetVertexCount() = 0;
		virtual uint32_t GetIndexCount() = 0;
	};
}
