/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:32:33 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/03 13:33:27 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd()
{
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
        else
                return 1;
    return 0;
}
