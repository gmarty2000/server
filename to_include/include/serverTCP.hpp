#include <list>
#include <iterator>

#include "socketTCP.hpp"
#include "serverConn.hpp"

#define MAX_MESSAGE 4096
#define MAX_CLIENT 50

#ifndef __SERVERTCP_HPP
#define __SERVERTCP_HPP

using namespace std;

class ServerTCP: public SocketTCP {
	private:	list <ServerConn*> connessioni;
	public:		ServerTCP(int);
			ServerConn* accetta();
			void disconnetti(ServerConn*);
			bool inviaATutti(char*);
			bool inviaATuttiRaw(char*, int);
			~ServerTCP();
	private:	void chiudiConnessioni();
};

ServerTCP::ServerTCP(int port = PORT_ZERO) {

	Address address (strdup(IP_LO), port);
	struct sockaddr_in socketAddr = address.getBinary();

	bind(this->sock_id, (struct sockaddr*) &socketAddr, sizeof(struct sockaddr_in));

	listen(this->sock_id, MAX_CLIENT);
}

ServerConn* ServerTCP::accetta() {
	ServerConn* ret;

	sockaddr_in myself;
	int myself_len = sizeof(sockaddr_in);
	int conn_id;

	conn_id = accept(	this->sock_id,
				(struct sockaddr*) &myself,
				(socklen_t*) &myself_len);

	ret = new ServerConn(conn_id);
	this->connessioni.push_front(ret);

	return ret;
}

void ServerTCP::disconnetti(ServerConn* conn) {
	delete conn;
	this->connessioni.remove(conn);
}

bool ServerTCP::inviaATutti(char* msg) {
	return inviaATuttiRaw(msg, strlen(msg));
}

bool ServerTCP::inviaATuttiRaw(char* msg, int length) {
	bool ret = true;

	for (list<ServerConn*>::iterator it = this->connessioni.begin(); it != this->connessioni.end(); it++) {
		ServerConn* myself = *it;
		ret &= myself->invia(msg);
	}

	return ret;
}

void ServerTCP::chiudiConnessioni() {
	while (!this->connessioni.empty())
		disconnetti(this->connessioni.front());
}

ServerTCP::~ServerTCP() {
	chiudiConnessioni();
}

#endif // __SERVERTCP_HPP
