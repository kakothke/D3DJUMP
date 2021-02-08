#include "Fps.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "DebugFont.h"
#include <tchar.h>

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Fps::Fps()
	: mFps(0)
	, mFrameTime(0)
	, mMinFrameTime(1.0f / Define::Fps)
{
	QueryPerformanceCounter(&mTimeStart);
}

//-------------------------------------------------------------------------------------------------
/// fpsを調整する
void Fps::adjust()
{
	// 今の時間を取得
	QueryPerformanceCounter(&mTimeEnd);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	mFrameTime = static_cast<float>(mTimeEnd.QuadPart - mTimeStart.QuadPart) / static_cast<float>(mTimeFreq.QuadPart);

	// 時間に余裕がある場合
	if (mFrameTime < mMinFrameTime) {
		// ミリ秒に変換
		DWORD sleepTime = static_cast<DWORD>((mMinFrameTime - mFrameTime) * 1000);

		// 待つ
		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);

		return;
	}

	// 経過時間が0より大きい
	if (mFrameTime > 0) {
		// 平均fpsを計算
		mFps = (mFps * 0.99f) + (0.01f / mFrameTime);
	}

	// 入れ替え
	mTimeStart = mTimeEnd;
}

//-------------------------------------------------------------------------------------------------
/// 現在のfpsを描画する
void Fps::draw() const
{
	TCHAR debugText[20];
	_stprintf_s(debugText, 20, _T("%2.0ffps"), mFps);
	DebugFont::getInst()->draw(debugText, 170, 50);
}

} // namespace
// EOF
