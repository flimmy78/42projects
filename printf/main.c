/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 03:29:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/29 04:59:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "ft_printf.h"

int main()
{
	ft_printf(">------------<%46.33zo>------------<\n", 0);
	printf(">------------<%46.33zo>------------<\n", 0);
	ft_printf("^.^/%44zo^.^/\n", 0);
	printf("^.^/%44zo^.^/\n", 0);
	ft_printf("^.^/%46.10zo^.^/\n", 0);
	printf("^.^/%46.10zo^.^/\n", 0);
	ft_printf(">------------<%8jo>------------<\n", 0);
	printf(">------------<%8jo>------------<\n", 0);
	ft_printf("^.^/%19.37jo^.^/\n", 0);
	printf("^.^/%19.37jo^.^/\n", 0);
	ft_printf(">------------<%16hho>------------<\n", 0);
	printf(">------------<%16hho>------------<\n", 0);
	ft_printf("!%42.58hho!\n", 0);
	printf("!%42.58hho!\n", 0);
	ft_printf("42%38ho42\n", 0);
	printf("42%38ho42\n", 0);
	ft_printf("\\!/%3o\\!/\n", 0);
	printf("\\!/%3o\\!/\n", 0);
	ft_printf(">------------<%56.7zo>------------<\n", 0);
	printf(">------------<%56.7zo>------------<\n", 0);
	return 0;
}
