/*======================================================

	[SceneTutorial.h]
	�T�v : �`���[�g���A���V�[�����Ǘ�����
	Author : �o���đ�

======================================================*/

#pragma once
#include "SceneBase.h"

//# SceneTutorial�N���X
/* �`���[�g���A���V�[�����Ǘ�����N���X */
class SceneTutorial : public SceneBase
{
public:	
	void Init();	//	�Q�[���̏���������	
	void Uninit();	//	�Q�[���̏I������
	void Update();	//	�Q�[���̍X�V����
	void Draw();	//	�Q�[���̕`�揈��
};

