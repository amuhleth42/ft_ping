#include "ft_ping.h"

void	print_addrinfo(struct addrinfo *res)
{
	while (res)
	{
		printf("ai_flags: %d\n", res->ai_flags);
		printf("ai_family: %d\n", res->ai_family);
		printf("ai_socktype: %d\n", res->ai_socktype);
		printf("ai_protocol: %d\n", res->ai_protocol);
		printf("ai_addrlen: %d\n", (int)res->ai_addrlen);
		printf("ai_canonname: %s\n\n", res->ai_canonname);
		res = res->ai_next;
	}
}

int	handle_getaddrinfo(t_data *a)
{
	int status;

	a->hints.ai_family = AF_INET;
	a->hints.ai_socktype= SOCK_RAW;
	a->hints.ai_protocol= IPPROTO_ICMP;
	status = getaddrinfo(a->hostname, NULL, &a->hints, &a->res);
	if (status != 0)
	{
		fprintf(stderr, "ft_ping: %s\n", gai_strerror(status));
		return (1);
	}

	print_addrinfo(a->res);

	return (0);
}
