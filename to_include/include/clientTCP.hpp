#include "socketTCP.hpp"
#include "clientConn.hpp"

#define MAX_MESSAGE 4096

#ifndef __CLIENTTCP_HPP
#define __CLIENTTCP_HPP

class ClientTCP: public SocketTCP {
	private:	ClientConn* connection;
	public:		/* (FORSE) BUG --> ClientTCP(); */
			int connetti(Address);
			bool invia(char*);
			bool inviaRaw(char*, int);
			char* ricevi();
			void* riceviRaw(int);
			ClientConn* getConnection();
			~ClientTCP();
};

ClientTCP::ClientTCP() {}

bool ClientTCP::connetti(Address address) {
	int ret = 0;

	sockaddr_in myself = address.getBinary();

	ret = connect(	this->sock_id,
			(const struct sockaddr*) &myself,
			sizeof(struct sockaddr_in));

	this->connection = new ClientConn(this->sock_id);

	return (ret != -1);
}

bool ClientTCP::invia(char* msg) {
	return connection->invia(msg);
}

bool ClientTCP::inviaRaw(char* msg, int length) {
	return connection->inviaRaw(msg, length);
}

char* ClientTCP::ricevi() {
	return connection->ricevi();
}

void* ClientTCP::riceviRaw(int length) {
	return connection->riceviRaw(length);
}

ClientConn* ClientTCP::getConnection() {
	return this->connection;
}

ClientTCP()::~ClientTCP() {}

#endif // __CLIENTTCP_HPP
