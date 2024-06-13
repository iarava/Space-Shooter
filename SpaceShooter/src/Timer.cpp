#include "Timer.hpp"

// Konstruktur
// Aufgabe: Initialisierung
CTimer::CTimer() {
	// Initialisierung
	m_fCurrTime = 0.0f;
	m_fLastTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = 0.0f;
}


// Update
// Aufgabe: Timer updaten
void CTimer::Update() {
	// Vergangene Zeit seit dem letzten Frame berechnen

	do {
		m_fCurrTime = SDL_GetTicks() / 1000.0f;

		m_fElapsed = m_fCurrTime - m_fLastTime;
	} while (m_fElapsed < 0.04f);

	m_fLastTime = m_fCurrTime;
}