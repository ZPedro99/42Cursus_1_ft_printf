/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:40:14 by jomirand          #+#    #+#             */
/*   Updated: 2022/12/02 17:58:14 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return(1);
}

int	ft_print_string(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		return (write(1, "(null)", 6));
	}
	while (*(str + count))
	{
		write(1, (str + count), 1);
		count++;
	}
	return (count);
}

int	ft_print_numbs(int num)

{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789";
	if (num < 0)
	{
		num *= -1;
		count += ft_print_char('-');
	}
	if (num < 10)
	{
		count += ft_print_char(*(base + num));
	}
	if (num >= 10)
	{
		count += ft_print_numbs(num / 10);
		count += ft_print_numbs(num % 10);
	}
	return (count);
}

int	ft_print_unsigned(unsigned int num)

{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789";
	if (num < 10)
	{
		count += ft_print_char(*(base + num));
	}
	if (num >= 10)
	{
		count += ft_print_unsigned(num / 10);
		count += ft_print_unsigned(num % 10);
	}
	return (count);
}

int	ft_print_hexa(unsigned long num, char c)

{
	int		count;
	char	*base;

	count = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (num < 16)
	{
		count += ft_print_char(base[num]);
	}
	if (num >= 16)
	{
		count += ft_print_hexa(num / 16, c);
		count += ft_print_hexa(num % 16, c);
	}
	return(count);
}

int	ft_print_address(unsigned long num)
{
	int	count;

	count = 0;
	if (!num)
		return (write(1, "(nil)", 5));
	else
		write (1, "0x", 2);
	count += ft_print_hexa(num, 'x');
	return (count + 2);
}

int	ft_check_specifier(char c, va_list args, int *byte_count)

{
	byte_count++;
	if(c == 'c')
		ft_print_char(va_arg(args, int));
	else if(c == '%')
		write(1, "%", 1);
	else if(c == 's')
		ft_print_string(va_arg(args, char *));
	else if(c == 'd' || c == 'i')
		ft_print_numbs(va_arg(args, int));
	else if(c == 'u')
		ft_print_unsigned(va_arg(args, unsigned int));
	else if(c == 'X' ||c == 'x')
		ft_print_hexa(va_arg(args, unsigned int), c);
	else if(c == 'p')
		ft_print_address(va_arg(args, unsigned long));
	return(*byte_count);
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
		{
			write(1, (format + i), 1);
			byte_count++;
		}
		else
		{
			i++;
			ft_check_specifier(*(format + i), args, &byte_count);
		}
		i++;
	}
	va_end(args);
	return (byte_count);
}

/* int	main(int argc, char **argv)

{
	char	c;
	unsigned int	d;

	c = 'M';
	d = 235728;
	if(argc < 2)
		return(0);
	ft_printf("%u", d);
	return(0);
} */

int	main()

{
	unsigned long	n;
	unsigned long	*a;

	n = 683;
	a = &n;
	ft_printf("%p\n", a);
	printf("%p", a);
	return(0);
}