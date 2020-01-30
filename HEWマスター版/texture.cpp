/*==================================
	
	[texture.cpp]
	Author : 出合翔太

==================================*/

//インクルードファイル
#include <d3dx9.h>
#include "main.h"
#include "texture.h"

//マクロ定義
#define TEXTURE_FILENAME_MAX (64)	//ファイルの文字数

//	TEXTURE構造体
struct TEXTURE
{
	char filename[TEXTURE_FILENAME_MAX];	//ファイル名
	int width;								//テクスチャの横幅
	int height;								//テクスチャの縦幅
};

//テクスチャファイルの一覧
static const TEXTURE g_TextureFiles[] = 
{
	{ "asset/texture/result.png",1920,1080 },		//	リザルト背景テクスチャ
	{ "asset/texture/modeselect.png",1920,1080 },	//	モード選択背景テクスチャサンプル
	{ "asset/texture/UI.png",1008, 911},			//	UIテクスチャ
	{ "asset/texture/Quiz.png",6404,1603},			//	問題文
	{ "asset/texture/Answer.png",2141,9602},		//	解答
	{ "asset/texture/number.tga",320,32},			//	数字
	{ "asset/texture/Frame.png",216,216},			//	枠
	{ "asset/texture/Title.png", 1920,1080}			//	タイトル
};

static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);	//テクスチャファイルを数える

static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");	

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {};	//テクスチャを格納するインスタンス

//テクスチャファイルの読み込み
int Texture_Load()
{   
    LPDIRECT3DDEVICE9 m_Device = GetD3DDevice();
	if( !m_Device )
	{
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( FAILED(D3DXCreateTextureFromFile(m_Device, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            // DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

//テクスチャファイルの解放
void Texture_Release()
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ )
	{
		SAFE_RELEASE(g_pTextures[i]);
	}
}

//テクスチャオブジェクトを画像ファイルから読み込む関数
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) 
	{
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

	return g_TextureFiles[index].width;	//	テクスチャの横幅の値
}

//テクスチャの縦幅
int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) 
	{
        return NULL;
    }

	return g_TextureFiles[index].height;	//	テクスチャの縦幅の値
}
