/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_w.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dpattij <dpattij@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 17:03:41 by dpattij        #+#    #+#                */
/*   Updated: 2019/12/02 17:06:27 by dpattij       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_W_H
# define MALLOC_W_H

# define MALLOC(x) malloc_wr(x, __LINE__, __FILE__, __func__)
# define FREE(x) free_wr(x)

void	*malloc_wr(
	unsigned long size,
	int line,
	const char *file,
	const char *func
);

void	free_wr(
	void *ptr
);

void	print_pointers(void);
void	set_failure(int x);

extern int g_failat;

#endif
