/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:34:48 by gaubert           #+#    #+#             */
/*   Updated: 2021/11/08 16:10:08 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *str)
{
	free(str);
	return (0);
}

int	ft_strlengnl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	res = malloc(sizeof(char) * (ft_strlengnl(s1) + ft_strlengnl(s2) + 1));
	if (!res)
		return (0);
	while (s1 && s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free((void *)s1);
	s1 = NULL;
	return (res);
}
