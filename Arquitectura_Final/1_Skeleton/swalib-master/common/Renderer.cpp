#include "Renderer.h"

const char* fpsCounter; 
CRenderer* CRenderer::_instance = nullptr;

CRenderer* CRenderer::instance()
{
	if (!_instance)
	{
		_instance = new CRenderer();
	}
	return _instance;
}

void CRenderer::InitRender()
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen.

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}

void CRenderer::Draw(GLuint* _texbkg)
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

		// Render background
	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
			CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), *_texbkg);
		}
	}

	//// Render balls
	for (int i = 0; i < m_renderComponents.size(); i++) 
	{
		m_renderComponents[i]->Draw();
	}

	 //Text
	//float fps = 1 / _elapsedTime;
	//char str[30];
	//sprintf(str, "FPS: %.2f", fps);
	//FONT_DrawString(vec2(SCR_WIDTH / 2 + 9 * 16, 16), str);
	//char str1[30];
	//sprintf(str1, "TT: %.2f", _totalTime);
	//FONT_DrawString(vec2(SCR_WIDTH / 2 - 20 * 16, 16), str1);
	//char str2[30];
	//sprintf(str2, "TLT: %.2f", _logicTime);
	//FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), str2);

	// Exchanges the front and back buffers
	SYS_Show();

	SYS_Pump();	// Process Windows messages.
	//SYS_Sleep(17);	// To force 60 fps
}

void CRenderer::End(GLuint* _texbkg)
{
	// Unload textures.
	CORE_UnloadPNG(*_texbkg);
	FONT_End();
}

void CRenderer::SetRenderComponent(RenderComponent* _renderComponent)
{
	m_renderComponents.push_back(_renderComponent);
}

void CRenderer::Clear()
{
	m_renderComponents.clear();	// Clear color buffer to preset values.
}

CRenderer::CRenderer() {}

