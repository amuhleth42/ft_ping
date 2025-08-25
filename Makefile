NAME	= ft_ping


CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCS	=	test1.c					\
			parse_arguments.c		\
			handle_addrinfo.c		\
			icmp_packet.c			\


OBJS	= $(SRCS:.c=.o)


all :	$(NAME)

$(NAME) :	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:	%.s
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -Rf $(OBJS)

fclean :	clean
	rm -Rf $(NAME)

re :	fclean all
