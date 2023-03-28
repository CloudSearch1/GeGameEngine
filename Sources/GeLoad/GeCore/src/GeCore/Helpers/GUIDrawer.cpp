#include <array>

#include <GeUtils/Utils/PathParser.h>

#include <GeUI/Widgets/Texts/TextColored.h>
#include <GeUI/Widgets/Drags/DragSingleScalar.h>
#include <GeUI/Widgets/Drags/DragMultipleScalars.h>
#include <GeUI/Widgets/InputFields/InputText.h>
#include <GeUI/Widgets/Selection/ColorEdit.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Layout/Columns.h>
#include <GeUI/Widgets/Selection/CheckBox.h>
#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/Buttons/ButtonSmall.h>
#include <GeUI/Plugins/DDTarget.h>

#include <GeCore/Global/ServiceLocator.h>
#include <GeCore/ResourceManagement/ModelManager.h>
#include <GeCore/ResourceManagement/TextureManager.h>
#include <GeCore/ResourceManagement/ShaderManager.h>
#include <GeCore/ResourceManagement/MaterialManager.h>
#include <GeCore/ResourceManagement/SoundManager.h>

#include "GeCore/Helpers/GUIDrawer.h"

const GeUI::Types::Color GeCore::Helpers::GUIDrawer::TitleColor = { 0.85f, 0.65f, 0.0f };
const GeUI::Types::Color GeCore::Helpers::GUIDrawer::ClearButtonColor = { 0.5f, 0.0f, 0.0f };
const float GeCore::Helpers::GUIDrawer::_MIN_FLOAT = -999999999.f;
const float GeCore::Helpers::GUIDrawer::_MAX_FLOAT = +999999999.f;
GeRendering::Resources::Texture* GeCore::Helpers::GUIDrawer::__EMPTY_TEXTURE = nullptr;

void GeCore::Helpers::GUIDrawer::ProvideEmptyTexture(GeRendering::Resources::Texture& p_emptyTexture)
{
	__EMPTY_TEXTURE = &p_emptyTexture;
}

void GeCore::Helpers::GUIDrawer::CreateTitle(GeUI::Internal::WidgetContainer& p_root, const std::string & p_name)
{
	p_root.CreateWidget<GeUI::Widgets::Texts::TextColored>(p_name, TitleColor);
}

void GeCore::Helpers::GUIDrawer::DrawBoolean(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, bool & p_data)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Selection::CheckBox>();
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<bool>>();
	dispatcher.RegisterReference(reinterpret_cast<bool&>(p_data));
}

void GeCore::Helpers::GUIDrawer::DrawVec2(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeMaths::FVector2 & p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 2>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 2>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 2>&>(p_data));
}

void GeCore::Helpers::GUIDrawer::DrawVec3(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeMaths::FVector3 & p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 3>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 3>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 3>&>(p_data));
}

void GeCore::Helpers::GUIDrawer::DrawVec4(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeMaths::FVector4& p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 4>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(p_data));
}

void GeCore::Helpers::GUIDrawer::DrawQuat(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeMaths::FQuaternion & p_data, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 4>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(p_data));
}

void GeCore::Helpers::GUIDrawer::DrawString(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::string & p_data)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::InputFields::InputText>("");
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::string>>();
	dispatcher.RegisterReference(p_data);
}

void GeCore::Helpers::GUIDrawer::DrawColor(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeUI::Types::Color & p_color, bool p_hasAlpha)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Selection::ColorEdit>(p_hasAlpha);
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<GeUI::Types::Color>>();
	dispatcher.RegisterReference(p_color);
}

GeUI::Widgets::Texts::Text& GeCore::Helpers::GUIDrawer::DrawMesh(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeRendering::Resources::Model *& p_data, GeUtils::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<GeUI::Widgets::Texts::Text>(displayedText);

	widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (GeUtils::Utils::PathParser::GetFileType(p_receivedData.first) == GeUtils::Utils::PathParser::EFileType::MODEL)
		{
			if (auto resource = OVSERVICE(GeCore::ResourceManagement::ModelManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<GeUI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.content = "Empty";
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

GeUI::Widgets::Visual::Image& GeCore::Helpers::GUIDrawer::DrawTexture(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeRendering::Resources::Texture *& p_data, GeUtils::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<GeUI::Widgets::Visual::Image>(p_data ? p_data->id : (__EMPTY_TEXTURE ? __EMPTY_TEXTURE->id : 0), GeMaths::FVector2{ 75, 75 });

	widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (GeUtils::Utils::PathParser::GetFileType(p_receivedData.first) == GeUtils::Utils::PathParser::EFileType::TEXTURE)
		{
			if (auto resource = OVSERVICE(GeCore::ResourceManagement::TextureManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.textureID.id = resource->id;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<GeUI::Widgets::Buttons::Button>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.textureID.id = (__EMPTY_TEXTURE ? __EMPTY_TEXTURE->id : 0);
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

GeUI::Widgets::Texts::Text& GeCore::Helpers::GUIDrawer::DrawShader(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeRendering::Resources::Shader *& p_data, GeUtils::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<GeUI::Widgets::Texts::Text>(displayedText);

	widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (GeUtils::Utils::PathParser::GetFileType(p_receivedData.first) == GeUtils::Utils::PathParser::EFileType::SHADER)
		{
			if (auto resource = OVSERVICE(GeCore::ResourceManagement::ShaderManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<GeUI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.content = "Empty";
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

GeUI::Widgets::Texts::Text& GeCore::Helpers::GUIDrawer::DrawMaterial(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, GeCore::Resources::Material *& p_data, GeUtils::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<GeUI::Widgets::Texts::Text>(displayedText);

	widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (GeUtils::Utils::PathParser::GetFileType(p_receivedData.first) == GeUtils::Utils::PathParser::EFileType::MATERIAL)
		{
			if (auto resource = OVSERVICE(GeCore::ResourceManagement::MaterialManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<GeUI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.content = "Empty";
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

GeUI::Widgets::Texts::Text& GeCore::Helpers::GUIDrawer::DrawSound(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, GeAudio::Resources::Sound*& p_data, GeUtils::Eventing::Event<>* p_updateNotifier)
{
	CreateTitle(p_root, p_name);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto & rightSide = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

	auto & widget = rightSide.CreateWidget<GeUI::Widgets::Texts::Text>(displayedText);

	widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
	{
		if (GeUtils::Utils::PathParser::GetFileType(p_receivedData.first) == GeUtils::Utils::PathParser::EFileType::SOUND)
		{
			if (auto resource = OVSERVICE(GeCore::ResourceManagement::SoundManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
				if (p_updateNotifier)
					p_updateNotifier->Invoke();
			}
		}
	};

	widget.lineBreak = false;

	auto & resetButton = rightSide.CreateWidget<GeUI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
	{
		p_data = nullptr;
		widget.content = "Empty";
		if (p_updateNotifier)
			p_updateNotifier->Invoke();
	};

	return widget;
}

GeUI::Widgets::Texts::Text& GeCore::Helpers::GUIDrawer::DrawAsset(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name, std::string& p_data, GeUtils::Eventing::Event<>* p_updateNotifier)
{
    CreateTitle(p_root, p_name);

    const std::string displayedText = (p_data.empty() ? std::string("Empty") : p_data);
    auto& rightSide = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

    auto& widget = rightSide.CreateWidget<GeUI::Widgets::Texts::Text>(displayedText);

    widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data, p_updateNotifier](auto p_receivedData)
    {
        p_data = p_receivedData.first;
        widget.content = p_receivedData.first;
        if (p_updateNotifier)
            p_updateNotifier->Invoke();
    };

    widget.lineBreak = false;

    auto& resetButton = rightSide.CreateWidget<GeUI::Widgets::Buttons::ButtonSmall>("Clear");
    resetButton.idleBackgroundColor = ClearButtonColor;
    resetButton.ClickedEvent += [&widget, &p_data, p_updateNotifier]
    {
        p_data = "";
        widget.content = "Empty";
        if (p_updateNotifier)
            p_updateNotifier->Invoke();
    };

    return widget;
}

void GeCore::Helpers::GUIDrawer::DrawBoolean(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<bool(void)> p_gatherer, std::function<void(bool)> p_provider)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Selection::CheckBox>();
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<bool>>();

	dispatcher.RegisterGatherer([p_gatherer]()
	{
		bool value = p_gatherer();
		return reinterpret_cast<bool&>(value);
	});

	dispatcher.RegisterProvider([p_provider](bool p_value)
	{
		p_provider(reinterpret_cast<bool&>(p_value));
	});
}

void GeCore::Helpers::GUIDrawer::DrawVec2(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<GeMaths::FVector2(void)> p_gatherer, std::function<void(GeMaths::FVector2)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 2>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 2>>>();
	
	dispatcher.RegisterGatherer([p_gatherer]()
	{
		GeMaths::FVector2 value = p_gatherer();
		return reinterpret_cast<const std::array<float, 2>&>(value);
	});

	dispatcher.RegisterProvider([p_provider](std::array<float, 2> p_value)
	{
		p_provider(reinterpret_cast<GeMaths::FVector2&>(p_value));
	});
}

void GeCore::Helpers::GUIDrawer::DrawVec3(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<GeMaths::FVector3(void)> p_gatherer, std::function<void(GeMaths::FVector3)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 3>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 3>>>();

	dispatcher.RegisterGatherer([p_gatherer]()
	{
		GeMaths::FVector3 value = p_gatherer();
		return reinterpret_cast<const std::array<float, 3>&>(value);
	});

	dispatcher.RegisterProvider([p_provider](std::array<float, 3> p_value)
	{
		p_provider(reinterpret_cast<GeMaths::FVector3&>(p_value));
	});
}

void GeCore::Helpers::GUIDrawer::DrawVec4(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<GeMaths::FVector4(void)> p_gatherer, std::function<void(GeMaths::FVector4)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 4>>>();
	
	dispatcher.RegisterGatherer([p_gatherer]()
	{
		GeMaths::FVector4 value = p_gatherer();
		return reinterpret_cast<const std::array<float, 4>&>(value);
	});

	dispatcher.RegisterProvider([p_provider](std::array<float, 4> p_value)
	{
		p_provider(reinterpret_cast<GeMaths::FVector4&>(p_value));
	});
}

void GeCore::Helpers::GUIDrawer::DrawQuat(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<GeMaths::FQuaternion(void)> p_gatherer, std::function<void(GeMaths::FQuaternion)> p_provider, float p_step, float p_min, float p_max)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Drags::DragMultipleScalars<float, 4>>(GetDataType<float>(), p_min, p_max, 0.f, p_step, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::array<float, 4>>>();
	
	dispatcher.RegisterGatherer([p_gatherer]()
	{
		GeMaths::FQuaternion value = p_gatherer();
		return reinterpret_cast<const std::array<float, 4>&>(value);
	});

	dispatcher.RegisterProvider([&dispatcher, p_provider](std::array<float, 4> p_value)
	{
		p_provider(GeMaths::FQuaternion::Normalize(reinterpret_cast<GeMaths::FQuaternion&>(p_value)));
	});
}

void GeCore::Helpers::GUIDrawer::DrawDDString(GeUI::Internal::WidgetContainer& p_root, const std::string& p_name,
	std::function<std::string()> p_gatherer, std::function<void(std::string)> p_provider,
	const std::string& p_identifier)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::InputFields::InputText>("");
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::string>>();
	dispatcher.RegisterGatherer(p_gatherer);
	dispatcher.RegisterProvider(p_provider);

	auto& ddTarget = widget.AddPlugin<GeUI::Plugins::DDTarget<std::pair<std::string, GeUI::Widgets::Layout::Group*>>>(p_identifier);
	ddTarget.DataReceivedEvent += [&widget, &dispatcher](std::pair<std::string, GeUI::Widgets::Layout::Group*> p_data)
	{
		widget.content = p_data.first;
		dispatcher.NotifyChange();
	};
}

void GeCore::Helpers::GUIDrawer::DrawString(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<std::string(void)> p_gatherer, std::function<void(std::string)> p_provider)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::InputFields::InputText>("");
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<std::string>>();
	dispatcher.RegisterGatherer(p_gatherer);
	dispatcher.RegisterProvider(p_provider);
}

void GeCore::Helpers::GUIDrawer::DrawColor(GeUI::Internal::WidgetContainer & p_root, const std::string & p_name, std::function<GeUI::Types::Color(void)> p_gatherer, std::function<void(GeUI::Types::Color)> p_provider, bool p_hasAlpha)
{
	CreateTitle(p_root, p_name);
	auto& widget = p_root.CreateWidget<GeUI::Widgets::Selection::ColorEdit>(p_hasAlpha);
	auto& dispatcher = widget.AddPlugin<GeUI::Plugins::DataDispatcher<GeUI::Types::Color>>();
	dispatcher.RegisterGatherer(p_gatherer);
	dispatcher.RegisterProvider(p_provider);
}
