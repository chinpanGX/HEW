/*==============================================

	[SceneDebug.h]
	Author : �o���đ�

==============================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "DebugCamera.h"
#include "Map.h"
#include "Character.h"
#include "sprite.h"

//# SceneDebug : �e�N���XSceneBase
class SceneDebug: public SceneBase
{
private:
	//Character			m_Character;	//	Character�^�̃C���X�^���X
	CharacterCamera	m_CharaCamera;	//	CharacterCamera�^�̃C���X�^���X
	//DebugCamera			m_Camera;		//	DebugCamera�^�̃C���X�^���X	
	Map					m_Map;			//	Map�^�̃C���X�^���X
	Sprite				m_Sprite;		//	Sprite�^�̃C���X�^���X
public:
	//SceneBase�̃����o�[�֐��̃I�[�o�[���C�h
	void Init();	//	�Q�[���̏���������	
	void Uninit();	//	�Q�[���̏I������
	void Update();	//	�Q�[���̍X�V����
	void Draw();	//	�Q�[���̕`�揈��
};

