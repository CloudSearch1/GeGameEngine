#pragma once

#include <string>

#include <GeUI/Types/Color.h>

#include <GeMaths/FVector2.h>
#include <GeMaths/FVector3.h>
#include <GeMaths/FVector4.h>
#include <GeMaths/FQuaternion.h>
#include <GeUtils/Filesystem/tinyxml2.h>



namespace GeRendering::Resources
{
	class Model;
	class Texture;
	class Shader;
}

namespace GeAudio::Resources
{
	class Sound;
}

namespace GeCore::Resources
{
	class Material;
}

namespace GeCore::Helpers
{
	class Serializer
	{
	public:
		#pragma region SERIALIZATION_HELPERS
		static void SerializeBoolean(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool p_value);
		static void SerializeString(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const std::string& p_value);
		static void SerializeFloat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float p_value);
		static void SerializeDouble(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double p_value);
		static void SerializeInt(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int p_value);
		static void SerializeUint(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, unsigned p_value);
		static void SerializeInt64(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t p_value);
		static void SerializeVec2(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const GeMaths::FVector2& p_value);
		static void SerializeVec3(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const GeMaths::FVector3& p_value);
		static void SerializeVec4(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const GeMaths::FVector4& p_value);
		static void SerializeQuat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const GeMaths::FQuaternion& p_value);
		static void SerializeColor(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const GeUI::Types::Color& p_value);
		static void SerializeModel(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeRendering::Resources::Model* p_value);
		static void SerializeTexture(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeRendering::Resources::Texture* p_value);
		static void SerializeShader(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeRendering::Resources::Shader* p_value);
		static void SerializeMaterial(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeCore::Resources::Material* p_value);
		static void SerializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeAudio::Resources::Sound* p_value);
		#pragma endregion

		#pragma region DESERIALIZATION_HELPERS
		static void DeserializeBoolean(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool& p_out);
		static void DeserializeString(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, std::string& p_out);
		static void DeserializeFloat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float& p_out);
		static void DeserializeDouble(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double& p_out);
		static void DeserializeInt(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int& p_out);
		static void DeserializeUint(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, unsigned& p_out);
		static void DeserializeInt64(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t& p_out);
		static void DeserializeVec2(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeMaths::FVector2& p_out);
		static void DeserializeVec3(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeMaths::FVector3& p_out);
		static void DeserializeVec4(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeMaths::FVector4& p_out);
		static void DeserializeQuat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeMaths::FQuaternion& p_out);
		static void DeserializeColor(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeUI::Types::Color& p_out);
		static void DeserializeModel(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeRendering::Resources::Model*& p_out);
		static void DeserializeTexture(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeRendering::Resources::Texture*& p_out);
		static void DeserializeShader(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeRendering::Resources::Shader*& p_out);
		static void DeserializeMaterial(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeCore::Resources::Material *& p_out);
		static void DeserializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeAudio::Resources::Sound*& p_out);

		static bool DeserializeBoolean(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static std::string DeserializeString(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static float DeserializeFloat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static double DeserializeDouble(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static int DeserializeInt(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static unsigned DeserializeUint(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static int64_t DeserializeInt64(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeMaths::FVector2 DeserializeVec2(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeMaths::FVector3 DeserializeVec3(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeMaths::FVector4 DeserializeVec4(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeMaths::FQuaternion DeserializeQuat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeUI::Types::Color DeserializeColor(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeRendering::Resources::Model* DeserializeModel(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeRendering::Resources::Texture* DeserializeTexture(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeRendering::Resources::Shader* DeserializeShader(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeCore::Resources::Material* DeserializeMaterial(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static GeAudio::Resources::Sound* DeserializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		#pragma endregion
	};
}
