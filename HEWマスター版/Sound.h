//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"	// サウンド処理で必要

// サウンドファイル
enum  SOUND_LABEL
{
	S_MOVE,			//カーソル移動
	S_INCORRECT,	//はずれ
	S_DECISION,		//決定
	S_CORRECT,		//正解
	S_MONDAI,		//問題

	SOUND_LABEL_MAX,//←こいつは数に含めない
};

bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
/*
class Sound
{
private:
	static IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
public:
	static bool Init(HWND hWnd);
	static void Uninit();
	static void Play(SOUND_LABEL label);
	static void Stop(SOUND_LABEL label);
	static void Stop();
};
*/

