#include"GeUtils/Filesystem/File.h"

#include <filesystem>
#include <fstream>
namespace GeUtils::Filesystem
{
  template<typename T>
  T File::Get(const std::string& p_key)
  {
    if constexpr (std::is_same<bool, T>::value)
    {
      if (!IsKeyExisting(p_key))
        return false;

      return StringToBoolean(m_data[p_key]);
    }
    else if constexpr (std::is_same<std::string, T>::value)
    {
      if (!IsKeyExisting(p_key))
        return std::string("NULL");

      return m_data[p_key];
    }
    else if constexpr (std::is_integral<T>::value)
    {
      if (!IsKeyExisting(p_key))
        return static_cast<T>(0);

      return static_cast<T>(std::atoi(m_data[p_key].c_str()));
    }
    else if constexpr (std::is_floating_point<T>::value)
    {
      if (!IsKeyExisting(p_key))
        return static_cast<T>(0.0f);

      return static_cast<T>(std::atof(m_data[p_key].c_str()));
    }
    else
    {
      static_assert(false, "The given type must be : bool, integral, floating point or string");
      return T();
    }
  }

  template<typename T>
  T File::GetOrDefault(const std::string& p_key, T p_default)
  {
    return IsKeyExisting(p_key) ? Get<T>(p_key) : p_default;
  }

  template<typename T>
  bool File::Set(const std::string& p_key, const T& p_value)
  {
    if (IsKeyExisting(p_key))
    {
      if constexpr (std::is_same<bool, T>::value)
      {
        m_data[p_key] = p_value ? "true" : "false";
      }
      else if constexpr (std::is_same<std::string, T>::value)
      {
        m_data[p_key] = p_value;
      }
      else if constexpr (std::is_integral<T>::value)
      {
        m_data[p_key] = std::to_string(p_value);
      }
      else if constexpr (std::is_floating_point<T>::value)
      {
        m_data[p_key] = std::to_string(p_value);
      }
      else
      {
        static_assert(false, "The given type must be : bool, integral, floating point or string");
      }

      return true;
    }

    return false;
  }

  template<typename T>
  bool File::Add(const std::string& p_key, const T& p_value)
  {
    if (!IsKeyExisting(p_key))
    {
      if constexpr (std::is_same<bool, T>::value)
      {
        RegisterPair(p_key, p_value ? "true" : "false");
      }
      else if constexpr (std::is_same<std::string, T>::value)
      {
        RegisterPair(p_key, p_value);
      }
      else if constexpr (std::is_integral<T>::value)
      {
        RegisterPair(p_key, std::to_string(p_value));
      }
      else if constexpr (std::is_floating_point<T>::value)
      {
        RegisterPair(p_key, std::to_string(p_value));
      }
      else
      {
        static_assert(false, "The given type must be : bool, integral, floating point or std::string");
      }

      return true;
    }

    return false;
  }


  Filesystem::File::File(const std::string& p_filePath)
    : m_filePath(p_filePath)
  {
    Load();
  }

  void File::Reload()
  {
    RemoveAll();
    Load();
  }

  bool File::Remove(const std::string& p_key)
  {
    if (IsKeyExisting(p_key))
    {
      m_data.erase(p_key);
      return true;
    }

    return false;
  }

  void File::RemoveAll()
  {
    m_data.clear();
  }

  bool File::IsKeyExisting(const std::string& p_key) const
  {
    return m_data.find(p_key) != m_data.end();
  }

  void File::RegisterPair(const std::string& p_key, const std::string& p_value)
  {
    RegisterPair(std::make_pair(p_key, p_value));
  }

  void File::RegisterPair(const AttributePair& p_pair)
  {
    m_data.insert(p_pair);
  }

  std::vector<std::string> File::GetFormattedContent() const
  {
    std::vector<std::string> result;

    for (const auto& [key, value] : m_data)
      result.push_back(key + "=" + value);

    return result;
  }

  void File::Load()
  {
    std::fstream File;
    File.open(m_filePath);

    if (File.is_open())
    {
      std::string currentLine;

      while (std::getline(File, currentLine))
      {
        if (IsValidLine(currentLine))
        {
          currentLine.erase(std::remove_if(currentLine.begin(), currentLine.end(), isspace), currentLine.end());
          RegisterPair(ExtractKeyAndValue(currentLine));
        }
      }

      File.close();
    }
  }

  void File::Rewrite() const
  {
    std::ofstream outfile;
    outfile.open(m_filePath, std::ios_base::trunc);

    if (outfile.is_open())
    {
      for (const auto& [key, value] : m_data)
        outfile << key << "=" << value << std::endl;
    }

    outfile.close();
  }

  std::pair<std::string, std::string> File::ExtractKeyAndValue(const std::string& p_line) const
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

  bool File::IsValidLine(const std::string& p_attributeLine) const
  {
    if (p_attributeLine.size() == 0)
      return false;

    if (p_attributeLine[0] == '#' || p_attributeLine[0] == ';' || p_attributeLine[0] == '[')
      return false;

    if (std::count(p_attributeLine.begin(), p_attributeLine.end(), '=') != 1)
      return false;

    return true;
  }

  bool File::StringToBoolean(const std::string& p_value) const
  {
    return (p_value == "1" || p_value == "T" || p_value == "t" || p_value == "True" || p_value == "true");
  }

}
