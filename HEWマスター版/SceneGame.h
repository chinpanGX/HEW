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
	int State;		//���p�X�e�[�g
	Mondai			test;
	Sprite			m_Sprite;
	D3DCOLOR		m_Color;
	bool			m_ColorFlag; //	�I��UI�t���O
	
	//	Update()�̃w���p�[�֐�
	void UpdateFrame();
	void UpdateState();
	bool EndCheck();

	//	Draw()�̃w���p�[�֐�
	void DrawFrame();

public:
	void Init();	//	�Q�[���̏���������	
	void Uninit();	//	�Q�[���̏I������
	void Update();	//	�Q�[���̍X�V����
	void Draw();	//	�Q�[���̕`�揈��
};
