#include "include/serverTCP.hpp"

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

int main(int argc,char* argv[]){
	int port=atoi(argv[1]);
	char* home=HOME_PAGE;
	ServerTCP* myself =new ServerTCP(port);
	while(true){
		ServerConn* conn=myself->accetta();
		conn->invia(home);
		myself->disconnetti(conn);
	}
	delete(myself);
	return 0;	
}
