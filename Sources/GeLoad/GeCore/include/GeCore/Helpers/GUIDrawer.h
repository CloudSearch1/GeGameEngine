#pragma once

#include <GeMaths/FVector2.h>
#include <GeMaths/FVector3.h>
#include <GeMaths/FVector4.h>
#include <GeMaths/FQuaternion.h>

#include <GeUI/Internal/WidgetContainer.h>
#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Drags/DragSingleScalar.h>
#include <GeUI/Widgets/Drags/DragMultipleScalars.h>
#include <GeUI/Widgets/InputFields/InputText.h>
#include <GeUI/Widgets/Visual/Image.h>
#include <GeUI/Types/Color.h>



namespace GeCore::Resources
{
	class Material;
}

namespace GeAudio::Resources
{
	class Sound;
}

namespace GeRendering::Resources
{
	class Model;
	class Shader;
	class Texture;
}

namespace GeCore::Helpers
{
  //提供一些绘制UI元素的助手
	class GUIDrawer
	{
	public:
		static const GeUI::Types::Color TitleColor;
		static const GeUI::Types::Color ClearButtonColor;

		static const float _MIN_FLOAT;
		static const float _MAX_FLOAT;

    //定义纹理资源字段中没有纹理时使用的纹理
		static void ProvideEmptyTexture(GeRendering::Resources::Texture& p_emptyTexture);

    //用标题颜色绘制标题
		static void CreateTitle(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name);
	
		template <typename T>
		static void DrawScalar(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, T& p_data, float p_step = 1.f, T p_min = std::numeric_limits<T>::min(), T p_max = std::numeric_limits<T>::max());
		static void DrawBoolean(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, bool& p_data);
		static void DrawVec2(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeMaths::FVector2& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawVec3(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeMaths::FVector3& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawVec4(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeMaths::FVector4& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawQuat(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeMaths::FQuaternion& p_data, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawString(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::string& p_data);
		static void DrawColor(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeUI::Types::Color& p_color, bool p_hasAlpha = false);
		static GeUI::Widgets::Texts::Text& DrawMesh(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeRendering::Resources::Model*& p_data, GeUtils::Eventing::Event<>* p_updateNotifier = nullptr);
		static GeUI::Widgets::Visual::Image& DrawTexture(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeRendering::Resources::Texture*& p_data, GeUtils::Eventing::Event<>* p_updateNotifier = nullptr);
		static GeUI::Widgets::Texts::Text& DrawShader(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeRendering::Resources::Shader*& p_data, GeUtils::Eventing::Event<>* p_updateNotifier = nullptr);
		static GeUI::Widgets::Texts::Text& DrawMaterial(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeCore::Resources::Material*& p_data, GeUtils::Eventing::Event<>* p_updateNotifier = nullptr);
		static GeUI::Widgets::Texts::Text& DrawSound(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeAudio::Resources::Sound*& p_data, GeUtils::Eventing::Event<>* p_updateNotifier = nullptr);
		static GeUI::Widgets::Texts::Text& DrawAsset(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::string& p_data, GeUtils::Eventing::Event<>* p_updateNotifier = nullptr);

		template <typename T>
		static void DrawScalar(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<T(void)> p_gatherer, std::function<void(T)> p_provider, float p_step = 1.f, T p_min = std::numeric_limits<T>::min(), T p_max = std::numeric_limits<T>::max());
		static void DrawBoolean(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<bool(void)> p_gatherer, std::function<void(bool)> p_provider);
		static void DrawVec2(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<GeMaths::FVector2(void)> p_gatherer, std::function<void(GeMaths::FVector2)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawVec3(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<GeMaths::FVector3(void)> p_gatherer, std::function<void(GeMaths::FVector3)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawVec4(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<GeMaths::FVector4(void)> p_gatherer, std::function<void(GeMaths::FVector4)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawQuat(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<GeMaths::FQuaternion(void)> p_gatherer, std::function<void(GeMaths::FQuaternion)> p_provider, float p_step = 1.f, float p_min = _MIN_FLOAT, float p_max = _MAX_FLOAT);
		static void DrawDDString(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<std::string(void)> p_gatherer, std::function<void(std::string)> p_provider, const std::string& p_identifier);
		static void DrawString(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<std::string(void)> p_gatherer, std::function<void(std::string)> p_provider);
		static void DrawColor(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::function<GeUI::Types::Color(void)> p_gatherer, std::function<void(GeUI::Types::Color)> p_provider, bool p_hasAlpha = false);

		template <typename T>
		static ImGuiDataType_ GetDataType();

		template <typename T>
		static std::string GetFormat();

	private:
		static GeRendering::Resources::Texture* __EMPTY_TEXTURE;
	};
}

#include "GeCore/Helpers/GUIDrawer.inl"
