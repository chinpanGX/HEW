/*===================================================

	[SceneResult.cpp]
	Author : 出合翔太

====================================================*/

#include "SceneResult.h"
#include "SceneManager.h"
#include "Controller.h"
#include"Fade.h"
//	スタティック変数
int SceneResult::m_Ranking[5];

void SceneResult::Init()
{
	m_bEnd = false;
	Fade::Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
	//Sort(ゲッターで飛距離の値を持ってくる);
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
	
	/*スコアの描画
	for (int i = 0; i < RANKING_MAX; i++)	//	描画を五回繰り返す
	{
		Score_Draw(SCREEN_WIDTH / 2 - 48, SCREEN_HEIGHT / 3 + i * 32, ranking[i], 3, true);	
	}	
	*/
	
}

void SceneResult::Sort(int Score)
{
	for (int i = 0; i < 5; i++)
	{//1位から比較
		//今の順位よりも高ければそれが今回の順位となる
		//(1位より高ければ1位、1位より低く2位より高ければ2位、…)
		if (Score > m_Ranking[i])
		{
			for (int j = 5 - 1; j > i; j--) //今回の順位以降のスコアをずらす
			{
				m_Ranking[j] = m_Ranking[j - 1];
			}
			m_Ranking[i] = Score;//今回のスコアを記憶
			break;//以降の順位は調べない
		}
	}
}
