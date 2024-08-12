/**
 * Project Reactor
 */


#ifndef _SOCKETIO_H
#define _SOCKETIO_H

class SocketIO {
public: 
    int _fd;
    
/**
 * @param fd
 */
explicit SocketIO(int fd);
    
~SocketIO();
/**
 * @param buf
 * @param len
 */
int readn(char* buf, int len);
    
/**
 * @param buf
 * @param len
 */
int writen(const char* buf, int len);
    
/**
 * @param buf
 * @param len
 */
int readline(char* buf, int len);
};

#endif //_SOCKETIO_H
