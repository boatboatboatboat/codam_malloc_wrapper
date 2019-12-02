/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_w.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/29 17:55:20 by dpattij        #+#    #+#                */
/*   Updated: 2019/11/29 21:25:12 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include <dlfcn.h>
#include <stdio.h>
#include "get_next_line.h"
#include <mach/mach_init.h>
#include <sys/sysctl.h>
#include <mach/mach_vm.h>

typedef struct		s_pointer_holder
{
	void		*ptr;
	int			line;
	const char	*file;
	const char	*func;
	void		*bt_ps[420];
	int			bt_pc;
	size_t		size;
}					t_pointer_holder;

t_pointer_holder	g_pointers[40000];
int					g_pointer_count = 0;
int					g_total_pointers = 0;
int					g_failat = -1;

void	set_failure(int x)
{
	g_failat = x;
}

void	*malloc_wr(
	unsigned long size,
	int line,
	const char *file,
	const char *func
)
{
	void				*ptr;
	t_pointer_holder	ph;

	if (g_failat == g_total_pointers)
		return (NULL);
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	ph.ptr = ptr;
	ph.line = line;
	ph.file = file;
	ph.func = func;
	ph.size = size;
	ph.bt_pc = backtrace(ph.bt_ps, 420);
	g_pointers[g_total_pointers] = ph;
	g_pointer_count += 1;
	g_total_pointers += 1;
	return (ptr);
}

void	free_wr(
	void *ptr
)
{
	int k;

	if (ptr == NULL)
		return ;
	k = 0;
	g_pointer_count -= 1;
	free(ptr);
	while (k <= 40000)
	{
		if (g_pointers[k].ptr == ptr)
		{
			g_pointers[k].ptr = NULL;
			break ;
		}
		k += 1;
	}
}

void	print_pointers(void)
{
	int	 	k;
	int 	i;
	int		W;
	char	**t;

	k = 0;
	i = 0;
	printf("\n\n-----------------------------------\n");
	printf("print_pointers() called\n");
	printf("-----------------------------------\n");
	while (k <= g_total_pointers)
	{
		if (g_pointers[k].ptr != NULL)
		{
			printf("\n%04d | %16p:%-4lu | %42s | %s:%d%n\n",
				k,
				g_pointers[k].ptr,
				g_pointers[k].size,
				g_pointers[k].file,
				g_pointers[k].func,
				g_pointers[k].line,
				&W);
			printf("%.*s\n", W, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
			printf("\tcall stack of size [%d], originating from:\n", g_pointers[k].bt_pc);
			t = backtrace_symbols(g_pointers[k].bt_ps, g_pointers[k].bt_pc);
			i = 1;
			while (i < g_pointers[k].bt_pc)
			{
				printf("\t\t%s\n", t[i]);
				i += 1;
			}
			g_pointers[k].ptr = NULL;
			free(t);
		}
		k += 1;
	}
	printf("%d alive, %d created total\n", g_pointer_count, g_total_pointers);
}
