#include "ft_ping.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		printf("ft_ping: usage error: Destination address required\n");
		return (1);
	}
}
