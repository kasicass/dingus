#pragma once

#include "dingus/GlobalSetting.hpp"

namespace dingus {

class CStringHelper
{
public:
	static void replaceTabs(std::string &s);         // replaces tabs with single spaces
	static void replaceLineEnds(std::string &s);     // replaces line ends with single spaces
	static void replaceWhitespace(std::string &s);   // replaces white space with single spaces

	static void trimString(std::string &s);          // trims whitespace from ends
	static int countLines(const std::string &s);     // counts number of lines

	static bool isLetter(char c);
	static bool isDigit(char c);

	static bool startsWith(const std::string &s, const std::string &subs);
	static bool endsWith(const std::string &s, const std::string &subs);

	static char toLower(char c);
	static char toUpper(char c);
	static void toLower(std::string &s);
	static void toUpper(std::string &s);

};

}