#pragma once
#include <Windows.h>

class _fixedTick
{
	float m_deltaTime;
	float m_elapsedTime;
	float m_currentTime;
	float m_lastTime;
	float m_fixedTick;
	float m_totalTime;
	float m_logicTime;

	LARGE_INTEGER prevTime;
	LARGE_INTEGER frecuency;

private:
	float GetTime();
public:
	_fixedTick(float _desiredFps);

	float GetDeltaTime();
	float GetElapsedTime();
	float GetTotalTime();
	float GetLogicTime();
	float GetFixedTick();

	void InitSlotsToProcess();
	bool ProcessSlots();
};

