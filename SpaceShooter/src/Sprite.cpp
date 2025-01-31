#include "Sprite.hpp"

// Konstruktor
// Aufgabe: Zeiger auf Screen holen
CSprite::CSprite() {
	m_pScreen = g_pFramework->GetScreen();
}

// Destruktor
// Aufgabe: Surface des Sprites freigeben
CSprite::~CSprite() {
	SDL_FreeSurface(m_pImage);
}

// Load
// Aufgabe: Einfaches, nicht animiertes Sprite laden
void CSprite::Load(const string sFilename) {
	// Bitmap laden
	m_pImage = SDL_LoadBMP(sFilename.c_str());

	// Pr�fen, ob alles glattging
	if (m_pImage == NULL) {
		cout << "Fehler beim Laden von: " << sFilename.c_str();
		cout << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		// Framework herunterfahren
		g_pFramework->Quit();

		// Gesamtes Spiel beenden
		exit(1);
	}

	// Rect initialisieren
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = m_pImage->w;
	m_Rect.h = m_pImage->h;
}

// Load
// Aufgabe: Animiertes Frame laden
void CSprite::Load(const string sFilename, int NumFrames, int FrameWidth, int FrameHeight) {
	// Bitmap laden
	Load(sFilename);

	// Rect f�r Animatinsphase initialisieren
	m_NumFrames = NumFrames;
	m_FrameWidth = FrameWidth;
	m_FrameHeight = FrameHeight;
	m_FrameRect.w = FrameWidth;
	m_FrameRect.h = FrameHeight;
	m_NumFramesX = m_pImage->w / m_FrameWidth;
}

// SetColorKey
// Aufgabe: Transparente Farbe festlegen
void CSprite::SetColorKey(int R, int G, int B) {
	SDL_SetColorKey(m_pImage, SDL_TRUE, SDL_MapRGB(m_pImage->format, R, G, B));
}

// SetPos
// Aufgabe: Position des Sprites festlegen
void CSprite::SetPos(float fXPos, float fYPos) {
	// Rect updaten
	m_Rect.x = static_cast<int>(fXPos);
	m_Rect.y = static_cast<int>(fYPos);
}

// Render
// Aufgabe: Sprite rendern (ohne Animation)
void CSprite::Render() {
	SDL_BlitSurface(m_pImage, NULL, m_pScreen, &m_Rect);
}

// Render
// Aufgabe: Ausschnitt des Sprites rendern (Animationsphase)
void CSprite::Render(float fFrameNumber) {
	// Zeile Spalte & Zeile berechnen
	int Column = static_cast<int>(fFrameNumber) % m_NumFramesX;
	int Row = static_cast<int>(fFrameNumber) / m_NumFramesX;

	// Rect berechnen
	m_FrameRect.x = Column * m_FrameWidth;
	m_FrameRect.y = Row * m_FrameHeight;

	// Ausschnit rendern
	SDL_BlitSurface(m_pImage, &m_FrameRect, m_pScreen, &m_Rect);
}