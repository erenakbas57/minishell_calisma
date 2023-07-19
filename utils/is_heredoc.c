/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:08 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:01:15 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
"contain_heredoc" adlı fonksiyon, verilen "t_process" tipindeki bir nesnenin 
"redirects" alanında HEREDOC operatörünün bulunup bulunmadığını kontrol eder. 
Eğer bulunuyorsa, "TRUE" değerini döndürür; bulunmuyorsa, "FALSE" döndürür.*/
int	contain_heredoc(t_process *process)
{
	int	i;

	i = 0;
	while (process->redirects[i])
	{
		if (is_operator(process->redirects[i]) == HERE_DOC)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
