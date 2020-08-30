#include <cassert>
#include <locale>
#include <iostream>

//
// __cplusplus の値は「追加のオプション」で /Zc:__cplusplus を直接指定しないと 199711L のままになってしまう
//
// * https://docs.microsoft.com/ja-jp/cpp/build/reference/zc-cplusplus?view=vs-2019
// 

#pragma message("__cplusplus=" _CRT_STRINGIZE(__cplusplus))
#pragma message("_MSVC_LANG=" _CRT_STRINGIZE(_MSVC_LANG))

#if (__cplusplus >= 201703L) || (_MSVC_LANG >= 201703L)

#include "string_convert.h"

void main()
{
	std::locale::global(std::locale(""));

	try
	{
		assert(convert(L"ほげほげ").compare("ほげほげ") == 0);
		assert(convert("ほげほげ").compare(L"ほげほげ") == 0);
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}

#else

// マルチバイト文字列との変換器の型は結局１つに決まる
using mbs_codecvt = std::codecvt<wchar_t, char, std::mbstate_t>;

void main()
{
	// local クラスのデフォルトコンストラクタは、現在のグローバルロケールを複製するが...
	// グローバルロケールを特に設定していなければ、初期状態は日本語ではない

	// local クラスのコンストラクタに空文字列を渡すと、環境変数など OS のルールに従ったロケールが複製される
	// 実行環境が日本語であれば日本語になり、そうでなければ日本語ではない

	std::locale::global(std::locale(""));

	// 変換器は参照として得られる
	const mbs_codecvt & cvt = std::use_facet<mbs_codecvt>(std::locale());

	// wstring_convert は変換器へのポインタを使う
	std::wstring_convert<mbs_codecvt> converter(&cvt);

	// リテラルでなく何かの入力値でテストした方が良さそうだが... mbs の値がちゃんと最初の文字列と同じはず
	std::wstring wcs = converter.from_bytes("ほげほげ");
	std::string mbs = converter.to_bytes(wcs.c_str());

	std::cout << mbs << std::endl;

	assert(mbs.compare("ほげほげ") == 0);
}

#endif
