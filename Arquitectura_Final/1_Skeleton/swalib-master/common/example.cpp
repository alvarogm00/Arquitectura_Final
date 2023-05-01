#include "sys.h"
#include "vector2d.h"
//#include "SBall.h"
#include "Renderer.h"
#include "GameLogic.h"
#include "TimeManager.h"
#include "Entity.h"
#include "../swalib_example/swalib_example/Lvl1Factory.h"
#include "../swalib_example/swalib_example/Lvl2Factory.h"
#include <Windows.h>
//-----------------------------------------------------------------------------

int Main(void)
{
	GLuint texbkg = CORE_LoadPNG("data/background.png", true);
	GLuint texsmallball = CORE_LoadPNG("data/smallBall.png", false);
	GLuint texmedball = CORE_LoadPNG("data/mediumBall.png", false);
	GLuint texbigball = CORE_LoadPNG("data/bigBall.png", false);
	GLuint texprojectileball = CORE_LoadPNG("data/projectile.png", false);
	GLuint texplayer = CORE_LoadPNG("data/player.png", false);

	Lvl1Factory* factory = new Lvl1Factory(3, 60.f, 80.f, 120.f, Entity::MEDIUM_BALL, texsmallball, texmedball, texbigball, texplayer, vec2(30.f, 36.f), texprojectileball, vec2(250.f, 250.f));
	Lvl2Factory* factory2 = new Lvl2Factory(2, 60.f, 80.f, 120.f, Entity::BIG_BALL, texsmallball, texmedball, texbigball, texplayer, vec2(30.f, 36.f), texprojectileball, vec2(250.f, 250.f));
	// Control tiempo
	_fixedTick* timer = new _fixedTick(60.0f);

	CGameLogic::instance()->AddFactory(factory);
	CGameLogic::instance()->AddFactory(factory2);

	CGameLogic::instance()->InitGameLogic(factory);
	CRenderer::instance()->InitRender();
	// Set up rendering.
	while (!CGameLogic::instance()->GetIsShutDown())
	{	// Controlling a request to terminate an application.
		timer->InitSlotsToProcess();

		while (timer->ProcessSlots())
		{
			CGameLogic::instance()->UpdateGameLogic(timer->GetFixedTick());
		}
		CRenderer::instance()->Draw(&texbkg);
	}
	// End app.
	CGameLogic::instance()->CloseGameLogic();
	CRenderer::instance()->End(&texbkg);

	return 0;
}
