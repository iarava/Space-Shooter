#include "Game.hpp"

// Konstruktor
// Aufgabe: Allgemeine Initialisierungen
CGame::CGame() {
	m_pPlayer = NULL;
	m_pSpriteBackground = NULL;
	m_pSpriteAsteroid = NULL;
}

// Init
// Aufgabe: Spieler, Hintergrund und Asteroid initialisieren
void CGame::Init() {
	// Neuen Spieler initialisieren
	m_pPlayer = new CPlayer;
	m_pPlayer->Init();
	m_pPlayer->Reset();

	// Hintergrundbild (Sprite) laden
	m_pSpriteBackground = new CSprite;
	m_pSpriteBackground->Load("Data/Background.bmp");

	// Sprite für Asteroiden laden
	m_pSpriteAsteroid = new CSprite;
	m_pSpriteAsteroid->Load("Data/Asteroid.bmp", 20, 64, 64);
	m_pSpriteAsteroid->SetColorKey(255, 0, 255);

	// Timer für Asteroiden zurücksetzen
	m_fAsteroidTimer = 0.0f;

	// Spiel läuft
	m_bGameRun = true;
}

// Run
// Aufgabe: Intanzen freigeben
void CGame::Quit() {
	// Spieler freigeben
	if (m_pPlayer != NULL) {
		m_pPlayer->Quit();
		delete (m_pPlayer);
		m_pPlayer = NULL;
	}

	// Hintergrundsprite freigeben
	if (m_pSpriteBackground != NULL) {
		delete (m_pSpriteBackground);
		m_pSpriteBackground = NULL;
	}

	// Asteroidensprite freigeben
	if (m_pSpriteAsteroid != NULL) {
		delete (m_pSpriteAsteroid);
		m_pSpriteAsteroid = NULL;
	}
}

// Run
// Aufgabe: Hauptschleife des Spiels
void CGame::Run() {
	while (m_bGameRun) {
		// Events bearbeiten
		ProcessEvents();

		// Framework updaten und Buffer löschen
		g_pFramework->Update();
		g_pFramework->Clear();

		// Hintergrundbild rendern
		m_pSpriteBackground->Render();

		// Spieler updaten und rendern
		m_pPlayer->Update();
		m_pPlayer->Render();

		// Neue Asteroiden hinzufügen
		SpawnAsteroids();

		// Kollision prüfen
		CheckCollision();

		// Asteroiden rendern
		RenderAsteroids();
	}
}

// ProcessEvents
// Aufgabe: Events bearbeiten
void CGame::ProcessEvents() {
	SDL_Event Event;

	// Gabe es ein Event
	if (SDL_PollEvent(&Event)) {
		// Welches Event?
		switch (Event.type) {

			// Beenden?
			case (SDL_QUIT):
			{
				m_bGameRun = false;
			}
			break;

			// Taste gedrückt?
			case (SDL_KEYDOWN):
			{
				switch (Event.key.keysym.sym) {
				case(SDLK_ESCAPE):
				{
					m_bGameRun = false;
				}
				break;
				}
			}
			break;
		}
	}

	
}

// SpawnAsteroids
// Aufgabe: Nach Ablauf einer bestimmten Zeit neuen Asteroiden erzeugen
void CGame::SpawnAsteroids() {
	// Timer für nächsten Asteroiden erhöhen
	m_fAsteroidTimer += g_pTimer->GetElapsed();

	// Wenn eine halbe Sekunde vergange ist,
	// dann einen neuen Asteroiden erzeugen
	if (m_fAsteroidTimer >= 1.0f) {
		CAsteroid Asteroid;

		int XPos = rand() % 736;

		Asteroid.Init(m_pSpriteAsteroid, static_cast<float>(XPos), -60.0f);

		m_AsteroidList.push_back(Asteroid);

		m_fAsteroidTimer = 0.0f;
	}
}

// RenderAsteroids
// Aufgabe: Alle Asteroiden rendern und updaten
void CGame::RenderAsteroids() {
	// Iterator für die Steroiden-Liste
	list<CAsteroid>::iterator itAsteroids;

	// Asteroiden-Liste durchlaufen
	for (itAsteroids = m_AsteroidList.begin(); itAsteroids != m_AsteroidList.end(); ++itAsteroids) {
		itAsteroids->Render();
		itAsteroids->Update();
	}
}

// CheckCollisions
// Aufgabe: Kollisionen zwischen Asteroiden und Schüssen prüfen
void CGame::CheckCollision() {
	// Schussliste des Spielers holen
	list<CShot> *ShotList = m_pPlayer->GetShotList();

	// Iteratoren für Asteroiden- und Schussliste
	list<CAsteroid>::iterator itAsteroid = m_AsteroidList.begin();
	list<CShot>::iterator itShot;

	// Rects für Asteroiden und Schüsse
	SDL_Rect RectAsteroid;
	SDL_Rect RectShot;

	// Alle Asteroiden durchlaufen
	while (itAsteroid != m_AsteroidList.end()) {
		// Rect des Asteroiden holen
		RectAsteroid = itAsteroid->GetRect();

		// Alle Schüsse durchlaufen
		for (itShot = ShotList->begin(); itShot != ShotList->end(); ++itShot) {
			// Rect des Schusses holen
			RectShot = itShot->GetRect();

			// Überschneiden sich die Rects?
			if (RectShot.y < RectAsteroid.y + RectAsteroid.h &&
				RectShot.y + RectShot.h > RectAsteroid.y &&
				RectShot.x < RectAsteroid.x + RectAsteroid.w &&
				RectShot.x + RectShot.w > RectAsteroid.x) {
				itAsteroid->SetAlive(false);
				itShot->SetAlive(false);
			}
		}

		if (itAsteroid->IsAlive()) {
			itAsteroid++;
		}
		else {
			itAsteroid = m_AsteroidList.erase(itAsteroid);
		}
	}
}