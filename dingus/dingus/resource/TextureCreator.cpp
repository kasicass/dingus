#include "dingus/resource/TextureCreator.hpp"
#include "dingus/utils/Errors.hpp"
#include "dingus/kernel/D3DDevice.hpp"
#include "dingus/console/Console.hpp"

using namespace dingus;

IDirect3DTexture9* CFixedTextureCreator::createTexture()
{
	IDirect3DDevice9& dxdev = CD3DDevice::getInstance().getDevice();
	HRESULT hr;
	IDirect3DTexture9* texture = NULL;

	UINT width = mWidth;
	UINT height = mHeight;
	UINT levels = mLevels;
	D3DFORMAT fmt = mFormat;
	D3DXCheckTextureRequirements(&dxdev, &width, &height, &levels, mUsage, &fmt, mPool);

	hr = dxdev.CreateTexture(width, height, levels, mUsage, fmt, mPool, &texture, NULL);
	if (FAILED(hr))
	{
		char buf[1000];
		sprintf(buf,
			"FixedTextureCreator: failed to create texture\n"
			"(w=%i h=%i lvl=%i usage=%i fmt=%i pool=%i)",
			width, height, levels, mUsage, fmt, mPool);
		std::string msg = buf;
		CConsole::CON_ERROR.write(msg);
		THROW_DXERROR(hr, msg);
	}

	assert(texture);
	return texture;
}

IDirect3DTexture9* CScreenBasedTextureCreator::createTexture()
{
	HRESULT hr;
	IDirect3DTexture9* texture = NULL;

	CD3DDevice& device = CD3DDevice::getInstance();
	int width  = int(device.getBackBufferWidth() * mWidthFactor);
	int height = int(device.getBackBufferHeight() * mHeightFactor);

	hr = device.getDevice().CreateTexture(width, height, mLevels, mUsage, mFormat, mPool, &texture, NULL);
	if (FAILED(hr))
	{
		char buf[1000];
		sprintf(buf,
			"CScreenBasedTextureCreator: failed to create texture\n"
			"(w=%i h=%i lvl=%i usage=%i fmt=%i pool=%i)",
			width, height, mLevels, mUsage, mFormat, mPool);
		std::string msg = buf;
		CConsole::CON_ERROR.write(msg);
		THROW_DXERROR(hr, msg);
	}

	assert(texture);
	return texture;
}

IDirect3DTexture9* CScreenBasedDivTextureCreator::createTexture()
{
	HRESULT hr;
	IDirect3DTexture9* texture = NULL;

	CD3DDevice& device = CD3DDevice::getInstance();
	int bbWidth = device.getBackBufferWidth();
	int bbHeight = device.getBackBufferHeight();
	int cropWidth = bbWidth - bbWidth % mBBDivisibleBy;
	int cropHeight = bbHeight - bbHeight % mBBDivisibleBy;
	int width = int(cropWidth * mWidthFactor);
	int height = int(cropWidth * mHeightFactor);

	hr = device.getDevice().CreateTexture(width, height, mLevels,
		mUsage, mFormat, mPool, &texture, NULL);
	if (FAILED(hr))
	{
		char buf[1000];
		sprintf(buf,
			"CScreenBasedDivTextureCreator: failed to create texture\n"
			"(w=%i h=%i lvl=%i usage=%i fmt=%i pool=%i)",
			width, height, mLevels, mUsage, mFormat, mPool);
		std::string msg = buf;
		CConsole::CON_ERROR.write(msg);
		THROW_DXERROR(hr, msg);
	}

	assert(texture);
	return texture;
}

IDirect3DTexture9* CScreenBasedPow2TextureCreator::createTexture()
{
	HRESULT hr;
	IDirect3DTexture9* texture = NULL;

	CD3DDevice& device = CD3DDevice::getInstance();
	int width  = int(device.getBackBufferWidth() * mWidthFactor);
	int height = int(device.getBackBufferHeight() * mHeightFactor);

	// lower width/height to be power-of-2
	int hibit;
	
	hibit = 0;
	while (width>>hibit != 0)
		++hibit;
	width &= (1<<(hibit-1));

	hibit = 0;
	while (height>>hibit != 0)
		++hibit;
	height &= (1<<(hibit-1));

	hr = device.getDevice().CreateTexture(width, height, mLevels, mUsage,
		mFormat, mPool, &texture, NULL);
	if (FAILED(hr))
	{
		char buf[1000];
		sprintf(buf,
			"CScreenBasedPow2TextureCreator: failed to create texture\n"
			"(w=%i h=%i lvl=%i usage=%i fmt=%i pool=%i)",
			width, height, mLevels, mUsage, mFormat, mPool);
		std::string msg = buf;
		CConsole::CON_ERROR.write(msg);
		THROW_DXERROR(hr, msg);
	}

	assert(texture);
	return texture;
}
