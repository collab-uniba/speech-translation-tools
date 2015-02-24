#pragma once

// https://github.com/juanchopanza/cppblog/blob/master/Patterns/Observer/Subject.h

#include <map>
#include <vector>
#include <list> 
#include <utility> // for std::forward
//#include <function>
#include "Event.h"

class Observer;
class Subject
{
public:
	Subject() = default; 
	void registerObserver(const EventTS& event, Observer&& observer)
	{
		observers_[event].push_back(observer);
	}
	void registerObserver(EventTS&& event, Observer&& observer)
	{
		observers_[std::move(event)].push_back(observer);
	}
	/*void Detach(const EventTS& event, Observer&& t_obs)
	{
		observers_[event].erase(t_obs);
	}*/
	template <typename T>
	void Notify(const EventTS& event, T *value)
	{
		for (const auto& obs : observers_.at(event))
			obs->Update(value);
	}

	Subject(const Subject&) = delete;
	Subject& operator=(const Subject&) = delete;
private:
	std::map<EventTS, std::vector<Observer>> observers_;
};



/*#include <functional>
#include <map>
#include <vector>
#include <utility> // for std::forward


enum class EventType { NOTIFY_USERS, NOTIFY_MSG };

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