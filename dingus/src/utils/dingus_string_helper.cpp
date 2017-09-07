#include "dingus_string_helper.hpp"

using namespace dingus;

void CStringHelper::replaceTabs(std::string &s)
{
	size_t n = s.size();
	for (size_t i = 0; i < n; ++i)
	{
		if (s[i] == '\t') s[i] = ' ';
	}
}

