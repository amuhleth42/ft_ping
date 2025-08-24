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


int	main(int argc, char **argv)
{
	t_data	a;
	bzero(&a, sizeof(a));
	if (parse_arguments(&a, argc, argv))
		return (1);

	return (0);
}
