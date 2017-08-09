/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:05:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/09 21:07:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main()
{
	ft_printf("BONJOUR\n");
	ft_printf("%%\n");
	ft_printf("%5%.\n");
	ft_printf("%-5%.\n");
	ft_printf("%.0%.\n");
	ft_printf("%x\n", 0);
	ft_printf("%x\n", 42);
	ft_printf("%X\n", 42);
	ft_printf("%x\n", -42);
	ft_printf("%X\n", -42);
	return 0;
}