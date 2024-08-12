/**
 * Project Reactor
 */


#ifndef _SOCKET_H
#define _SOCKET_H

class Socket {
public: 
    int _fd;
    
/**
 * @param fd
 */
explicit Socket(int fd);

~Socket();
    
Socket();
    
int getFd() const;
    
};

#endif //_SOCKET_H
