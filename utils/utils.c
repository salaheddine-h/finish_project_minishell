/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:03:48 by salhali           #+#    #+#             */
/*   Updated: 2025/07/10 17:14:52 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_strcpy(char *dest,const char *src)
{
    int i = 0;

    if(!dest || !src)
        return(printf("check (create_env_string) 64\n "), NULL);
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}

// void free_env(char **env)
// {
//     int i = 0;

//     if (!env)
//         return;
//     while (env[i])
//     {
//         free(env[i]);
//         i++;
//     }
//     free(env);
// }

// void print_env_sorted(t_env *env)
// {
//     // Count env
//     int len = 0;
//     t_env *tmp;

//     tmp = env;
//     while (tmp)
//     {
//         len++;
//         tmp = tmp->next;
//     }

//     char **keys = malloc(sizeof(char *) * (len + 1));
//     tmp = env;

//     int i = 0;
//     while (i < len)
//     {
//         keys[i] = strdup(tmp->key);
//         tmp = tmp->next;
//         i++;
//     }
//     keys[len] = NULL;

//     i = 0;
//     while (i < len - 1)
//     {
//         int j = 0;
//         while (j < len - i - 1)
//         {
//             if (ft_strcmp(keys[j], keys[j + 1]) > 0)
//             {
//                 char *t = keys[j];
//                 keys[j] = keys[j + 1];
//                 keys[j + 1] = t;
//             }
//             j++;
//         }
//         i++;
//     }

//     i = 0;
//     while (i < len)
//     {
//         char *val = get_env_value_ll(env, keys[i]);
//         if (val && val[0] != '\0')
//             printf("declare -x %s=\"%s\"\n", keys[i], val);
//         else
//             printf("declare -x %s\n", keys[i]);
//         free(keys[i]);
//         i++;
//     }
//     free(keys);
// }

void	ft_free_2d_array(char **arr)
{
	int	i = 0;

	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *get_env_value(char **env, const char *key)
{
    size_t len = ft_strlen(key);
    int i = 0;
    while (env[i])
    {
        if (strncmp(env[i], key, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
        i++;
    }
    return NULL;
}
