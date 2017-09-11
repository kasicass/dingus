#pragma once

#include "dingus/GlobalSetting.hpp"

namespace dingus {

//---------------------------------------------------------------------------

struct CD3DEnumErrors : public boost::noncopyable
{
public:
	typedef std::set<std::string> TStringSet;

public:
	void addError(const std::string& s) { mErrors.insert(s); }
	const TStringSet& getErrors() const { return mErrors; }

private:
	TStringSet mErrors;
};

//---------------------------------------------------------------------------

class CD3DDeviceCaps
{
public:
	enum eVSVersion { VS_FFP = 0, VS_1_1, VS_2_0, VS_3_0 };
	enum ePSVersion { PS_TSS = 0, PS_1_1, PS_1_4, PS_2_0, PS_3_0 };
	enum eVertexProcessing { VP_PURE_HW = 0, VP_HW, VP_MIXED, VP_SW, VPCOUNT };

public:
	CD3DDeviceCaps();

	void setData(IDirect3D9& d3d, UINT adapterOrdinal, D3DDEVTYPE devType, const D3DCAPS9& caps);
	void setVertexProcessing(eVertexProcessing vproc) { mVertexProcessing = vproc; }

	const D3DCAPS9& getCaps() const { return mCaps; }
	const D3DADAPTER_IDENTIFIER9& getAdapterID() const { return mAdapterID; }
	D3DADAPTER_IDENTIFIER9& getAdapterID() { return mAdapterID; }
	UINT getAdapterOridinal() const { return mAdapterOrdinal; }
	D3DDEVTYPE getDeviceType() const { return mDeviceType; }

	eVSVersion getVShaderVersion() const { return mVShaderVersion; }
	ePSVersion getPShaderVersion() const { return mPShaderVersion; }
	eVertexProcessing getVertexProcessing() const { assert(mVertexProcessing != VPCOUNT); return mVertexProcessing; }

	// True if native shadow maps are supported
	bool hasShadowMaps() const { return mHasShadowMaps; }

	// True if floating point rendertargets (r32f and abgr16) are supported
	bool hasFloatTextures() const { return mHasFloatTextures; }

	int getMRTCount() const { return mCaps.NumSimultaneousRTs; }

	// Gets linear StretchRect() filter if supported, or none
	D3DTEXTUREFILTERTYPE getStretchFilter() const {
		return (mCaps.StretchRectFilterCaps & (D3DPTFILTERCAPS_MAGFLINEAR|D3DPTFILTERCAPS_MINFLINEAR)) == (D3DPTFILTERCAPS_MAGFLINEAR|D3DPTFILTERCAPS_MINFLINEAR)
			? D3DTEXF_LINEAR : D3DTEXF_NONE;
	}

	int getVideoMemoryMB() const { return mVideoMemoryMB; }
	int getCpuMhz() const { return mCpuMhz; }

private:
	int calcVideoMemory();

private:
	D3DCAPS9               mCaps;
	D3DADAPTER_IDENTIFIER9 mAdapterID;
	UINT                   mAdapterOrdinal;
	D3DDEVTYPE             mDeviceType;

	bool                   mHasShadowMaps;
	bool                   mHasFloatTextures;

	eVSVersion             mVShaderVersion;
	ePSVersion             mPShaderVersion;
	eVertexProcessing      mVertexProcessing;

	int                    mVideoMemoryMB;  // approximate amount of video memory
	int                    mCpuMhz;         // NOTE: can be -1 if can't get the mhz!
};

}
