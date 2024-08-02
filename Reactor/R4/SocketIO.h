/**
 * Project reactor
 */


#ifndef _SOCKETIO_H
#define _SOCKETIO_H

class SocketIO {
public: 
/**
 * @param fd
 */
explicit SocketIO(int fd);
  
~SocketIO();

/**
 * @param buf
 * @param len
 */
int readn(char * buf, int len);
    
/**
 * @param buf
 * @param len
 */
int readLine(char * buf, int len);
    
/**
 * @param buf
 * @param len
 */
int writen(const char * buf, int len);
private:
	int _fd;
};

#endif //_SOCKETIO_H
