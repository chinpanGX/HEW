/*===========================================================

	[Field.h]
	Author : �o���đ�

=============================================================*/

#pragma once
#include "Model.h"

//	�}�N����`
#define ACTOR_NUM 1	// 3D���f���̐�

//# Field�N���X
/* �Q�[���̔w�i�̕`�������N���X */
class Field
{
private:
	static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffField;	// ���_�o�b�t�@�ւ̃|�C���^
	static D3DXMATRIX				g_mtxWorldField;	// ���[���h�}�g���b�N�X
	static LPDIRECT3DDEVICE9		pDevice;			// �f�o�C�X�擾�p�ϐ�
	//	3�����x�N�g��
	static D3DXVECTOR3				g_posField;			// �n�ʂ̈ʒu
	static D3DXVECTOR3				g_rotField;			// �n�ʂ̌���(��])
	static D3DXVECTOR3				g_sclField;			// �n�ʂ̑傫��(�X�P�[��)
public:
	HRESULT Init();										//	����������
	void Uninit();										//	�I������
	void Draw();										//	�`��
	HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);	//	���_�쐬
};
