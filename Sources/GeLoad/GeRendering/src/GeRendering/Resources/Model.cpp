#include <algorithm>

#include "GeRendering/Resources/Model.h"

const GeRendering::Geometry::BoundingSphere& GeRendering::Resources::Model::GetBoundingSphere() const
{
	return m_boundingSphere;
}

GeRendering::Resources::Model::Model(const std::string & p_path) : path(p_path)
{
}

GeRendering::Resources::Model::~Model()
{
	for (auto mesh : m_meshes)
		delete mesh;
}

void GeRendering::Resources::Model::ComputeBoundingSphere()
{
	if (m_meshes.size() == 1)
	{
		m_boundingSphere = m_meshes[0]->GetBoundingSphere();
	}
	else
	{
		m_boundingSphere.position = GeMaths::FVector3::Zero;
		m_boundingSphere.radius = 0.0f;

		if (!m_meshes.empty())
		{
			float minX = std::numeric_limits<float>::max();
			float minY = std::numeric_limits<float>::max();
			float minZ = std::numeric_limits<float>::max();

			float maxX = std::numeric_limits<float>::min();
			float maxY = std::numeric_limits<float>::min();
			float maxZ = std::numeric_limits<float>::min();

			for (const auto& mesh : m_meshes)
			{
				const auto& boundingSphere = mesh->GetBoundingSphere();
				minX = std::min(minX, boundingSphere.position.x - boundingSphere.radius);
				minY = std::min(minY, boundingSphere.position.y - boundingSphere.radius);
				minZ = std::min(minZ, boundingSphere.position.z - boundingSphere.radius);

				maxX = std::max(maxX, boundingSphere.position.x + boundingSphere.radius);
				maxY = std::max(maxY, boundingSphere.position.y + boundingSphere.radius);
				maxZ = std::max(maxZ, boundingSphere.position.z + boundingSphere.radius);
			}

			m_boundingSphere.position = GeMaths::FVector3{ minX + maxX, minY + maxY, minZ + maxZ } / 2.0f;
			m_boundingSphere.radius = GeMaths::FVector3::Distance(m_boundingSphere.position, { minX, minY, minZ });
		}
	}
}

const std::vector<GeRendering::Resources::Mesh*>& GeRendering::Resources::Model::GetMeshes() const
{
	return m_meshes;
}

const std::vector<std::string>& GeRendering::Resources::Model::GetMaterialNames() const
{
	return m_materialNames;
}
