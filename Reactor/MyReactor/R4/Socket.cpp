/**
 * Project Reactor
 */


#include "Socket.h"
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Socket implementation
 */


/**
 * @param fd
 */
Socket:: Socket(int fd) 
:_fd(fd)
{

}

Socket::Socket() {
	_fd = socket(AF_INET,SOCK_STREAM,0);
	if(_fd < 0){
		perror("socket");
		return;
	}
}

/**
 * @return int
 */
int Socket::getFd() const{
	return _fd;
}

Socket::~Socket() {
	close(_fd);
}
