#pragma once

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ゲームオブジェクトを見分ける為の構造体
enum class GameObjectTag
{
	Untagged,

	Camera,
	Light,
	TestMan,

	TERM
};

} // namespace
// EOF
