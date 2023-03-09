#include"GeUtils/Utils/PathParser.h"

#include <algorithm>

namespace GeUtils::Utils
{
  std::string PathParser::MakeWindowsStyle(const std::string& p_path)
  {
    std::string result;
    result.resize(p_path.size());

    for (size_t i = 0; i < p_path.size(); ++i)
      result[i] = p_path[i] == '/' ? '\\' : p_path[i];

    return result;
  }

  std::string PathParser::MakeNonWindowsStyle(const std::string& p_path)
  {
    std::string result;
    result.resize(p_path.size());

    for (size_t i = 0; i < p_path.size(); ++i)
      result[i] = p_path[i] == '\\' ? '/' : p_path[i];

    return result;
  }

  std::string PathParser::GetContainingFolder(const std::string& p_path)
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

  std::string PathParser::GetElementName(const std::string& p_path)
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

  std::string PathParser::GetExtension(const std::string& p_path)
  {
    std::string result;

    for (auto it = p_path.rbegin(); it != p_path.rend() && *it != '.'; ++it)
      result += *it;

    std::reverse(result.begin(), result.end());

    return result;
  }

  std::string PathParser::FileTypeToString(EFileType p_fileType)
  {
    switch (p_fileType)
    {
    case PathParser::EFileType::MODEL:		return "Model";
    case PathParser::EFileType::TEXTURE:	return "Texture";
    case PathParser::EFileType::SHADER:		return "Shader";
    case PathParser::EFileType::MATERIAL:	return "Material";
    case PathParser::EFileType::SOUND:		return "Sound";
    case PathParser::EFileType::SCENE:		return "Scene";
    case PathParser::EFileType::SCRIPT:		return "Script";
    case PathParser::EFileType::FONT:		  return "Font";
    }

    return "Unknown";
  }

  PathParser::EFileType PathParser::GetFileType(const std::string& p_path)
  {
    std::string ext = GetExtension(p_path);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == "fbx" || ext == "obj")											return EFileType::MODEL;
    else if (ext == "png" || ext == "jpeg" || ext == "jpg" || ext == "tga")		return EFileType::TEXTURE;
    else if (ext == "glsl")														return EFileType::SHADER;
    //else if (ext == "ovmat")													return EFileType::MATERIAL;
    else if (ext == "material")													return EFileType::MATERIAL;
    else if (ext == "wav" || ext == "mp3" || ext == "ogg")						return EFileType::SOUND;
    //else if (ext == "ovscene")													return EFileType::SCENE;
    else if (ext == "scene")													return EFileType::SCENE;
    else if (ext == "lua")														return EFileType::SCRIPT;
    else if (ext == "ttf")														return EFileType::FONT;

    return EFileType::UNKNOWN;
  }

}
