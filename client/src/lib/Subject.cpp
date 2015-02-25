#include "Subject.h"

std::map<EventSub, std::vector<std::function<void()>>> observers_;