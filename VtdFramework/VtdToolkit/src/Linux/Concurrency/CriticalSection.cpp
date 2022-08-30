#include <VtdThreads/CriticalSection.h>

namespace VTD {

CriticalSection::CriticalSection() {
    ::pthread_mutex_init(&mutex_, NULL);
}

CriticalSection::~CriticalSection() {
    ::pthread_mutex_destroy(&mutex_);
}

void CriticalSection::lock() {
    ::pthread_mutex_lock(&mutex_);
}

void CriticalSection::release() {
    ::pthread_mutex_unlock(&mutex_);
}

CriticalSection::CriticalSection(const CriticalSection&) { }
CriticalSection& CriticalSection::operator=(const CriticalSection&) { }

} //namespace VTD
