#include <sys/types.h>
#include <sys/socket.h>

// SOCKETS

int	socket(int domain, int type, int protocol);
// Domain : AF_INET -> IPv4, AF_INET6 -> IPv6
// Type : SOCK_RAW (man 7 icmp)
// Protocol : IPPROTO_ICMP (man 7 icmp)

getsockopt()
setsockopt()

close()

// Network address translation
getaddrinfo()

inet_pton()
inet_ntop()
htons()
htonl()
ntohs()
ntohl()

// Send and Receive

sendto()
recvfrom()

// memory management

memset()
memcpy()
