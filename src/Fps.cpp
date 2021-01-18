#include "Fps.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Fps::Fps()
	: mFps(0)
	, mFrameTime(0)
	, mMinFrameTime(1.0f / Define::Fps)
{
	QueryPerformanceCounter(&mTimeStart);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Fps::~Fps()
{
}

//-------------------------------------------------------------------------------------------------
/// fps�𒲐�����
void Fps::adjust()
{
	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&mTimeEnd);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	mFrameTime = static_cast<float>(mTimeEnd.QuadPart - mTimeStart.QuadPart) / static_cast<float>(mTimeFreq.QuadPart);

	// ���Ԃɗ]�T������ꍇ
	if (mFrameTime < mMinFrameTime) {
		// �~���b�ɕϊ�
		DWORD sleepTime = static_cast<DWORD>((mMinFrameTime - mFrameTime) * 1000);

		// �҂�
		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);

		return;
	}

	// �o�ߎ��Ԃ�0���傫��
	if (mFrameTime > 0) {
		// ����fps���v�Z
		mFps = (mFps * 0.99f) + (0.01f / mFrameTime);
	}

	// ����ւ�
	mTimeStart = mTimeEnd;
}

//-------------------------------------------------------------------------------------------------
/// ���݂�fps��`�悷��
void Fps::draw() const
{
}

} // namespace
// EOF
