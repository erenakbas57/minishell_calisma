/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:10:49 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:12:17 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon, bir dosya adı verilen dosyayı okunabilir olarak açar ve 
standart giriş (STDIN) ile dosya arasında bir çiftleme yapar. Bu, komutların 
dosyadan okunmasını ve standart giriş yerine dosya girdisi olarak kullanmasını 
sağlar. Eğer dosya açılamazsa, "no_file_err" fonksiyonu çağrılır ve dosya adı 
ile birlikte bir hata mesajı görüntülenir.
*/
void	input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (no_file_err(file));
	dup2(fd, 0);
	close(fd);
}
