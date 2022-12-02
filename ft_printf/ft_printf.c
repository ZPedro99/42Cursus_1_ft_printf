/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:40:14 by jomirand          #+#    #+#             */
/*   Updated: 2022/12/02 13:05:31 by jomirand         ###   ########.fr       */
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
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str && *(str + i))
	{
		write(1, (str + i), 1);
		i++;
		count++;
	}
	return(count);
}

void	ft_print_numbs(int num)

{
	long	n;

	n = num;
	if (n == -2147483648)
	{
		write(1, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
	}
	if (n >= 0 && n <= 9)
		ft_print_char(n + '0');
	else
	{
		ft_print_numbs(n / 10);
		ft_print_numbs(n % 10);
	}
}

void	ft_print_unsigned(unsigned int num)

{
	if (num >= 0 && num <= 9)
		ft_print_char(num + '0');
	else
	{
		ft_print_numbs(num / 10);
		ft_print_numbs(num % 10);
	}
}

int ft_get_num_len(long long num, int base)
{
	int len;

	if (num == 0)
		return (1);
	len = 0;
	while (num != 0)
	{
		len++;
		num /= base;
	}
	return (len);
}

/* void	ft_print_hex_low(unsigned int num)

{
	char	*hexadecimal;
	int		rest;
	int		i;
	int		len;

	len = ft_get_num_len(num, 16);
	hexadecimal = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (num != 0)
	{
		rest = num % 16;
		if (rest < 10)
			hexadecimal[i++] = 48 + rest;
		else
			hexadecimal[i++] = 87 + rest;
		num = num / 16;
	}
	i--;
	while (*(hexadecimal + i) > 1)
	{
		write(1, (hexadecimal + i), 1);
		i--;
	}
}

void	ft_print_hex_up(unsigned int num)

{
	char	*hexadecimal;
	int		rest;
	int		i;
	int		len;

	len = ft_get_num_len(num, 16);
	hexadecimal = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (num != 0)
	{
		rest = num % 16;
		if (rest < 10)
			hexadecimal[i++] = 48 + rest;
		else
			hexadecimal[i++] = 55 + rest;
		num = num / 16;
	}
	i--;
	while (*(hexadecimal + i) > 1)
	{
		write(1, (hexadecimal + i), 1);
		i--;
	}
} */

int	ft_print_hexa(unsigned int num, char c)

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

int	ft_print_address(unsigned long long num)
{
	int	count;

	count = 0;
	if (!num)
		return (ft_print_string("(nil)"));
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
	/* else if(*(format + i) == 'x')
		ft_print_hex_low(va_arg(args, unsigned int));
	else if(*(format + i) == 'X')
		ft_print_hex_up(va_arg(args, unsigned int)); */
	else if(c == 'X' ||c == 'x')
		ft_print_hexa(va_arg(args, unsigned int), c);
	else if(c == 'p')
		ft_print_address(va_arg(args, unsigned long long));
	else
		write(1, "invalid conversion specifier", 29);
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
	int		*a;
	int		c;

	c = 683;
	a = &c;
	ft_printf("%p\n", a);
	printf("%p", a);
	return(0);
}