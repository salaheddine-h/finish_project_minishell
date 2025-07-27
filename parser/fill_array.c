/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:28:27 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/07/26 17:38:55 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_array_plus(t_pars *pars)
{
	if (pars->content[pars->i] == pars->content[pars->i + 1]
		&& (pars->content[pars->i] == '<' || pars->content[pars->i] == '>'))
	{
		pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 2);
		if (pars->content[pars->i] == '<')
			pars->herdoc_flag = 1;
		pars->i += 2;
	}
	else
	{
		pars->content1[pars->k++] = ft_substr(pars->content, pars->i, 1);
		pars->i++;
	}
}

char	*fill_array_and_callexpand(t_pars *pars,t_shell *shell)
{
	char	*part;
	int		start;
	int		len;
	int		z;
	char	*expanded;

	z = 0;
	start = pars->i;
	check_herdoc(pars->content,pars);
	while (check_spaces_and_red(pars) == 1)
		pars->i++;
	len = pars->i - start;
	part = ft_substr(pars->content, start, len);
	if(pars->herdoc_flag == 0)
	{		
		while (pars->numdollar > z)
		{
			expanded = expand_variables(part,shell);
			pars->expand_flag = 1;
			free(part);
			part = expanded;
			z++;
		}
	}
	return (part);
}

char	*fill_between_space_and_red(t_pars *pars, char *token,t_shell *shell)
{
	char	*part;
	char	*tmp;

	pars->expand_flag = 0;
	pars->herdoc_flag = 0;
	while (pars->content[pars->i] && !is_whitespace(pars->content[pars->i])
		&& !is_redirection(pars->content[pars->i]))
	{
		part = NULL;
		if (is_quotes(pars->content[pars->i]) == 1)
		{
			part = handlequotes(pars, pars->content[pars->i],shell);
			pars->dflag = 1;
		}
		else
			part = fill_array_and_callexpand(pars,shell);
		if (token[0] != '\0')
			pars->content1[pars->k++] = ft_strdup(token);
		tmp = ft_strjoin(token, part);
		free(token);
		free(part);
		token = tmp;
	}
	return (token);
}

void	fill_the_array(t_pars *pars,t_shell *shell)
{
	char	*token;

	pars->k = 0;
	pars->expand_flag =0;
	pars->dflag = 0;
	count_dollar(pars);
	while (pars->content[pars->i])
	{
		skipwhitespaces(pars);
		if (pars->content[pars->i] == '\0')
			break ;
		token = ft_strdup("");
		token = fill_between_space_and_red(pars, token,shell);
		if (token[0])
			pars->content1[pars->k++] = ft_strdup(token);
		else
			pars->content1[pars->k++] = ft_strdup("");
		if (is_redirection(pars->content[pars->i]))
			fill_array_plus(pars);
	}
	pars->content1[pars->k] = NULL;
	if (pars->expand_flag == 1 && pars->dflag == 0)
		reparse_variable(pars,shell);
}

void	reparse_variable(t_pars *pars,t_shell *shell)
{
	char			*new_input;
	unsigned int	j;
	pars->expand_flag = 0;
	j =0;
	while(pars->content1[j])
		{
			if(strcmp("$",pars->content1[j]) == 0)
				return ;
			j++;
		}
	new_input = ft_strjoin_all(pars->content1);
	
	pars->content = ft_strdup(new_input);
	if (new_input)
		free(new_input);
	j = -1;
	while (++j < pars->lenofarray + pars->nbofpipes)
		free(pars->content1[j]);
	free(pars->content1);
	pars->content1 = malloc(sizeof(char *) * (pars->lenofarray + pars->nbofpipes
				+ 1));
	fill_the_array(pars,shell);
	return ;
}
