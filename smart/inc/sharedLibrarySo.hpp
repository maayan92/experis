#ifndef SHARED_LIBRARY_SO_HPP
#define SHARED_LIBRARY_SO_HPP

#include <cassert>
#include "uncopyable.hpp"
#include "iObserver.hpp"

namespace smart_house {

class SharedLibrarySo : private experis::Uncopyable {
public:
    SharedLibrarySo(const char* a_fileName);
    ~SharedLibrarySo();

    template<typename T>
    T SymbolAddr(const char* a_symbolName);

private:
    void* getSymbol(const char* a_symbolName);

private:
    void* m_handle;
};

template<typename T>
T SharedLibrarySo::SymbolAddr(const char* a_symbolName)
{
    assert(a_symbolName);
    return reinterpret_cast<T>(getSymbol(a_symbolName));
}

} // smart_house

#endif