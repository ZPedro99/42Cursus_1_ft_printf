/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:54:30 by jomirand          #+#    #+#             */
/*   Updated: 2022/12/05 15:19:32 by jomirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);
int	ft_print_char(char c);
int	ft_print_string(char *str);
int	ft_print_numbs(long num);
int	ft_print_unsigned(unsigned int num);
int	ft_print_hexa(unsigned long num, char c);
int	ft_print_address(unsigned long num);

#endif