/*==============================================

	[Fade.cpp]
	Author : 出合翔太

==============================================*/

#include "Fade.h"

//	頂点フォーマットに合わせた構造体
struct FadeVertex
{
	D3DXVECTOR4 m_Position;
	D3DXCOLOR	m_Color;
};

#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)	//	頂点フォーマット

//	スタティック変数
D3DXCOLOR			Fade::m_FadeColor(0.0f, 0.0f, 0.0f, 1.0f);
float				Fade::m_Alpha = 0.0f;
float				Fade::m_AddAlpha = 0.0f;
bool				Fade::m_bOut = false;
bool				Fade::m_bIsFade = false;
LPDIRECT3DDEVICE9	Fade::m_pDevice;

void Fade::Init()
{
	m_bIsFade = false;
	m_Alpha = 0.0f;
}

void Fade::Update()
{
	if (!m_bIsFade)
	{
		return;
	}
	m_Alpha += m_AddAlpha;

	if (m_bOut)
	{
		if (m_Alpha >= 1.0f)
		{
			m_Alpha = 1.0f;
			m_bIsFade = false;
		}
	}
	else
	{
		if (m_Alpha <= 0.0f)
		{
			m_Alpha = 0.0f;
			m_bIsFade = false;
		}
	}
}

void Fade::Draw()
{
	if (m_Alpha == 0.0f)
	{
		return;
	}
	m_FadeColor.a = m_Alpha;
	D3DCOLOR color = m_FadeColor;

	FadeVertex vertex[] = 
	{
		{D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),color},
		{D3DXVECTOR4(SCREEN_WIDTH,0.0f,0.0f,1.0f),color},
		{D3DXVECTOR4(0.0f,SCREEN_HEIGHT,0.0f,1.0f),color},
		{D3DXVECTOR4(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f,1.0f),color}
	};
	m_pDevice = GetD3DDevice();
	m_pDevice->SetFVF(FVF_FADE_VERTEX);
	m_pDevice->SetTexture(0, NULL);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(FadeVertex));
}

void Fade::Start(bool bOut, int frame, D3DXCOLOR color)
{
	m_bOut = bOut;
	m_AddAlpha = 1.0f / frame;
	m_FadeColor = color;
	m_bIsFade = true;
	if (m_bOut)
	{
		m_Alpha = 0.0f;
	}
	else
	{
		m_Alpha = 1.0f;
		m_AddAlpha = -m_AddAlpha;                                                      
	}
}

bool Fade::IsFade()
{
	return m_bIsFade;
}
