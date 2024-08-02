/**
 * Project Reactor
 */


#include "SocketIO.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

/**
 * SocketIO implementation
 */


/**
 * @param fd
 */
SocketIO::SocketIO(int fd) 
:_fd(fd)
{

}

SocketIO::~SocketIO() {

}

/**
 * @param buf
 * @param len
 * @return int
 */
int SocketIO::readn(char* buf, int len) {
	int left = len;
	char *pstr = buf;
	int ret = 0;
	while(left){
		ret = read(_fd,pstr,left);
		if(-1 == ret && errno == EINTR){
			continue;
		}else if(-1 == ret){
			return -1;
		}else if(0 == ret){
			break;
		}else{
			pstr += ret;
			left -= ret;
		}
	}

    return len - left;
}

/**
 * @param buf
 * @param len
 * @return int
 */
int SocketIO::writen(const char* buf, int len) {
	int left = len;
	const char *pstr = buf;
	int ret = 0;
	while(left){
		ret = write(_fd,pstr,left);
		if(-1 == ret && errno == EINTR){
			continue;
		}else if(-1 == ret){
			return -1;
		}else if(0 == ret){
			break;
		}else{
			pstr += ret;
			left -= ret;
		}
	}
	return len - left;
}

/**
 * @param buf
 * @param len
 * @return int
 */
int SocketIO::readline(char* buf, int len) {
	int left = len-1;
	char *pstr = buf;
	int ret = 0;
	while(left){
		ret = recv(_fd,pstr,left,MSG_PEEK);
		
	}

    return 0;
}

