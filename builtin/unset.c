/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:22 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 14:18:36 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
`remove_env` fonksiyonu, belirtilen bir değişkenin ortam değişkeni dizisinden 
kaldırılmasını sağlar. Fonksiyon, belirtilen değişkenin ismini alır ve ortam değişkeni 
dizisinde bulunan tüm girişleri kontrol eder. Eğer bulunan giriş belirtilen 
değişkene eşitse, o giriş ortam değişkeni dizisinden silinir ve kalan girişler 
yeni bir ortam değişkeni dizisi oluşturulur.
*/
void	remove_env(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), env_len() + 1);
	while (g_ms.env[i])
	{
		if (ft_strncmp(g_ms.env[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_ms.env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_ms.env);
	g_ms.env = new_env;
}

/*
Bu C dilinde bir fonksiyondur ve "unset" komutunun işlevini yerine getirir. Bu fonksiyon, 
girdi olarak verilen değişkenleri ortam değişkenlerinden kaldırır ve set_paths() fonksiyonunu 
çağırarak yolun güncellenmesini sağlar. Eğer fonksiyon çalışan bir ebeveyn işlem değilse, 
başarıyla çıkış yapar (EXIT_SUCCESS).
*/
void	builtin_unset(char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		data = ft_strjoin(*input, "=");
		remove_env(data);
		free(data);
		input++;
	}
	set_paths();
	if (!is_parent())
		exit (EXIT_SUCCESS);
}
