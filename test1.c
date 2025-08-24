#include "ft_ping.h"

void	usage(char **argv)
{
	fprintf(stderr, "%s: usage error: Destination address required\n", argv[0]);
}

//int	parse_arguments(int argc, char **argv)
//{
//}


int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		usage(argv);
		return (1);
	}
}
