//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"	// サウンド処理で必要

// サウンドファイル
enum  SoundLabel
{
	S_SE_MOVE,		// カーソル移動
	S_SE_INCORRECT,	// はずれ
	S_SE_DECISION,	// 決定
	S_SE_CORRECT,	// 正解
	S_SE_MONDAI,	// 問題

	SOUND_MAX,//←こいつは数に含めない
};

class Sound
{
private:
	static IXAudio2 *m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_MAX];					// オーディオデータサイズ

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
public:
	static bool Init(HWND hWnd);
	static void Uninit();
	static void Play(SoundLabel label);
	static void Stop(SoundLabel label);
	static void Stop();
};


