#pragma once

#include <string>
#include <unordered_map>


namespace GeUtils::Filesystem
{
  //IniFile 类表示一个文件 .ini，它存储一组可以读取和写入的属性/值
	class IniFile final
	{
	public:
		using AttributePair = std::pair<std::string, std::string>;
		using AttributeMap = std::unordered_map<std::string, std::string>;

    //通过解析给定的文件路径并提取键/值对以供将来使用来创建 IniFile
		IniFile(const std::string& p_filePath);

    //通过重新加载文件覆盖当前数据的内容
		void Reload();

    //用当前值重写整个 .ini 文件。
    //.ini 文件中的任何注释或换行符都将被销毁
		void Rewrite() const;

    //返回附加到给定键的值,如果key不存在，返回默认值（0, false, "NULL"）
		template<typename T>
		T Get(const std::string& p_key);

    //返回附加到给定键的值
		template<typename T>
		T GetOrDefault(const std::string& p_key, T p_default);

    //为给定键设置一个新值（在调用 Rewrite() 或 Save() 之前不会应用于真实文件）
		template<typename T>
		bool Set(const std::string& p_key, const T& p_value);

    //向 IniFile 对象添加一个新的键/值（在调用 Rewrite() 或 Save() 之前不会应用于真实文件）
		template<typename T>
		bool Add(const std::string& p_key, const T& p_value);

    //删除由给定键标识的键/值对（直到调用 Rewrite() 或 Save() 才应用于真实文件）
		bool Remove(const std::string& p_key);

		//删除所有键/值对（直到调用 Rewrite() 或 Save() 才应用于真实文件）
		void RemoveAll();

		//验证给定的key是否存在
		bool IsKeyExisting(const std::string& p_key) const;

    //获取ini文件中存储的内容作为字符串向量（每个字符串对应一个属性对：Attribute=Value
		std::vector<std::string> GetFormattedContent() const;

	private:
		void RegisterPair(const std::string& p_key, const std::string& p_value);
		void RegisterPair(const AttributePair& p_pair);

		void Load();

		AttributePair	ExtractKeyAndValue(const std::string& p_attributeLine)  const;
		bool  IsValidLine(const std::string& p_attributeLine) const;
		bool  StringToBoolean(const std::string& p_value) const;

	private:
		std::string  m_filePath;
		AttributeMap m_data;
	};
}

#include "GeUtils/Filesystem/IniFile.inl"
