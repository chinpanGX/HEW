/*======================================================

	[debugCamera.cpp]
	Author : �o���đ�

======================================================*/

#include "DebugCamera.h"

#include "main.h"
#include "Controller.h"
#include "debugproc.h"


//�@�}�N����`
#define	CAM_POS_V_X		(0.0f)											// �J�����̎��_�����ʒu(X���W)
#define	CAM_POS_V_Y		(0.0f)											// �J�����̎��_�����ʒu(Y���W)
#define	CAM_POS_V_Z		(-100.0f)										// �J�����̎��_�����ʒu(Z���W)
#define	CAM_POS_R_X		(0.0f)											// �J�����̒����_�����ʒu(X���W)
#define	CAM_POS_R_Y		(0.0f)											// �J�����̒����_�����ʒu(Y���W)
#define	CAM_POS_R_Z		(100.0f)											// �J�����̒����_�����ʒu(Z���W)
#define	VIEW_ANGLE		(D3DXToRadian(70.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l	�l���߂��ƕ`�悵�Ȃ�
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l	�l��艓���ƕ`�悵�Ȃ�
#define MOVE_CAMERA		(1.0f)
#define ROTATE_CAMERA	(D3DX_PI * 0.01f)
#define CAMERADISTANCE	(1.0f)

//	�X�^�e�B�b�N�ϐ�
D3DXVECTOR3 DebugCamera::m_Velocity;
D3DXVECTOR3	DebugCamera::m_rot;
float		DebugCamera::m_fDistance;

//#	�J�����̏�����
void DebugCamera::Init()
{
	Camera::Init();
	m_Velocity = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
}

//#	�J�����̏I������
void DebugCamera::Uninit()
{

}

//# �J�����̍X�V����
void DebugCamera::Update()
{
	if (KeyBoard::IsPress(DIK_S))
	{
		posV.z += m_Velocity.z;
		posR.z += m_Velocity.z;
	}

	if (KeyBoard::IsPress(DIK_W))
	{
		posR.z -= m_Velocity.z;
		posV.z -= m_Velocity.z;
	}

	if (KeyBoard::IsPress(DIK_A))
	{
		posV.x += m_Velocity.x;
		posR.x += m_Velocity.x;
	}

	if (KeyBoard::IsPress(DIK_D))
	{
		posV.x -= m_Velocity.x;
		posR.x -= m_Velocity.x;
	}
	if (KeyBoard::IsPress(DIK_Z))
	{
		m_rot.y += ROTATE_CAMERA;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		posR.x = posV.x - sinf(m_rot.y) * m_fDistance;
		posR.z = posV.z - cosf(m_rot.y) * m_fDistance;
	}

	if (KeyBoard::IsPress(DIK_C))
	{
		m_rot.y -= ROTATE_CAMERA;
		if (m_rot.y < D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
		posR.x = posV.x - sinf(m_rot.y) * m_fDistance;
		posR.z = posV.z - cosf(m_rot.y) * m_fDistance;
	}

	if (KeyBoard::IsPress(DIK_Y))
	{
		posV.y += MOVE_CAMERA;
		posR.y += MOVE_CAMERA;
	}

	if (KeyBoard::IsPress(DIK_N))
	{
		posV.y -= MOVE_CAMERA;
		posR.y -= MOVE_CAMERA;
	}

	if (KeyBoard::IsPress(DIK_E))
	{
		m_rot.y += ROTATE_CAMERA;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		posR.x = posV.x - sinf(m_rot.y) * m_fDistance;
		posR.z = posV.z - cosf(m_rot.y) * m_fDistance;
	}

	if (KeyBoard::IsPress(DIK_Q))
	{
		m_rot.y -= ROTATE_CAMERA;
		if (m_rot.y < D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
		posR.x = posV.x + sinf(m_rot.y) * m_fDistance;
		posR.z = posV.z + cosf(m_rot.y) * m_fDistance;
	}

	if (KeyBoard::IsPress(DIK_T))
	{
		posR.y += MOVE_CAMERA;
	}

	if (KeyBoard::IsPress(DIK_B))
	{
		posR.y -= MOVE_CAMERA;
	}


	if (KeyBoard::IsPress(DIK_U))
	{
		m_fDistance -= CAMERADISTANCE;
		if (m_fDistance < 100.0f)
		{
			m_fDistance = 100.0f;
		}
		posV.x = posR.x + sinf(m_rot.y) * m_fDistance;
		posV.z = posR.z + cosf(m_rot.y) * m_fDistance;
	}

	if (KeyBoard::IsPress(DIK_M))
	{
		m_fDistance += CAMERADISTANCE;
		if (m_fDistance > 1000.0f)
		{
			m_fDistance = 1000.0f;
		}
		posV.x = posR.x + sinf(m_rot.y) * m_fDistance;
		posV.z = posR.z + cosf(m_rot.y) * m_fDistance;
	}

	if (KeyBoard::IsPress(DIK_SPACE))
	{
		posV = D3DXVECTOR3(CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);	//	�J�����ʒu
		posR = D3DXVECTOR3(CAM_POS_R_X, CAM_POS_R_X, CAM_POS_R_X);	//	�����_
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//	�J�����̏�x�N�g��

		float x, z;
		x = posV.x - posR.x;
		z = posV.z - posR.z;
		m_fDistance = sqrtf(x * x + z * z);
	}

	DebugProc_Print((char*)"�J�����̎��_ [%f : %f : %f]\n", posV.x, posV.y, posV.z);
	DebugProc_Print((char*)"�J�����̒����_ [%f : %f : %f]\n", posR.x, posR.y, posR.z);
	DebugProc_Print((char*)"�J�����̌��� [%f]\n", m_rot.y);
	DebugProc_Print((char*)"�J�����̋���[%f]\n", m_fDistance);
	DebugProc_Print((char*)"\n");
}

//#	�J�����̐ݒ�
void DebugCamera::Set()
{
	Camera::Set();
}
