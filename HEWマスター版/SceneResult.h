/*===================================================
	
	[SceneResult.h]
	�T�v : ���U���g�V�[�����Ǘ�����
	Author : �o���đ�

===================================================*/

#pragma once
#include"SceneBase.h"
#include "sprite.h"

class SceneResult : public SceneBase
{
public:
	void Init();	//	�Q�[���̏���������	
	void Uninit();	//	�Q�[���̏I������
	void Update();	//	�Q�[���̍X�V����
	void Draw();	//	�Q�[���̕`�揈��
};

