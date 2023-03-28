#pragma once

#include <vector>
#include <memory>

#include "GeRendering/Buffers/VertexArray.h"
#include "GeRendering/Buffers/IndexBuffer.h"
#include "GeRendering/Resources/IMesh.h"
#include "GeRendering/Geometry/Vertex.h"
#include "GeRendering/Geometry/BoundingSphere.h"

namespace GeRendering::Resources
{
  //渲染器的标准网格
	class Mesh : public IMesh
	{
	public:
    //使用给定的顶点、索引和材质索引创建网格
		Mesh(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices, uint32_t p_materialIndex);

    virtual void Bind() override;
		virtual void Unbind() override;

    //返回顶点数
		virtual uint32_t GetVertexCount() override;

		//返回索引的数量
		virtual uint32_t GetIndexCount() override;

    //返回网格的材质索引
		uint32_t GetMaterialIndex() const;

    //返回网格的包围球
		const GeRendering::Geometry::BoundingSphere& GetBoundingSphere() const;

	private:
		void CreateBuffers(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices);
		void ComputeBoundingSphere(const std::vector<Geometry::Vertex>& p_vertices);

	private:
		const uint32_t m_vertexCount;
		const uint32_t m_indicesCount;
		const uint32_t m_materialIndex;

		Buffers::VertexArray							                  m_vertexArray;
		std::unique_ptr<Buffers::VertexBuffer<float>>	      m_vertexBuffer;
		std::unique_ptr<Buffers::IndexBuffer>			          m_indexBuffer;

		Geometry::BoundingSphere m_boundingSphere;
	};
}
