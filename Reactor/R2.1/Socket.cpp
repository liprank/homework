/**
 * Project reactor
 */


#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Socket implementation
 */


Socket::Socket() {
	_fd = ::socket(AF_INET,SOCK_STREAM,0);
	if(_fd < 0){
		perror("socket");
		return;
	}
}

/**
 * @param fd
 */
Socket:: Socket(int fd)
:_fd(fd)
{
	
}

Socket::~Socket() {
	close(_fd);
}

/**
 * @return int
 */
int Socket::fd() const{
    return _fd;
}


void Socket::shutDownWrite(){
	int ret = shutdown(_fd,SHUT_WR);
	if(ret){
		perror("shutdown");
		return;
	}
}

