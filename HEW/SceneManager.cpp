/*==============================================

	[SceneManager.cpp]	
	Author : �o���đ�

===============================================*/
#include "main.h"
#include "input.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneModeSelect.h"
#include "SceneTutorial.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneDebug.h"

//	�X�^�e�B�b�N�ϐ�
SceneBase			*SceneManager::m_scene[SCENE_NUMBER];	//	�V�[���̃C���X�^���X���i�[[�V�[���̔z��]
SCENE_STATE			SceneManager::m_sceneState;				//	�V�[���̃X�e�[�g�}�V���i�V�[���̏�Ԃ��i�[�j
LPDIRECT3DDEVICE9	SceneManager::p3DDevice;				//	�f�o�C�X

//	����������
void SceneManager::Init()
{
	p3DDevice = GetD3DDevice();			//	�f�o�C�X�̎擾

	//	�������̊m��
	m_scene[0] = new SceneTitle;		
	m_scene[1] = new SceneModeSelect;	
	m_scene[2] = new SceneTutorial;		
	m_scene[3] = new SceneGame;			
	m_scene[4] = new SceneResult;
	m_scene[5] = new SceneDebug;

	m_sceneState = SCENE_TITLE;			//	�����V�[���̐ݒ�(�Q�[�����N�������Ƃ��̍ŏ��̃V�[��)
	m_scene[m_sceneState]->Init();		//	�����V�[���̏�����
}

//	�I������
void SceneManager::Uninit()
{
	//	�e�V�[����Uninit�֐����Ăяo��
	m_scene[5]->Uninit();
	m_scene[4]->Uninit();
	m_scene[3]->Uninit();
	m_scene[2]->Uninit();
	m_scene[1]->Uninit();
	m_scene[0]->Uninit();

	//	�e�V�[���̃������̉��
	delete m_scene[5];
	delete m_scene[4];
	delete m_scene[3];
	delete m_scene[2];
	delete m_scene[1];
	delete m_scene[0];
}

//	�X�V����
void SceneManager::Update()
{
	m_scene[m_sceneState]->Update();	//	�e�V�[����Update�֐��̌Ăяo��
}

//	�`�揈��
void SceneManager::Draw()
{
	m_scene[m_sceneState]->Draw();		//	�e�V�[����Draw�֐��̌Ăяo��
}

//	�V�[���J�ڏ���
void SceneManager::ChangeSceneState()
{
	switch (m_sceneState)
	{
	case SCENE_TITLE:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_MODESELECT;	//	���[�h�I���ɑJ��
		m_scene[m_sceneState]->Init();
		break;
	case SCENE_MODESELECT:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_TUTORIAL;		//	�`���[�g���A���֑J��
		m_scene[m_sceneState]->Init();
		break;
	case SCENE_TUTORIAL:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_GAME;			//	�Q�[���֑J��
		m_scene[m_sceneState]->Init();
		break;
	case SCENE_GAME:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_RESULT;		//	���U���g�֑J��
		m_scene[m_sceneState]->Init();
		break;
	case SCENE_RESULT:
		m_scene[m_sceneState]->Uninit();
		m_sceneState = SCENE_TITLE;			//	�^�C�g���֑J��
		m_scene[m_sceneState]->Init();
		break;
	//!	�f�o�b�O�V�[���͂��Ƃŏ���
	case SCENE_DEBUG:	
		m_scene[m_sceneState]->Uninit();
	}
}
 