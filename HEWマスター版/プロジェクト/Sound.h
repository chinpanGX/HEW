//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"	// �T�E���h�����ŕK�v

// �T�E���h�t�@�C��
enum  SoundLabel
{
	S_SE_MOVE,		// �J�[�\���ړ�
	S_SE_INCORRECT,	// �͂���
	S_SE_DECISION,	// ����
	S_SE_CORRECT,	// ����
	S_SE_MONDAI,	// ���

	SOUND_MAX,//�������͐��Ɋ܂߂Ȃ�
};

class Sound
{
private:
	static IXAudio2 *m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;		// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
public:
	static bool Init(HWND hWnd);
	static void Uninit();
	static void Play(SoundLabel label);
	static void Stop(SoundLabel label);
	static void Stop();
};


