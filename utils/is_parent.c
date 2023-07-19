/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:13 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:05:42 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
"is_parent" fonksiyonu, g_ms global değişkeninin parent_pid 
değerinin geçerli işlemin (process) PID değerine eşit olup 
olmadığını kontrol eder. Eğer eşitse, fonksiyon 1 döndürür, 
eşit değilse 0 döndürür.
*/
int	is_parent(void)
{
	return (g_ms.parent_pid == getpid());
}
