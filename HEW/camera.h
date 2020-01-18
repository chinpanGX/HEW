/*=============================================================================

	camera.h
	Author : �o���đ�

=============================================================================*/

#pragma once
#include "main.h"

class Camera
{
private:
	D3DXVECTOR3 posV;			// �J�����̎��_
	D3DXVECTOR3 posR;			// �J�����̒����_
	D3DXVECTOR3 vecU;			// �J�����̏����
	D3DXVECTOR3 posVDest;		// �J�����̎��_�̖ړI�ʒu
	D3DXVECTOR3 posRDest;		// �J�����̒����_�̖ړI�ʒu
	D3DXVECTOR3 rot;			// �J�����̉�]
	float fLengthInterval;		// �J�����̎��_�ƒ����_�̋���
	float fHeightV;				// �J�����̎��_�̍���
	float fHeightR;				// �J�����̒����_�̍���
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	float fRateRotAuto;			// ������荞�݌W��
	bool bMoveAuto;				// ������荞��ON/OFF
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Set();
	D3DXVECTOR3 GetRot();
};

#if 0
//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
struct CAMERA
{
	D3DXVECTOR3 posV;			// �J�����̎��_
	D3DXVECTOR3 posR;			// �J�����̒����_
	D3DXVECTOR3 vecU;			// �J�����̏����
	D3DXVECTOR3 posVDest;		// �J�����̎��_�̖ړI�ʒu
	D3DXVECTOR3 posRDest;		// �J�����̒����_�̖ړI�ʒu
	D3DXVECTOR3 rot;			// �J�����̉�]
	float fLengthInterval;		// �J�����̎��_�ƒ����_�̋���
	float fHeightV;				// �J�����̎��_�̍���
	float fHeightR;				// �J�����̒����_�̍���
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	float fRateRotAuto;			// ������荞�݌W��
	bool bMoveAuto;				// ������荞��ON/OFF
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Camera_Initialize(void);
void Camera_Finalize(void);
void Camera_Update(void);

void Camera_SetCamera(void);
CAMERA *GetCamera(void);

#endif

