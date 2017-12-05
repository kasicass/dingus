#include "dingus/GlobalSetting.hpp"
#include "dingus/utils/MemoryPool.hpp"

using namespace dingus;

CMemoryPool::CMemoryPool(int blockSize, int numElements, bool dontGrow, const char* name) :
	mBlockSize(blockSize < sizeof(void*) ? sizeof(void*) : blockSize),
	mBlocksPerBubble(numElements),
	mDontGrow(dontGrow),
	mPeekAllocCount(0),
	mName(name)
{
	reset();
	allocNewBubble();
}

CMemoryPool::~CMemoryPool()
{
	if (mAllocCount > 0)
	{
		ASSERT_FAIL_MSG("leaked!");
	}

	deallocateAll();
}

void CMemoryPool::reset()
{
	mAllocCount = 0;
	mHeadOfFreeList = 0;
}

void CMemoryPool::deallocateAll()
{
	stl_utils::wipe(mBubbles);
	reset();
}

void CMemoryPool::allocNewBubble()
{
	size_t sizeMultiplier;

	if (mDontGrow && !mBubbles.empty())
	{
		ASSERT_FAIL_MSG("CMemoryPool::allocNewBubble: can't grow");
		return;
	}

	sizeMultiplier = mBubbles.size() + 1;

	size_t elemCount = mBlocksPerBubble * sizeMultiplier;
	size_t bubbleSize = mBlockSize * elemCount;
	SBubble *bubble = (SBubble*)malloc(sizeof(SBubble) + bubbleSize - 1);
	assert(bubble);

	bubble->mByteCount = bubbleSize;

	// put to bubble list
	mBubbles.push_back(bubble);

	// setup the free list inside a bubble
	mHeadOfFreeList = bubble->mData;
	assert(mHeadOfFreeList);

	void **newBubble = (void**)mHeadOfFreeList;
	for (size_t j = 0; j < elemCount-1; ++j)
	{
		newBubble[0] = (char*)newBubble + mBlockSize;
		newBubble = (void**)newBubble[0];
	}
	newBubble[0] = NULL;
}

void* CMemoryPool::allocate()
{
	return allocate(mBlockSize);
}

void* CMemoryPool::allocate(unsigned int amount)
{
	void *returnBlock;

	if (amount > (unsigned int)mBlockSize)
	{
		ASSERT_FAIL_MSG("requested larget amount than block size!");
		return NULL;
	}

	if (!mHeadOfFreeList)
	{
		if (mDontGrow)
			return NULL;

		allocNewBubble();

		if (!mHeadOfFreeList)
		{
			ASSERT_FAIL_MSG("CMemoryPool::allocate: out of memory");
			return NULL;
		}
	}

	++mAllocCount;
	if (mAllocCount > mPeekAllocCount)
		mPeekAllocCount = mAllocCount;

	returnBlock = mHeadOfFreeList;

	// move to the next block
	mHeadOfFreeList = *((void**)mHeadOfFreeList);

	return returnBlock;
}

void CMemoryPool::deallocate(void* memBlock)
{
	if (!memBlock)
		return;

#ifdef _DEBUG
	// check to see if the memory is from the allocated range
	bool ok = false;
	size_t n = mBubbles.size();
	for (size_t i = 0; i < n; ++i)
	{
		SBubble* p = mBubbles[i];
		if ((char*)memBlock >= p->mData && (char*)memBlock < (p->mData + p->mByteCount))
		{
			ok = true;
			break;
		}
	}
	assert(ok);
#endif

#ifdef _DEBUG
	// invalidate the memory
	memset(memBlock, 0xDEADBEEF, mBlockSize);
#endif

	--mAllocCount;

	*((void**)memBlock) = mHeadOfFreeList;
	mHeadOfFreeList = memBlock;
}
