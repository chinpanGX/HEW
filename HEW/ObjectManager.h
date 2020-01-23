/*============================================

	[ObjectManager.h]	
	�T�v�F�I�u�W�F�N�g�̃Q�b�^�[���Ǘ�
	Author :�@�o���đ�

============================================*/

#pragma once
#include "SceneManager.h"
#include "SceneGame.h"

class ObjectManager
{
public:
	static Character* SetCharacter();	//	�L�����N�^�[�I�u�W�F�N�g�̃Q�b�^�[
	static Field* SetField();			//	�}�b�v�I�u�W�F�N�g�̃Q�b�^�[
	static Camera* SetCamera();			//	�J�����I�u�W�F�N�g�̃Q�b�^�[
};

