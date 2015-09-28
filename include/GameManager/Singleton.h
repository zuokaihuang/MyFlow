//
//  Singleton.h
//  HelloWorldDemo
//
//  Created by yons on 15/4/4.
//
//

#ifndef HelloWorldDemo_Singleton_h
#define HelloWorldDemo_Singleton_h

namespace tds{

	template <class T>
	class Singleton{

	public:

		static inline T* Instance();

		void Release();

	protected:

		Singleton(){}
		~Singleton(){}

		static T* m_Instance;


	};


	template<class T>
	inline T* Singleton<T>::Instance(){

		if (nullptr == m_Instance){
			m_Instance = new T;
		}
		return m_Instance;

	}

	template<class T>
	void Singleton<T>::Release(){

		if (m_Instance){
			return;
		}
		delete m_Instance;
		m_Instance = nullptr;

	}

#define DECLARE_SINGLETON_MEMBER(_Ty)	\
	template <> _Ty* Singleton<_Ty>::m_Instance = nullptr;

};//end namesapce tds
#endif
