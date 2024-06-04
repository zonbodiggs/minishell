/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:32:30 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/03 13:33:23 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(char **cmd)
{
    size_t  i;
    size_t  j;
    int     end_n;

    i = 1;
    end_n = 0;
    if (!cmd)
        return (-1);

    while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
    {
        j = 2;
        while (cmd[i][j] == 'n')
            j++;
        if (cmd[i][j] != '\0')
            break;
        i++;
        end_n = 1;
    }

    while (cmd[i])
    {
        printf("%s", cmd[i]);
        if (cmd[i + 1])
            printf(" ");
        i++;
    }
    if (end_n == 0)
        printf("%c", '\n');
    return (0);
}
