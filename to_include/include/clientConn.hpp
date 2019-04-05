#include "connessione.hpp"

#ifndef __CLIENTCONN_HPP
#define __CLIENTCONN_HPP

class ClientConn: public Connessione {
	public:		ClientConn(int);
			~ClientConn();
};

ClientConn::ClientConn(int sock_id) : Connessione(sock_id) {}

ClientConn()::~ClientConn() {}

#endif // __CLIENTCONN_HPP
