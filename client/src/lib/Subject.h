//
// Copyright (c) 2013 Juan Palacios juan.palacios.puyana@gmail.com
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//
#pragma once

#include <functional>
#include <map>
#include <vector>
#include <utility> // for std::forward
template <typename Event>
class Subject
{
public:
	Subject() = default;
	template <typename Observer>
	static void registerObserver(const Event& event, Observer&& observer)
	{
		observers_[event].push_back(std::forward<Observer>(observer));
	}
	template <typename Observer>
	static void registerObserver(Event&& event, Observer&& observer)
	{
		observers_[std::move(event)].push_back(std::forward<Observer>(observer));
	}
	static void notify(const Event& event) 
	{
		for (const auto& obs : observers_.at(event)) obs();
	}
	// disallow copying and assigning
	Subject(const Subject&) = delete;
	Subject& operator=(const Subject&) = delete;
private:
	static std::map<Event, std::vector<std::function<void()>>> observers_;
};
