/*============================================

[Character.cpp]
Author :hohman yuushi

=============================================*/

#include "Character.h"
#include "Map.h"
#include "Model.h"
#include "input.h"
#include "main.h"
#include <d3dx9.h>
#include <math.h>
#include "Controller.h"
#include "XFile.h"


//	�}�N����`
#define FILELIST 1	//	�ǂݍ��ރt�@�C���̐�

/*--------------------------------------------------------------
enum
---------------------------------------------------------------*/
enum PLAYER_STATE		//g_Player�̏�ԑJ��
{
	PLAYER_WAIT,		//	�ҋ@
	PLAYER_START,		//	�J�n
	PLAYER_ANSWER,		//	��
	PLAYER_JUMP,		//	�W�����v
	PLAYER_FINISH		//	�I��(���n����)
};


enum LANE_STATE			//���[���̂Ȃ񂩂���
{
	LANE_START,


	LANE_SELECT,

	LANE_1,
	LANE_2,
	LANE_3,
	LANE_4,


	LANE_JUMP,

	LANE_END
};


/*---------------------------------------------------------------------------------
global
-----------------------------------------------------------------------------------*/
static HWND hWnd;				//���b�Z�[�W�\���Ɏg�p

static int	g_LaneStatus;			//���[���X�e�[�^�X
static int	g_count;				//��萔�J�E���^
static int	g_Q,g_A;				//����ԍ��i�[�A�񓚊i�[

static float		Speedtmp;					//SPEED�ꎞ�ۑ�


LPDIRECT3DDEVICE9 Character::g_pD3DDevice;

extern std::map<std::string, XFile *>g_pXFileList;

//static Model g_Player;

/*-----------------------------------------
�֐����X
-----------------------------------------*/
Character::Character()
{

}


Character::~Character()
{
	
}


void Character::Init()
{
	//!	XFlie�̃��[�h����
	// �ǂݍ��݃t�@�C�������X�g
	std::string file_name_list[] =
	{
		"asset/model/ri.x",
	};

	// XFile�ǂݍ���
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}

	//���b�Z�[�W�ŗ��p���Ă邩��
	hWnd = GetHWND();
}


void Character::Uninit()
{

}


void Character::Update()
{
	CharacterCamera* p_CharCamera;
	p_CharCamera = GetCharCam();

	g_pD3DDevice = GetD3DDevice();
	// ���[���h���W�s��쐬
	D3DXMATRIX world_matrix, trans_matrix, rot_matrix, scale_matrix;
	D3DXMatrixIdentity(&world_matrix);
	D3DXMatrixTranslation(&trans_matrix, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&rot_matrix, angle.y, angle.x, angle.z);
	D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.y);

	world_matrix *= rot_matrix * trans_matrix;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_matrix);

	if (pmodel != NULL)
	{
		pmodel->Draw();
	}

	//p_CharCamera->Init = D3DXVECTOR3(position.x, position.y, position.z);
	//p_CharCamera->Init = D3DXVECTOR3(position.x, position.y, position.z);

	if (KeyBoard::IsTrigger(DIK_W))
	{
		position.y += 1.0f;
		position.z += 1.0f;
	}
}


void Character::Draw()
{
}
