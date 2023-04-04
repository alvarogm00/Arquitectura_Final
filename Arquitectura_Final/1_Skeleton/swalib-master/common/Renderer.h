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
	void Draw(GLuint* _texbkg);
	void End(GLuint* _texbkg);
	void SetRenderComponent(RenderComponent* _renderComponent);
	void Clear();

private:
	CRenderer();
	static CRenderer* _instance;

	std::vector<RenderComponent*> m_renderComponents;
};