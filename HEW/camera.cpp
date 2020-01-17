/*========================================================

	[Camera.cpp]
	Author : �o���đ�

==========================================================*/

#include "camera.h"
#include "Character.h"
#include "debugproc.h"
#include "ObjectManager.h"

//	�}�N����`
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

// �J�����̏�����
HRESULT Camera::Init()
{
	posV = D3DXVECTOR3(0.0f, 100.0f, -250.0f);
	posR = D3DXVECTOR3(0.0f, 50.0f, -30.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	posVDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fRateRotAuto = 0.01f;

	float vx,vz;
	vx = posV.x - posR.x;
	vz = posV.z - posR.z;
	fLengthInterval = sqrtf(vx * vx + vz * vz);

	fHeightV = CHASE_HEIGHT_V;
	fHeightR = CHASE_HEIGHT_R;

	return S_OK;
}

// �J�����̏I������
void Camera::Uninit()
{
}

// �J�����̍X�V����
void Camera::Update()
{
	Character *pPlayer;
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 rotPlayer;
	D3DXVECTOR3 movePlayer;
	float fIntervalCamera, fLengthMove;
	float fRateChaseCameraP, fRateChaseCameraR;
	float fHeightFieldPlayer;

	// �v���C���[���擾
	pPlayer = ObjectManager::SetCharacter();

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
		fHeightR += 1.0f;
		if(fHeightR > 100.0f)
		{
			fHeightR = 100.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_B))
	{// �����_���~
		fHeightR -= 1.0f;
		if(fHeightR < -200.0f)
		{
			fHeightR = -200.0f;
		}
	}

	if (KeyBoard::IsPress(DIK_Y))
	{// ���_�㏸
		fHeightV += 1.0f;
		if(fHeightV > 200.0f)
		{
			fHeightV = 200.0f;
		}
	}
	if (KeyBoard::IsPress(DIK_N))
	{// ���_���~
		fHeightV -= 1.0f;
		if(fHeightV < -100.0f)
		{
			fHeightV = -100.0f;
		}
	}

	if (KeyBoard::IsPress(DIK_U))
	{// �Y�[���C��
		if(fLengthInterval > 100.0f)
		{
			fLengthInterval -= 1.0f;
			fHeightV -= 0.35f;
		}
	}
	if (KeyBoard::IsPress(DIK_M))
	{// �Y�[���A�E�g
		if(fLengthInterval < 300.0f)
		{
			fLengthInterval += 1.0f;
			fHeightV += 0.35f;
		}
	}

	if (KeyBoard::IsPress(DIK_Z))
	{// ���_����u���v
		rot.y += VALUE_ROTATE_CAMERA;
		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}

		posV.x = posR.x - sinf(rot.y) * fLengthInterval;
		posV.z = posR.z - cosf(rot.y) * fLengthInterval;
	}

	if (KeyBoard::IsPress(DIK_C))
	{// ���_����u�E�v
		rot.y -= VALUE_ROTATE_CAMERA;
		if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}

		posV.x = posR.x - sinf(rot.y) * fLengthInterval;
		posV.z = posR.z - cosf(rot.y) * fLengthInterval;
	}
	
	// �����_�̖ړI�ʒu
	posRDest.x = posPlayer.x - sin(rotPlayer.y) * fIntervalCamera;
	posRDest.y = posPlayer.y + fHeightR;
	posRDest.z = posPlayer.z - cos(rotPlayer.y) * fIntervalCamera;

	// ���_�̖ړI�ʒu
	posVDest.x = posPlayer.x - sinf(rot.y) * fLengthInterval - sin(rotPlayer.y) * fLengthMove;
	posVDest.y = posPlayer.y + fHeightV;
	posVDest.z = posPlayer.z - cosf(rot.y) * fLengthInterval - cos(rotPlayer.y) * fLengthMove;

	// �����_�̕␳
	posR.x += (posRDest.x - posR.x) * fRateChaseCameraR;
	posR.y += (posRDest.y - posR.y) * 0.10f;
	posR.z += (posRDest.z - posR.z) * fRateChaseCameraR;

	// ���_�̕␳
	posV.x += (posVDest.x - posV.x) * fRateChaseCameraP;
	posV.y += (posVDest.y - posV.y) * fRateChaseCameraP;
	posV.z += (posVDest.z - posV.z) * fRateChaseCameraP;

	DebugProc_Print((char*)"[�J�����̎��_  �F(%f : %f : %f)]\n", posV.x, posV.y, posV.z);
	DebugProc_Print((char*)"[�J�����̒����_�F(%f : %f : %f)]\n", posR.x, posR.y, posR.z);
	DebugProc_Print((char*)"[�J�����̌���  �F(%f)]\n", rot.y);
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

// �J�����̐ݒ菈��
void Camera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView, 
						&posV,		// �J�����̎��_
						&posR,		// �J�����̒����_
						&vecU);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
								VIEW_ANGLE,			// ����p
								VIEW_ASPECT,		// �A�X�y�N�g��
								VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

D3DXVECTOR3 Camera::GetRot()
{
	return rot;
}
