#include <Windows.h>
#include <memory>
#include "CloseHandle.h"

std::unique_ptr<char, decltype(LocalFree)*> error_message_for(DWORD e)
{
	LPSTR lpBuffer;
	if (FormatMessageA
	( /*_In_     DWORD     dwFlags     */FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK
	, /*_In_opt_ LPCVOID   lpSource    */nullptr
	, /*_In_     DWORD     dwMessageId */e
	, /*_In_     DWORD     dwLanguageId*/0
	, /*_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) != 0, _At_((LPSTR*)lpBuffer, _Outptr_result_z_))*/
		/*_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) == 0, _Out_writes_z_(nSize))                    */
		/*         LPSTR     lpBuffer    */LPSTR(&lpBuffer)
	, /*_In_     DWORD     nSize       */32
	, /*_In_opt_ va_list * Arguments   */nullptr
	))
		return { lpBuffer, LocalFree };
	else
		return { nullptr, LocalFree };
}
RAII::CloseHandle<INVALID_HANDLE_VALUE> open_file_for_input(LPCWSTR lpFileName)
{
	auto hFile = CreateFileW
	( /*_In_     LPCWSTR               lpFileName           */lpFileName
	, /*_In_     DWORD                 dwDesiredAccess      */GENERIC_READ
	, /*_In_     DWORD                 dwShareMode          */FILE_SHARE_READ
	, /*_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes */nullptr
	, /*_In_     DWORD                 dwCreationDisposition*/OPEN_EXISTING
	, /*_In_     DWORD                 dwFlagsAndAttributes */0
	, /*_In_opt_ HANDLE                hTemplateFile        */nullptr
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		//エラー
		//このスレッドにおいての直近のシステムエラーコードが得られる
		if (const auto errmsg = error_message_for(GetLastError())) {
			OutputDebugStringA(errmsg.get());
			OutputDebugStringA("\n");
		}
		else
			OutputDebugStringA("エラーメッセージ取得失敗\n");
		return INVALID_HANDLE_VALUE;
	}
	else {
		//成功
		return hFile;
	}
}


#include <stdexcept>
#include <iostream>
#include <sstream>
int main()
{
	try {
		static const wchar_t filename1[] = L"NUL";
		if (const auto hFile1 = open_file_for_input(filename1)) {
			static const wchar_t filename2[] = L"NUL";
			if (const auto hFile2 = open_file_for_input(filename2)) {
				//
			}
			else
				throw std::runtime_error((std::ostringstream() << "ファイル '" << filename2 << "' がオープンできませんでした。").str());
		}
		else
			throw std::runtime_error((std::ostringstream() << "ファイル '" << filename1 << "' がオープンできませんでした。").str());
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
