//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"	// �T�E���h�����ŕK�v

// �T�E���h�t�@�C��
enum  SOUND_LABEL
{
	S_MOVE,	//�J�[�\���ړ�
	S_COUNTDOWN,
	S_START,
	S_JUMP_BAD,
	S_JUMP_EXCELLENT,
	S_JUMP_GOOD,
	S_INCORRECT,
	S_DECISION,
	S_CORRECT,
	S_SPEEDUP,
	s_FLY,
	S_MONDAI,

	SOUND_LABEL_MAX,//�������͐��Ɋ܂߂Ȃ�
};

class Sound
{
private:
	static IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
public:
	static bool Init(HWND hWnd);
	static void Uninit();
	static void Play(SOUND_LABEL label);
	static void Stop(SOUND_LABEL label);
	static void Stop();
};

