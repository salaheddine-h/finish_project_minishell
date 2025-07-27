/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:17:29 by salhali           #+#    #+#             */
/*   Updated: 2025/07/26 18:08:44 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_env_list(t_shell *shell, const char *key, const char *value)
{
    t_env *tmp = shell->envv;

    // Check if key already exists in env list
    while (tmp)
    {
        if (ft_strcmp(tmp->key, (char *)key) == 0)
        {
            free(tmp->value);
            if (value == NULL)
                tmp->value = NULL;
            else
                tmp->value = ft_strdup(value);
            return;
        }
        tmp = tmp->next;
    }

    // Create new node if key doesn't exist
    t_env *new = create_env_node((char *)key, (char *)value);
    if (!new)
        return ; // optionally handle malloc failure

    if (shell->envv == NULL)
        shell->envv = new;
    else
    {
        tmp = shell->envv;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

t_env *create_env_node(char *key, char *value)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return NULL;

    new->key = ft_strdup(key);
    if (value != NULL)
        new->value = ft_strdup(value);
    else
        new->value = NULL;

    new->next = NULL;
    return new;
}
char *get_env_value_ll(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, (char *)key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}
void print_env(char **env)
{
    int i = 0;
    while (env && env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

char **dup_envp(char **envp)
{
    int i = 0;
    int count = 0;
    char **new_env;

    while (envp[count])
        count++;

    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return NULL;

    while (i < count)
    {
        new_env[i] = strdup(envp[i]);
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}
