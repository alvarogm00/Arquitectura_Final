#pragma once
#include "font.h"
#include "SBall.h"
#include "stdafx.h"
#include "core.h"
#include "GameLogic.h"
#include "../swalib_example/swalib_example/RenderComponent.h"

class CRenderer
{
public: 
	static CRenderer* instance();

	void InitRender();
	void Draw(GLuint* _texbkg, float _fpsCounter, float _totalTime, float _logicTime /*CSprite* _sprites[], int _size*/);
	void End(GLuint* _texsmallball, GLuint* _texbkg);
	void SetRenderComponent(RenderComponent* _renderComponent);

private:
	CRenderer();
	static CRenderer* _instance;

	std::vector<RenderComponent*> m_renderComponents;
};