#include "dingus/dxutils/D3DApplication.hpp"
#include "dingus/kernel/D3DDevice.hpp"

using namespace dingus;

static CD3DApplication* gD3DApp = NULL;

LRESULT CALLBACK gWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return gD3DApp->msgProc(hWnd, uMsg, wParam, lParam);
}

CD3DApplication::CD3DApplication() :
	mDeviceObjectsInited(false),
	mDeviceObjectsRestored(false),
	mWindowed(true),
	mCreationWidth(640),
	mCreationHeight(480),
	mWindowTitle("D3D9 Application")
{
}

CD3DApplication::~CD3DApplication()
{
}

HRESULT CD3DApplication::create(HINSTANCE hInstance)
{
	HRESULT hr;

	mHInstance = hInstance;

	// create the Direct3D object
	mD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (mD3D == NULL)
		return NODIRECT3D;

	// Setup the window class
	WNDCLASSEX wc;
	memset(&wc,0, sizeof(wc));
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= gWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= 0;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW); 
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "Dingus D3D Window";
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
	
	// Register the window class
	RegisterClassEx(&wc);

	// Specify the window style
	mWindowStyle = (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	
	// Record the desired device size
	RECT rc;
	rc.top = rc.left = 0;
	rc.right = mCreationWidth;
	rc.bottom = mCreationHeight;

	// Adjust the window size for correct device size
	AdjustWindowRect(&rc, mWindowStyle, FALSE);

	long width  = rc.right - rc.left;
	long height = rc.bottom - rc.top;

	mHWnd = CreateWindowEx(
		NULL,              // extended style
		wc.lpszClassName,  // class name
		mWindowTitle,      // window title
		mWindowStyle,      // window style
		100, 100,          // initial x, y
		width, height,     // initial width, height
		NULL,              // handle to parent
		NULL,              // handle to menu
		mHInstance,        // instance of this application
		NULL);             // extra creation params

	ShowWindow(mHWnd, SW_SHOWNORMAL);
	UpdateWindow(mHWnd);

	// initialize the app
	if (FAILED(hr = this->initialize()))
	{
		DINGUS_SAFE_RELEASE(mD3D);
		return hr;
	}

	if (FAILED(hr = initialize3DEnvironment()))
	{
		DINGUS_SAFE_DELETE(mD3D);
		return hr;
	}

	return S_OK;
}

HRESULT CD3DApplication::initialize3DEnvironment()
{
	HRESULT hr;

	mPresentParams.BackBufferWidth            = 0;
	mPresentParams.BackBufferHeight           = 0;
	mPresentParams.BackBufferFormat           = D3DFMT_UNKNOWN;
	mPresentParams.BackBufferCount            = 1;
	mPresentParams.MultiSampleType            = D3DMULTISAMPLE_NONE;
	mPresentParams.MultiSampleQuality         = 0;
	mPresentParams.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
	mPresentParams.hDeviceWindow              = mHWnd;
	mPresentParams.Windowed                   = mWindowed;
	mPresentParams.EnableAutoDepthStencil     = true;
	mPresentParams.AutoDepthStencilFormat     = D3DFMT_D24S8;
	mPresentParams.Flags                      = 0;
	mPresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	mPresentParams.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	DWORD behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	D3DDEVTYPE devType = D3DDEVTYPE_HAL;

	hr = mD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		devType,
		mHWnd,
		behaviorFlags,
		&mPresentParams,
		&mD3DDevice);
	if (SUCCEEDED(hr))
	{
		mD3DDevice->GetDeviceCaps(&mD3DCaps);
		mCreateFlags = behaviorFlags;

		hr = internalCreateDevice();
		if (FAILED(hr))
		{
			internalDeleteDevice();
		}
		else
		{
			mDeviceObjectsInited = true;
			hr = internalActivateDevice();
			if (FAILED(hr))
			{
				internalPassivateDevice();
			}
			else
			{
				mDeviceObjectsRestored = true;
				return S_OK;
			}
		}

		cleanup3DEnvironment();
	}
}

void CD3DApplication::cleanup3DEnvironment()
{
	if (mD3DDevice != NULL)
	{
		if (mDeviceObjectsRestored)
		{
			mDeviceObjectsRestored = false;
			internalPassivateDevice();
		}

		if (mDeviceObjectsInited)
		{
			mDeviceObjectsInited = false;
			internalDeleteDevice();
		}

		if (mD3DDevice->Release() > 0)
			exit(0);

		mD3DDevice = NULL;
	}
}

HRESULT	CD3DApplication::internalCreateDevice()
{
	assert(mD3DDevice);

	CD3DDevice& device = CD3DDevice::getInstance();
	device.setDevice(mD3DDevice, CD3DDeviceCaps::VP_HW);

	return this->createDeviceObjects();
}

HRESULT	CD3DApplication::internalDeleteDevice()
{
	HRESULT hr = deleteDeviceObjects();
	CD3DDevice::getInstance().setDevice(NULL, CD3DDeviceCaps::VP_SW);
	return hr;
}

HRESULT CD3DApplication::internalActivateDevice()
{
	CD3DDevice::getInstance().activateDevice(mHWnd);
	return this->activateDeviceObjects();
}

HRESULT CD3DApplication::internalPassivateDevice()
{
	HRESULT hr = this->passivateDeviceObjects();
	CD3DDevice::getInstance().passivateDevice();
	return hr;
}
