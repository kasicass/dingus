#include "dingus/renderer/RenderCamera.hpp"

using namespace dingus;

CRenderCamera::CRenderCamera() :
	mEye(0, 0, 0, 1)
{
	mCameraMatrix.identify();
	mProjectionMatrix.identify();
	mCameraRotMatrix.identify();
	mViewMatrix.identify();
	mViewProjMatrix.identify();
}

CRenderCamera::~CRenderCamera()
{
}

void CRenderCamera::setCameraMatrix(const SMatrix4x4& matrix)
{
	mCameraMatrix = matrix;
	mCameraRotMatrix = matrix;
	mCameraRotMatrix.getOrigin().set(0,0,0);
	D3DXMatrixInverse(&mViewMatrix, NULL, &mCameraMatrix);
	mEye = SVector4(matrix._41, matrix._42, matrix._43, 1.0f);
	mViewProjMatrix = mViewMatrix * mProjectionMatrix;
}

void CRenderCamera::setProjectionMatrix(const SMatrix4x4& matrix)
{
	mProjectionMatrix = matrix;
	mViewProjMatrix = mViewMatrix * mProjectionMatrix;
}

