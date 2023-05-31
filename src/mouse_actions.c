/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahinog <nsahinog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:40:58 by nsahinog          #+#    #+#             */
/*   Updated: 2023/05/30 22:17:24 by nsahinog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key_macos_en.h"

int	zoom(int button, int x, int y, t_fractol *frctl)
{
	t_complex	pos;
	double		zoom;

	if (button == SCROLL_UP || button == SCROLL_DOWN
		|| button == KEY_D || button == KEY_U)
	{
		pos.re = frctl->c_min.re + x * frctl->scale.re;
		pos.im = frctl->c_max.im - y * frctl->scale.im;
		if (button == SCROLL_UP || button == KEY_U)
			zoom = 0.9;
		else
			zoom = 1.1;
		frctl->c_min.re = pos.re + (frctl->c_min.re - pos.re) * zoom;
		frctl->c_max.re = pos.re + (frctl->c_max.re - pos.re) * zoom;
		frctl->c_min.im = pos.im + (frctl->c_min.im - pos.im) * zoom;
		frctl->c_max.im = pos.im + (frctl->c_max.im - pos.im) * zoom;
		fractol_loop(frctl);
	}
	return (0);
}

int	julia_mouse_motion(int x, int y, t_fractol *frctl)
{
	if (!frctl->is_fixed && (frctl->fractal_func == julia))
	{
		frctl->c_julia.re = 4 * ((double)x / SIZE_X - 0.5);
		frctl->c_julia.im = 4 * ((double)(SIZE_Y - y) / SIZE_Y - 0.5);
		fractol_loop(frctl);
	}
	return (0);
}
