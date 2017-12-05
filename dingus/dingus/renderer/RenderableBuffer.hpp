#pragma once

#include "dingus/renderer/Renderable.hpp"
#include "dingus/kernel/Proxies.hpp"
#include "dingus/utils/MemoryPool.hpp"

namespace dingus {

// --------------------------------------------------------------------------

// Abstract base class for vertex and indexed vertex buffer renderables
class CAbstractRenderableBuffer : public CRenderable
{
public:
	enum { VERTEX_STREAM_COUNT = 16 };

public:
	CAbstractRenderableBuffer(const SVector3* origin = 0, int priority = 0);

	void setVB(CD3DVertexBuffer& vb, int stream = 0);
	const CD3DVertexBuffer* getVB(int stream = 0) const { return mVB[stream]; }
	CD3DVertexBuffer* getVB(int stream = 0) { return mVB[stream]; }

	void resetVBs();

	void setStride(unsigned int stride, int stream = 0) { mStride[stream] = stride; }
	unsigned int getStride(int stream = 0) const { return mStride[stream]; }

	void setByteOffset(unsigned int offset, int stream = 0) { mByteOffset[stream] = offset; }
	unsigned int getByteOffset(int stream = 0) const { return mByteOffset[stream]; }

	void setVertexDecl(CD3DVertexDecl* decl) { mVertexDecl = decl; }
	CD3DVertexDecl* getVertexDecl() const { mVertexDecl; }

	void setPrimType(D3DPRIMITIVETYPE primitiveType) { mPrimType = primitiveType; }
	D3DPRIMITIVETYPE getPrimType() const { return mPrimType; }

	void setPrimType(int primitiveCount) { mPrimCount = primitiveCount; }
	int getPrimCount() const { return mPrimCount; }

	virtual const CD3DVertexBuffer* getUsedVB() const { return mVB[0]; }

protected:
	void applyStreams();
	void unapplyStreams();
	int getLargestActiveStream() const { return mLargestActiveStream; }

private:
	CD3DVertexBuffer* mVB[VERTEX_STREAM_COUNT];
	unsigned int      mStride[VERTEX_STREAM_COUNT];
	unsigned int      mByteOffset[VERTEX_STREAM_COUNT];
	int               mLargestActiveStream;
	CD3DVertexDecl*   mVertexDecl;

	D3DPRIMITIVETYPE  mPrimType;
	int               mPrimCount;
};

// --------------------------------------------------------------------------

// Vertex buffer renderable
class CRenderableBuffer : public CAbstractRenderableBuffer
{
public:
	CRenderableBuffer(const SVector3* origin = 0, int priority = 0);

	void setStartVertex(int startVertex) { mStartVertex = startVertex; }
	int getStartVertex() const { return mStartVertex; }

	virtual void render(const CRenderContext& ctx);
	virtual const CD3DIndexBuffer* getUsedIB() const { return NULL; }

private:
	DECLARE_POOLED_ALLOC(dingus::CRenderableBuffer);

private:
	int mStartVertex;
};

// --------------------------------------------------------------------------

// Indexed vertex buffer renderable
class CRenderableIndexedBuffer : public CAbstractRenderableBuffer
{
public:
	CRenderableIndexedBuffer(const SVector3* origin = 0, int priority = 0);

	void setIB(CD3DIndexBuffer& ibuffer) { mIB = &ibuffer; }
	const CD3DIndexBuffer* getIB() const { return mIB; }
	CD3DIndexBuffer* getIB() { return mIB; }

	// Set vertex that is treated as the first one. All indices will be relative
	// to this vertex. This can be done with setByteOffset() in many cases, but
	// sometimes it isn't supported.
	void setBaseVertex(int baseVertex) { mBaseVertex = baseVertex; }
	int getBaseVertex() const { return mBaseVertex; }

	void setMinVertex(int minVertex) { mMinVertex = minVertex; }
	int getMinVertex() const { return mMinVertex; }

	void setNumVertices(int numVertices) { mNumVertices = numVertices; }
	int getNumVertices() const { return mNumVertices; }

	void setStartIndex(int startIndex) { mStartIndex = startIndex; }
	int getStartIndex() const { return mStartIndex; }

	virtual void render(const CRenderContext& ctx);
	virtual const CD3DIndexBuffer* getUsedIB() const { return mIB; }

private:
	DECLARE_POOLED_ALLOC(dingus::CRenderableIndexedBuffer);

private:
	CD3DIndexBuffer* mIB;
	int mBaseVertex;
	int mMinVertex;
	int mNumVertices;
	int mStartIndex;
};

}
