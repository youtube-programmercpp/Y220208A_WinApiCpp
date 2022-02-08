#include "CloseHandle.h"
#include <utility>

template<HANDLE hInvalid>RAII::CloseHandle<hInvalid>::CloseHandle(HANDLE&& hObject) noexcept
	: hObject(hObject)
{
	hObject = hInvalid;
}
template RAII::CloseHandle<INVALID_HANDLE_VALUE>::CloseHandle(HANDLE&& hObject) noexcept;
template RAII::CloseHandle<nullptr             >::CloseHandle(HANDLE&& hObject) noexcept;

template<HANDLE hInvalid>RAII::CloseHandle<hInvalid>::CloseHandle() noexcept
	: CloseHandle(hInvalid)
{
}
template RAII::CloseHandle<INVALID_HANDLE_VALUE>::CloseHandle() noexcept;
template RAII::CloseHandle<nullptr             >::CloseHandle() noexcept;

template<HANDLE hInvalid>RAII::CloseHandle<hInvalid>::~CloseHandle()
{
	if (hObject != hInvalid)
		::CloseHandle(hObject);
}
template RAII::CloseHandle<INVALID_HANDLE_VALUE>::~CloseHandle();
template RAII::CloseHandle<nullptr             >::~CloseHandle();

template<HANDLE hInvalid>RAII::CloseHandle<hInvalid>::CloseHandle(CloseHandle&& r) noexcept
	: CloseHandle(std::move(r.hObject))
{
}
template RAII::CloseHandle<INVALID_HANDLE_VALUE>::CloseHandle(CloseHandle&& r) noexcept;
template RAII::CloseHandle<nullptr             >::CloseHandle(CloseHandle&& r) noexcept;

template<HANDLE hInvalid>auto RAII::CloseHandle<hInvalid>::operator=(CloseHandle&& r) noexcept->CloseHandle&
{
	std::swap(hObject, r.hObject);
	return *this;
}
template auto RAII::CloseHandle<INVALID_HANDLE_VALUE>::operator=(CloseHandle&& r) noexcept->CloseHandle&;
template auto RAII::CloseHandle<nullptr             >::operator=(CloseHandle&& r) noexcept->CloseHandle&;
