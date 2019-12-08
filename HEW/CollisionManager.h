/*=============================================

	[CollisionManager.h]
	Author : èoçá„ƒëæ

===============================================*/

#pragma once
#include "Collision.h"
#include "Character.h"
#include "Map.h"
#include "Model.h"
#include "XFile.h"

class CollisionManager
{
private:
	static Collision m_Collision;
public:
	static void Player_vs_Map();
};

