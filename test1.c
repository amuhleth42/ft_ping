#include "ft_ping.h"

void	usage(char **argv)
{
	fprintf(stderr, "%s: usage error: Destination address required\n", argv[0]);
}

int	parse_arguments(t_data *a, int argc, char **argv)
{
	int option;
	
	while ((option = getopt(argc, argv, "v")) != -1)
	{
		switch (option)
		{
			case 'v':
				a->verbose = 1;
				break;
			default:
				return (1);
				
		}
	}
	if (optind >= argc)
	{
		fprintf(stderr, "%s: usage error: Destination address required\n", argv[0]);
		return (1);
	}
	a->hostname = argv[optind];
	printf("a->hostname: %s\n", a->hostname);
	return (0);
}

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

int	send_ping(t_data *a)
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

int	main(int argc, char **argv)
{
	t_data	a;
	bzero(&a, sizeof(a));
	if (parse_arguments(&a, argc, argv))
		return (1);
	
	return (send_ping(&a));
}
