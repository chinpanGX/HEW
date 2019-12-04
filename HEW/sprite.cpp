/*==================================

	[sprite.cpp]
	Author : �o���đ�

==================================*/

#include <d3dx9.h>
#include <math.h>
#include "main.h"
#include "texture.h"
#include "sprite.h"

//	�}�N����`
#define MINA	(0.5f)	//	��ʂ̕\���ʒu�̏C���Œ�l

//	�O���[�o���ϐ�
D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);	//�J���[�̕ύX���\

//	�X�^�e�B�b�N�ϐ�
D3DXMATRIX				Sprite::m_mtxWorld;			//	���[���h�}�g���b�N�X
LPDIRECT3DVERTEXBUFFER9 Sprite::m_pVertexBuffer;	//	���_�o�b�t�@(���_���)���i�[����������
LPDIRECT3DINDEXBUFFER9	Sprite::m_pIndexBuffer;		//	�C���f�b�N�X�o�b�t�@
LPDIRECT3DDEVICE9		Sprite::m_Device;			//	�f�o�C�X

//	����������
HRESULT Sprite::Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL)))
	{
		return E_FAIL;
	}
	if(FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL)))
	{
		return E_FAIL;
	}
	VERTEX_3D *pVtx;	//	���_�o�b�t�@�ւ̃|�C���^
	WORD* pIndex;		//	�C���f�N�X�o�b�t�@�ւ̃|�C���^
	m_pVertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-30.0f,  30.0f, -30.0f);	
	pVtx[1].pos = D3DXVECTOR3( 30.0f,  30.0f, -30.0f);
	pVtx[2].pos = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
	pVtx[3].pos = D3DXVECTOR3( 30.0f, -30.0f, -30.0f);
	pVtx[4].pos = D3DXVECTOR3( 30.0f, -30.0f,  30.0f);
	pVtx[5].pos = D3DXVECTOR3(-30.0f, -30.0f,  30.0f);

	for (int i = 0; i < 5 ; i++)
	{
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(3.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(2.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(3.0f, 1.0f);
	
	m_pVertexBuffer ->Unlock();
	
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;
	m_pIndexBuffer->Unlock();
}

//	�I������
void Sprite::Uninit()
{
	DEVICE_RELEASE(m_pIndexBuffer);
	DEVICE_RELEASE(m_pVertexBuffer);
}

//	�F��ݒ肷��Z�b�^�[
void Sprite::SetColor(D3DCOLOR color)
{
	g_Color = color;
}

//	�`�� (�����F�e�N�X�`���AX���W�AY���W)
void Sprite::Draw(TextureIndex texture_index, float dx, float dy)
{
	m_Device = GetD3DDevice();
	if (!m_Device) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	VERTEX_2D vertexes[] = {
		{ D3DXVECTOR4(dx - MINA, dy - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx + w - MINA, dy - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - MINA, dy + h - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx + w - MINA, dy + h - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 1.0f) },
	};

	m_Device->SetFVF(FVF_VERTEX2D);
	m_Device->SetTexture(0, Texture_GetTexture(texture_index));

	m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

//	�`�� (�����F�e�N�X�`���AX���W�AY���W�A�e�N�X�`��X���W�A�e�N�X�`��Y���W�A�e�N�X�`���̉����A�e�N�X�`���̏c��)
void Sprite::Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty,int tw, int th)
{
	m_Device = GetD3DDevice();
    if( !m_Device ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

    VERTEX_2D vertexes[] = 
	{
        { D3DXVECTOR4(dx      - MINA, dy      - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
        { D3DXVECTOR4(dx + tw - MINA, dy      - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx      - MINA, dy + th - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - MINA, dy + th - MINA, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
    };

    m_Device->SetFVF(FVF_VERTEX2D);
	m_Device->SetTexture(0, Texture_GetTexture(texture_index));
    m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

//	�`�� (�����F�e�N�X�`���A�J���[�ݒ�AX���W�AY���W�A�e�N�X�`��X���W�A�e�N�X�`��Y���W�A�e�N�X�`���̉����A�e�N�X�`���̏c��)
void Sprite::Draw(TextureIndex texture_index, int col_r, int col_g, int col_b, int col_a,float dx, float dy, int tx, int ty, int tw, int th)
{
	m_Device = GetD3DDevice();
	if (!m_Device) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

	VERTEX_2D vertexes[] =
	{
		{ D3DXVECTOR4(dx - MINA, dy - MINA, 0.0f, 1.0f),D3DCOLOR_RGBA(col_r,col_g,col_b,col_a), D3DXVECTOR2(u[0], v[0]) },
		{ D3DXVECTOR4(dx + tw - MINA, dy - MINA, 0.0f, 1.0f),D3DCOLOR_RGBA(col_r,col_g,col_b,col_a), D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx - MINA, dy + th - MINA, 0.0f, 1.0f),D3DCOLOR_RGBA(col_r,col_g,col_b,col_a), D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - MINA, dy + th - MINA, 0.0f, 1.0f),D3DCOLOR_RGBA(col_r,col_g,col_b,col_a), D3DXVECTOR2(u[1], v[1]) },
	};

	m_Device->SetFVF(FVF_VERTEX2D);
	m_Device->SetTexture(0, Texture_GetTexture(texture_index));
	m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

//	�`�� (�����F�e�N�X�`���AX���W�AY���W�A�e�N�X�`��X���W�A�e�N�X�`��Y���W�A�e�N�X�`���̉����A�e�N�X�`���̏c���A�e�N�X�`���̒��S���W�A�g��k���A��])
void Sprite::Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation)
{
	m_Device = GetD3DDevice();
	if (!m_Device) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

	D3DXMATRIX matBase[4];

	D3DXMatrixTranslation(&matBase[0], -(tw - (tw - cx)), -(th - (th - cy)), 0.0f);
	D3DXMatrixTranslation(&matBase[1],   tw - cx,         -(th - (th - cy)), 0.0f);
	D3DXMatrixTranslation(&matBase[2], -(tw - (tw - cx)),   th - cy,         0.0f);
	D3DXMatrixTranslation(&matBase[3],   tw - cx,           th - cy,         0.0f);

	D3DXMATRIX matTrans;
	D3DXMATRIX matRot;
	D3DXMATRIX matScale;
	D3DXMATRIX matAll;
	float px[4], py[4];

	D3DXMatrixTranslation(&matTrans, dx, dy, 0.0f);
	D3DXMatrixRotationZ(&matRot, rotation);
	D3DXMatrixScaling(&matScale, sx, sy, 1.0f);

	for (int i = 0; i < 4; i++){
		matAll = matBase[i] * matScale * matRot * matTrans;
		px[i] = matAll._41;
		py[i] = matAll._42;
	}

	VERTEX_2D vertexes[] = 
	{
		{ D3DXVECTOR4(px[0] - 0.4f, py[0] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
		{ D3DXVECTOR4(px[1] - 0.4f, py[1] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(px[2] - 0.4f, py[2] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(px[3] - 0.4f, py[3] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
	};

	m_Device->SetFVF(FVF_VERTEX2D);
	m_Device->SetTexture(0, Texture_GetTexture(texture_index));
	m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}
