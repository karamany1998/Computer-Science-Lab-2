#pragma once

#include "vertagt_aktion.h"
#include <list>


namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default; //= ...; // Benötigt man einen Standardkonstruktor?
		
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			//...
			~VListe();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			//...
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			//...
			return p_objekte.end();
		}
		bool empty() const
		{
			//...
			if (p_objekte.size() == 0)return true;
			return false;
		}

		// Schreibfunktionen
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			//...
			//VPushBack(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj))	{}

			//unique_ptr<T> ptr = make_unique<T>(obj);

			unique_ptr<VPushBack<T>> ptr1 = make_unique<VPushBack<T>>(p_objekte, move(obj));
			p_aktionen.push_back(std::move(ptr1));
		}

		void push_front(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			//...
			//unique_ptr<T> ptr = make_unique<T>(obj);
			unique_ptr<VPushFront<T>> ptr1 = make_unique<VPushFront<T>>(p_objekte, move(obj));
			p_aktionen.push_back(std::move(ptr1));

		}

		void erase(iterator it)
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			//...
			unique_ptr<VErase<T>> ptr1 = make_unique<VErase<T>>(p_objekte, it);
			p_aktionen.push_back(std::move(ptr1));

		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			// Änderungen auf Objektliste übertragen
			for (auto& pAktion : p_aktionen)
			{
				// Aktion ausführen
				//...
				pAktion->vAusfuehren();
			}
			p_aktionen.clear();
			// Aktionsliste löschen
			//...
		}

	};
	
} // namespace vertagt
