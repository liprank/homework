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
	while(left > 0){
		ret = read(_fd,pstr,left);
		if(-1 == ret && errno == EINTR){
			continue;
		}else if(-1 == ret){
			perror("read");
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
	while(left > 0){
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
	int ret = 0,total = 0;
	while(left > 0){
		ret = recv(_fd,pstr,left,MSG_PEEK);
		if(-1 == ret && errno == EINTR){
			continue;
		}else if(-1 == ret){
			return -1;
		}else if(0 == ret){
			perror("readline");
			break;
		}else{
			for(int i = 0; i < left; ++i){
				if(pstr[i] == '\n'){
					readn(pstr,i+1);
					pstr += i+1;
					*pstr = '\0';
					return total+i+1;
				}
			}

			readn(pstr,left);
			total += ret;
			pstr += ret;
			left -= ret;
		}
	}

	*pstr = '\0';
    return total - left;
}

