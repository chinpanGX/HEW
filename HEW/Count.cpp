#include "main.h"
#include "Count.h"
#include "texture.h"


//static Count g_Count[COUNTDOWN];

void Count::Init()
{
	
}

void Count::Uninit()
{
}

void Count::Update()
{
	
}

void Count::Draw()
{
	m_Limit.Draw(TEXTURE_INDEX_SU,880.0f,530.0f,576.0f,0.0f,64.0f,64.0f,0.0f,0.0f,3.0f,3.0f,0.0f);
}

