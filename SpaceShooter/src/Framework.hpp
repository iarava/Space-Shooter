#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Timer.hpp"

using namespace std;

#define g_pFramework CFramework::Get()

class CFramework : public TSingleton<CFramework>
{
	public:
		bool Init(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen);
		void Quit();
		void Update();
		void Clear();
		void Flip();
		bool KeyDown(int Key_ID);
		SDL_Surface *GetScreen() { return m_pScreen; }

	private:
		SDL_Window *m_pWindow;	// Window für den Screen
		SDL_Surface *m_pScreen;	// Surface für den Screen
		const Uint8 *m_pKeyState;		// Array für aktuellen Tastaturstatus
};

#endif
