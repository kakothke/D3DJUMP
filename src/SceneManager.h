#pragma once

//-------------------------------------------------------------------------------------------------
#include <stack>
#include <memory>

#include "SceneList.h"
#include "IOnSceneChangedListener.h"
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
namespace myGame{

/// �V�[���Ǘ�
class SceneManager : public IOnSceneChangedListener
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	SceneManager();
	~SceneManager();
	//@}

	/// @name ����
	//@{
	void run() const;
	//@}

	/// @name �V�[���J��
	//@{
	void onSceneChanged(const SceneList aSceneList) override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�[���̃X�^�b�N
	std::stack<std::shared_ptr<AbstractScene>> mSceneStack;
	//@}

};

} // namespace
// EOF
