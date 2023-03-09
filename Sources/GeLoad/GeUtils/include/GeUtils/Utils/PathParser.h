#pragma once

#include <string>


namespace GeUtils::Utils
{
  class PathParser
  {
  public:
    enum class EFileType
    {
      UNKNOWN,
      MODEL,
      TEXTURE,
      SHADER,
      MATERIAL,
      SOUND,
      SCENE,
      SCRIPT,
      FONT
    };

    PathParser() = delete;

    //返回给定路径的 windows 样式版本（'/' 替换为 '\\'）
    static std::string MakeWindowsStyle(const std::string& p_path);

    //返回给定路径的非 Windows 样式版本（'\\' 替换为 '/'）
    static std::string MakeNonWindowsStyle(const std::string& p_path);

    //返回由给定路径标识的文件或文件夹的包含文件夹
    static std::string GetContainingFolder(const std::string& p_path);

    //返回给定路径标识的文件或文件夹的名称
    static std::string GetElementName(const std::string& p_path);

    //返回给定路径标识的文件或文件夹的扩展名
    static std::string GetExtension(const std::string& p_path);

    //将 EFileType 值转换为字符串
    static std::string FileTypeToString(EFileType p_fileType);

    //返回给定路径标识的文件的文件类型
    static EFileType GetFileType(const std::string& p_path);
  };
}
