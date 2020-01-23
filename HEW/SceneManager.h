/*======================================================

	[SceneManager.h]
	�T�v : �Q�[�����[�v���Ǘ�����
	Author : �o���đ�

======================================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"

//#	SceneManager�N���X
class SceneManager
{
private:
	static SceneBase			*m_scene[4];	//	�V�[���Ǘ��|�C���^�ϐ�
	static SCENE_STATE			m_sceneState;	//	�V�[���X�e�[�g�̊Ǘ��ϐ�
	static LPDIRECT3DDEVICE9	p3DDevice;		//	�f�o�C�X�̎擾�ϐ�
public:
	static void Init();					//	����������
	static void Uninit();				//	�I������
	static void Update();				//	�X�V����
	static void Draw();					//	�`�揈��
	static void ChangeSceneState();		//	�V�[���J�ڏ���
	static SceneBase*	SetSceneGame();	
};

