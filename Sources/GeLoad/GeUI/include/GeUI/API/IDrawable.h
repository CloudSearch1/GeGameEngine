/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

namespace GeUI::API
{
	/**
	* Interface for any drawable class
	*/
	class IDrawable
	{
	public:
		virtual void Draw() = 0;

	protected:
		virtual ~IDrawable() = default;
	};
}
