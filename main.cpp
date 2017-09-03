#include <cassert>
#include <locale>
#include <iostream>


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
