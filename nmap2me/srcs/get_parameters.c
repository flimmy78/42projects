
#include "all.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static bool		isvalidportparameter(char *port)
{
	while (*port) {
		if (!ft_isdigit(*port) && *port != '-' && *port != ',')
			return false;
		port++;
	}
	return true;
}

static bool 	isregisteredportnumber(int port)
{
	for (int i = 0; i < globals.ports_nb; i++) {
		if (globals.ports[i] == port)
			return true;
	}
	return false;
}

void			get_ports_parameters()
{
	if (globals.flags[NM_PORTS]) {
		char 	*ports 	= globals.flags[NM_PORTS];
		if (!isvalidportparameter(ports))
			nmap_error("%s: Invalid ports parameters: `%s'", globals.progname, ports);
		while (*ports) {
			int left = ft_atoi(ports);
			if (left <= 0 || left >= MAX_PORT_NUMBER)
				nmap_error("%s: Invalid ports parameter: `%d'", globals.progname, left);
			while (ft_isdigit(*ports))
				ports++;
			if (*ports == '-') {
				int right = ft_atoi(++ports);
				if (right <= 0 || right > MAX_PORT_NUMBER)
					nmap_error("%s: Invalid ports parameter: `%d'", globals.progname, right);
				if (left > right) {
					int swap = left;
					left = right;
					right = swap;
				}
				if (globals.ports_nb + (right - left) >= MAX_PORTS_SCAN)
					nmap_error("%s: Invalid ports count: %d (max: %d)", globals.progname,
						globals.ports_nb + right - left,
						MAX_PORTS_SCAN);
				for (;left <= right; left++) {
					if (!isregisteredportnumber(left))
						globals.ports[globals.ports_nb++] = left;
				}
				while (ft_isdigit(*ports))
					ports++;
			} else {
				if (globals.ports_nb + 1 >= MAX_PORTS_SCAN)
					nmap_error("%s: Invalid ports count: %d (max: %d)", globals.progname,
						globals.ports_nb + 1,
						MAX_PORTS_SCAN);
				if (!isregisteredportnumber(left))
					globals.ports[globals.ports_nb++] = left;
			}
			if (*ports)
				ports++;
		}
	} else {
		for (globals.ports_nb = 0; globals.ports_nb < MAX_PORTS_SCAN; globals.ports_nb++) {
			globals.ports[globals.ports_nb] = globals.ports_nb + 1;
		}
	}
}

static t_addr 	*new_t_addr(char *name)
{
	t_addr 		*addr = NULL;

	if (name == NULL)
		return NULL;
	addr = malloc(sizeof(*addr));
	if (addr == NULL)
		return NULL;
	addr->name = name;
	ft_bzero(addr->hostaddr, 255);
	ft_bzero(addr->buff, PACKET_SIZE);
	addr->error = NULL;
	addr->next = NULL;
	return addr;
}


void 			get_ip_parameters()
{
	globals.addresses_nb = 0;
	globals.addresses = NULL;
	if (globals.flags[NM_IP]) {
		globals.addresses_nb = 1;
		globals.addresses = new_t_addr(ft_strdup(globals.flags[NM_IP]));
		if (globals.addresses == NULL)
			nmap_error("%s: malloc failed.", globals.progname);
	}
	if (globals.flags[NM_FILE]) {

		int 	fd = open(globals.flags[NM_FILE], O_RDONLY);
		if (fd < 0)
			nmap_error("%s: Can't open file: \"%s\"", globals.progname, globals.flags[NM_FILE]);

		t_addr	*tmp = globals.addresses;
		char 	*line = NULL;
		int 	ret;
		while ((ret = get_next_line(fd, &line)) > 0) {
			if (line == NULL)
				nmap_error("%s: A problem occured while getting \"%s\" lines.", globals.progname, globals.flags[NM_FILE]);
			if (*line) {
				globals.addresses_nb++;
				if (tmp == NULL) {
					globals.addresses = new_t_addr(line);
					tmp = globals.addresses;
				} else {
					tmp->next = new_t_addr(line);
					tmp = tmp->next;
				}
				if (tmp == NULL)
					nmap_error("%s: malloc failed.", globals.progname);
			} else {
				free(line);
			}
			line = NULL;
		}
		close(fd);
		if (ret < 0)
			nmap_error("%s: A problem occured while getting \"%s\" lines.", globals.progname, globals.flags[NM_FILE]);
	}
}

void 			get_threads_parameters()
{
	if (!globals.flags[NM_SPEEDUP])
		globals.threads_nb = 1;
	else
		globals.threads_nb = ft_atoi(globals.flags[NM_SPEEDUP]);
	if (globals.threads_nb <= 0 || globals.threads_nb > MAX_THREADS_NUMBER)
		nmap_error("%s: Wrong parameter: %s (%d max).", globals.progname,
			globals.flags[NM_SPEEDUP], MAX_THREADS_NUMBER);
}

void 			get_scans_parameters()
{
	if (!globals.flags[NM_SCANS]) {
		globals.scans_nb = 6;
		globals.scans_types = NM_SYN | NM_NULL | NM_FIN | NM_XMAS | NM_ACK | NM_UDP;
		globals.scans = ft_strsplit("SYN/NULL/FIN/XMAS/ACK/UDP", '/');
		if (globals.scans == NULL)
			nmap_error("%s: unable to parse: `%s'", globals.progname, "SYN/NULL/FIN/XMAS/ACK/UDP");
	} else {
		char 	*scan[] = { "SYN",  "NULL",  "FIN",  "XMAS",  "ACK",  "UDP",  NULL };
		int 	type[]  = { NM_SYN, NM_NULL, NM_FIN, NM_XMAS, NM_ACK, NM_UDP };

		globals.scans_nb = 0;
		globals.scans_types = 0x0000;
		globals.scans = ft_strsplit(globals.flags[NM_SCANS], '/');
		if (globals.scans == NULL)
			nmap_error("%s: unable to parse: `%s'", globals.progname, globals.flags[NM_SCANS]);
		for (int i = 0, j = 0; globals.scans[i]; i++) {
			for (j = 0; scan[j]; j++) {
				if (!ft_strcmp(globals.scans[i], scan[j])) {
					if (!(globals.scans_types & type[j])) {
						globals.scans_types |= type[j];
						globals.scans_nb++;
					}
					break ;
				}
			}
			if (!scan[j])
				nmap_error("%s: Unrecognized scan type: `%s'", globals.progname, globals.scans[i]);
		}
	}
}
