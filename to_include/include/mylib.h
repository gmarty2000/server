#include <errno.h>

#ifndef __MYLIB_HPP
#define __MYLIB_HPP

/* PROTOTIPI */
void errore(char* s, int n);

void errore(char* s, int n) {
	printf("Errore su %s\nCode: %d (%s)\nReturn code: %d\n", s, errno, strerror(errno), n);
	exit(n);
}

#endif // __MYLIB_HPP
