#include "sys.h"
#include "vector2d.h"
#include "SBall.h"
#include "Renderer.h"
#include "GameLogic.h"
#include "TimeManager.h"
#include <Windows.h>
//-----------------------------------------------------------------------------

int Main(void)
{
	GLuint texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	GLuint texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

	// Control tiempo
	_fixedTick* timer = new _fixedTick(60.0f);

	CGameLogic::instance()->InitGameLogic(&texsmallball);
	CRenderer::instance()->InitRender();
	// Set up rendering.
	while (!SYS_GottaQuit()) 
	{	// Controlling a request to terminate an application.
		timer->InitSlotsToProcess();

		while (timer->ProcessSlots())
		{
			CGameLogic::instance()->UpdateGameLogic(timer->GetFixedTick());
		}
		CRenderer::instance()->Draw(&texbkg, timer->GetElapsedTime(), timer->GetTotalTime(), timer->GetLogicTime()/*CGameLogic::instance()->GetSpritesArray(), CGameLogic::instance()->GetNumBalls()*/);
	}
	// End app.
	CGameLogic::instance()->CloseGameLogic();
	CRenderer::instance()->End(&texsmallball, &texbkg);

	return 0;
}
