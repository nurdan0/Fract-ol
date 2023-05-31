/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:41:09 by nsahinog          #+#    #+#             */
/*   Updated: 2023/05/23 20:41:11 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	complex_set(t_complex *z, double x, double y)
{
	z->re = x;
	z->im = y;
}

void	my_mlx_pixel_put(t_mlximg *img, int x, int y, int color)
{	
	char	*dest;

	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	ft_atoi(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	else if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		i++;
	}
	if (*str >= 48 && *str <= 57)
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	return (sign * i);
}

void	printf_warning(void)
{
	write (1, "Please use one of the following parameters: ", 44);
	write (1, "[mandelbrot, julia, celtic_mandelbrot, burning_ship]\n", 53);
}
