#ifndef TSINGLETON
#define TSINGLETON

template <class T>
class TSingleton
{
	// Membervariablen
	protected:
		static T *m_pSingleton;		// Statisches Objekt

	// Membervariablen
	public:
		// Destruktor
		virtual ~TSingleton() {}

		// Get
		// Aufgabe: Wenn nötig, statisches Objekt erzeugen und
		// Zeiger darauf zurückgeben
		inline static T* Get() {
			//Existiert schon eine Instanz?
			if (!m_pSingleton)
				m_pSingleton = new T;	// Nein, dann neue Instanz

			// Zeiger auf die Instanz zurückgeben
			return (m_pSingleton);
		}

		// Statisches Objekt freigeben
		static void Del() {
			delete (m_pSingleton);		// Ja, dann freigeben
			m_pSingleton = NULL;		// und Zeiger auf NULL setzen
		}
};

// Die statische Variable erzeugen
template <class T>
T* TSingleton<T>::m_pSingleton = 0;

#endif
