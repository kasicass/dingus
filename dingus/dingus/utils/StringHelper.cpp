#include "dingus/utils/StringHelper.hpp"

using namespace dingus;

void CStringHelper::replaceTabs(std::string &s)
{
	size_t n = s.size();
	for (size_t i = 0; i < n; ++i)
	{
		if (s[i] == '\t') s[i] = ' ';
	}
}

void CStringHelper::replaceLineEnds(std::string &s)
{
	size_t n = s.size();
	for (size_t i = 0; i < n; ++i)
	{
		if (s[i] == '\r' || s[i] == '\n') s[i] = ' ';
	}
}

void CStringHelper::replaceWhitespace(std::string &s)
{
	size_t n = s.size();
	for (size_t i = 0; i < n; ++i)
	{
		if (!isprint(s[i])) s[i] = ' ';
	}
}

void CStringHelper::trimString(std::string &s)
{
	size_t first = s.find_first_not_of(" \t\n\r");
	if (first == std::string::npos)
	{
		s = "";
		return;
	}

	size_t last = s.find_last_not_of(" \t\n\r");
	s = s.substr(first, (last-first+1));
}

int CStringHelper::countLines(const std::string &s)
{
	int c = 1;
	size_t n = s.size();
	for (size_t i = 0; i < n; ++i)
	{
		if (s[i] == '\n') ++c;
	}
	return c;
}

bool CStringHelper::isLetter(char c)
{
	return !!isalpha(c);
}

bool CStringHelper::isDigit(char c)
{
	return !!isdigit(c);
}

bool CStringHelper::startsWith(const std::string &s, const std::string &subs)
{
	return s.find(subs) == 0;
}

bool CStringHelper::endsWith(const std::string &s, const std::string &subs)
{
	return s.find(subs) == (s.length() - subs.length());
}

char CStringHelper::toLower(char c)
{
	return (char)tolower(c);
}

char CStringHelper::toUpper(char c)
{
	return (char)toupper(c);
}

void CStringHelper::toLower(std::string &s)
{
	size_t n = s.size();
	for (size_t i = 0; i < n; ++i)
	{
		s[i] = (char)tolower(s[i]);
	}
}

void CStringHelper::toUpper(std::string &s)
{
	size_t n = s.size();
	for (size_t i = 0; i < n; ++i)
	{
		s[i] = (char)toupper(s[i]);
	}
}
