#pragma once

#include "dingus/GlobalSetting.hpp"

namespace dingus {

class ITextureCreator : public CRefCounted
{
public:
	typedef DingusSmartPtr<ITextureCreator> TShreadPtr;

public:
	virtual ~ITextureCreator() {}
	virtual IDirect3DTexture9* createTexture() = 0;
};

class CAbstractTextureCreator : public ITextureCreator
{
public:
	CAbstractTextureCreator(DWORD usage, D3DFORMAT format, D3DPOOL pool) :
		mUsage(usage), mFormat(format), mPool(pool) {}

protected:
	const DWORD mUsage;
	const D3DFORMAT mFormat;
	const D3DPOOL mPool;
};

// Creates fixed size texture
class CFixedTextureCreator : public CAbstractTextureCreator
{
public:
	CFixedTextureCreator(int width, int height, int levels, DWORD usage, D3DFORMAT format, D3DPOOL pool) :
		CAbstractTextureCreator(usage, format, pool), mWidth(width), mHeight(height), mLevels(levels) {}

	virtual IDirect3DTexture9* createTexture() override;

protected:
	const int mWidth, mHeight, mLevels;
};

// Create texture with size proportional to backbuffer
class CScreenBasedTextureCreator : public CAbstractTextureCreator
{
public:
	CScreenBasedTextureCreator(float widthFactor, float heightFactor, int levels, DWORD usage, D3DFORMAT format, D3DPOOL pool) :
		CAbstractTextureCreator(usage, format, pool), mWidthFactor(widthFactor), mHeightFactor(heightFactor), mLevels(levels) {}

	virtual IDirect3DTexture9* createTexture() override;

protected:
	const float mWidthFactor;
	const float mHeightFactor;
	const int   mLevels;
};

// Creates texture with size proportional to backbuffer, cropped to make divisible by some number.
class CScreenBasedDivTextureCreator : public CScreenBasedTextureCreator
{
public:
	CScreenBasedDivTextureCreator(float widthFactor, float heightFactor, int bbDivisibleBy, int levels, DWORD usage, D3DFORMAT format, D3DPOOL pool) :
		CScreenBasedTextureCreator(widthFactor, heightFactor, levels, usage, format, pool), mBBDivisibleBy(bbDivisibleBy) {}

	virtual IDirect3DTexture9* createTexture() override;

protected:
	const int mBBDivisibleBy;
};

class CScreenBasedPow2TextureCreator : public CScreenBasedTextureCreator
{
public:
	CScreenBasedPow2TextureCreator(float widthFactor, float heightFactor, int levels, DWORD usage, D3DFORMAT format, D3DPOOL pool) :
		CScreenBasedTextureCreator(widthFactor, heightFactor, levels, usage, format, pool) {}

	virtual IDirect3DTexture9* createTexture() override;
};

}
