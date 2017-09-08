#include "dingus/kernel/RenderStats.hpp"
#include <string.h>

using namespace dingus;

void CRenderStats::reset()
{
	memset(this, 0, sizeof(*this));
}
