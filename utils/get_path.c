/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:06 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:04:52 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon `check_dir`, verilen `cmd` argümanının bir dizin 
olup olmadığını kontrol eder. Eğer bir dizin ise, `directory_err` 
fonksiyonu çağırılır.
*/
void	check_dir(char *cmd)
{
	DIR	*dir;

	if (!cmd)
		exit(EXIT_SUCCESS);
	dir = opendir(cmd);
	if (dir && readdir(dir))
	{
		closedir(dir);
		directory_err(cmd);
	}
}

/*
Bu fonksiyon, iki string verilen "mim" ve "path" parametrelerini 
birleştirir ve "mim" parametresinin bellekte ayrılmış alanını 
serbest bırakır. Sonuç olarak, "path" parametresi döndürülür.
*/
char	*mimi_ret_free(char *mim, char *path)
{
	free(mim);
	return (path);
}

/*
Bu fonksiyon "cmd" adındaki bir komutun yolunu almaya çalışır. 
İlk olarak "cmd" yolunun geçerli olup olmadığını kontrol eder. 
Eğer geçerli ise, "cmd" yolunun kopyasını döndürür. Eğer "cmd" yolu 
geçerli değilse, g_ms.paths değişkenindeki yolları kullanarak komutun 
yolunu bulmaya çalışır. Eğer yol bulunamazsa, "cmd" içinde "/" karakteri 
varsa, no_file_err fonksiyonunu çağırarak "cmd" adındaki dosya veya dizin 
bulunamadı hatası verir. Eğer g_ms.paths değişkeni de tanımlı değilse, 
command_err fonksiyonunu çağırarak komut bulunamadı hatası verir.
*/
char	*get_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*new_cmd;

	check_dir(cmd);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	paths = g_ms.paths;
	if (!paths)
		command_err(cmd);
	new_cmd = ft_strjoin("/", cmd);
	while (*paths)
	{
		path = ft_strjoin(*paths, new_cmd);
		if (!access(path, F_OK))
			return (mimi_ret_free(new_cmd, path));
		free(path);
		paths++;
	}
	if (ft_strchr(cmd, '/'))
		no_file_err(cmd);
	free(new_cmd);
	return (NULL);
}
