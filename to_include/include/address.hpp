/* GUARDIAN --> "CANCELLETTI FETIDI" */

#ifndef __ADDRESS_HPP
#define __ADDRESS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define IP_LO "127.0.0.1"
#define IP_DHCP "0.0.0.0"
#define PORT_ZERO 0

#define MTX_KEY 4242

class Address {
	private:	char*	ip;
			int	port;
			static pthread_mutex_t	mtxProcesso;
	public:		Address(char*, int);
			Address();
			Address(const Address&);	/* PASSAGGIO PER RIFERIMENTO */
			Address(struct sockaddr_in);

		char*			getIp();
		int			getPort();
		struct sockaddr_in	getBinary();
		void			setIp(char*);
		void			setPort(int);
		void			setBinary(struct sockaddr_in);

		char*	toString();

		~Address();
};

pthread_mutex_t Address::mtxProcesso = PTHREAD_MUTEX_INITIALIZER;

Address::Address(char* ip, int port) {
	this->ip = strdup(ip);
	this->port = port;
}

Address::Address() {
	this->ip = strdup(IP_LO);
	this->port = PORT_ZERO;
}

Address::Address(const Address& a) {
	this->ip = strdup(a.ip);
	this->port = a.port;
}

Address::Address(struct sockaddr_in a) {
	this->setBinary(a);
}

char* Address::getIp() {
	return this->ip;
}

int Address::getPort() {
	return this->port;
}

struct sockaddr_in Address::getBinary() {
	struct sockaddr_in ret;

	ret.sin_family = AF_INET;
	if (!inet_aton(this->ip, &ret.sin_addr))
		printf("Error during extract IP address");

	ret.sin_port = htons(this->port);
	for (int i=0; i<8; i++)
		ret.sin_zero[i] = 0;

	return ret;
}

void Address::setIp(char* ip) {
	this->ip = strdup(ip);
}

void Address::setPort(int port) {
	this->port = port;
}

void Address::setBinary(struct sockaddr_in a) {
	pthread_mutex_lock(&mtxProcesso);
	this->ip = strdup(inet_ntoa(a.sin_addr));
	pthread_mutex_unlock(&mtxProcesso);

	this->port = ntohs(a.sin_port);
}

char* Address::toString() {
	char buffer[100];
	sprintf(buffer, "%s:%d", this->getIp(), this->getPort());
	return strdup(buffer);
}

Address::~Address() {
	free(this->ip);
	printf("Distruzione Address\n");
}

#endif // __ADDRESS_HPP
