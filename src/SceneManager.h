#pragma once

//-------------------------------------------------------------------------------------------------
#include <stack>
#include <memory>

#include "SceneList.h"
#include "IOnSceneChangedListener.h"
#include "AbstractScene.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace myGame{

/// シーン管理
class SceneManager : public IOnSceneChangedListener
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SceneManager();
	~SceneManager();
	//@}

	/// @name 動作
	//@{
	void run();
	//@}

	/// @name シーン遷移
	//@{
	void onSceneChanged(const SceneList aSceneList) override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// シーンのスタック
	std::stack<std::shared_ptr<AbstractScene>> mSceneStack;
	/// fps制御クラス
	Fps mFps;
	//@}

};

} // namespace
// EOF
