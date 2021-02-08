#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SceneManager::SceneManager()
	: mSceneStack()
	, mFps()
{
	// テストシーンをプッシュ
	mSceneStack.push(std::make_shared<TestScene>(this));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
SceneManager::~SceneManager()
{
	// スタックを全部ポップする(スタックを空にする)
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}

//-------------------------------------------------------------------------------------------------
/// 動作
void SceneManager::run()
{
	Direct3D9::getInst()->drawStart();

	// シーン処理
	if (!mSceneStack.empty()) {
		mSceneStack.top()->update();
		mSceneStack.top()->draw();
	}

	// fpsを調整する
	mFps.adjust();
	mFps.draw();

	Direct3D9::getInst()->drawEnd();
}

//-------------------------------------------------------------------------------------------------
/// シーン遷移
/// @param aSceneList 切り替えるシーンを指定する構造体
void SceneManager::onSceneChanged(const SceneList aSceneList)
{
	switch (aSceneList) {
	case SceneList::POP:
		// 現在のシーンをポップする
		mSceneStack.pop();
		break;
	case SceneList::Test:
		mSceneStack.push(std::make_shared<TestScene>(this));
		break;
	case SceneList::Title:
		//mSceneStack.push(std::make_shared<TitleScene>(this));
		break;
	case SceneList::Game:
		//mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	default:
		// エラーメッセージ
		MessageBox(NULL, TEXT("存在しないシーンを読み込もうとしました。"), TEXT("SCENE_ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
