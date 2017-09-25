#include "System.hpp"
#include <dingus/console/FileConsoleRenderingContext.hpp>

#include <dingus/resource/TextureBundle.hpp>

SAppStartupParams CSystem::getStartupParams()
{
	SAppStartupParams sp;
	sp.windowTitle    = "HelloWnd";
	sp.dataPath       = "data/";
	sp.windowWdith    = 800;
	sp.windowHeight   = 600;
	sp.minColorBits   = 4;
	sp.minAlphaBits   = 4;
	sp.minZBits       = 16;
	sp.minStencilBits = 0;
	return sp;
}

IConsoleRenderingContext* CSystem::createStdConsoleCtx(HWND hwnd)
{
	return new CFileConsoleRenderingContext("dingus_log");
}

void CSystem::setupBundles(const std::string& dataPath)
{
	CTextureBundle::getInstance().addDirectory(dataPath + "tex/");

	CDeviceResourceManager& deviceManager = CDeviceResourceManager::getInstance();
	deviceManager.addListener(CTextureBundle::getInstance());
}

void CSystem::setupContexts(HWND hwnd)
{
	mHWnd = hwnd;
}

void CSystem::destroyContexts()
{
}

void CSystem::destroyBundles()
{
	CTextureBundle::finalize();
}
