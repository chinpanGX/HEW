/*==================================

	[sprite.cpp]
	Author : 出合翔太

==================================*/

//!	このソースコードは使わない！

//インクルードファイル
#include <d3dx9.h>
#include <math.h>
#include "main.h"
#include "texture.h"
#include "sprite.h"

//VERTEX2Dクラス
 struct VERTEX2D
{
	//メンバ変数
    D3DXVECTOR4 position;	//ポリゴンの座標
	D3DCOLOR	color;		//ポリゴンの色
	D3DXVECTOR2 texcoord;	//テクスチャ座標
};

//マクロ定義
//2D描画用のスクリーン座標変換	
//#D3DFVF_XYZRHWは自動でスクリーン座標を行う
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	

//static D3DCOLOR g_Color = 0xffffffff;
static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);	//カラーの変更が可能

void SPRITE::SetColor(D3DCOLOR color)
{
	g_Color = color;
}

void SPRITE::Draw(TextureIndex texture_index, float dx, float dy)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
    if( !pDevice ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    VERTEX2D vertexes[] = 
	{
        { D3DXVECTOR4(dx     - 0.5f, dy     - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 0.0f) },
        { D3DXVECTOR4(dx + w - 0.5f, dy     - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx     - 0.5f, dy + h - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f, dy + h - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 1.0f) },
    };

    pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX2D));
}


void SPRITE::Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty,int tw, int th)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
    if( !pDevice ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

    VERTEX2D vertexes[] = 
	{
        { D3DXVECTOR4(dx      - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
        { D3DXVECTOR4(dx + tw - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx      - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
    };

    pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX2D));
}
#if 0
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty,int tw, int th, float cx, float cy, float sx, float sy, float rotation)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
    if( !pDevice ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    float u[2], v[2];
    u[0] = (float)tx / w;
    v[0] = (float)ty / h;
    u[1] = (float)(tx + tw) / w;
    v[1] = (float)(ty + th) / h;

	float px[4], py[4];
	px[0] = -cx        * sx * cos(rotation) - -cy        * sy * sin(rotation);
	py[0] = -cx        * sx * sin(rotation) + -cy        * sy * cos(rotation);
	px[1] = (-cx + tw) * sx * cos(rotation) - -cy        * sy * sin(rotation);
	py[1] = (-cx + tw) * sx * sin(rotation) + -cy        * sy * cos(rotation);
	px[2] = -cx        * sx * cos(rotation) - (-cy + th) * sy * sin(rotation);
	py[2] = -cx        * sx * sin(rotation) + (-cy + th) * sy * cos(rotation);
	px[3] = (-cx + tw) * sx * cos(rotation) - (-cy + th) * sy * sin(rotation);
	py[3] = (-cx + tw) * sx * sin(rotation) + (-cy + th) * sy * cos(rotation);

    VERTEX2D vertexes[] = {
        { D3DXVECTOR4(px[0] + dx + cx - 0.5f, py[0] + dy + cy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
        { D3DXVECTOR4(px[1] + dx + cx - 0.5f, py[1] + dy + cy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
        { D3DXVECTOR4(px[2] + dx + cx - 0.5f, py[2] + dy + cy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
        { D3DXVECTOR4(px[3] + dx + cx - 0.5f, py[3] + dy + cy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
    };

    pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX2D));
}
#endif

void SPRITE::Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (!pDevice) return;

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

	VERTEX2D vertexes[] = 
	{
		{ D3DXVECTOR4(px[0] - 0.4f, py[0] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
		{ D3DXVECTOR4(px[1] - 0.4f, py[1] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(px[2] - 0.4f, py[2] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(px[3] - 0.4f, py[3] - 0.4f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX2D));
}

