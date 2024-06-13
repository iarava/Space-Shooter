#include "Framework.hpp"

// Init
// Aufgabe: Framework initialisieren
bool CFramework::Init(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen) {
	// Alle Systeme der SDL initialisieren
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
		cout << "SDL konnte nicht initialisiert werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

		return (false);
	}

	// Vollbild oder Fenstermodus einstellen
	if (bFullscreen == true) {
		m_pWindow = SDL_CreateWindow("SDL Game",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			ScreenWidth, ScreenHeight,
			SDL_WINDOW_FULLSCREEN);
	}
	else {
		m_pWindow = SDL_CreateWindow("SDL Game",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			ScreenWidth, ScreenHeight,
			0);
	}

	// Prüfen, ob alles funktioniert hat
	if (m_pWindow == NULL) {
		cout << "Game-Fenster konnte nicht erzeugt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

		return (false);
	}

	// Surface aus Window setzen
	m_pScreen = SDL_GetWindowSurface(m_pWindow);

	// Prüfen, ob alles funktioniert hat
	if (m_pWindow == NULL) {
		cout << "Surface konnte nicht erzeugt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

		return (false);
	}
	
	// Zeiger auf internes Array für Tastaturstatus ermitteln
	m_pKeyState = SDL_GetKeyboardState(NULL);

	// Alles ging glatt, also true zurückliefern
	return(true);
}

// Quit
// Aufgabe: Framework (SDL) beenden
void CFramework::Quit() {//Destroy window
	SDL_DestroyWindow(m_pWindow);

	SDL_Quit();
}

// Update
// Aufgabe: Timer und Keyboardstatus updaten
void CFramework::Update() {
	//Update the surface
	SDL_UpdateWindowSurface(m_pWindow);

	// Timer updaten
	g_pTimer->Update();

	// Tastaturstatus ermitteln
	SDL_PumpEvents();
}

// Clear
// Aufgabe: Buffer löschen
void CFramework::Clear() {
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 0, 0, 0));

	//Update the surface
	SDL_UpdateWindowSurface(m_pWindow);
}

// Flip
// Aufgabe: Surace umschalten (flippen)
void CFramework::Flip() {
	/*
	SDL_LockSurface(m_pScreen);

	int pitch = m_pScreen->pitch; // row size
	char* temp = new char[pitch]; // intermediate buffer
	char* pixels = (char*)m_pScreen->pixels;

	for (int i = 0; i < m_pScreen->h / 2; ++i) {
		// get pointers to the two rows to swap
		char* row1 = pixels + i * pitch;
		char* row2 = pixels + (m_pScreen->h - i - 1) * pitch;

		// swap rows
		memcpy(temp, row1, pitch);
		memcpy(row1, row2, pitch);
		memcpy(row2, temp, pitch);
	}

	delete[] temp;

	SDL_UnlockSurface(m_pScreen);
	*/
}

// Keydown
// Aufgabe: Tastendruck abfragen
bool CFramework::KeyDown(int Key_ID) {
	return (m_pKeyState[static_cast<Uint8>(Key_ID)] ? true : false);
}