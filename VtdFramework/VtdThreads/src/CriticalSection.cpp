#include <VtdThreads/CriticalSection.h>

namespace VTD {

CriticalSection::CriticalSection()
{
}

CriticalSection::~CriticalSection()
{
}

void CriticalSection::lock()
{
    mutex_.lock();
}

void CriticalSection::release()
{
    mutex_.unlock();
}

CriticalSection::CriticalSection(const CriticalSection&) { }
CriticalSection& CriticalSection::operator=(const CriticalSection&) { return *this;}

} //namespace VTD
