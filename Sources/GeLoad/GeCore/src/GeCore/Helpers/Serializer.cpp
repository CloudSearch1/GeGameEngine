#include "GeCore/ResourceManagement/TextureManager.h"
#include "GeCore/ResourceManagement/ModelManager.h"
#include "GeCore/ResourceManagement/ShaderManager.h"
#include "GeCore/ResourceManagement/MaterialManager.h"
#include "GeCore/ResourceManagement/SoundManager.h"
#include "GeCore/Global/ServiceLocator.h"
#include "GeCore/Helpers/Serializer.h"

void GeCore::Helpers::Serializer::SerializeBoolean(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, bool p_value)
{
	tinyxml2::XMLElement* element = p_doc.NewElement(p_name.c_str());
	element->SetText(p_value);
	p_node->InsertEndChild(element);
}

void GeCore::Helpers::Serializer::SerializeString(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, const std::string & p_value)
{
	tinyxml2::XMLElement* element = p_doc.NewElement(p_name.c_str());
	element->SetText(p_value.c_str());
	p_node->InsertEndChild(element);
}

void GeCore::Helpers::Serializer::SerializeFloat(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, float p_value)
{
	tinyxml2::XMLElement* element = p_doc.NewElement(p_name.c_str());
	element->SetText(p_value);
	p_node->InsertEndChild(element);
}

void GeCore::Helpers::Serializer::SerializeDouble(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, double p_value)
{
	tinyxml2::XMLElement* element = p_doc.NewElement(p_name.c_str());
	element->SetText(p_value);
	p_node->InsertEndChild(element);
}

void GeCore::Helpers::Serializer::SerializeInt(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, int p_value)
{
	tinyxml2::XMLElement* element = p_doc.NewElement(p_name.c_str());
	element->SetText(p_value);
	p_node->InsertEndChild(element);
}

void GeCore::Helpers::Serializer::SerializeUint(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, unsigned p_value)
{
	tinyxml2::XMLElement* element = p_doc.NewElement(p_name.c_str());
	element->SetText(p_value);
	p_node->InsertEndChild(element);
}

void GeCore::Helpers::Serializer::SerializeInt64(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, int64_t p_value)
{
	tinyxml2::XMLElement* element = p_doc.NewElement(p_name.c_str());
	element->SetText(p_value);
	p_node->InsertEndChild(element);
}

void GeCore::Helpers::Serializer::SerializeVec2(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, const GeMaths::FVector2 & p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);
}

void GeCore::Helpers::Serializer::SerializeVec3(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, const GeMaths::FVector3 & p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = p_doc.NewElement("z");
	z->SetText(p_value.z);
	element->InsertEndChild(z);
}

void GeCore::Helpers::Serializer::SerializeVec4(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, const GeMaths::FVector4 & p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = p_doc.NewElement("z");
	z->SetText(p_value.z);
	element->InsertEndChild(z);

	tinyxml2::XMLElement* w = p_doc.NewElement("w");
	w->SetText(p_value.w);
	element->InsertEndChild(w);
}

void GeCore::Helpers::Serializer::SerializeQuat(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, const GeMaths::FQuaternion & p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* x = p_doc.NewElement("x");
	x->SetText(p_value.x);
	element->InsertEndChild(x);

	tinyxml2::XMLElement* y = p_doc.NewElement("y");
	y->SetText(p_value.y);
	element->InsertEndChild(y);

	tinyxml2::XMLElement* z = p_doc.NewElement("z");
	z->SetText(p_value.z);
	element->InsertEndChild(z);

	tinyxml2::XMLElement* w = p_doc.NewElement("w");
	w->SetText(p_value.w);
	element->InsertEndChild(w);
}

void GeCore::Helpers::Serializer::SerializeColor(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, const GeUI::Types::Color & p_value)
{
	tinyxml2::XMLNode* element = p_doc.NewElement(p_name.c_str());
	p_node->InsertEndChild(element);

	tinyxml2::XMLElement* r = p_doc.NewElement("r");
	r->SetText(p_value.r);
	element->InsertEndChild(r);

	tinyxml2::XMLElement* g = p_doc.NewElement("g");
	g->SetText(p_value.g);
	element->InsertEndChild(g);

	tinyxml2::XMLElement* b = p_doc.NewElement("b");
	b->SetText(p_value.b);
	element->InsertEndChild(b);

	tinyxml2::XMLElement* a = p_doc.NewElement("a");
	a->SetText(p_value.a);
	element->InsertEndChild(a);
}

void GeCore::Helpers::Serializer::SerializeModel(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeRendering::Resources::Model * p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->path : "?");
}

void GeCore::Helpers::Serializer::SerializeTexture(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeRendering::Resources::Texture * p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->path : "?");
}

void GeCore::Helpers::Serializer::SerializeShader(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeRendering::Resources::Shader * p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->path : "?");
}

void GeCore::Helpers::Serializer::DeserializeBoolean(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, bool & p_out)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryBoolText(&p_out);
}

void GeCore::Helpers::Serializer::SerializeMaterial(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeCore::Resources::Material * p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->path : "?");
}

void GeCore::Helpers::Serializer::SerializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeAudio::Resources::Sound* p_value)
{
	SerializeString(p_doc, p_node, p_name.c_str(), p_value ? p_value->path : "?");
}

void GeCore::Helpers::Serializer::DeserializeString(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, std::string & p_out)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
	{
		const char* result = element->GetText();
		p_out = result ? result : "";
	}
}

void GeCore::Helpers::Serializer::DeserializeFloat(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, float & p_out)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryFloatText(&p_out);
}

void GeCore::Helpers::Serializer::DeserializeDouble(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, double & p_out)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryDoubleText(&p_out);
}

void GeCore::Helpers::Serializer::DeserializeInt(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, int & p_out)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryIntText(&p_out);
}

void GeCore::Helpers::Serializer::DeserializeUint(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, unsigned & p_out)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryUnsignedText(&p_out);
}

void GeCore::Helpers::Serializer::DeserializeInt64(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, int64_t & p_out)
{
	if (auto element = p_node->FirstChildElement(p_name.c_str()); element)
		element->QueryInt64Text(&p_out);
}

void GeCore::Helpers::Serializer::DeserializeVec2(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeMaths::FVector2 & p_out)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_out.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_out.y);
	}
}

void GeCore::Helpers::Serializer::DeserializeVec3(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeMaths::FVector3 & p_out)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_out.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_out.y);

		if (auto element = node->FirstChildElement("z"); element)
			element->QueryFloatText(&p_out.z);
	}
}

void GeCore::Helpers::Serializer::DeserializeVec4(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeMaths::FVector4 & p_out)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_out.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_out.y);

		if (auto element = node->FirstChildElement("z"); element)
			element->QueryFloatText(&p_out.z);

		if (auto element = node->FirstChildElement("w"); element)
			element->QueryFloatText(&p_out.w);
	}
}

void GeCore::Helpers::Serializer::DeserializeQuat(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeMaths::FQuaternion & p_out)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("x"); element)
			element->QueryFloatText(&p_out.x);

		if (auto element = node->FirstChildElement("y"); element)
			element->QueryFloatText(&p_out.y);

		if (auto element = node->FirstChildElement("z"); element)
			element->QueryFloatText(&p_out.z);

		if (auto element = node->FirstChildElement("w"); element)
			element->QueryFloatText(&p_out.w);
	}
}

void GeCore::Helpers::Serializer::DeserializeColor(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeUI::Types::Color & p_out)
{
	if (auto node = p_node->FirstChildElement(p_name.c_str()); node)
	{
		if (auto element = node->FirstChildElement("r"); element)
			element->QueryFloatText(&p_out.r);

		if (auto element = node->FirstChildElement("g"); element)
			element->QueryFloatText(&p_out.g);

		if (auto element = node->FirstChildElement("b"); element)
			element->QueryFloatText(&p_out.b);

		if (auto element = node->FirstChildElement("q"); element)
			element->QueryFloatText(&p_out.a);
	}
}

void GeCore::Helpers::Serializer::DeserializeModel(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeRendering::Resources::Model *& p_out)
{
	if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
		p_out = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::ModelManager>().GetResource(path);
	else
		p_out = nullptr;
}

void GeCore::Helpers::Serializer::DeserializeTexture(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeRendering::Resources::Texture *& p_out)
{
	if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
		p_out = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::TextureManager>().GetResource(path);
	else
		p_out = nullptr;
}

void GeCore::Helpers::Serializer::DeserializeShader(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeRendering::Resources::Shader *& p_out)
{
	if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
		p_out = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::ShaderManager>().GetResource(path);
	else
		p_out = nullptr;
}

void GeCore::Helpers::Serializer::DeserializeMaterial(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name, GeCore::Resources::Material *& p_out)
{
	if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
		p_out = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::MaterialManager>().GetResource(path);
	else
		p_out = nullptr;
}

void GeCore::Helpers::Serializer::DeserializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, GeAudio::Resources::Sound*& p_out)
{
	if (std::string path = DeserializeString(p_doc, p_node, p_name.c_str()); path != "?" && path != "")
		p_out = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::SoundManager>().GetResource(path);
	else
		p_out = nullptr;
}

bool GeCore::Helpers::Serializer::DeserializeBoolean(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	bool result;
	DeserializeBoolean(p_doc, p_node, p_name, result);
	return result;
}

std::string GeCore::Helpers::Serializer::DeserializeString(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	std::string result;
	DeserializeString(p_doc, p_node, p_name, result);
	return result;
}

float GeCore::Helpers::Serializer::DeserializeFloat(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	float result;
	DeserializeFloat(p_doc, p_node, p_name, result);
	return result;
}

double GeCore::Helpers::Serializer::DeserializeDouble(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	double result;
	DeserializeDouble(p_doc, p_node, p_name, result);
	return result;
}

int GeCore::Helpers::Serializer::DeserializeInt(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	int result;
	DeserializeInt(p_doc, p_node, p_name, result);
	return result;
}

unsigned GeCore::Helpers::Serializer::DeserializeUint(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	unsigned result;
	DeserializeUint(p_doc, p_node, p_name, result);
	return result;
}

int64_t GeCore::Helpers::Serializer::DeserializeInt64(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	int64_t result;
	DeserializeInt64(p_doc, p_node, p_name, result);
	return result;
}

GeMaths::FVector2 GeCore::Helpers::Serializer::DeserializeVec2(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeMaths::FVector2 result;
	DeserializeVec2(p_doc, p_node, p_name, result);
	return result;
}

GeMaths::FVector3 GeCore::Helpers::Serializer::DeserializeVec3(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeMaths::FVector3 result;
	DeserializeVec3(p_doc, p_node, p_name, result);
	return result;
}

GeMaths::FVector4 GeCore::Helpers::Serializer::DeserializeVec4(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeMaths::FVector4 result;
	DeserializeVec4(p_doc, p_node, p_name, result);
	return result;
}

GeMaths::FQuaternion GeCore::Helpers::Serializer::DeserializeQuat(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeMaths::FQuaternion result;
	DeserializeQuat(p_doc, p_node, p_name, result);
	return result;
}

GeUI::Types::Color GeCore::Helpers::Serializer::DeserializeColor(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeUI::Types::Color result;
	DeserializeColor(p_doc, p_node, p_name, result);
	return result;
}

GeRendering::Resources::Model* GeCore::Helpers::Serializer::DeserializeModel(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeRendering::Resources::Model* result;
	DeserializeModel(p_doc, p_node, p_name, result);
	return result;
}

GeRendering::Resources::Texture* GeCore::Helpers::Serializer::DeserializeTexture(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeRendering::Resources::Texture* result;
	DeserializeTexture(p_doc, p_node, p_name, result);
	return result;
}

GeRendering::Resources::Shader* GeCore::Helpers::Serializer::DeserializeShader(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeRendering::Resources::Shader* result;
	DeserializeShader(p_doc, p_node, p_name, result);
	return result;
}

GeCore::Resources::Material * GeCore::Helpers::Serializer::DeserializeMaterial(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node, const std::string & p_name)
{
	GeCore::Resources::Material* result;
	DeserializeMaterial(p_doc, p_node, p_name, result);
	return result;
}

GeAudio::Resources::Sound* GeCore::Helpers::Serializer::DeserializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name)
{
	GeAudio::Resources::Sound* result;
	DeserializeSound(p_doc, p_node, p_name, result);
	return result;
}
