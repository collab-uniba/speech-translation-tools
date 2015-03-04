#pragma once

#include <vector>
#include <algorithm>
#include "Observer.h"

class Observer;
//-----------------------------------------------------
// Observee Class									
//-----------------------------------------------------
class Observee
{
public:
	virtual ~Observee();		//destructor
	bool AddObserver(Observer* observer);
	bool RemoveObserver(Observer* observer);
	bool NotifyObservers();
protected:
	//constructor is protected
	Observee();
private:
	vector<Observer*> m_ObserverVec;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Observee(const Observee& yRef);
	Observee& operator=(const Observee& yRef);
};


