/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:20:01 by sagonzal          #+#    #+#             */
/*   Updated: 2024/06/19 11:20:04 by sagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	len_to_newln(t_list *list)
{
	int	i;
	int	len;

	if (NULL == list)
		return (0);
	len = 0;
	//Si list no es null.
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	l;

	if (NULL == list)
		return ;
	l = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				str[l++] = '\n';
				str[l] = '\0';
				return ;
			}
			str[l++] = list->str_buff[i++];
		}
		list = list->next;
	}
	str[l] = '\0';
	
}

void	dealloc(t_list **list, t_list *clean_node, char *buff)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buff);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->str_buff[0])
		*list = clean_node;
	else
	{
		free(buff);
		free(clean_node);
	}
}
