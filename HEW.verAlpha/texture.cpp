/*==================================
	
	[texture.cpp]
	Author : 出合翔太

==================================*/

//!	このソースコードは使わない！

//インクルードファイル
#include <d3dx9.h>
#include "main.h"
#include "texture.h"

//マクロ定義
#define TEXTURE_FILENAME_MAX (64)	//ファイルの文字数

//TEXTUREクラス
class TEXTURE
{
public:
	char filename[TEXTURE_FILENAME_MAX];	//ファイル名
	int width;								//テクスチャの横幅
	int height;								//テクスチャの縦幅
};

//テクスチャファイルの一覧
static const TEXTURE g_TextureFiles[] = 
{
    { "asset/texture/yukidaruma.tga"	, 256 , 256 },
	{ "asset/texture/bullet00.png"		, 32  , 32  },
	{ "asset/texture/bullet01.png"		, 32  , 32  },
	{ "asset/texture/exp.png"			, 128 , 128 },
	{ "asset/texture/number.tga"		, 320 , 32  },
	{ "asset/texture/title.png"			, 1024, 576 },
	{ "asset/texture/result.png"		, 1024, 576 },
	{ "asset/texture/kokosozai.png"		, 512 , 512 },
	{ "asset/texture/sousa.png"			, 1024, 576 },
	{ "asset/texture/rule.png"			, 1024, 576 },
};

static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);	//テクスチャファイルを数える

static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");	

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {};	//テクスチャを格納するインスタンス

//テクスチャファイルの読み込み
int Texture_Load()
{   
    LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if( !pDevice ) {
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            // DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

//テクスチャファイルの解放
void Texture_Release()
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( g_pTextures[i] ) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

//テクスチャオブジェクトを画像ファイルから読み込む関数
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_pTextures[index];
}

//テクスチャの横幅
int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) 
	{
        return NULL;
    }

	return g_TextureFiles[index].width;	//テクスチャの横幅の値をリターン
}

//テクスチャの縦幅
int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) 
	{
        return NULL;
    }

	return g_TextureFiles[index].height;	//テクスチャの縦幅の値をリターン
}
