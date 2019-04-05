#include "include/serverTCP.hpp"
#include <pthread.h>

#define HOME_PAGE "HTTP/1.1 200 OK\n\
Date: Wed, 19 Apr 2017 16:34:20 GMT\n\
Content-Type: text/html; charset=UTF-8\n\
\n <!DOCTYPE html>\n\
<html class=\"client-nojs\" lang=\"it\" dir=\"ltr\">\n\
<head>\n\
<title>web site</title>\n\
<body>\n\
<h1>Hello world</h1>\n\
</body>\n\
</html>"
ServerTCP* myself;

typedef struct {
	ServerConn* conn;
	ServerTCP* myself;
} Params;

void* request(void* p) {
	static char* home = HOME_PAGE;
	Params* p = (Params*) p;
	ServerConn* conn = (ServerConn*) p->conn;
	ServerTCP* myself = (ServerTCP*) p->myself;

	conn->ricevi();
	conn->invia(home);
	myself->disconnetti(conn);
	pthread_exit(NULL);
}

int main(int argc,char* argv[]) {
	int port = atoi(argv[1]);
	myself = new ServerTCP(port);

	while(true) {
		ServerConn* conn = myself->accetta();
		Params* params = (Params*) malloc(sizeof(Params)),
		params->connection = conn;
		params->myself = myself;

		pthread_t thread_id;
		pthread_create(&thread_id,
				NULL,
				request,
				(void*) params);
	}

	delete(myself);
	return 0;	
}
