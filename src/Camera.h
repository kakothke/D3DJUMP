#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// カメラ
class Camera : public GameObject
{
public:
	/// @name コンストラクタ
	//@{
	Camera();
	Camera(Transform aTransform);
	Camera(float aZoom);
	Camera(Transform aTransform, float aZoom);
	//@}
	
	/// @name 更新/描画
	//@{
	virtual void update() override;
	virtual void draw() const override {}
	//@}

protected:
	/// @name 内部実装関数
	//@{
	/// 射影
	void setViewMatrix();
	/// 指定した位置を向く
	void lookAt(Vector3 aPos);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// 注視点
	Vector3 mLookPos;
	// / 視野角
	float mZoom;
	/// 注視中
	bool mIslookAt;
	//@}

};

} // namespace
// EOF
