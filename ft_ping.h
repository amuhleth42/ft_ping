#ifndef FT_PING_H
# define FT_PING_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <arpa/inet.h>
# include <errno.h>

typedef struct s_icmp_hdr
{
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
	uint16_t	id;
	uint16_t	seq_num;
}				t_icmp_hdr;

typedef struct s_ping
{
	uint16_t		seq;
	struct timeval	send_time;
	struct timeval	recv_time;
	double			rtt;
	int				received;
	int				ttl;
	size_t			bytes;
}					t_ping;

typedef struct s_data	
{
	int 			verbose;
	int				payloadsize;
	size_t			packetsize;
	char			*hostname;
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				sockfd;
	t_icmp_hdr		packet_hdr;
	char			*packet;
	char			buf[1500];
	struct sockaddr	sender;
	socklen_t		sender_addrlen;
	t_ping			pings[2048];
}					t_data;

int		parse_arguments(t_data *a, int argc, char **argv);

int		handle_getaddrinfo(t_data *a);

void	build_icmp_packet(t_data *a, int seq);



#endif
