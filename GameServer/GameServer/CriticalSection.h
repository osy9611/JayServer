#include"stdafx.h"

struct CriticalSection :public CRITICAL_SECTION
{
	CriticalSection() { InitializeCriticalSection(this); }
	~CriticalSection() { DeleteCriticalSection(this); }
};

/*
RAII
 C++ 같이 개발자가 직접 리소스 관리를 해줘야하는 언어에서 메모리 누수를 방지하기 위한 중요한 기법으로 해당 리소스의 사용범위가
 끝날 경우에 자동으로 해제를 해주어 예외가 발생하거나 하는 경우에는 획득한 자원이 해제됨을 보장하여 안전한 코드를 작성할 수 있다.
*/

class CriticalSectionLock
{
public:
	CriticalSectionLock(const CRITICAL_SECTION& cs) :m_pcs(&cs)
	{
		assert(m_pcs != nullptr);
		EnterCriticalSection((LPCRITICAL_SECTION)m_pcs);
	}

	~CriticalSectionLock()
	{
		if(m_pcs!=nullptr)
			LeaveCriticalSection((LPCRITICAL_SECTION)m_pcs);
	}

	//explicit : 암시적인 형변환을 막기위하여 사용
	explicit operator bool() { return true; }
private:
	const CRITICAL_SECTION* m_pcs;
};

//c#에서는 lock이라는 메크로를 선언해서 CriticalSection을 보다 쉽게 구현이 가능하지만
//c++은 없기 때문에 따로 만들어줘야한다
#define CSLOCK(cs_) if(CriticalSectionLock CONCATENATE(lock,__LINE__) = cs_) //__LINE__ : 디버거가 포함된 컴파일러들은 보통 실행하면서 어떤 라인에서 에러가났는지 출력해줌
