#pragma once

class Message;
class User;
class Observer
{
public:
	//template <typename T>
	virtual void Update(Message & value) = 0;
};
