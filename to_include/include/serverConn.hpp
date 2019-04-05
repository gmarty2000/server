#include "connessione.hpp"

#ifndef __SERVERCONN_HPP
#define __SERVERCONN_HPP

class ServerConn: public Connessione {
	public:		ServerConn(int);
			~ServerConn();
};

ServerConn::ServerConn(int conn_id) : Connessione(conn_id) {}

ServerConn::~ServerConn(){	
	shutdown(this->id, SHUT_RDWR);
}

#endif // __SERVERCONN_HPP
