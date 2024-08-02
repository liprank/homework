/**
 * Project reactor
 */


#include "SocketIO.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/**
 * SocketIO implementation
 */


/**
 * @param fd
 */
SocketIO:: SocketIO(int fd) 
:_fd(fd)
{

}

SocketIO::~SocketIO(){
	close(_fd);
}

/**
 * @param buf
 * @param len
 * @return int
 */
int SocketIO::readn(char * buf, int len) {
	int left = len;
	char *pstr = buf;
	int ret = 0;

	while(left > 0){
		ret = read(_fd,pstr,left);
		if(-1 == ret && errno == EINTR){
			continue;
		}else if(-1 == ret){
			perror("read error -1");
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
int SocketIO::readLine(char * buf, int len) {
	int left = len - 1;
	char *pstr = buf;
	int ret = 0, total = 0;

	while(left > 0){
		ret = recv(_fd,pstr,left,MSG_PEEK);
		if(-1 == ret && errno == EINTR){
			continue;
		}else if(-1 == ret){
			perror("readLine error -1");
			return -1;
		}else if(0 == ret){
			break;
		}else{
			for(int idx = 0;idx < ret; ++idx){
				if(pstr[idx] == '\n'){
					int lline = idx + 1;
					readn(pstr,lline);
					pstr += lline;
					*pstr += '\0';

					return total + lline;
				}
			}

			//如果没有换行符
			readn(pstr,ret);
			total += ret;
			pstr += ret;
			left -= ret;
		}
	}

	*pstr = '\0';
	return total - left;
}

/**
 * @param buf
 * @param len
 * @return int
 */
int SocketIO::writen(const char * buf, int len) {
	int left = len;
	const char *pstr = buf;
	int ret = 0;

	while(left > 0){
		ret = write(_fd,pstr,left);
		if(-1 == ret && errno == EINTR){
			continue;
		}else if(-1 == ret){
			perror("write error -1");
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

