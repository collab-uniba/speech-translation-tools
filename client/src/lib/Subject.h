#include <functional>
#include <map>
#include <vector>
#include <utility> // for std::forward



template <typename Event, typename Observer>
class Subject
{
private:
	typedef std::function<void(Observer * ob)> fnobserver;
	struct observers{
		fnobserver fn; 
		Observer * ob;
	};

	std::map<Event, std::vector<observers>> observers_;

public:
	
	Subject() = default;
 
	void registerObserver(const Event& event, fnobserver fn, Observer * ob)
	{
		observers absr = { fn, ob };

		observers_[event].push_back({ fn, ob });
		//observers_[event].push_back(std::forward<Observer>(observer));
	}
 
	void notify(const Event& event) const
	{
		for (const auto& obs : observers_.at(event)){
			obs.fn(obs.ob);
		}
	}
	// disallow copying and assigning
	Subject(const Subject&) = delete;
	Subject& operator=(const Subject&) = delete;

};


/*
template <typename Event>
class Subject
{
public:
	Subject() = default;
	template <typename Observer>
	void registerObserver(const Event& event, Observer&& observer)
	{
		observers_[event].push_back(std::forward<Observer>(observer));
	}
	template <typename Observer>
	void registerObserver(Event&& event, Observer&& observer)
	{
		observers_[std::move(event)].push_back(std::forward<Observer>(observer));
	}
	void notify(const Event& event) const
	{
		for (const auto& obs : observers_.at(event)) obs();
	}
	// disallow copying and assigning
	Subject(const Subject&) = delete;
	Subject& operator=(const Subject&) = delete;
private:
	std::map<Event, std::vector<std::function<void()>>> observers_;
};*/