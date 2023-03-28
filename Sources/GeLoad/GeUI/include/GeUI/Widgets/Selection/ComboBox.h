/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <map>

#include <GeUtils/Eventing/Event.h>

#include "GeUI/Widgets/DataWidget.h"

namespace GeUI::Widgets::Selection
{
	/**
	* Widget that can display a list of values that the user can select
	*/
	class ComboBox : public DataWidget<int>
	{
	public:
		/**
		* Constructor
		* @param p_currentChoice
		*/
		ComboBox(int p_currentChoice = 0);

	protected:
		void _Draw_Impl() override;

	public:
		std::map<int, std::string> choices;
		int currentChoice;

	public:
		GeUtils::Eventing::Event<int> ValueChangedEvent;
	};
}