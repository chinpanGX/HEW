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
#include "CharacterCamera.h"


//	�}�N����`
#define FILELIST 1	//	�ǂݍ��ރt�@�C���̐�
#define	MODEL_CAR			"asset/model/ri.x"	// �ǂݍ��ރ��f����
#define	VALUE_MOVE_MODEL	(0.1f)					// �ړ����x
#define	RATE_MOVE_MODEL		(0.2f)					// �ړ������W��
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)		// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)					// ��]�����W��

#define	VALUE_JUMP				(10.0f)							// �W�����v��
#define	VALUE_GRAVITY			(0.45f)							// �d��
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��


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

/*---------------------------------------------------------------------------------
global
-----------------------------------------------------------------------------------*/
static HWND hWnd;				//���b�Z�[�W�\���Ɏg�p

static int	g_LaneStatus;			//���[���X�e�[�^�X
static int	g_count;				//��萔�J�E���^
static int	g_Q,g_A;				//����ԍ��i�[�A�񓚊i�[

static float		Speedtmp;					//SPEED�ꎞ�ۑ�


//�d�͂Ŏg�p
static bool flag;
static double Gravity;
static double moveGravity;

LPDIRECT3DDEVICE9 Character::pDevice;
//extern std::map<std::string, XFile *>g_pXFileList;
LPDIRECT3DTEXTURE9	Character::m_pTextureModel;		//	�e�N�X�`���ւ̃|�C���^
LPD3DXMESH			Character::m_pMeshModel;		//	���b�V�����ւ̃|�C���^
LPD3DXBUFFER		Character::m_pBuffMatModel;		//	�}�e���A�����ւ̃|�C���^
DWORD				Character::m_nNumMatModel;		//	�}�e���A�����̑���
//static Model g_Player;

/*-----------------------------------------
�֐����X
-----------------------------------------*/
Character::Character()
{
	m_pTextureModel = NULL;
	m_pMeshModel	= NULL;
	m_pBuffMatModel = NULL;
}


Character::~Character()
{
	
}


HRESULT Character::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	pDevice = GetD3DDevice();

	//�ʒu�E�����E�ړ��̏����ݒ�
	posModel = pos;
	rotModel = rot;
	rotDestModel = rot;
	moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.05f);

	//�d�͂̂��
	Gravity = -0.0089;	//�萔��˂���
	moveGravity = 0;
	flag = false;

	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(MODEL_CAR,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel)))
	{
		return E_FAIL;
	}
	return S_OK;
#if 0
	//!	XFlie�̃��[�h����
	// �ǂݍ��݃t�@�C�������X�g
	std::string file_name_list[] =
	{
		"asset/model/dai.x",
	};

	// XFile�ǂݍ���
	for (int i = 0; i < FILELIST; i++)
	{
		g_pXFileList[file_name_list[i]] = new XFile();
		g_pXFileList[file_name_list[i]]->Load(file_name_list[i]);
	}
#endif
	//���b�Z�[�W�ŗ��p���Ă邩��
	hWnd = GetHWND();
}


void Character::Uninit()
{
	
}


void Character::Update()
{
	CharacterCamera *pCamera;
	float fDiffRotY;

	// �J�����̎擾
	pCamera = GetCharCam();
#if 0
	if (KeyBoard::IsPress(DIK_A))
	{
		if (KeyBoard::IsPress(DIK_UP))
		{// �����ړ�
			moveModel.x += sinf(-D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(-D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_DOWN))
		{// ����O�ړ�
			moveModel.x += sinf(-D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(-D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		else
		{// ���ړ�
			moveModel.x += sinf(-D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(-D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_D))
	{
		if (KeyBoard::IsPress(DIK_UP))
		{// �E���ړ�
			moveModel.x += sinf(D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(D3DX_PI * 0.75f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		else if (KeyBoard::IsPress(DIK_DOWN))
		{// �E��O�ړ�
			moveModel.x += sinf(D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(D3DX_PI * 0.25f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{// �E�ړ�
			moveModel.x += sinf(D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;
			moveModel.z -= cosf(D3DX_PI * 0.50f - pCamera->rot.y) * VALUE_MOVE_MODEL;

			rotDestModel.y = pCamera->rot.y - D3DX_PI * 0.50f;
		}
	}
	else if (KeyBoard::IsPress(DIK_W))
	{// �O�ړ�
		moveModel.x += sinf(D3DX_PI * 1.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;
		moveModel.z -= cosf(D3DX_PI * 1.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;

		rotDestModel.y = pCamera->rot.y + D3DX_PI * 1.0f;
	}
	if (KeyBoard::IsPress(DIK_LSHIFT))
	{// ����]
		rotDestModel.y -= VALUE_ROTATE_MODEL;
		if (rotDestModel.y < -D3DX_PI)
		{
			rotDestModel.y += D3DX_PI * 2.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_RSHIFT))
	{// �E��]
		rotDestModel.y += VALUE_ROTATE_MODEL;
		if (rotDestModel.y > D3DX_PI)
		{
			rotDestModel.y -= D3DX_PI * 2.0f;
		}
	}
#endif
	
	moveModel.x += sinf(D3DX_PI * 0.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;
	moveModel.z -= cosf(D3DX_PI * 0.0f - pCamera->rot.y) * VALUE_MOVE_MODEL;

	rotDestModel.y = pCamera->rot.y + D3DX_PI * 0.0f;

	

	// �ړI�̊p�x�܂ł̍���
	fDiffRotY = rotDestModel.y - rotModel.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	rotModel.y += fDiffRotY * RATE_ROTATE_MODEL;
	if (rotModel.y > D3DX_PI)
	{
		rotModel.y -= D3DX_PI * 2.0f;
	}
	if (rotModel.y < -D3DX_PI)
	{
		rotModel.y += D3DX_PI * 2.0f;
	}

	/// �ʒu�ړ�
	posModel.x += moveModel.x;
	posModel.z += moveModel.z;


	// �ړ��ʂɊ�����������
	moveModel.x += (0.0f - moveModel.x) * RATE_MOVE_MODEL;
	moveModel.z += (0.0f - moveModel.z) * RATE_MOVE_MODEL;

	if (KeyBoard::IsPress(DIK_A))
	{
		posModel.x += RATE_MOVE_MODEL;
	}
	if (KeyBoard::IsPress(DIK_D))
	{
		posModel.x -= RATE_MOVE_MODEL;
	}


	//������R���l���Ȃ��ꍇ
	if (flag == true)
	{
		if (posModel.y > -100)
		{
			moveGravity += Gravity;
			moveModel.y += moveGravity;
		}
	}

	if (KeyBoard::IsPress(DIK_G))
	{
		flag = true;
	}


	
#if 0
	// �͈̓`�F�b�N
	if (g_posModel.x < -310.0f)
	{
		g_posModel.x = -310.0f;
	}
	if (g_posModel.x > 310.0f)
	{
		g_posModel.x = 310.0f;
	}
	if (g_posModel.z < -310.0f)
	{
		g_posModel.z = -310.0f;
	}
	if (g_posModel.z > 310.0f)
	{
		g_posModel.z = 310.0f;
	}
#endif

	if (KeyBoard::IsPress(DIK_RETURN))
	{// ���Z�b�g
		posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rotDestModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
#if 0
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
#endif

}


void Character::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorldModel);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotModel.y, rotModel.x, rotModel.z);
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &mtxRot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, posModel.x, moveModel.y, posModel.z);
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &mtxTranslate);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldModel);
	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTextureModel);
		//�`��
		m_pMeshModel->DrawSubset(nCntMat);

	}
	//�}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}


