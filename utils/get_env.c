/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:03 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:02:45 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
"split_env" fonksiyonu, bir string içinde "=" simgesinin 
sağındaki değerini kopyalamak için kullanılır. Fonksiyon, 
bir "=" simgesini bulana kadar string içinde ilerler ve bu 
simge bulunduğunda sağındaki değeri kopyalar ve yeni bir 
string olarak döndürür.
*/
char	*split_env(char *str)
{
	while (*str != '=')
		str++;
	str++;
	return (ft_strdup(str));
}

/*
Bu fonksiyon, verilen "str" değişkeni ile eşleşen 
bir ortam değişkeninin değerini bulmak için kullanılır. 
Eğer bir eşleşme bulunursa, bu değer döndürülür. 
Aksi takdirde, boş bir karakter dizisi döndürülür.
*/
char	*get_env(char *str)
{
	size_t	len;
	char	**env;
	char	*new_str;

	env = g_ms.env;
	new_str = ft_strjoin(str, "=");
	len = ft_strlen(new_str);
	while (*env)
	{
		if (!ft_strncmp(*env, new_str, len))
		{
			free(new_str);
			return (split_env(*env));
		}
		env++;
	}
	free(new_str);
	return (ft_calloc(sizeof(char *), 1));
}
