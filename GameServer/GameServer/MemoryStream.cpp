#include "stdafx.h"

void OutputMemoryStream::ReallocBuffer(int inNewDataLength)
{
	if (mBuffer == nullptr)
	{
		mBuffer = static_cast<char*>(std::malloc(inNewDataLength));
	}
	else
	{
		char* tempBuffer = static_cast<char *>(std::malloc(inNewDataLength));
		memset(mBuffer, 0, inNewDataLength);
		memcpy(tempBuffer, mBuffer, mCapacity);
		std::free(mBuffer);
		mBuffer = tempBuffer;
	}

	mCapacity = inNewDataLength;
}