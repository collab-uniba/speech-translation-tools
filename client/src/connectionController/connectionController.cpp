#include "connectionController.h"


/*
Initialize string structure for HTTP interactions
*/
void ConnectionController::init_string(struct stringa *s) {
	s->len = 0;
	s->ptr = (char*)malloc(s->len + 1);
	if (s->ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->ptr[0] = '\0';
}

/*
Save data from http request into string
*/
size_t ConnectionController::writefunc(void *ptr, size_t size, size_t nmemb, struct stringa *s)
{
	size_t new_len = s->len + size*nmemb;
	s->ptr = (char*)realloc(s->ptr, new_len + 1);
	if (s->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->ptr + s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;
}

/*
This function save into the file the access_key value for the bing
translation transitions
*/
int ConnectionController::JSON()
{
	const char json[2048 * 2] = { "" };
	/*
	Load json string to parse
	*/
	FILE * jfile;
	if (jfile = fopen("..\\conf\\pagina.htm", "r"))
	{
		fscanf(jfile, "%s", &json);
		fflush(jfile);
		fclose(jfile);
	}
	Document document;	// Default template parameter uses UTF8 and MemoryPoolAllocator.

#if 0
	// "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
	if (document.Parse<0>(json).HasParseError())
		return 1;
#else
	// In-situ parsing, decode strings directly in the source string. Source must be string.
	char buffer[sizeof(json)];
	memcpy(buffer, json, sizeof(json));
	if (document.ParseInsitu<0>(buffer).HasParseError())
		return 1;
#endif

	// http://rapidjson.googlecode.com/svn-history/r95/trunk/example/tutorial/tutorial.cpp

	////////////////////////////////////////////////////////////////////////////
	// 2. Access values in document. 

	printf("\nAccess values in document:\n");
	assert(document.IsObject());	// Document is a JSON value represents the root of DOM. Root can be either an object or array.

	assert(document.HasMember("token_type"));
	assert(document["token_type"].IsString());
	printf("hello = %s\n", document["token_type"].GetString());

	assert(document.HasMember("access_token"));
	assert(document["access_token"].IsString());
	printf("hello = %s\n", document["access_token"].GetString());

	assert(document.HasMember("expires_in"));
	assert(document["expires_in"].IsString());
	printf("hello = %s\n", document["expires_in"].GetString());

	assert(document.HasMember("scope"));
	assert(document["scope"].IsString());
	printf("hello = %s\n", document["scope"].GetString());

	/*
	Save into JSON.txt the access_key
	*/
	FILE*js;
	if (js = fopen("..\\conf\\JSON.txt", "w"))
	{
		fprintf(js, "%s", document["access_token"].GetString());
		fclose(js);
	}
	//return document["access_token"].GetString();
	return 0;
}