#include <algorithm>

#include "GeUtils/Utils/PathParser.h"

std::string GeUtils::Utils::PathParser::MakeWindowsStyle(const std::string & p_path)
{
	std::string result;
	result.resize(p_path.size());

	for (size_t i = 0; i < p_path.size(); ++i)
		result[i] = p_path[i] == '/' ? '\\' : p_path[i];

	return result;
}

std::string GeUtils::Utils::PathParser::MakeNonWindowsStyle(const std::string & p_path)
{
	std::string result;
	result.resize(p_path.size());

	for (size_t i = 0; i < p_path.size(); ++i)
		result[i] = p_path[i] == '\\' ? '/' : p_path[i];

	return result;
}

std::string GeUtils::Utils::PathParser::GetContainingFolder(const std::string & p_path)
{
	std::string result;

	bool extraction = false;

	for (auto it = p_path.rbegin(); it != p_path.rend(); ++it)
	{
		if (extraction)
			result += *it;

		if (!extraction && it != p_path.rbegin() && (*it == '\\' || *it == '/'))
			extraction = true;
	}

	std::reverse(result.begin(), result.end());

	if (!result.empty() && result.back() != '\\')
		result += '\\';

	return result;
}

std::string GeUtils::Utils::PathParser::GetElementName(const std::string & p_path)
{
	std::string result;

	std::string path = p_path;
	if (!path.empty() && path.back() == '\\')
		path.pop_back();

	for (auto it = path.rbegin(); it != path.rend() && *it != '\\' && *it != '/'; ++it)
		result += *it;

	std::reverse(result.begin(), result.end());

	return result;
}

std::string GeUtils::Utils::PathParser::GetExtension(const std::string & p_path)
{
	std::string result;

	for (auto it = p_path.rbegin(); it != p_path.rend() && *it != '.'; ++it)
		result += *it;

	std::reverse(result.begin(), result.end());

	return result;
}

std::string GeUtils::Utils::PathParser::FileTypeToString(EFileType p_fileType)
{
	switch (p_fileType)
	{
	case GeUtils::Utils::PathParser::EFileType::MODEL:		return "Model";
	case GeUtils::Utils::PathParser::EFileType::TEXTURE:	return "Texture";
	case GeUtils::Utils::PathParser::EFileType::SHADER:		return "Shader";
	case GeUtils::Utils::PathParser::EFileType::MATERIAL:	return "Material";
	case GeUtils::Utils::PathParser::EFileType::SOUND:		return "Sound";
	case GeUtils::Utils::PathParser::EFileType::SCENE:		return "Scene";
	case GeUtils::Utils::PathParser::EFileType::SCRIPT:		return "Script";
	case GeUtils::Utils::PathParser::EFileType::FONT:		return "Font";
	}

	return "Unknown";
}

GeUtils::Utils::PathParser::EFileType GeUtils::Utils::PathParser::GetFileType(const std::string & p_path)
{
	std::string ext = GetExtension(p_path);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	if (ext == "fbx" || ext == "obj")											return EFileType::MODEL;
	else if (ext == "png" || ext == "jpeg" || ext == "jpg" || ext == "tga")		return EFileType::TEXTURE;
	else if (ext == "glsl")														return EFileType::SHADER;
	else if (ext == "ovmat")													return EFileType::MATERIAL;
	else if (ext == "wav" || ext == "mp3" || ext == "ogg")						return EFileType::SOUND;
	else if (ext == "ovscene")													return EFileType::SCENE;
	else if (ext == "lua")														return EFileType::SCRIPT;
	else if (ext == "ttf")														return EFileType::FONT;

	return EFileType::UNKNOWN;
}