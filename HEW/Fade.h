/*===============================================

	[Fade.h]
	Author : èoçá„ƒëæ

===============================================*/

#pragma once
#include "main.h"

class Fade
{
private:
	static D3DXCOLOR			m_FadeColor;
	static float				m_Alpha;
	static float				m_AddAlpha;
	static bool					m_bOut;
	static bool					m_bIsFade;
	static LPDIRECT3DDEVICE9	m_pDevice;
public:
	static void Init();
	static void Update();
	static void Draw();
	static void Start(bool bOut,int frame, D3DXCOLOR color);
	static bool IsFade();
};

