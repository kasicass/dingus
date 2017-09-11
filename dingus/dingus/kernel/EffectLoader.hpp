#pragma once

#include "dingus/kernel/ProxyEffect.hpp"

namespace dingus {

	class CConsoleChannel;

	namespace fxloader {

		bool initialize(const char* cfgFileName);
		void shutdown();

		// Load effect. This will examine the effect, complain about
		// missing states, generate restore pass and return
		// ready-to-use effect.
		bool load(
			const std::string& id, const std::string& fileName,
			const char* skipConstants,
			CD3DXEffect& dest, std::string& errorMsgs,
			ID3DXEffectPool* pool, ID3DXEffectStateManager* stateManager,
			const D3DXMACRO* macros, size_t macroCount, bool optimizeShaders,
			CConsoleChannel& console);
	}
}
