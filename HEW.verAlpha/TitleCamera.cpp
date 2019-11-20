/*===========================================

	[TitleCamera.cpp]
	Author : o‡ãÄ‘¾

===========================================*/

#include "main.h"
#include "TitleCamera.h"

D3DXVECTOR3			Camera::posV;
D3DXVECTOR3			Camera::posR;
D3DXVECTOR3			Camera::vecU;
D3DXMATRIX			Camera::mtxProjection;
D3DXMATRIX			Camera::mtxView;
LPDIRECT3DDEVICE9	Camera::pDevice;
D3DXVECTOR3			TitleCamera::m_Velocity;

void TitleCamera::Init()
{
	m_Velocity = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Camera::Init();
	posV.y = -200.0f;
}

void TitleCamera::Uninit()
{

}

void TitleCamera::Update()
{
	posV.x += m_Velocity.x;
	if (posV.x > 100.0f)
	{
		posV.x = 100.0f;
		m_Velocity *= -1;
	}
	else if(posV.x <-100.0f)
	{
		posV.x = -100.0f;
		m_Velocity *= -1;
	}
}

void TitleCamera::Set()
{
	Camera::Set();
}
