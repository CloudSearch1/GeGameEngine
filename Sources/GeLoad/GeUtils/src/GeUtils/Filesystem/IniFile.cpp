#include "GeUtils/Filesystem/IniFile.h"

#include <filesystem>
#include <fstream>

GeUtils::Filesystem::IniFile::IniFile(const std::string& p_filePath) : m_filePath(p_filePath)
{
	Load();
}

void GeUtils::Filesystem::IniFile::Reload()
{
	RemoveAll();
	Load();
}

bool GeUtils::Filesystem::IniFile::Remove(const std::string & p_key)
{
	if (IsKeyExisting(p_key))
	{
		m_data.erase(p_key);
		return true;
	}

	return false;
}

void GeUtils::Filesystem::IniFile::RemoveAll()
{
	m_data.clear();
}

bool GeUtils::Filesystem::IniFile::IsKeyExisting(const std::string& p_key) const
{
	return m_data.find(p_key) != m_data.end();
}

void GeUtils::Filesystem::IniFile::RegisterPair(const std::string& p_key, const std::string& p_value)
{
	RegisterPair(std::make_pair(p_key, p_value));
}

void GeUtils::Filesystem::IniFile::RegisterPair(const AttributePair& p_pair)
{
	m_data.insert(p_pair);
}

std::vector<std::string> GeUtils::Filesystem::IniFile::GetFormattedContent() const
{
	std::vector<std::string> result;

	for (const auto&[key, value] : m_data)
		result.push_back(key + "=" + value);

	return result;
}

void GeUtils::Filesystem::IniFile::Load()
{
	std::fstream iniFile;
	iniFile.open(m_filePath);

	if (iniFile.is_open())
	{
		std::string currentLine;

		while (std::getline(iniFile, currentLine))
		{
			if (IsValidLine(currentLine))
			{
				currentLine.erase(std::remove_if(currentLine.begin(), currentLine.end(), isspace), currentLine.end());
				RegisterPair(ExtractKeyAndValue(currentLine));
			}
		}

		iniFile.close();
	}
}

void GeUtils::Filesystem::IniFile::Rewrite() const
{
	std::ofstream outfile;
	outfile.open(m_filePath, std::ios_base::trunc);

	if (outfile.is_open())
	{
		for (const auto&[key, value] : m_data)
			outfile << key << "=" << value << std::endl;
	}

	outfile.close();
}

std::pair<std::string, std::string> GeUtils::Filesystem::IniFile::ExtractKeyAndValue(const std::string& p_line) const
{
	std::string key;
	std::string value;

	std::string* currentBuffer = &key;

	for (auto& c : p_line)
	{
		if (c == '=')
			currentBuffer = &value;
		else
			currentBuffer->push_back(c);
	}

	return std::make_pair(key, value);
}

bool GeUtils::Filesystem::IniFile::IsValidLine(const std::string & p_attributeLine) const
{
	if (p_attributeLine.size() == 0)
		return false;
	
	if (p_attributeLine[0] == '#' || p_attributeLine[0] == ';' || p_attributeLine[0] == '[')
		return false;
	
	if (std::count(p_attributeLine.begin(), p_attributeLine.end(), '=') != 1)
		return false;

	return true;
}

bool GeUtils::Filesystem::IniFile::StringToBoolean(const std::string & p_value) const
{
	return (p_value == "1" || p_value == "T" || p_value == "t" || p_value == "True" || p_value == "true");
}
