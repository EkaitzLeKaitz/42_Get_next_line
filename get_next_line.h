/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:20:15 by sagonzal          #+#    #+#             */
/*   Updated: 2024/06/19 11:20:18 by sagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_list
{
	char		*str_buff;
	struct s_list	*next;
}			t_list;

int	found_nl(t_list *list);
char	*get_next_line(int fd);

#endif
