/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:40:14 by jomirand          #+#    #+#             */
/*   Updated: 2022/12/05 14:13:47 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_check_specifier(char c, va_list args)

{
	int	byte_count;

	byte_count = 0;
	if (c == 'c')
		byte_count += ft_print_char(va_arg(args, int));
	else if (c == '%')
		byte_count += write(1, "%", 1);
	else if (c == 's')
		byte_count += ft_print_string(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		byte_count += ft_print_numbs(va_arg(args, int));
	else if (c == 'u')
		byte_count += ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'X' || c == 'x')
		byte_count += ft_print_hexa(va_arg(args, unsigned int), c);
	else if (c == 'p')
		byte_count += ft_print_address(va_arg(args, unsigned long));
	return (byte_count);
}

int	ft_printf(const char *format, ...)

{
	va_list		args;
	static int	byte_count;
	int			i;

	va_start(args, format);
	byte_count = 0;
	i = 0;
	while (*(format + i) != '\0')
	{
		if (*(format + i) != '%')
			byte_count += write(1, (format + i), 1);
		else
		{
			i++;
			byte_count += ft_check_specifier(*(format + i), args);
		}
		i++;
	}
	va_end(args);
	return (byte_count);
}

int	main()

{
	//unsigned int	b;

	//b = -1;
	printf("boas malta");
	ft_printf("boas malta");
}