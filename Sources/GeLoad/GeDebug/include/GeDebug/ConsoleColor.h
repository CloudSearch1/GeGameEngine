#pragma once

#include <iostream>
#include <windows.h>

#define COLOR_BLUE GeDebug::blue
#define COLOR_RED GeDebug::red
#define COLOR_GREEN GeDebug::green
#define COLOR_YELLOW GeDebug::yellow
#define COLOR_WHITE GeDebug::white
#define COLOR_DEFAULT GeDebug::grey

namespace GeDebug
{
	inline std::ostream& blue(std::ostream& s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_BLUE | FOREGROUND_GREEN |
			FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& red(std::ostream& s)
	{
		HANDLE hStdout = GetStdHandle(STD_ERROR_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_RED | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& green(std::ostream& s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& yellow(std::ostream& s)
	{
		HANDLE hStdout = GetStdHandle(STD_ERROR_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_GREEN | FOREGROUND_RED |
			FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& white(std::ostream& s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_RED | FOREGROUND_GREEN |
			FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& grey(std::ostream& s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_RED | FOREGROUND_GREEN |
			FOREGROUND_BLUE);
		return s;
	}

	struct color
	{
		color(WORD attribute) : m_color(attribute)
		{
		}

		WORD m_color;
	};

	template <class _Elem, class _Traits>
	std::basic_ostream<_Elem, _Traits>&
		operator<<(std::basic_ostream<_Elem, _Traits>& i, color& c)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, c.m_color);
		return i;
	}
}
