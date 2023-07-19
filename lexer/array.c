/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:51:40 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:19:39 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon, verilen bir dizi ("arg_arr") ve bir metin dizesi ("str") alır 
ve bu metin dizesini dizinin sonuna ekleyerek yeni bir dizi oluşturur. Eski 
dizi önce serbest bırakılır ve yeni dizi döndürür.
*/
char	**push_array(char **arg_arr, char *str)
{
	int		i;
	int		len;
	char	**new_arr;

	i = 0;
	len = 0;
	while (arg_arr && arg_arr[len])
		len++;
	new_arr = ft_calloc(sizeof(char *), len + 2);
	while (i < len)
	{
		new_arr[i] = arg_arr[i];
		i++;
	}
	new_arr[i] = str;
	free(arg_arr);
	return (new_arr);
}
