#include "ft_ping.h"

int	open_socket(t_data *a)
{
	a->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (a->sockfd < 0)
	{
		perror("socket");
		return (1);
	}
	return (0);
}

int	send_requests(t_data *a)
{
	printf("yoe\n");
	int		seq;

	seq = 1;
	while (1)
	{
		build_icmp_packet(a, seq);
		sendto(a->sockfd, a->packet, a->packetsize, 0, a->res->ai_addr, a->res->ai_addrlen);
		printf("sendto\n");
		a->sender_addrlen = sizeof(a->sender);
		//recvfrom(a->sockfd, a->buf, sizeof(a->buf), 0, &a->sender, &a->sender_addrlen);
		printf("recvfrom\n");
		sleep(1);
		seq++;
	}
}

int	send_ping(t_data *a)
{
	int	status;

	status = handle_getaddrinfo(a);
	if (status != 0)
		return (1);
	status = open_socket(a);
	if (status != 0)
		return (1);
	status = send_requests(a);
	if (status != 0)
		return (1);
	return (send_requests(a));
}

int	main(int argc, char **argv)
{
	t_data	a;
	bzero(&a, sizeof(a));
	if (parse_arguments(&a, argc, argv))
		return (1);
	
	return (send_ping(&a));
}
