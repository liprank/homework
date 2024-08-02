/**
 * Project reactor
 */


#ifndef _SOCKET_H
#define _SOCKET_H

#include "NonCopyable.h"

class Socket 
:NonCopyable
{
public: 
Socket();
    
/**
 * @param fd
 */
explicit Socket(int fd);
    
~Socket();
    
int fd() const;

void shutDownWrite();

private:
	int _fd;
};

#endif //_SOCKET_H
