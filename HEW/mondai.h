
//��


#pragma once
#include "main.h"
#include "sprite.h"

class Mondai
{
private:
	Sprite	m_Sprite;	
	static bool	m_flg;				//	�𓚃t���O
public:
	void Update();
	void Draw(int snow);			//	�v���C���[�ŌĂяo���`��
	static bool GetAnswer();		//	�t���O�̃Q�b�^�[
private:
	void Show(int show);			//	��蕶�̑I�o
	void MondaiOne(int answer);		//	�P��ڂ̕`��
	void MondaiTwo(int answer);		//	�Q��ڂ̕`��
	void MondaiThree(int answer);	//	�R��ڂ̕`��
	static bool Answer(bool flg);	//	�����͂ǂ����H�̔���
};
