#pragma once
#include "font.h"
#include "SBall.h"
#include "stdafx.h"
#include "core.h"
#include "GameLogic.h"

class CRenderer
{
public: 
	static CRenderer* instance();

	void InitRender();
	void Draw(GLuint* _texbkg, float _fpsCounter, float _totalTime, float _logicTime /*CSprite* _sprites[], int _size*/);
	void End(GLuint* _texsmallball, GLuint* _texbkg);
	void SetSprite(int _i, CSprite* _sprite);

private:
	CRenderer();
	static CRenderer* _instance;

	std::vector<CSprite*> sprites;
};