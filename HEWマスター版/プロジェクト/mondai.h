#pragma once
#include "main.h"
#include "sprite.h"

enum MONDAI_NUM
{
	MONDAI_1st,
	MONDAI_2nd,
	MONDAI_3rd,
	MONDAI_END,
};

int	 GetScore();

class Mondai
{
private:
	Sprite	m_Sprite;	
	static bool	m_flg;	  //�𓚃t���O
	static bool dr_flag1; //�`��̃t���O
	static bool dr_flag2;
	void Show(int show);			//	��蕶�̑I�o
	void MondaiOne(int answer);		//	�P��ڂ̕`��
	void MondaiTwo(int answer);		//	�Q��ڂ̕`��
	void MondaiThree(int answer);	//	�R��ڂ̕`��

public:
	void Init();
	void Update();
	void Draw(int snow);			//	�v���C���[�ŌĂяo���`��
	static bool Answer(bool question, bool answer);		//	�t���O�̃Q�b�^�[

};
