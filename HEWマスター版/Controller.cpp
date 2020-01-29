/*===============================================

	[Controller.cpp]
	Author : �o���đ�

================================================*/

#include "main.h"
#include "Controller.h"

LPDIRECTINPUTDEVICE8	KeyBoard::m_pDevKeyboard = NULL;								//	�L�[�{�[�h�f�o�C�X
BYTE					KeyBoard::m_aKeyState[NUM_KEY_MAX];								//	�L�[�{�[�h���i�����Ă���ԁj
BYTE					KeyBoard::m_aKeyStateTrigger[NUM_KEY_MAX];						//	�L�[�{�[�h���i�������u�ԁj
BYTE					KeyBoard::m_aKeyStateRelease[NUM_KEY_MAX];						//	�L�[�{�[�h���i�������u�ԁj	
LPDIRECTINPUTDEVICE8	GamePad::m_pGamePad[GAMEPADMAX] = { NULL, NULL, NULL, NULL };	//	�p�b�h�f�o�C�X
DWORD					GamePad::m_padState[GAMEPADMAX];								//	�p�b�h���i�����Ă���ԁj
DWORD					GamePad::m_padTrigger[GAMEPADMAX];								//	�p�b�h���i�������u�ԁj
int						GamePad::m_padCount = 0;										//	���o�����p�b�h�̐�

//	�L�[�{�[�h�̏�����
bool KeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (!Input::Init(hInstance))
	{

		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}
	//													 DISCL_BACKGROUND | DISCL_EXCLUSIVE	
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}

	m_pDevKeyboard->Acquire();
	return true;
}

//	�L�[�{�[�h�̏I������
void KeyBoard::Uninit()
{
	SAFE_RELEASE(m_pDevKeyboard);
	Input::Uninit();
}

//	�L�[�{�[�h�̍X�V����
void KeyBoard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];

	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];

			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();
	}
}

//�L�[�{�[�h�������Ă����
bool KeyBoard::IsPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h���������u��
bool KeyBoard::IsTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�𗣂����Ƃ�
bool KeyBoard::IsRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//�Q�[���p�b�h�p�R�[���o�b�N�֐�
BOOL GamePad::SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT result;

	result = m_pInput->CreateDevice(lpddi->guidInstance, &m_pGamePad[m_padCount++], NULL);
	return DIENUM_CONTINUE;	// ���̃f�o�C�X���
}

//�Q�[���p�b�h�̏���������
bool GamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (!Input::Init(hInstance))
	{

		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	HRESULT		result;
	int			i;

	m_padCount = 0;
	// �W���C�p�b�h��T��
	m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B

	for (i = 0; i < m_padCount; i++)
	{
		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
		result = m_pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		//		if ( FAILED(result) )
		//			return false; // ���[�h�̐ݒ�Ɏ��s

		// ���̒l�͈̔͂�ݒ�
		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
		// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
		// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;
		// X���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_X;
		m_pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		m_pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_X;
		m_pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Y;
		m_pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//�W���C�X�e�B�b�N���͐���J�n
		m_pGamePad[i]->Acquire();
	}

	return true;
}


void GamePad::Uninit()
{
	for (int i = 0; i < GAMEPADMAX; i++) {
		if (m_pGamePad[i])
		{
			m_pGamePad[i]->Unacquire();
			m_pGamePad[i]->Release();
		}
	}
	Input::Uninit();
}

//�Q�[���p�b�h�̍X�V����
void GamePad::Update()
{
	HRESULT			result;
	DIJOYSTATE2		dijs;	//�Q�[���p�b�h�̓��͒l
	int				i;

	for (i = 0; i < m_padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = m_padState[i];	//�Q�[���p�b�h�̃{�^���z��
		m_padState[i] = 0x00000000l;	// ���͗p32�r�b�g�̏�����

		result = m_pGamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
		if (FAILED(result))
		{
			result = m_pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = m_pGamePad[i]->Acquire();
		}

		result = m_pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			result = m_pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = m_pGamePad[i]->Acquire();
		}

		/*---------------------------------------------------------------------------------------------------
			�R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���//long�^�f�t�H���g�i32767���炢�j
		-----------------------------------------------------------------------------------------------------*/

		//�@��	����
		//! �ԁ@Xbox�̂�
		//" �@PS4�̂�
		//!	���Ӂ@Xbox��PS4�̓��͂𓯎��Ɏg��Ȃ�����

		// Xbox��PS4:���X�e�B�b�Ny-axis (forward)
		if (dijs.lY < 0)					m_padState[i] |= LEFTSTICK_UP;
		// Xbox��PS4:���X�e�B�b�Ny-axis (backward)
		if (dijs.lY > 0)					m_padState[i] |= LEFTSTICK_DOWN;
		// Xbox��PS4:���X�e�B�b�Nx-axis (left)
		if (dijs.lX < 0)					m_padState[i] |= LEFTSTICK_LEFT;
		// Xbox��PS4:���X�e�B�b�Nx-axis (right)
		if (dijs.lX > 0)					m_padState[i] |= LEFTSTICK_RIGHT;

		//! Xbox:�E�X�e�B�b�Ny-axis (forward)
		if (dijs.lRy < 16383)				m_padState[i] |= XboxRIGHTSTICK_UP;
		//! Xbox:�E�X�e�B�b�Ny-axis (backward)
		if (dijs.lRy > 49150)				m_padState[i] |= XboxRIGHTSTICK_DOWN;
		//! Xbox:�E�X�e�B�b�Nx-axis (left)
		if (dijs.lRx < 16383)				m_padState[i] |= XboxRIGHTSTICK_LEFT;
		//! Xbox:�E�X�e�B�b�Nx-axis (right)
		if (dijs.lRx > 49150)				m_padState[i] |= XboxRIGHTSTICK_RIGHT;

		//" PS4:�E�X�e�B�b�Ny-axis (forward)
		if (dijs.lRz < 16383)				m_padState[i] |= PS4RIGHTSTICK_UP;
		//" PS4:�E�X�e�B�b�Ny-axis (backward)
		if (dijs.lRz > 49150)				m_padState[i] |= PS4RIGHTSTICK_DOWN;
		//" PS4:�E�X�e�B�b�Nx-axis (left)
		if (dijs.lZ < 16383)				m_padState[i] |= PS4RIGHTSTICK_LEFT;
		//" PS4:�E�X�e�B�b�Nx-axis (right)
		if (dijs.lZ > 49150)				m_padState[i] |= PS4RIGHTSTICK_RIGHT;

		//! Xbox:LT�g���K�[
		if (dijs.lZ > 49150)				m_padState[i] |= TRIGGER_LT;
		//! Xbox:RT�g���K�[
		if (dijs.lZ < 16383)				m_padState[i] |= TRIGGER_RT;
		//" PS4:L2�g���K�[
		if (dijs.lRx > 10000)				m_padState[i] |= TRIGGER_L2;
		//" PS4:R2�g���K�[
		if (dijs.lRy > 10000)				m_padState[i] |= TRIGGER_R2;

		//* Xbox:�`�{�^��	�@PS4�F���{�^��
		if (dijs.rgbButtons[0] & 0x80)		m_padState[i] |= BUTTON_1;
		//* Xbox:�w�{�^��	  PS4�F�Z�{�^��
		if (dijs.rgbButtons[2] & 0x80)		m_padState[i] |= BUTTON_2;
		//* Xbox:�a�{�^��	�@PS4�F�~�{�^��
		if (dijs.rgbButtons[1] & 0x80)		m_padState[i] |= BUTTON_3;
		//*	Xbox:�x�{�^��	�@PS4�F���{�^��
		if (dijs.rgbButtons[3] & 0x80)		m_padState[i] |= BUTTON_4;
		//* Xbox:LB�{�^��	�@PS4�FL1�{�^��
		if (dijs.rgbButtons[4] & 0x80)		m_padState[i] |= BUTTON_LB;
		//* Xbox:RB�{�^��	�@PS4�FR1�{�^��
		if (dijs.rgbButtons[5] & 0x80)		m_padState[i] |= BUTTON_RB;
		//* Xbox:BACK�{�^�� �@PS4 : OPTION�{�^��
		if (dijs.rgbButtons[6] & 0x80)		m_padState[i] |= BUTTON_BACK;
		//* Xbox:START�{�^���@PS4 : SHARE�{�^��
		if (dijs.rgbButtons[7] & 0x80)		m_padState[i] |= BUTTON_START;

		//! Xbox:L3�{�^��	
		if (dijs.rgbButtons[8] & 0x80)		m_padState[i] |= BUTTON_L3;
		//! Xbox:R3�{�^��	
		if (dijs.rgbButtons[9] & 0x80)		m_padState[i] |= BUTTON_R3;

		//* Xbox��PS4�F�����L�[��
		if (dijs.rgdwPOV[0] <= 0)									m_padState[i] |= BUTTON_UP;
		//* Xbox��PS4�F�����L�[��
		if (dijs.rgdwPOV[0] <= 18000 && dijs.rgdwPOV[0] > 9000)		m_padState[i] |= BUTTON_DOWN;
		//* Xbox��PS4�F�����L�[��
		if (dijs.rgdwPOV[0] <= 27000 && dijs.rgdwPOV[0] > 18000)	m_padState[i] |= BUTTON_LEFT;
		//* Xbox��PS4�F�����L�[�E
		if (dijs.rgdwPOV[0] <= 9000 && dijs.rgdwPOV[0] > 0)			m_padState[i] |= BUTTON_RIGHT;

		// Trigger�ݒ�
		m_padTrigger[i] = ((lastPadState ^ m_padState[i])	// �O��ƈ���Ă���
			& m_padState[i]);					// ��������ON�̂��

	}
}

//�Q�[���p�b�h�̃{�^���������Ă����
BOOL GamePad::IsPress(int padNo, DWORD button)
{
	return (button & m_padState[padNo]);
}

//�Q�[���p�b�h�̃{�^�����������u��
BOOL GamePad::IsTrigger(int padNo, DWORD button)
{
	return (button & m_padTrigger[padNo]);
}
