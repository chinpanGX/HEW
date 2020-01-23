/*========================================

	[Camera.cpp]
	Author : �o���đ�

========================================*/

#include "Camera.h"
#include "ObjectManager.h"
#include "Controller.h"

// �}�N����`
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))							// ����p
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z			(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(100000.0f)										// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA	(2.0f)											// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)								// �J�����̉�]��
#define	INTERVAL_CAMERA_R	(100.0f)										// ���f���̎����̐�܂ł̋���
#define	RATE_CHASE_CAMERA_V	(0.35f)											// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)											// �J�����̒����_�ւ̕␳�W��
#define	CHASE_HEIGHT_V		(10.0f)											// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R		(10.0f)											// �ǐՎ��̒����_�̍���

//	����������
void Camera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 500.0f, -200.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 500.0f, -200.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float vx, vz;
	vx = m_posV.x - m_posR.x;
	vz = m_posV.z - m_posR.z;
	m_fLengthInterval = sqrtf(vx * vx + vz * vz);
	m_fHeightV = CHASE_HEIGHT_V;
	m_fHeightR = CHASE_HEIGHT_R;
}

//	�I������
void Camera::Uninit()
{
}

//	�X�V����
void Camera::Update()
{	
	Character *pPlayer;
	pPlayer = ObjectManager::SetCharacter();	//	Player�C���X�^���X�̎擾
	D3DXVECTOR3 posPlayer = pPlayer->GetPos();	//	�ʒu�̎擾
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();	//	�����̎擾
	D3DXVECTOR3 movePlayer = pPlayer->GetMove();	//	�ړ��ʂ̎擾
	float fIntervalCamera, fLengthMove;
	float fRateChaseCameraP, fRateChaseCameraR;
	float fHeightFieldPlayer;
	fHeightFieldPlayer = posPlayer.y * 200.0f;	//	���݂��鍂��
	fLengthMove = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;	//	�ړ���
	//	�v���C���[���ړ����Ă���Ƃ�
	if (movePlayer.x < -0.05f || movePlayer.x > 0.05f || movePlayer.z < -0.05f || movePlayer.z > 0.05f)
	{
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 10.0f;
		fRateChaseCameraR = 0.10f;
		fRateChaseCameraP = 0.3f;

	}
	else
	{
		fIntervalCamera = INTERVAL_CAMERA_R + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		fRateChaseCameraR = 0.0005f;
		fRateChaseCameraP = 0.3f;
	}

	// �����_�̖ړI�ʒu
	m_posRDest.x = posPlayer.x - sin(rotPlayer.y) * fIntervalCamera;
	m_posRDest.y = posPlayer.y + m_fHeightR;
	m_posRDest.z = posPlayer.z - cos(rotPlayer.y) * fIntervalCamera;

	// ���_�̖ړI�ʒu
	m_posVDest.x = posPlayer.x - sinf(m_rot.y) * m_fLengthInterval - sin(rotPlayer.y) * fLengthMove;
	m_posVDest.y = posPlayer.y + m_fHeightV + 50.0f;
	m_posVDest.z = posPlayer.z - cosf(m_rot.y) * m_fLengthInterval - cos(rotPlayer.y) * fLengthMove;

	// �����_�̕␳
	m_posR.x += (m_posRDest.x - m_posR.x) * fRateChaseCameraR;
	m_posR.y += (m_posRDest.y - m_posR.y) * 1.0f;
	m_posR.z += (m_posRDest.z - m_posR.z) * fRateChaseCameraR;

	// ���_�̕␳
	m_posV.x += (m_posVDest.x - m_posV.x) * fRateChaseCameraP;
	m_posV.y += (m_posVDest.y - m_posV.y) * fRateChaseCameraP;
	m_posV.z += (m_posVDest.z - m_posV.z) * fRateChaseCameraP;

}

//	�J�����̃Z�b�g
void Camera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	/// <summary>
	/// �r���[�}�g���b�N�X�̍쐬(�J�������_�A�J���������_�A�J������x�N�g��)
	///	<summary>
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	/// <summary>
	/// �v���W�F�N�V�����}�g���b�N�X�̍쐬(����p�A�A�X�y�N�g��A�r���[���ʂ�NearZ�l�A�r���[���ʂ�FarZ�l)
	/// </summary>
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
D3DXVECTOR3 Camera::GetRot()
{
	return m_rot;
}
