#pragma once

#include "dingus/GlobalSetting.hpp"

#include "dingus/math/Vector3.hpp"
#include "dingus/math/Quaternion.hpp"
#include "dingus/math/Matrix4x4.hpp"

namespace dingus {

class CLuaValue;

class CLuaHelper
{
public:
	static std::string getString(CLuaValue& val, const char* name);
	static double getNumber(CLuaValue& val, const char* name);
	static SVector3 getVector3(CLuaValue& val, const char* name);
	static SQuaternion getQuaternion(CLuaValue& val, const char* name);
	static void getMatrix3x3(CLuaValue& val, const char* name, SMatrix4x4& m);
};

}
