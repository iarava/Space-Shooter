#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL.h>
#include "Singleton.hpp"

#define g_pTimer CTimer::Get()
class CTimer : public TSingleton<CTimer>
{
	public:
		CTimer();
		void Update();
		float GetElapsed() {
			return m_fElapsed;
		}

	private:
		float m_fElapsed;
		float m_fCurrTime;
		float m_fLastTime;
};

#endif
