#include "ft_ping.h"

void	print_icmp_packet(unsigned char *packet, int payloadsize)
{
	t_icmp_hdr	*icmp;
	uint8_t		*p;
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
	uint8_t	*p;
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

uint16_t	get_checksum(uint8_t *buf, size_t size)
{
	uint16_t	checksum;
	uint32_t	sum;
	uint16_t	word;
	size_t		i;

	sum = 0;
	i = 0;
	while (i < size)
	{
		word = (buf[i] << 8);
		if (i + 1 < size)
			word = word | buf[i + 1];
		sum += word;
		i += 2;
	}
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	checksum = ~sum;
	return (checksum);
}

bool	checksum_is_valid(uint8_t *buf, size_t len)
{
    uint16_t result = get_checksum(buf, len);
	printf("Result: %d\n", result);
    return (result == 0);
}

void	print_checksum_is_valid(uint8_t *buf, size_t len)
{
	if (checksum_is_valid(buf, len))
		printf("Checksum is valid\n");
	else
		printf("Checksum is NOT valid\n");
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
	uint8_t *p = a->packet;
	*(uint16_t*)(p+2) = htons(get_checksum(a->packet, a->packetsize));
	//print_checksum_is_valid(a->packet, a->packetsize);
	//print_icmp_packet(a->packet, a->payloadsize);
}

void	analyze_response(t_data *a)
{
	struct iphdr	*ip;
	t_icmp_hdr		*icmp;
	size_t			iphdr_len;

	ip = (struct iphdr *) a->buf;
	iphdr_len = ip->ihl * 4;
	icmp = (t_icmp_hdr*)(a->buf + iphdr_len);
	printf("ICMP Response:\n");
	printf("Type: %d\n", icmp->type);
	printf("Code: %d\n", icmp->code);
	printf("Checksum: %d\n", ntohs(icmp->checksum));
	printf("ID: %d\n", ntohs(icmp->id));
	printf("Sequence: %d\n", ntohs(icmp->seq_num));
	//printf("Payload:\n");
}
