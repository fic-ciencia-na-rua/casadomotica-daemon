#include "util_daemon.h"

char * subString(const char* str, size_t begin, size_t len){
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len))
	return 0;

    return strndup(str + begin, len);
}
