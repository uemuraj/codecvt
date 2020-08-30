#include <cassert>
#include <locale>
#include <iostream>

//
// __cplusplus �̒l�́u�ǉ��̃I�v�V�����v�� /Zc:__cplusplus �𒼐ڎw�肵�Ȃ��� 199711L �̂܂܂ɂȂ��Ă��܂�
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
		assert(convert(L"�ق��ق�").compare("�ق��ق�") == 0);
		assert(convert("�ق��ق�").compare(L"�ق��ق�") == 0);
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}

#else

// �}���`�o�C�g������Ƃ̕ϊ���̌^�͌��ǂP�Ɍ��܂�
using mbs_codecvt = std::codecvt<wchar_t, char, std::mbstate_t>;

void main()
{
	// local �N���X�̃f�t�H���g�R���X�g���N�^�́A���݂̃O���[�o�����P�[���𕡐����邪...
	// �O���[�o�����P�[������ɐݒ肵�Ă��Ȃ���΁A������Ԃ͓��{��ł͂Ȃ�

	// local �N���X�̃R���X�g���N�^�ɋ󕶎����n���ƁA���ϐ��Ȃ� OS �̃��[���ɏ]�������P�[�������������
	// ���s�������{��ł���Γ��{��ɂȂ�A�����łȂ���Γ��{��ł͂Ȃ�

	std::locale::global(std::locale(""));

	// �ϊ���͎Q�ƂƂ��ē�����
	const mbs_codecvt & cvt = std::use_facet<mbs_codecvt>(std::locale());

	// wstring_convert �͕ϊ���ւ̃|�C���^���g��
	std::wstring_convert<mbs_codecvt> converter(&cvt);

	// ���e�����łȂ������̓��͒l�Ńe�X�g���������ǂ���������... mbs �̒l�������ƍŏ��̕�����Ɠ����͂�
	std::wstring wcs = converter.from_bytes("�ق��ق�");
	std::string mbs = converter.to_bytes(wcs.c_str());

	std::cout << mbs << std::endl;

	assert(mbs.compare("�ق��ق�") == 0);
}

#endif
