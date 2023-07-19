/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:11:39 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:15:49 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
"input" ve "output" fonksiyonları, belirtilen dosya isimli dosyalardan veya bu dosyalara 
veri okumak/yazmak için kullanılan dosya tanımlayıcılarını yönetmek için kullanılır. Bu fonksiyonlar, 
verilerin standart giriş veya standart çıkış akışından okunması veya yazılması yerine belirtilen 
dosyalardan okunması veya belirtilen dosyalara yazılmasını sağlar.
*/
void	output(char *file, int mode)
{
	int		fd;

	fd = 0;
	if (mode == REPLACE)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == APPEND)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
			return ;
		else
			exit(errno);
	}
	dup2(fd, 1);
	close(fd);
}
