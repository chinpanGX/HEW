/*==================================

	[input.cpp]
	Author : �o���đ�

====================================*/

#include "input.h"
#include "main.h"

//	�X�^�e�B�b�N�ϐ�
LPDIRECTINPUT8			Input::m_pInput = NULL;		//	DirectInput�I�u�W�F�N�g
			
//	DirectInput�I�u�W�F�N�g������
bool Input::Init(HINSTANCE hInstance)
{
	//	DirectInput8�̍쐬
	if (m_pInput == NULL)
	{
		//	�쐬�̎��s
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return false;
		}
	}
	return true;	//����I��
}

//DirectInput�I�u�W�F�N�g�I������
void Input::Uninit()
{	
	SAFE_RELEASE(m_pInput);
}
