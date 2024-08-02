/**
 * Project reactor
 */


#ifndef _SOCKET_H
#define _SOCKET_H

class Socket {
public: 
    int _fd;
    
Socket();
    
/**
 * @param fd
 */
explicit Socket(int fd);
    
~Socket();
    
int fd() const;

void shutDownWrite();
};

#endif //_SOCKET_H
