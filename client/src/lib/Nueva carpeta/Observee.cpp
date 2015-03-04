#include "Observee.h"

//---------------------------
// Forward Declarations
//---------------------------

class Notifier
{
public:
	Notifier(Observee* observee) : m_pObservee(observee)
	{}

	void operator()(Observer* observer)
	{
		observer->Notify(m_pObservee);
	}

private:
	Observee* m_pObservee;
};
//---------------------------
// Constructor & Destructor
//---------------------------
Observee::Observee()
{
	// nothing to create
}

Observee::~Observee()
{
	// nothing to destroy
}

bool Observee::AddObserver(Observer* observer)
{
	vector<Observer*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
	if (temp != m_ObserverVec.end())
		return false;

	m_ObserverVec.push_back(observer);
	return true;
}

bool Observee::RemoveObserver(Observer* observer)
{
	vector<Observer*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
	if (temp == m_ObserverVec.end())
		return false;
	else
		m_ObserverVec.erase(remove(m_ObserverVec.begin(), m_ObserverVec.end(), observer));
	return true;


}

bool Observee::NotifyObservers()
{
	for_each(m_ObserverVec.begin(), m_ObserverVec.end(), Notifier(this));

	return (m_ObserverVec.size() > 0);
}


