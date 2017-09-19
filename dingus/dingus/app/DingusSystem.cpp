#include "dingus/app/DingusSystem.hpp"

#include "dingus/console/Console.hpp"

#include "dingus/resource/DeviceResource.hpp"

#include "dingus/kernel/D3DDevice.hpp"


#define APP_CHANNEL CConsole::getChannel("app")

using namespace dingus;

CDingusSystem::CDingusSystem(IDingusApplication& application) :
	mApplication(&application),
	mAppInited(false),
	mStdConsoleCtx(0)
{
	SAppStartupParams params = mApplication->getStartupParams();
	mCreationWidth  = params.windowWdith;
	mCreationHeight = params.windowHeight;
	mWindowTitle    = params.windowTitle;
	mDataPath       = params.dataPath;
}

CDingusSystem::~CDingusSystem()
{
}

// Initialization. Paired with shutdown()
// The window has been created and the IDirect3D9 interface has been
// created, but the device has not been created yet. Here you can
// perform application-related initialization and cleanup that does
// not depend on a device.
HRESULT CDingusSystem::initialize()
{
	assert(mApplication);

	// init console
	mStdConsoleCtx = mApplication->createStdConsoleCtx(mHWnd);
	CConsole::getInstance().setDefaultRenderingContext(*mStdConsoleCtx);

	APP_CHANNEL << "creating device resource manager" << endl;
	CDeviceResourceManager::getInstance();

	return S_OK;
}

bool CDingusSystem::checkDevice(const CD3DDeviceCaps& caps, CD3DDeviceCaps::eVertexProcessing vproc, CD3DEnumErrors& errors)
{
	return mApplication->checkDevice(caps, vproc, errors);
}

HRESULT CDingusSystem::createDeviceObjects()
{
	if (!mAppInited)
	{
		APP_CHANNEL << "setup resource bundles" << endl;
		mApplication->setupBundles(mDataPath);
	}

	APP_CHANNEL << "create d3d resources" << endl;
	CDeviceResourceManager::getInstance().createResource();

	// CEffectParamsNotifier::getInstance().notify();

	return S_OK;
}

HRESULT CDingusSystem::activateDeviceObjects()
{
	APP_CHANNEL << "activate d3d resources" << endl;
	CDeviceResourceManager::getInstance().activateResource();

	if (!mAppInited)
	{
		APP_CHANNEL << "setup app contexts" << endl;
		mApplication->setupContexts(mHWnd);

		APP_CHANNEL << "initialize app" << endl;
		mApplication->initialize();

		APP_CHANNEL << "app initialized" << endl;
		mAppInited = true;
	}

	return S_OK;
}

// Called once per frame, the call is the entry point for 3d rendering. This
// function sets up render states, clears the viewport, and renders the scene.
HRESULT CDingusSystem::performOneTime()
{
	CD3DDevice& device = CD3DDevice::getInstance();

	// pipeline
	device.getStats().reset();
	device.getStats().setFPS(0);  // TODO

	// needs to reset device cache; otherwise we can get funky things with
	// render targets
	device.resetCachedState();

	mApplication->perform();

	// stats
	if (mApplication->shouldShowStats())
	{
		// TODO
	}

	// poll for close
	if (mApplication->shouldFinish())
	{
		// TODO
	}

	return S_OK;
}

LRESULT CDingusSystem::msgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (mApplication && mAppInited)
	{
		mApplication->msgProc(hWnd, msg, wParam, lParam);
	}

	return CD3DApplication::msgProc(hWnd, msg, wParam, lParam);
}

// Invalidates device objects. Paired with activateDeviceObjects().
HRESULT CDingusSystem::passivateDeviceObjects()
{
	APP_CHANNEL << "passivate d3d resources" << endl;
	CDeviceResourceManager::getInstance().passivateResource();
	return S_OK;
}

// Paired with createDeviceObjects()
// Called when the app is exiting, or the device is being changed,
// this function deletes any device dependent objects.
HRESULT CDingusSystem::deleteDeviceObjects()
{
	APP_CHANNEL << "delete d3d resources" << endl;
	CDeviceResourceManager::getInstance().deleteResource();
	return S_OK;
}

// Called before the app exits, this function gives the app the chance
// to cleanup after itself.
HRESULT CDingusSystem::shutdown()
{
	APP_CHANNEL << "shutdown app" << endl;
	mApplication->shutdown();

	APP_CHANNEL << "shutdown device resource manager" << endl;
	CDeviceResourceManager::getInstance().clearListeners();
	CDeviceResourceManager::finalize();

	APP_CHANNEL << "destroy contexts" << endl;
	mApplication->destroyContexts();
	APP_CHANNEL << "destroy resource bundles" << endl;
	mApplication->destroyBundles();

	delete mStdConsoleCtx;
	CConsole::finalize();

	return S_OK;
}
