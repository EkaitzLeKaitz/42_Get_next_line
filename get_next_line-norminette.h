/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:20:15 by sagonzal          #+#    #+#             */
/*   Updated: 2024/11/20 11:10:10 by sagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str_buff;
	struct s_list	*next;
}					t_list;

int		found_newln(t_list *list);
char	*get_next_line(int fd);
void	create_list(t_list **list, int fd);
t_list	*find_last_node(t_list *list);
void	append(t_list **list, char *buff);
char	*get_line(t_list *list);
void	dealloc(t_list **list, t_list *clean_node, char *buff);
void	copy_str(t_list *list, char *str);
int		len_to_newln(t_list *list);
void	final_list(t_list **list);

#endif
