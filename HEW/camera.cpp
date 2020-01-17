//=============================================================================
//
// �J�������� [camera.cpp]
//
//=============================================================================
#include "camera.h"
#include "Character.h"
#include "input.h"
#include "debugproc.h"
#include "ObjectManager.h"
#include "Controller.h"

// �}�N����`
#define CAM_POS_V_X         (0.0f)                                          
#define CAM_POS_V_Y         (100.0f)                                        
#define CAM_POS_V_Z         (250.0f)                                        
#define CAM_POS_R_X         (0.0f)                                          
#define CAM_POS_R_Y         (50.0f)                                         
#define CAM_POS_R_Z         (-30.0f)                                        
#define VIEW_ANGLE          (D3DXToRadian(45.0f))                            
#define VIEW_ASPECT         ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)    
#define VIEW_NEAR_Z         (10.0f)                                         
#define VIEW_FAR_Z          (1000.0f)                                        
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// ����p
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z			(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(100000.0f)										// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA	(2.0f)											// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)								// �J�����̉�]��
#define	INTERVAL_CAMERA_R	(12.5f)					// ���f���̎����̐�܂ł̋���
#define	RATE_CHASE_CAMERA_V	(0.35f)					// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)					// �J�����̒����_�ւ̕␳�W��
#define	CHASE_HEIGHT_V		(100.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R		(0.0f)					// �ǐՎ��̒����_�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA	g_camera;		// �J�������

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT Camera_Initialize(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, 250.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 50.0f, 30.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 100.0f, 250.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 50.0f, 30.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fRateRotAuto = 0.01f;

	float vx,vz;
	vx = g_camera.posV.x - g_camera.posR.x;
	vz = g_camera.posV.z - g_camera.posR.z;
	g_camera.fLengthInterval = sqrtf(vx * vx + vz * vz);

	g_camera.fHeightV = CHASE_HEIGHT_V;
	g_camera.fHeightR = CHASE_HEIGHT_R;

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void Camera_Finalize(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void Camera_Update(void)
{
	Character *pPlayer;
	// �v���C���[���擾
	pPlayer = ObjectManager::SetCharacter();
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 rotPlayer;
	D3DXVECTOR3 movePlayer;
	float fIntervalCamera, fLengthMove;
	float fRateChaseCameraP, fRateChaseCameraR;
	float fHeightFieldPlayer;
	// �v���C���[�̈ʒu�擾
	posPlayer = pPlayer->m_position;

	// �v���C���[�̖ړI�̌����擾
	rotPlayer = pPlayer->m_rotation;

	// �v���C���[�̈ړ��ʎ擾
	movePlayer = pPlayer->m_velocity;

	// �v���C���[�����݂��鍂��
	fHeightFieldPlayer = posPlayer.y;

	// �v���C���[�̈ړ���
	fLengthMove = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;

	if(movePlayer.x < -0.05f || movePlayer.x > 0.05f
	|| movePlayer.z < -0.05f || movePlayer.z > 0.05f)
	{// ���f�����ړ���
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 10.0f;
		fRateChaseCameraR = 0.10f;
    	fRateChaseCameraP = 0.30f;
	}
	else
	{// ���f������~��
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		fRateChaseCameraR = 0.005f;
    	fRateChaseCameraP = 0.30f;
	}

#if 0
	if (KeyBoard::IsPress(DIK_T))
	{// �����_�㏸
		g_camera.fHeightR += 1.0f;
		if(g_camera.fHeightR > 100.0f)
		{
			g_camera.fHeightR = 100.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_B))
	{// �����_���~
		g_camera.fHeightR -= 1.0f;
		if(g_camera.fHeightR < -200.0f)
		{
			g_camera.fHeightR = -200.0f;
		}
	}

	if (KeyBoard::IsPress(DIK_Y))
	{// ���_�㏸
		g_camera.fHeightV += 1.0f;
		if(g_camera.fHeightV > 200.0f)
		{
			g_camera.fHeightV = 200.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_N))
	{// ���_���~
		g_camera.fHeightV -= 1.0f;
		if(g_camera.fHeightV < -100.0f)
		{
			g_camera.fHeightV = -100.0f;
		}
	}

	if (KeyBoard::IsPress(DIK_U))
	{// �Y�[���C��
		if(g_camera.fLengthInterval > 100.0f)
		{
			g_camera.fLengthInterval -= 1.0f;
			g_camera.fHeightV -= 0.35f;
		}
	}
	if (KeyBoard::IsPress(DIK_M))
	{// �Y�[���A�E�g
		if(g_camera.fLengthInterval < 300.0f)
		{
			g_camera.fLengthInterval += 1.0f;
			g_camera.fHeightV += 0.35f;
		}
	}

	if (KeyBoard::IsPress(DIK_Z))
	{// ���_����u���v
		g_camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLengthInterval;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLengthInterval;
	}

	if (KeyBoard::IsPress(DIK_C))
	{// ���_����u�E�v
		g_camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLengthInterval;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLengthInterval;
	}
	
	// �����_�̖ړI�ʒu
	g_camera.posRDest.x = posPlayer.x - sin(rotPlayer.y) * fIntervalCamera;
	g_camera.posRDest.y = posPlayer.y + g_camera.fHeightR;
	g_camera.posRDest.z = posPlayer.z - cos(rotPlayer.y) * fIntervalCamera;

	// ���_�̖ړI�ʒu
	g_camera.posVDest.x = posPlayer.x - sinf(g_camera.rot.y) * g_camera.fLengthInterval - sin(rotPlayer.y) * fLengthMove;
	g_camera.posVDest.y = posPlayer.y + g_camera.fHeightV;
	g_camera.posVDest.z = posPlayer.z - cosf(g_camera.rot.y) * g_camera.fLengthInterval - cos(rotPlayer.y) * fLengthMove;

	// �����_�̕␳
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * fRateChaseCameraR;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.10f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * fRateChaseCameraR;

	// ���_�̕␳
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * fRateChaseCameraP;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * fRateChaseCameraP;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * fRateChaseCameraP;

	DebugProc_Print((char*)"[�J�����̎��_  �F(%f : %f : %f)]\n", g_camera.posV.x, g_camera.posV.y, g_camera.posV.z);
	DebugProc_Print((char*)"[�J�����̒����_�F(%f : %f : %f)]\n", g_camera.posR.x, g_camera.posR.y, g_camera.posR.z);
	DebugProc_Print((char*)"[�J�����̌���  �F(%f)]\n", g_camera.rot.y);
	DebugProc_Print((char*)"\n");
	DebugProc_Print((char*)"*** �J�������� ***\n");
	DebugProc_Print((char*)"���_�㏸     : [ �x ]\n");
	DebugProc_Print((char*)"���_���~     : [ �m ]\n");
	DebugProc_Print((char*)"�����_�㏸   : [ �s ]\n");
	DebugProc_Print((char*)"�����_���~   : [ �a ]\n");
	DebugProc_Print((char*)"�Y�[���C��   : [ �t ]\n");
	DebugProc_Print((char*)"�Y�[���A�E�g : [ �l ]\n");
	DebugProc_Print((char*)"\n");
#endif
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void Camera_SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, 
						&g_camera.posV,		// �J�����̎��_
						&g_camera.posR,		// �J�����̒����_
						&g_camera.vecU);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
								VIEW_ANGLE,			// ����p
								VIEW_ASPECT,		// �A�X�y�N�g��
								VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera;
}

