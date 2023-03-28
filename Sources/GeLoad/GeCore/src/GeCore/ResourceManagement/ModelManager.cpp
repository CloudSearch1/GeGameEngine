#include "GeCore/ResourceManagement/ModelManager.h"

#include <GeUtils/Filesystem/IniFile.h>

GeRendering::Resources::Parsers::EModelParserFlags GetAssetMetadata(const std::string& p_path)
{
	auto metaFile = GeUtils::Filesystem::IniFile(p_path + ".meta");

	GeRendering::Resources::Parsers::EModelParserFlags flags = GeRendering::Resources::Parsers::EModelParserFlags::NONE;

	if (metaFile.GetOrDefault("CALC_TANGENT_SPACE",			true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::CALC_TANGENT_SPACE;
	if (metaFile.GetOrDefault("JOIN_IDENTICAL_VERTICES",	true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::JOIN_IDENTICAL_VERTICES;
	if (metaFile.GetOrDefault("MAKE_LEFT_HANDED",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::MAKE_LEFT_HANDED;
	if (metaFile.GetOrDefault("TRIANGULATE",				true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::TRIANGULATE;
	if (metaFile.GetOrDefault("REMOVE_COMPONENT",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::REMOVE_COMPONENT;
	if (metaFile.GetOrDefault("GEN_NORMALS",				false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::GEN_NORMALS;
	if (metaFile.GetOrDefault("GEN_SMOOTH_NORMALS",			true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::GEN_SMOOTH_NORMALS;
	if (metaFile.GetOrDefault("SPLIT_LARGE_MESHES",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::SPLIT_LARGE_MESHES;
	if (metaFile.GetOrDefault("PRE_TRANSFORM_VERTICES",		true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::PRE_TRANSFORM_VERTICES;
	if (metaFile.GetOrDefault("LIMIT_BONE_WEIGHTS",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::LIMIT_BONE_WEIGHTS;
	if (metaFile.GetOrDefault("VALIDATE_DATA_STRUCTURE",	false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::VALIDATE_DATA_STRUCTURE;
	if (metaFile.GetOrDefault("IMPROVE_CACHE_LOCALITY",		true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::IMPROVE_CACHE_LOCALITY;
	if (metaFile.GetOrDefault("REMOVE_REDUNDANT_MATERIALS", false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::REMOVE_REDUNDANT_MATERIALS;
	if (metaFile.GetOrDefault("FIX_INFACING_NORMALS",		false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::FIX_INFACING_NORMALS;
	if (metaFile.GetOrDefault("SORT_BY_PTYPE",				false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::SORT_BY_PTYPE;
	if (metaFile.GetOrDefault("FIND_DEGENERATES",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::FIND_DEGENERATES;
	if (metaFile.GetOrDefault("FIND_INVALID_DATA",			true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::FIND_INVALID_DATA;
	if (metaFile.GetOrDefault("GEN_UV_COORDS",				true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::GEN_UV_COORDS;
	if (metaFile.GetOrDefault("TRANSFORM_UV_COORDS",		false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::TRANSFORM_UV_COORDS;
	if (metaFile.GetOrDefault("FIND_INSTANCES",				true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::FIND_INSTANCES;
	if (metaFile.GetOrDefault("OPTIMIZE_MESHES",			true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::OPTIMIZE_MESHES;
	if (metaFile.GetOrDefault("OPTIMIZE_GRAPH",				true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::OPTIMIZE_GRAPH;
	if (metaFile.GetOrDefault("FLIP_UVS",					false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::FLIP_UVS;
	if (metaFile.GetOrDefault("FLIP_WINDING_ORDER",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::FLIP_WINDING_ORDER;
	if (metaFile.GetOrDefault("SPLIT_BY_BONE_COUNT",		false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::SPLIT_BY_BONE_COUNT;
	if (metaFile.GetOrDefault("DEBONE",						true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::DEBONE;
	if (metaFile.GetOrDefault("GLOBAL_SCALE",				true))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::GLOBAL_SCALE;
	if (metaFile.GetOrDefault("EMBED_TEXTURES",				false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::EMBED_TEXTURES;
	if (metaFile.GetOrDefault("FORCE_GEN_NORMALS",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::FORCE_GEN_NORMALS;
	if (metaFile.GetOrDefault("DROP_NORMALS",				false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::DROP_NORMALS;
	if (metaFile.GetOrDefault("GEN_BOUNDING_BOXES",			false))	flags |= GeRendering::Resources::Parsers::EModelParserFlags::GEN_BOUNDING_BOXES;

	return { flags };
}

GeRendering::Resources::Model* GeCore::ResourceManagement::ModelManager::CreateResource(const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);
	auto model = GeRendering::Resources::Loaders::ModelLoader::Create(realPath, GetAssetMetadata(realPath));
	if (model)
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(model) + offsetof(GeRendering::Resources::Model, path)) = p_path; // Force the resource path to fit the given path

	return model;
}

void GeCore::ResourceManagement::ModelManager::DestroyResource(GeRendering::Resources::Model* p_resource)
{
	GeRendering::Resources::Loaders::ModelLoader::Destroy(p_resource);
}

void GeCore::ResourceManagement::ModelManager::ReloadResource(GeRendering::Resources::Model* p_resource, const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);
	GeRendering::Resources::Loaders::ModelLoader::Reload(*p_resource, realPath, GetAssetMetadata(realPath));
}
