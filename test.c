#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	fd = open("get_next_line.c", 0);
	char *str;
	int	res = 1;
	int	lc = 1;
	int	failer;

	sscanf(argv[1], "%d", &failer);
	str = NULL;
	set_failure(failer);
	while (res > 0)
	{
		res = get_next_line(fd, &str);
		printf("%4d | %+d | %s$\n", lc, res, str);
		YEET_free_YEET(str);
		str = NULL;
		lc += 1;
	}
	print_pointers();
	return (0);
}
