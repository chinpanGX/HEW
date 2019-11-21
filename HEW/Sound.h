/*==================================================
	
	[Sound.h]
	Author : 出合翔太

====================================================*/

#pragma once
#include <windows.h>
#include "xaudio2.h"	

//#	サウンドラベル名
typedef enum
{
	SOUND_LABEL_001,	//　空っぽ

	SOUND_LABEL_MAX,

} SOUND_LABEL;

//#	Soundクラス
/* 音楽ファイルを管理するクラス　*/
class Sound
{
private:
	char *pFilename;												// ファイル名
	int nCntLoop;													// ループカウント
	static IXAudio2 *g_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *g_pMasteringVoice;				// マスターボイス
	static IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *g_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD g_aSizeAudio[SOUND_LABEL_MAX];						// オーディオデータサイズ
public:	
	Sound();						//	コンストラクタ->空
	~Sound();						//	デストトラクタ->空
	bool Init(HWND hWnd);			//	初期化
	void Uninit();					//	終了処理
	void Play(SOUND_LABEL label);	//	セグメント再生(引数：ラベル名)
	void Stop(SOUND_LABEL label);	//	セグメント停止(引数：ラベル名)
	void Stop();					//	セグメント停止：すべて
};

