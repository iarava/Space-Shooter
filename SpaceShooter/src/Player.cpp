#include "Player.hpp"

// Konstruktor
// Aufgabe: Allgemein
CPlayer::CPlayer() {
	m_pSpritePlayer = NULL;
	m_pSpriteShot = NULL;
}

// Init
// Aufgabe: Sprites erzeugen und laden
void CPlayer::Init() {
	// Spieler-Sprite erstellen
	m_pSpritePlayer = new CSprite;

	m_pSpritePlayer->Load("Data/Player.bmp", 11, 64, 64);
	m_pSpritePlayer->SetColorKey(255, 0, 255);

	// Spieler-Sprite erstellen
	m_pSpriteShot = new CSprite;

	m_pSpriteShot->Load("Data/Laser.bmp", 1, 64, 64);
	m_pSpriteShot->SetColorKey(255, 0, 255);
}

// Quit
// Aufgabe: Sprites freigeben
void CPlayer::Quit() {
	// Spieler-Sprite freigeben
	if (m_pSpritePlayer != NULL) {
		delete (m_pSpritePlayer);
		m_pSpritePlayer = NULL;
	}


	// Schuss-Sprite freigeben
	if (m_pSpriteShot != NULL) {
		delete (m_pSpriteShot);
		m_pSpriteShot = NULL;
	}
}

// Reset
// Aufgabe: Spielerwerte auf Standard setzen
void CPlayer::Reset() {
	// Startposition des Spielers
	m_fXPos = 376.0f;
	m_fYPos = 520.0f;

	// Animationsphase
	m_fAnimPhase = 5.0f;

	// Es darf geschossen werden
	m_bShotLock = false;
}

// Render
// Aufgabe: Spieler und Schüsse rendern
void CPlayer::Render() {
	// Position des Spielers setzen und Sprite rendern
	m_pSpritePlayer->SetPos(m_fXPos, m_fYPos);
	m_pSpritePlayer->Render(m_fAnimPhase);

	// Iterator für die Schussliste
	list<CShot>::iterator itShots = m_ShotList.begin();

	// Schussliste durchlaufen
	while (itShots != m_ShotList.end()) {
		// Schuss updaten
		itShots->Update();

		// Ist der Schuss noch aktiv?
		if (itShots->IsAlive()) {
			itShots->Render();
			itShots++;
		}
		else {
			itShots = m_ShotList.erase(itShots);
		}
	}
}

// Update
// Aufgabe: Spieler updaten
void CPlayer::Update() {
	ProcessMoving();
	ProcessShooting();
	CheckPosition();
}

// ProcessMoving
// Aufgabe: Bewegung des Spielers
void CPlayer::ProcessMoving() {
	// Nach links?
	if (g_pFramework->KeyDown(SDL_SCANCODE_LEFT) || g_pFramework->KeyDown(SDL_SCANCODE_A)) {
		m_fXPos -= 300.0f * g_pTimer->GetElapsed();
		m_fAnimPhase -= 20.0f * g_pTimer->GetElapsed();
	}
	// Nach rechts?
	else if (g_pFramework->KeyDown(SDL_SCANCODE_RIGHT) || g_pFramework->KeyDown(SDL_SCANCODE_D)) {
		m_fXPos += 300.0f * g_pTimer->GetElapsed();
		m_fAnimPhase += 20.0f * g_pTimer->GetElapsed();
	}
	// Spieler wurde nicht bewegt
	else {
		if(m_fAnimPhase > 5.0f)
			m_fAnimPhase -= 20.0f * g_pTimer->GetElapsed();
		if (m_fAnimPhase < 5.0f)
			m_fAnimPhase += 20.0f * g_pTimer->GetElapsed();
	}
}

// ProcessShooting
// Aufgabe: Waffe abfeuern
void CPlayer::ProcessShooting() {
	// Wurde Space gedrückt und darf geschossen werden?
	if (g_pFramework->KeyDown(SDL_SCANCODE_SPACE) && m_bShotLock == false) {
		// Schuss erzeugen und initialisieren
		CShot Shot;
		Shot.Init(m_pSpriteShot, m_fXPos, m_fYPos);

		// Schuss in Liste einfügen
		m_ShotList.push_back(Shot);

		// Schiessen erst wieder erlaubt, wenn Space losgelassen
		m_bShotLock = true;
	}

	// Ist die Leertaste nicht mehr gedrückt, schiessen wieder erlaubt
	if (g_pFramework->KeyDown(SDL_SCANCODE_SPACE) == false) {
		m_bShotLock = false;
	}
}

// CheckPosition
// Aufgabe: Position und Animatinsphase prüfen
void CPlayer::CheckPosition() {
	// Linker und rechter Rand
	if (m_fXPos < 0.0f)
		m_fXPos = 0.0f;
	else if (m_fXPos > 752.0f)
		m_fXPos = 752.0f;

	// Animationsphase prüfen
	if (m_fAnimPhase < 0.0f)
		m_fAnimPhase = 0.0f;
	else if (m_fAnimPhase > 10.0f)
		m_fAnimPhase = 10.0f;
}

