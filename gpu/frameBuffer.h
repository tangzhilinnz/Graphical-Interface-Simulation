#pragma once
#include "../global/base.h"

/*
* class FrameBuffer：
* 存储当前画布对应的bmp的内存指针，作为当前绘图画板
*/
class FrameBuffer {
public:
	FrameBuffer(uint32_t width, uint32_t height, void* buffer = nullptr);
	~FrameBuffer();
	// In C++, if you delete the copy constructor, the compiler will also
	// implicitly delete the copy assignment operator unless it is explicitly
	// defined. This means you cannot assign one FrameBuffer object to another
	// using the assignment operator (=) unless you explicitly define the copy
	// assignment operator.
	FrameBuffer(const FrameBuffer&) = delete;//不准拷贝复制

	uint32_t	mWidth{ 0 };
	uint32_t	mHeight{ 0 };
	RGBA*		mColorBuffer{ nullptr };
	float*      mDepthBuffer{ nullptr };
	bool		mExternBuffer{ false };
};