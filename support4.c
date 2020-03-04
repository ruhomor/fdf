#include "fdf.h"

t_point				transformx(t_point point, double angle)
{
	t_point tmp;

	tmp.x = point.x;
	tmp.y = point.y * cos(angle) + point.z * sin(angle);
	tmp.z = -point.y * sin(angle) + point.z * cos(angle);
	return (tmp);
}

t_point				transformy(t_point point, double angle)
{
	t_point tmp;

	tmp.x = point.x * cos(angle) + point.z * sin(angle);
	tmp.y = point.y;
	tmp.z = -point.x * sin(angle) + point.z * cos(angle);
	return (tmp);
}

t_point				transformxyz(t_point point, t_angle angle)
{
	return (transformy(transformx(point, angle.a), angle.b));
}

void				kph(int keycode, t_window *meme)
{
	if (keycode == 126)
		meme->shift.u_flag = (meme->shift.u_flag == 1) ? 0 : -1;
	if (keycode == 125)
		meme->shift.d_flag = (meme->shift.d_flag == -1) ? 0 : 1;
	if (keycode == 124)
		meme->shift.r_flag = (meme->shift.r_flag == -1) ? 0 : 1;
	if (keycode == 123)
		meme->shift.l_flag = (meme->shift.l_flag == 1) ? 0 : -1;
	if (keycode == 69)
		meme->attitude += 1;
	if (keycode == 78)
		meme->attitude -= 1;
	if (keycode == 53)
		escape_butt(meme);
	if (keycode == 18)
		meme->renmod = 1;
	if (keycode == 19)
		meme->renmod = 2;
	if (keycode == 20)
		meme->renmod = 3;
	if (keycode == 21)
		meme->renmod = 4;
}

int					key_press1(int keycode, void *p)
{
	t_window *meme;

	meme = (t_window *)p;
	kph(keycode, meme);
	if (keycode == 35)
	{
		meme->prjk += 1;
		meme->prjk %= 2;
	}
	meme->shift.x +=
			meme->shift.r_flag + meme->shift.l_flag;
	meme->shift.y += meme->shift.u_flag + meme->shift.d_flag;
	mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
	drawmap(meme);
	return (0);
}
