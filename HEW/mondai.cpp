// author ��



#include"main.h"
#include"mondai.h"
#include"texture.h"
#include "Controller.h"

//	�}�N����`
#define POLYGON_NUM 2
#define VERTEX_NUM 6

//	�X�^�e�B�b�N�ϐ�
LPDIRECT3DVERTEXBUFFER9 Mondai::g_pVtxBuffMondai = NULL;	//	���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9  Mondai::g_pIdxBuffMondai = NULL;
D3DXMATRIX				Mondai::g_mtxWorldMondai;			//	���[���h�}�g���b�N�X
D3DXVECTOR3				Mondai::g_posMondai;				//	�n�ʂ̈ʒu
D3DXVECTOR3				Mondai::g_rotMondai;				//	�n�ʂ̌���(��])
D3DXVECTOR3				Mondai::g_sclMondai;				//	�n�ʂ̑傫��	
LPDIRECT3DDEVICE9		Mondai::pDevice;					//	�f�o�C�X�擾�p�ϐ�


static bool flagMondai;
static int g_NumIndexMondai = 36;



//	�t�B�[���h�̏�����
HRESULT Mondai::Init()
{
	pDevice = GetD3DDevice();
	// ���_���̍쐬
	MakeVertexMondai(pDevice);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_posMondai = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMondai = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclMondai = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	flagMondai = false;

	return S_OK;
}

//	�t�B�[���h�̏I������
void Mondai::Uninit()
{
	DEVICE_RELEASE(pDevice);
	DEVICE_RELEASE(g_pVtxBuffMondai);
}

//	�t�B�[���h�̕`��
void Mondai::Draw()
{

	if (flagMondai == false)

	{
		pDevice = GetD3DDevice();

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		//	���[���h�ϊ��i���[���h�}�g���N�X�̏������j
		D3DXMatrixIdentity(&g_mtxWorldMondai);
		D3DXMatrixScaling(&mtxScl, g_sclMondai.x, g_sclMondai.y, g_sclMondai.z);
		D3DXMatrixMultiply(&g_mtxWorldMondai, &g_mtxWorldMondai, &mtxScl);						//�@������2�Ԗڂ�3�Ԗڂ̌v�Z���ʂ�1�Ԗڂɓ����
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMondai.x, g_rotMondai.y, g_rotMondai.z);
		D3DXMatrixMultiply(&g_mtxWorldMondai, &g_mtxWorldMondai, &mtxRot);
		D3DXMatrixTranslation(&mtxTranslate, g_posMondai.y, g_posMondai.x, g_posMondai.z);
		D3DXMatrixMultiply(&g_mtxWorldMondai, &g_mtxWorldMondai, &mtxTranslate);

		// ���[���h�}�g���N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMondai);

		//	���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffMondai, 0, sizeof(VERTEX_3D));

		//	���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX3D);

		//�e�N�X�`���̐ݒ�
		//pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_MONDAI));


		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_NumIndexMondai, 0, 12);

		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, POLYGON_NUM);

	}

}


HRESULT Mondai::MakeVertexMondai(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMondai,
		NULL)))
	{
		return E_FAIL;
	}

	{
		VERTEX_3D *pVtx;

		g_pVtxBuffMondai->Lock(0, 0, (void**)&pVtx, 0);

		////���_���W�̐ݒ�
		//for (int z = 0; z < 2; z++)
		//{
		//	for (int x = 0; x < 4; x++)
		//	{
		//		pVtx[z * 4 + x].pos = D3DXVECTOR3(x*100.0f, 0.0f, z*-100.0f);
		//	}
		//}


		pVtx[0].pos = D3DXVECTOR3(-30.0f, 30.0f, -30.0f);
		pVtx[1].pos = D3DXVECTOR3(30.0f, 30.0f, -30.0f);
		pVtx[2].pos = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		pVtx[3].pos = D3DXVECTOR3(30.0f, -30.0f, -30.0f);
		pVtx[4].pos = D3DXVECTOR3(30.0f, -30.0f, 30.0f);
		pVtx[5].pos = D3DXVECTOR3(-30.0f, -30.0f, 30.0f);
		/*pVtx[6].pos = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
		pVtx[7].pos = D3DXVECTOR3(-10.0f, 10.0f, 10.0f);*/

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);                 
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		/*pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
*/
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		/*pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);*/

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(3.0f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(3.0f, 1.0f);

		g_pVtxBuffMondai->Unlock();
	}

	//if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * 8,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&g_pIdxBuffMondai,
	//	NULL)))
	//{
	//	return E_FAIL;
	//}

	//{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	//	WORD *pIdx;

	//	g_pIdxBuffMondai->Lock(0, 0, (void**)&pIdx, 0);

	//	pIdx[0] = 4;
	//	pIdx[1] = 0;
	//	pIdx[2] = 5;
	//	pIdx[3] = 1;
	//	pIdx[4] = 6;
	//	pIdx[5] = 2;
	//	pIdx[6] = 7;
	//	pIdx[7] = 3;
	//

		//���_�o�b�t�@���A�����b�N
		//g_pVtxBuffMondai->Unlock();
	

	return S_OK;
}

void Mondai::Update()

{

	if (KeyBoard::IsPress(DIK_1) || KeyBoard::IsPress(DIK_2) || KeyBoard::IsPress(DIK_3) || KeyBoard::IsPress(DIK_4))

		flagMondai = true;

}