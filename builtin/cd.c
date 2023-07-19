/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:09 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 14:13:00 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon, minishell adlı bir programda CD (Change Directory) komutunun işlemini 
yapar. İlk olarak, eğer input[1] boş değilse, input[1] deki dizin adına geçmeyi 
deniyor. Eğer başarısız olursa, perror fonksiyonuyla hatayı ekrana yazdırıyor. 
Eğer input[1] boş ise, HOME değişkeni içindeki ev dizinine geçmeyi deniyor. Eğer 
ev dizini bulunamazsa, perror fonksiyonuyla hatayı ekrana yazdırıyor. Son olarak, 
eğer programın çalıştığı dizin ana dizin değilse (is_parent() fonksiyonu ile 
kontrol ediliyor), program exit(errno) fonksiyonuyla sonlandırılıyor.
*/
void	builtin_cd(char **input)
{
	char	*home;

	if (input[1] != NULL)
	{
		if (chdir(input[1]) != 0)
			errno = 1;
			write(2, "minishell : No such file or directory\n", 38);
			strerror(errno); 
	}
	else
	{
		home = getenv("HOME");
		if (home && *home)
			if (chdir(home))
				perror("minishell ");
	}
	if (!is_parent())
		exit (errno);
}

