#include "address.hpp"
#include "mylib.h"
#include <unistd.h>

#define MAX_MESSAGE 4096

#ifndef __SOCKETTCP_HPP
#define __SOCKETTCP_HPP

class SocketTCP {
	protected:	int sock_id;
	public:		SocketTCP();
			void setBroadcast(bool);
			~SocketTCP();
};

SocketTCP::SocketTCP() {
	this->sock_id = socket(AF_INET, SOCK_STREAM, 0);
}

/*void SocketTCP::setBroadcast(bool attivo) {
	int optval;
	int ret;

	if (attivo) {
		ret = setsockopt(	this->sock_id,
					SOL_SOCKET,
					SO_BROADCAST,
					&optval,
					sizeof(optval));

		if (ret)
			errore("setsockopt()", -1);
	}
}*/

SocketTCP::~SocketTCP() {
	close(this->sock_id);
}

#endif // __SOCKETTCP_HPP
