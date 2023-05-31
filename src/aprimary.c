/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aprimary.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:39:51 by nsahinog          #+#    #+#             */
/*   Updated: 2023/05/31 01:45:27 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractol	*frctl_init(int argc, char **argv)
{
	t_fractol	*frctl;

	frctl = malloc(sizeof(t_fractol));
	if (frctl == 0)
		return (0);
	frctl->color_scheme = malloc((50 + 1) * sizeof(int));
	if (frctl->color_scheme == 0)
		free_kill_all(frctl);
	frctl->mlx = NULL;
	frctl->color_shift = 0;
	set_pov(frctl);
	which_func(argc, argv, frctl);
	return (frctl);
}

int	set_pov(t_fractol *frctl)
{
	frctl->max_iter = 50;
	frctl->is_fixed = true;
	if (SIZE_X == SIZE_Y)
	{
		complex_set(&frctl->c_max, 2.4, 2.4);
		complex_set(&frctl->c_min, -2.4, -2.4);
	}
	else
	{
		complex_set(&frctl->c_min, -2.4, -2.4);
		frctl->c_max.im = 2.4;
		frctl->c_max.re = (SIZE_X / SIZE_Y
				* (frctl->c_max.im - frctl->c_min.im)
				+ frctl->c_min.re);
	}
	complex_set(&frctl->c_julia, -0.6, 0.6);
	set_color_array(frctl);
	return (0);
}

void	which_func(int argc, char **argv, t_fractol *frctl)
{
	frctl->fractal_func = NULL;
	if ((argc == 2 || argc == 4) && !ft_strncmp(argv[1], "julia", 6))
	{
		frctl->fractal_func = julia;
		if (argc == 4)
		{
			frctl->c_julia.re = ft_atoi(argv[2]);
			frctl->c_julia.im = ft_atoi(argv[3]);
		}
	}
	else if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
		frctl->fractal_func = mandelbrot;
	else if (argc == 2 && !ft_strncmp(argv[1], "burning_ship", 13))
		frctl->fractal_func = burning_ship;
	else if (argc == 2 && !ft_strncmp(argv[1], "celtic_mandelbrot", 18))
		frctl->fractal_func = celtic_mandelbrot;
	else
		printf_warning();
	if (frctl->fractal_func == NULL)
		free_kill_all(frctl);
}

int	free_kill_all(t_fractol *frctl)
{
	if (frctl->mlx != NULL)
	{
		mlx_destroy_image(frctl->mlx->ptr, frctl->mlx->img.ptr);
		mlx_destroy_window(frctl->mlx->ptr, frctl->mlx->win);
		free(frctl->mlx);
	}
	free(frctl->color_scheme);
	free(frctl);
	exit(0);
}
