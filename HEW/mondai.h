
//��




#pragma once
#include "Model.h"

//	�}�N����`
#define ACTOR_NUM 1	// 3D���f���̐�



class Mondai
{
private:
	static LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffMondai;	// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMondai;
	static D3DXMATRIX				g_mtxWorldMondai;	// ���[���h�}�g���b�N�X
	static LPDIRECT3DDEVICE9		pDevice;			// �f�o�C�X�擾�p�ϐ�
	//	3�����x�N�g��
	static D3DXVECTOR3				g_posMondai;			// �n�ʂ̈ʒu
	static D3DXVECTOR3				g_rotMondai;			// �n�ʂ̌���(��])
	static D3DXVECTOR3				g_sclMondai;			// �n�ʂ̑傫��(�X�P�[��)
public:
	static HRESULT Init();										//	����������
	static void Uninit();										//	�I������
	static void Draw();										//	�`��
	static void Update();
	//static void HitMondai();
	//static HRESULT MakeVertexMondai(LPDIRECT3DDEVICE9 pDevice);	//	���_�쐬
};

