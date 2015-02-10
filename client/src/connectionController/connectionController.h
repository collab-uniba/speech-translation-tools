#ifndef _CONNECTIONCONTROLLER_H_
#define _CONNECTIONCONTROLLER_H_

#include "..\GlobalVariables.h"


class ConnectionController{
	public:
		static void init_string(struct stringa *s);
		static size_t writefunc(void *ptr, size_t size, size_t nmemb, struct stringa *s);
		static int JSON();
};

#endif