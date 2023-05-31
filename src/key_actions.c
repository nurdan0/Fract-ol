/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:40:45 by nsahinog          #+#    #+#             */
/*   Updated: 2023/05/31 01:30:13 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key_macos_en.h"

int	key_actions(int key, t_fractol *frctl)
{
	if (key == EXIT_ESC)
		free_kill_all(frctl);
	else if (key == RESET_R)
		set_pov(frctl);
	else if (key == ARROW_UP || key == ARROW_DOWN)
		move(key, frctl);
	else if (key == KEY_D || key == KEY_U)
		zoom(key, 500, 500, frctl);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT)
		move(key, frctl);
	else if (key == COLOR_PLUS || key == COLOR_MINUS)
		change_maxiter(key, frctl);
	else if (key >= KEY_1 && key <= KEY_4)
		fractal_change(key, frctl);
	else if (key == MOVE_SPACE)
		frctl->is_fixed = !frctl->is_fixed;
	else if (key == CHANGE_FUNC_C)
		color_shift(frctl);
	fractol_loop(frctl);
	return (0);
}

void	move(int key, t_fractol *frctl)
{
	t_complex	c_size;

	c_size.re = frctl->c_max.re - frctl->c_min.re;
	c_size.im = frctl->c_max.im - frctl->c_min.im;
	if (key == ARROW_UP)
	{
		frctl->c_min.im += c_size.im * 0.05;
		frctl->c_max.im += c_size.im * 0.05;
	}
	else if (key == ARROW_DOWN)
	{
		frctl->c_min.im -= c_size.im * 0.05;
		frctl->c_max.im -= c_size.im * 0.05;
	}
	else if (key == ARROW_LEFT)
	{
		frctl->c_min.re -= c_size.re * 0.05;
		frctl->c_max.re -= c_size.re * 0.05;
	}
	else if (key == ARROW_RIGHT)
	{
		frctl->c_min.re += c_size.re * 0.05;
		frctl->c_max.re += c_size.re * 0.05;
	}
}

void	fractal_change(int key, t_fractol *frctl)
{
	if (key == KEY_1)
		frctl->fractal_func = mandelbrot;
	else if (key == KEY_2)
		frctl->fractal_func = julia;
	else if (key == KEY_3)
		frctl->fractal_func = celtic_mandelbrot;
	else if (key == KEY_4)
		frctl->fractal_func = burning_ship;
	set_pov(frctl);
}

void	color_shift(t_fractol *frctl)
{
	frctl->color_shift = (frctl->color_shift + 1) % 6;
	set_color_array(frctl);
}

void	change_maxiter(int key, t_fractol *frctl)
{
	if (key == COLOR_PLUS || key == COLOR_PLUS)
	{
		if (frctl->max_iter == 5000)
			return ;
		else if (frctl->max_iter < 50)
			frctl->max_iter += 1;
		else if (frctl->max_iter < 5000)
		{
			frctl->max_iter = (int)(frctl->max_iter * 1.05);
			if (frctl->max_iter > 5000)
				frctl->max_iter = 5000;
		}
	}
	else if (key == COLOR_MINUS)
	{
		if (frctl->max_iter > 50)
			frctl->max_iter = frctl->max_iter * 0.95;
		else if (frctl->max_iter > 1)
			frctl->max_iter -= 1;
	}
	set_color_array(frctl);
}
