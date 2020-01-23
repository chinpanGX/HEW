/*==================================

	[SceneGame.h]
	�T�v : �Q�[���V�[�����Ǘ�����
	Author : �o���đ�

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "Character.h"
#include "Field.h"
#include "camera.h"

//#	SceneGame�N���X:�e�N���X,SceneBase���p�������q�N���X
class SceneGame:public SceneBase
{
private:
	Character		m_Character;
	Field			m_Map;
	Camera			m_Camera;
	Score			m_Score;
	bool			EndCheck();
public:
	void Init();	//	�Q�[���̏���������	
	void Uninit();	//	�Q�[���̏I������
	void Update();	//	�Q�[���̍X�V����
	void Draw();	//	�Q�[���̕`�揈��
	Character*	SetCharacter();
	Field*		SetField();
	Camera*		SetCamera();
};
