/*=====================================================

	[SceneBase.h]
	Author : �o���đ�

======================================================*/

#pragma once
#include "main.h"
#include "sprite.h"
#include "Fade.h"

//#	SceneBase�N���X : �e�N���X

class SceneBase
{
protected:
	bool  m_bEnd;
	Sprite m_Sprite;
public:
	//�������z�֐��w��
	virtual ~SceneBase() {};	//	�f�X�g���N�^
	virtual void Init() = 0;	//	����������
	virtual void Uninit() = 0;	//	�I������
	virtual void Update() = 0;	//	�X�V����
	virtual void Draw() = 0;	//	�`�揈��
};
