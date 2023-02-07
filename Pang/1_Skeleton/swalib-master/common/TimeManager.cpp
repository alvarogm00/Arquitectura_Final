#include "TimeManager.h"

float _fixedTick::GetTime()
{
	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);

	return ((double)currentTime.QuadPart - (double)prevTime.QuadPart) / (double)frecuency.QuadPart;
}

_fixedTick::_fixedTick(float _desiredFps)
{
	QueryPerformanceFrequency(&frecuency);
	QueryPerformanceCounter(&prevTime);

	m_lastTime = GetTime();
	m_currentTime = 0;
	m_deltaTime = 0;
	m_fixedTick = 1.0f / _desiredFps;
	m_elapsedTime = 0;
	m_totalTime = 0;
	m_logicTime = 0;
}

float _fixedTick::GetDeltaTime()
{
	return m_deltaTime;
}

float _fixedTick::GetElapsedTime()
{
	return m_elapsedTime;
}

float _fixedTick::GetTotalTime()
{
	return m_totalTime;
}

float _fixedTick::GetLogicTime()
{
	return m_logicTime;
}

float _fixedTick::GetFixedTick()
{
	return m_fixedTick;
}

void _fixedTick::InitSlotsToProcess()
{
	m_currentTime = GetTime();
	m_elapsedTime = (m_currentTime - m_lastTime);
	m_deltaTime += m_elapsedTime;
	m_lastTime = m_currentTime;
	m_totalTime += m_elapsedTime;

	if (m_deltaTime > 1. / 15.) m_deltaTime = 1. / 15.; //Evitar espiral de la muerte
}

bool _fixedTick::ProcessSlots()
{
	if (m_deltaTime > m_fixedTick)
	{
		m_deltaTime -= m_fixedTick;
		m_logicTime += m_fixedTick;
		return true;
	}
	else
	{
		return false;
	}
}
