#include <windows.h>
#include <type_traits>
template<class CharT, class A, class W, std::enable_if_t<std::is_same<CharT,  char  >::value, bool> = true>A AW(A a, W w) { return a; }
template<class CharT, class A, class W, std::enable_if_t<std::is_same<CharT, wchar_t>::value, bool> = true>W AW(A a, W w) { return w; }

#define	FUNCTION_AW(CharT, name)   AW<CharT>(name##A, name##W)

template<class CharT>int StringLength(const CharT* s)
{
	return FUNCTION_AW(CharT, lstrlen)(s);
}

int main()
{
	const int n = StringLength( "•¶Žš—ñ");// CharT ...  char   Œ^
	const int m = StringLength(L"•¶Žš—ñ");// CharT ... wchar_t Œ^
}
