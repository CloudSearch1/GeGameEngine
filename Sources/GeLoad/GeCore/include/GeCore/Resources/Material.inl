#pragma once

#include <GeDebug/Logger.h>

#include "GeCore/Resources/Material.h"

namespace GeCore::Resources
{
	template<typename T>
	inline void Material::Set(const std::string p_key, const T& p_value)
	{
		if (HasShader())
		{
			if (m_uniformsData.find(p_key) != m_uniformsData.end())
				m_uniformsData[p_key] = std::any(p_value);
		}
		else
		{
			LOG_ERROR("Material Set failed: No attached shader");
		}
	}

	template<typename T>
	inline const T& Material::Get(const std::string p_key)
	{
		if (m_uniformsData.find(p_key) != m_uniformsData.end())
			return T();
		else
			return std::any_cast<T>(m_uniformsData.at(p_key));
	}
}
