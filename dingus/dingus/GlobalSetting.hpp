#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
// #include <tchar.h>

// STL
#include <list>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>

// libc
#include <assert.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
// do NOT include these, so it's less tempting to use rand() etc.
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>

// D3D
#include <d3d9.h>
#include <d3dx9.h>

// smart pointer
#include <boost/core/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>

// utils
#include "dingus/utils/RefCounted.hpp"
#include "dingus/utils/fastvector.hpp"
#include "dingus/utils/AssertHelper.hpp"
#include "dingus/utils/STLUtils.hpp"

// macros
#define DINGUS_SAFE_RELEASE(x) if (x) { x->Release(); x = NULL; }
#define DINGUS_SAFE_DELETE(x)  if (x) { delete x; x = NULL; }
