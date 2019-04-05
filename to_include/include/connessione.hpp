#include "address.hpp"

#ifndef __CONNESSIONE_HPP
#define __CONNESSIONE_HPP

class Connessione {
	protected:	int id;
	public:		Connessione(int);
			bool invia(char*);
			bool inviaRaw(void*, int);
			char* ricevi();
			void* riceviRaw(int*);
			~Connessione();
};

Connessione::Connessione(int id) {
	this->id = id;
}

bool Connessione::invia(char* msg) {
	return inviaRaw((void*) msg, strlen(msg) + 1);
}

bool Connessione::inviaRaw(void* msg, int length) {
	int ret = send(this->id, msg, length, 0);
	return ret != -1;
}

char* Connessione::ricevi() {
	int length;
	char* ret = (char*) riceviRaw(&length);

	ret[length] = '\0';
	return ret;
}

void* Connessione::riceviRaw(int* length) {
	void* buffer;
	*length = recv(this->id, buffer, MAX_MESSAGE, 0);
	return buffer;
}

Connessione::~Connessione() {}

#endif // __CONNESSIONE_HPP
