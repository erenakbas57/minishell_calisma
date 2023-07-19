/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:14 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 14:14:28 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon sistem ortam değişkenlerini yazdırır. "g_ms.env" global bir dizi 
olarak tanımlanmış ortam değişkenlerini içerir ve "env" pointerı bu diziyi 
gösterir. Her bir ortam değişkeni ekrana yazdırılır ve sonra bir sonraki ortam 
değişkenine geçilir. Fonksiyon sonunda, "is_parent()" fonksiyonu çağrılır ve çıktı 
eğer parent prosesse aitse "EXIT_SUCCESS" ile çıkılır.
*/
void	builtin_env(void)
{
	char	**env;

	env = g_ms.env;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	if (!is_parent())
		exit (EXIT_SUCCESS);
}
