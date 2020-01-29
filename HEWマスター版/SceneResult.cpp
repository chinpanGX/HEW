/*===================================================

	[SceneResult.cpp]
	�T�v : ���U���g�V�[�����Ǘ�����
	Author : �o���đ�

====================================================*/

#include "SceneResult.h"
#include "SceneManager.h"
#include "Controller.h"
#include"Fade.h"
//	�X�^�e�B�b�N�ϐ�
int SceneResult::m_Ranking[5];

void SceneResult::Init()
{
	m_bEnd = false;
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
	//Sort(�Q�b�^�[�Ŕ򋗗��̒l�������Ă���);
}

void SceneResult::Uninit()
{

}

void SceneResult::Update()
{
	if (!m_bEnd)
	{
		if (KeyBoard::IsTrigger(DIK_T))
		{
			m_bEnd = true;
			Fade::Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		}
	}
	else 
	{
		if (!Fade::IsFade())
		{
			SceneManager::ChangeSceneState();
		}
	}
}

void SceneResult::Draw()
{
	m_Sprite.Draw(TEXTURE_INDEX_RESULT,0.0f,0.0f);
	
	/*�X�R�A�̕`��
	for (int i = 0; i < RANKING_MAX; i++)	//	�`����܉�J��Ԃ�
	{
		Score_Draw(SCREEN_WIDTH / 2 - 48, SCREEN_HEIGHT / 3 + i * 32, ranking[i], 3, true);	
	}	
	*/
	
}

void SceneResult::Sort(int Score)
{
	for (int i = 0; i < 5; i++)
	{//1�ʂ����r
		//���̏��ʂ���������΂��ꂪ����̏��ʂƂȂ�
		//(1�ʂ�荂�����1�ʁA1�ʂ��Ⴍ2�ʂ�荂�����2�ʁA�c)
		if (Score > m_Ranking[i])
		{
			for (int j = 5 - 1; j > i; j--) //����̏��ʈȍ~�̃X�R�A�����炷
			{
				m_Ranking[j] = m_Ranking[j - 1];
			}
			m_Ranking[i] = Score;//����̃X�R�A���L��
			break;//�ȍ~�̏��ʂ͒��ׂȂ�
		}
	}
}
