/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:21 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:07:13 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
"set_paths" fonksiyonu PATH ortam değişkeninin değerini alır 
ve bu değerin parçalarını ": " karakteri kullanarak dizi olarak 
ayırır. Elde edilen dizi "g_ms.paths" değişkenine atanır. 
Eğer PATH değişkeni boş ise "g_ms.paths" değişkeni NULL olarak atanır.
*/
void	set_paths(void)
{
	char	*path;

	if (g_ms.paths)
		free_array(g_ms.paths);
	path = get_env("PATH");
	if (!(*path))
		g_ms.paths = NULL;
	else
		g_ms.paths = ft_split(path, ':');
	free(path);
}
