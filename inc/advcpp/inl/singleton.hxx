namespace advcpp {

template<typename T>
T* Singleton<T>::instance = 0;

template<typename T>
experis::AtomicFlag Singleton<T>::firstThread(false);

template<typename T>
experis::AtomicFlag Singleton<T>::wasCreated(false);

template<typename T>
T& Singleton<T>::Instance()
{
    if(firstOneToCome()) {
        createSingleton();
    }
    else {
        waitTillSingletonIsCreated();
    }
    
    return *instance;
}

template<typename T>
bool Singleton<T>::firstOneToCome()
{
    return firstThread.CheckAndSet();
}

template<typename T>
void Singleton<T>::createSingleton()
{
    instance = new T();
    wasCreated.CheckAndSet();
}

template<typename T>
void Singleton<T>::waitTillSingletonIsCreated()
{
    while(!wasCreated.GetValue())
        ;
}

} // advcpp