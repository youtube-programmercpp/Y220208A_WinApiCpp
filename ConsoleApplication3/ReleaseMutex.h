#pragma once
#include <Windows.h>
#include <memory>
namespace RAII {
	class ReleaseMutex
	{
		std::shared_ptr<std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(CloseHandle)*>> hMutex;
	public:
		ReleaseMutex(const std::shared_ptr<std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(CloseHandle)*>>& hMutex) noexcept;
		//¡‰ñ‚Í‚±‚±‚ÅI‚í‚è
	};
}
