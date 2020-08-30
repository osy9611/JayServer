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

void OutputMemoryStream::SetSize()
{
	//mBuffer[0] = mHead;
	//mBuffer[1] = 0;
	//std::cout << mHead << std::endl;
	//원래 방식이었지만 위의 방식이 메모리 할당을 안해도 되서 부담이 덜될듯?
	char* tempBuffer = static_cast<char *>(std::malloc(mHead + sizeof(short)));
	mHead += sizeof(short);
	(*(short*)(tempBuffer)) = (short)mHead;

	memcpy(tempBuffer + 2, mBuffer, mHead - sizeof(short));
	memcpy(mBuffer, tempBuffer, mHead);
	std::free(tempBuffer);
}
