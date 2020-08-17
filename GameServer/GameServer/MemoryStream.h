#pragma once
#include<cstdint>
#include<cstdlib>

class OutputMemoryStream
{
public:
	OutputMemoryStream() :
		mHead(2),	//사이즈를 넣기위함 short의 크기는 2비트 이기 때문
		mBuffer(nullptr)
	{
		ReallocBuffer(1500 * 8);
	}

	~OutputMemoryStream() { std::free(mBuffer); }

	const char* GetBufferPtr()	const { return mBuffer; }
	int GetDataLength()			const { return mHead; }

	template<typename T>
	void Write(T inData, int inDataCount = sizeof(T))
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"일반 읽기는 기본 데이터 유형 만 지원합니다");

		(*(T*)(mBuffer + mHead)) = inData;
		mHead += inDataCount;
	}

	void Write(const std::string& inString)
	{
		//string 같은 경우에는 사이즈가 어떨지 모름 때문에 직렬화를 할때 해당 사이즈를
		//먼저 기록하고 문자열을 직렬화한다.
		short elementCount = static_cast<short>(inString.size());
		Write(elementCount);
		for (const auto& element : inString)
		{
			Write(element);
		}
	}

	void Write(Vector3 data);

	void SetSize();
private:
	void ReallocBuffer(int inNewDataLength);

	char* mBuffer;
	int mHead;
	int mCapacity;
};

class InputMemoryStream
{
public:
	InputMemoryStream(char* inBuffer, int inDataCount) :
		mBuffer(inBuffer),
		mCapacity(inDataCount),
		mHead(sizeof(short)),
		mIsOwner(false){}

	~InputMemoryStream() { if (mIsOwner) std::free(mBuffer); }

	const char* GetBufferPtr() const { return mBuffer; }
	int GetRemainingDataCount() const { return mCapacity - mHead; }

	void ResetToCapacity(int inDataCapacity) { mCapacity = inDataCapacity; mHead = 0; }

	template<typename T>
	void Read(T& inData, int inDataCount = sizeof(T))
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"일반 읽기는 기본 데이터 유형 만 지원합니다");

		inData = (*(T*)(mBuffer + mHead));
		mHead += inDataCount;
	}

	void Read(std::string& inString)
	{
		short elementCount;
		Read(elementCount);
		inString.resize(elementCount);
		for (auto& element : inString)
		{
			Read(element);
		}
	}
private:
	char* mBuffer;
	int mCapacity;
	int mHead;
	bool mIsOwner;
};