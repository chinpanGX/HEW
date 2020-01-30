/*==================================

	[SceneGame.h]
	�T�v : �Q�[���V�[�����Ǘ�����
	Author : �o���đ�

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "mondai.h"

//#	SceneGame�N���X:�e�N���X,SceneBase���p�������q�N���X
class SceneGame : public SceneBase
{
private:
	int flag;		//���p�t���O
	Mondai			test;
	Sprite			m_Sprite;
	D3DCOLOR		m_Color;
	bool			m_ColorFlag;
	bool			EndCheck();
public:
	void Init();	//	�Q�[���̏���������	
	void Uninit();	//	�Q�[���̏I������
	void Update();	//	�Q�[���̍X�V����
	void Draw();	//	�Q�[���̕`�揈��
};
