#ifndef FT_PING_H
# define FT_PING_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <arpa/inet.h>

typedef struct s_data	
{
	int 	verbose;
	char	*hostname;
}			t_data;


#endif
