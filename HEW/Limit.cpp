#include <d3dx9.h>
#include <math.h>
#include "main.h"
#include "sprite.h"
#include "Limit.h"



//	�}�N����`
#define MINA	(0.5f)	//	��ʂ̕\���ʒu�̏C���Œ�l

//	�O���[�o���ϐ�
D3DCOLOR k_Color = D3DCOLOR_RGBA(255, 255, 255, 255);	//�J���[�̕ύX���\



//	�X�^�e�B�b�N�ϐ�
LPDIRECT3DDEVICE9		Limit::m_Device;			//	�f�o�C�X



void Limit::Update()
{
	
}

void Limit::Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation)
{

	static int m_tx=tx; //m_tx�@tx���l��static
	static int Cl = 0;  //Cl�@�����̕\���X�s�[�h�v�Z�p��static

	if (m_tx != 0)
	{
		m_Device = GetD3DDevice();
		if (!m_Device) return;

		float w = (float)Texture_GetWidth(texture_index);
		float h = (float)Texture_GetHeight(texture_index);

		float u[2], v[2];
		u[0] = (float)m_tx / w;
		v[0] = (float)ty / h;
		u[1] = (float)(m_tx + tw) / w;
		v[1] = (float)(ty + th) / h;

		D3DXMATRIX matBase[4];

		D3DXMatrixTranslation(&matBase[0], -(tw - (tw - cx)), -(th - (th - cy)), 0.0f);
		D3DXMatrixTranslation(&matBase[1], tw - cx, -(th - (th - cy)), 0.0f);
		D3DXMatrixTranslation(&matBase[2], -(tw - (tw - cx)), th - cy, 0.0f);
		D3DXMatrixTranslation(&matBase[3], tw - cx, th - cy, 0.0f);

		D3DXMATRIX matTrans;
		D3DXMATRIX matRot;
		D3DXMATRIX matScale;
		D3DXMATRIX matAll;
		float px[4], py[4];

		D3DXMatrixTranslation(&matTrans, dx, dy, 0.0f);
		D3DXMatrixRotationZ(&matRot, rotation);
		D3DXMatrixScaling(&matScale, sx, sy, 1.0f);

		for (int i = 0; i < 4; i++)
		{
			matAll = matBase[i] * matScale * matRot * matTrans;
			px[i] = matAll._41;
			py[i] = matAll._42;
		}

		VERTEX_2D vertexes[] =
		{
			{ D3DXVECTOR4(px[0] - 0.4f, py[0] - 0.4f, 0.0f, 1.0f), k_Color, D3DXVECTOR2(u[0], v[0]) },
			{ D3DXVECTOR4(px[1] - 0.4f, py[1] - 0.4f, 0.0f, 1.0f), k_Color, D3DXVECTOR2(u[1], v[0]) },
			{ D3DXVECTOR4(px[2] - 0.4f, py[2] - 0.4f, 0.0f, 1.0f), k_Color, D3DXVECTOR2(u[0], v[1]) },
			{ D3DXVECTOR4(px[3] - 0.4f, py[3] - 0.4f, 0.0f, 1.0f), k_Color, D3DXVECTOR2(u[1], v[1]) },
		};

		m_Device->SetFVF(FVF_VERTEX2D);
		m_Device->SetTexture(0, Texture_GetTexture(texture_index));
		m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));

		Cl++;
	
		
		if (Cl==60)//�����̕\���X�s�[�h�̒���
		{
			m_tx = m_tx - 64;//�����ω�
			Cl = 0;//������
		}
	}
	else
	{
		return ;
	}
}
