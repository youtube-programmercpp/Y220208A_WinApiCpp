#include "ReleaseMutex.h"
#include <utility>
#if 0
RAII::ReleaseMutex::ReleaseMutex(HANDLE&& hMutex) noexcept
	: hMutex(hMutex)
{
	hMutex = nullptr;
}

RAII::ReleaseMutex::ReleaseMutex() noexcept
	: ReleaseMutex(nullptr)
{
}

RAII::ReleaseMutex::~ReleaseMutex()
{
	if (hMutex != nullptr)
		::ReleaseMutex(hMutex);
}

RAII::ReleaseMutex::ReleaseMutex(ReleaseMutex&& r) noexcept
	: ReleaseMutex(std::move(r.hMutex))
{
}

auto RAII::ReleaseMutex::operator=(ReleaseMutex&& r) noexcept->ReleaseMutex&
{
	std::swap(hMutex, r.hMutex);
	return *this;
}

RAII::ReleaseMutex::operator bool() const noexcept
{
	return hMutex != nullptr;
}
#endif
