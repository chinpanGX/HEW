/*==================================

	[SceneGame.h]
	�T�v : �Q�[���V�[�����Ǘ�����
	Author : �o���đ�

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"

//#	SceneGame�N���X:�e�N���X,SceneBase���p�������q�N���X
class SceneGame:public SceneBase
{
private:

	bool			EndCheck();
public:
	void Init();	//	�Q�[���̏���������	
	void Uninit();	//	�Q�[���̏I������
	void Update();	//	�Q�[���̍X�V����
	void Draw();	//	�Q�[���̕`�揈��
};
