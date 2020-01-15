//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//	▼▼　ここにsound.cppに書いたファイル名に対応したラベル名を書く　▼▼
//	▼▼　ここのラベル名とsound.cppのファイル名の数は同じにしないとエラーになる　▼▼

// サウンドファイル
enum  SOUND_LABEL
{
	SOUND_LABEL_game_01,		    // game
	SOUND_LABEL_lose_01,		    // lose
	SOUND_LABEL_win_01,		    // win
	SOUND_LABEL_決定音_01,		// 決定音
	//SOUND_LABEL_SE_HIT,		// ヒット音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音

	SOUND_LABEL_MAX,//←こいつは数に含めない

};

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