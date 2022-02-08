#pragma once
#include <Windows.h>
namespace RAII {
	template<HANDLE hInvalid>class CloseHandle
	{
		HANDLE hObject;
	public:
		CloseHandle(HANDLE&& hObject) noexcept;
		CloseHandle() noexcept;
		~CloseHandle();
		CloseHandle(CloseHandle&& r) noexcept;
		auto operator=(CloseHandle&& r) noexcept->CloseHandle&;
		explicit operator bool() const noexcept
		{
			return hObject != hInvalid;
		}
	};
}
