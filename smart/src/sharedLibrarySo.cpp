#include "sharedLibrarySo.hpp"
#include <stdexcept>
#include <dlfcn.h>
using namespace std;

namespace smart_house {

SharedLibrarySo::SharedLibrarySo(const char* a_fileName)
{
    assert(a_fileName);
    m_handle = dlopen(a_fileName, RTLD_LAZY);
    if(!m_handle) {
        throw runtime_error(::dlerror());
    }
}

SharedLibrarySo::~SharedLibrarySo()
{
    ::dlclose(m_handle);
}

void* SharedLibrarySo::getSymbol(const char* a_symbolName)
{
    void* ptr = ::dlsym(m_handle, a_symbolName);
    if(!ptr) {
        throw runtime_error(::dlerror());
    }

    return ptr;
}

} // smart_house