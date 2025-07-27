/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:54:22 by salhali           #+#    #+#             */
/*   Updated: 2025/07/27 16:54:54 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_non_empty_args(t_cmd *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd->array[i])
	{
		if (ft_strlen(cmd->array[i]) > 0)
			count++;
		i++;
	}
	return (count);
}
void	copy_non_empty_args(t_cmd *cmd, char **filtered)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->array[i])
	{
		if (ft_strlen(cmd->array[i]) > 0)
		{
			filtered[j] = cmd->array[i];
			j++;
		}
		i++;
	}
	filtered[j] = NULL;
}
char	**filter_empty_args(t_cmd *cmd)
{
	char	**filtered;
	int		count;

	if (cmd->qflag == 0 || cmd->array == NULL)
		return (cmd->array);
	count = count_non_empty_args(cmd);
	filtered = malloc(sizeof(char *) * (count + 1));
	if (!filtered)
		return (cmd->array);
	copy_non_empty_args(cmd, filtered);
	return (filtered);
}
