#include "ft_ping.h"

void	print_icmp_packet(char *packet, int payloadsize)
{
	t_icmp_hdr	*icmp;
	char		*p;
	int			i;

	icmp = (t_icmp_hdr *) packet;
	printf("ICMP Packet:\n");
	printf("Type: %d\n", icmp->type);
	printf("Code: %d\n", icmp->code);
	printf("Checksum: %d\n", ntohs(icmp->checksum));
	printf("ID: %d\n", ntohs(icmp->id));
	printf("Sequence: %d\n", ntohs(icmp->seq_num));
	printf("Payload:\n");

	p = packet + sizeof(icmp);
	i = 0;
	while (i < payloadsize)
	{
		printf("%02x ", p[i]);
		if ((i + 1) % 16 == 0) printf("\n");
		i++;
	}
	printf("\n");
}

void	fill_payload(t_data *a)
{
	char	*p;
	int		i;

	p = a->packet + sizeof(t_icmp_hdr);
	i = 0;
	while (i < a->payloadsize)
	{
		*p = 'a';
		p++;
		i++;
	}
}

void	build_icmp_packet(t_data *a, int seq)
{
	a->packet_hdr.type = 8;
	a->packet_hdr.code = 0;
	a->packet_hdr.checksum = 0;
	a->packet_hdr.id = htons(getpid() & 0xFFFF);
	a->packet_hdr.seq_num = htons(seq);
	
	a->packetsize = sizeof(t_icmp_hdr) + a->payloadsize;
	a->packet = malloc(a->packetsize);
	if (!a->packet)
	{
		printf("malloc fail\n");
		exit(1); //todo clean exit
	}
	memcpy(a->packet, &a->packet_hdr, sizeof(t_icmp_hdr));
	fill_payload(a);
	//print_icmp_packet(a->packet, a->payloadsize);
}
