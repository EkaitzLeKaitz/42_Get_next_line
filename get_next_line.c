/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:19:22 by sagonzal          #+#    #+#             */
/*   Updated: 2024/11/19 12:51:14 by sagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void	append(t_list **list, char *buff)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	//Si la lista esta vacia salimos.
	if(NULL == new_node)
		return ;
	//Si *list == NULL creamos la lista o de existir añadimos el nuevo nodo al final.
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;

	//Guardamos en el nuevo nodo el contenido del buf y apuntamos a NULL.
	new_node->str_buff = buff;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int	char_read;
	char	*buff;

	//Comprueba si '/n' esta presente.
	while (!found_newln(*list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (NULL == buff)
			return ;

		char_read = read(fd, buff, BUFFER_SIZE);
		//Finaliza la función si no hay mas caracteres leidos.
		if (!char_read)
		{
			free(buff);
			return ;
		}
		//Añado '\0' al final de la cadena.
		buff[char_read] = '\0';
		//Anexar al ultimo nodo.
		append(list, buff);
	}
}

char	*get_line(t_list *list)
{
	int	str_len;
	char	*next_str;

	// if (NULL == next_str)
	// 	return (NULL);

	//Cuenta cuantos char hay hasta '/n' para poder reservar memoria.
	str_len = len_to_newln(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);

	//Copia la cadena en el buff y la devuelve.
	copy_str(list, next_str);
	return (next_str);
}

void	final_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int	i;
	int	l;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buff || NULL == clean_node)
		return ;
	last_node = find_last_node(*list);

	i = 0;
	l = 0;
	while (last_node->str_buff[i] != '\0' && last_node->str_buff[i] != '\n')
		++i;
	while (last_node->str_buff[i] != '\0' && last_node->str_buff[++i])
		buff[l++] = last_node->str_buff[i];
	buff[l] = '\0';
	clean_node->str_buff = buff;
	clean_node->next = NULL;
	dealloc(list, clean_node, buff);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char		*next_ln;
	
	//Los fd solo son positivos, read devuelve -1 si hay algun problema de lectura.
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	//Creo la lista hasta que encuentro '/n'(salto de linea).
	create_list(&list, fd);

	if (list == NULL)
		return(NULL);

	//Obtengo la linea de la lista.
	next_ln = get_line(list);

	//
	final_list(&list);
	return (next_ln);
}

int main()
{
	int	fd;
	char	*line;
	int	lines;

	lines = 1;
	fd = open("test.txt", O_RDONLY);

	while ((line = get_next_line(fd)))
	{
		printf("%d->%s", lines++, line);
		free(line);
	}
}
