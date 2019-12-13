/*===============================================

	[Fade.h]
	Author : èoçá„ƒëæ

===============================================*/

#pragma once
#include "main.h"

class Fade
{
private:
	static D3DXCOLOR	m_FadeColor;
	static float		m_Alpha;
	static float		m_AddAlpha;
	static bool			m_bOut;
	static bool			m_bIsFade;
	LPDIRECT3DDEVICE9	m_pDevice;
public:
	void Init();
	void Update();
	void Draw();
	void Start(bool bOut,int frame, D3DXCOLOR color);
	bool IsFade();
};

