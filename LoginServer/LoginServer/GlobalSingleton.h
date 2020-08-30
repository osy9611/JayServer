#pragma once

template<typename T>
class GlobalSingleton
{
public:
	inline static T& Singleton() { return SingletonCreator::Access(); }
	inline			 GlobalSingleton() {}
private:
	GlobalSingleton(const GlobalSingleton&);
	GlobalSingleton& operator=(const GlobalSingleton&);
protected:
	class SingletonCreator
	{
	public:
		inline SingletonCreator()
		{
			Access();
		}

		inline static T& Access()
		{
			/*
			정적 객체가 인라인 함수로 선언된 경우
			둘 이상의 객체를 만들 수 있다.
			이 문제를 해결하려면 내부에 정적 인스턴스있던 비 인라인 기능에 엑세스를 해야한다.
			*/
			static T& ref = _CreateUniqueInstance();
			return ref;
		}

	private:
		inline void _ToGuaranteeInstanceCreationBeforeMainFunction() {}

		__declspec(noinline)static T& _CreateUniqueInstance()
		{
			static T obj;
			//의미 없는 멤버 함수를 호출하여 'ms_SingletonCreator'를 생성해야 한다.
			//'T' 유형의 'obj'가 main()보다 먼저 생성된다는 뜻이다.
			ms_SingletonCreator._ToGuaranteeInstanceCreationBeforeMainFunction();
			return obj;
		}
	private:
		static SingletonCreator ms_SingletonCreator;
	};
};

template<typename T>
typename GlobalSingleton<T>::SingletonCreator GlobalSingleton<T>::SingletonCreator::ms_SingletonCreator;