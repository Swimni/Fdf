/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:43:35 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:29:25 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

# define WIDTH 1000
# define HEIGHT 1000

# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_ROTATE_X 113
# define KEY_ROTATE_Y 119
# define KEY_ROTATE_Z 101
# define KEY_ESC 65307

// STRUCTURES

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fdf
{
	int		width;
	int		height;
	t_point	**map;
	void	*mlx;
	void	*win;
	int		zoom;
	double	angle;
	int		x_offset;
	int		y_offset;
}	t_fdf;

typedef struct s_proj
{
	int		zoom;
	int		x_offset;
	int		y_offset;
	double	angle;
}	t_proj;

typedef struct s_line
{
	t_point	start;
	t_point	end;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		color_start;
	int		color_end;
}	t_line;

typedef struct s_line_vars
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line_vars;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_proj_bonus
{
	float	zoom;
	float	offset_x;
	float	offset_y;
	float	angle_x;
	float	angle_y;
	float	angle_z;
}	t_proj_bonus;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_point			**map;
	t_proj			proj;
	t_fdf			fdf;
	int				width;
	int				height;
	int				*line_widths;
	int				color;
	int				z_min;
	int				z_max;
	t_proj_bonus	proj_bonus;
}	t_data;

typedef struct s_map_info {
	t_point	**map;
	int		height;
	int		width;
}	t_map_info;

//draw.c
void	draw_points(t_fdf *fdf);
void	init_line_vars(t_line_vars *lv, t_line *line);
void	step_x(t_line_vars *lv);
void	step_y(t_line_vars *lv);
void	draw_line(t_data *data, t_line *line);

//ft_split.c
char	**get_last_split(char **new_split);
int		count_words(char const *s, char c);
int		len_word(char const *s, char c);
char	**ft_split(char const *s, char c);
void	free_all(char **tab, int i);
void	free_split(char **split);

//gnl_utils.c
int		tchek(int fd, char **stash);
void	ft_switchup(char **stash, char **buffer);
char	*clean(char **stash);
char	*ft_strjoin(const char *s1, const char *s2);

//gnl.c
int		linefinished(char *str);
char	*readfile(int fd, char **stash);
char	*get_next_line(int fd);

//libft.c
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *str);
void	ft_bzero(void *s, size_t n);

//main.c
int		close_window(t_data *data);
int		key_press(int keycode, t_data *data);

//nettoyage.c
void	free_fdf(t_fdf *fdf);
void	cleanup(t_data *data);
int		close_win(void *param);

//parser_utils.c
void	fill_point(t_point *p, int x, int y, char *str);
t_point	*parse_line(char *line, int width, int y);
void	parse_fdf(char *file, t_fdf *fdf);
int		ft_atoi_simple(const char *str);

//parser.c
int		get_height(char *filename);
int		get_width(char *filename);

//projection.c
void	iso_project(t_point p, t_proj proj, int result[2]);
void	draw_map(t_fdf *fdf, t_data *data);
void	init_projection(t_proj *proj, int win_width, int win_height);

//setup.c
int		parse_and_init(char *file, t_fdf *fdf, t_data *data);
void	free_map(t_point **map, int height);
int		render_frame(t_data *data);

//utils.c
int		abs_val(int x);
void	put_pixel(t_data *data, int x, int y, int color);
void	init_image(t_data *data);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	get_width_and_height(char *filename, t_fdf *fdf);
void	clear_image(t_data *data);
int		init_img(t_data *data);

//utils_colors.c
int		get_color_from_height(int z, int z_min, int z_max);
void	find_z_min_max(t_map_info *info, int *z_min, int *z_max);
int		interpolate_color(int color1, int color2, double t);

//FONCTIONS BONUS

//projections_bonus.c
void	init_proj_bonus(t_proj_bonus *proj);
void	zoom_bonus(t_proj_bonus *proj, float factor);
void	move_bonus(t_proj_bonus *proj, float dx, float dy);
void	rotate_bonus(t_proj_bonus *proj, float d_angle_x,
			float d_angle_y, float d_angle_z);
int		render_frame_bonus(void *param);

//controls_bonus.c
void	move_key_bonus(int keycode, t_proj_bonus *proj);
void	rotate_key_bonus(int keycode, t_proj_bonus *proj);
int		key_hook_bonus(int keycode, t_data *data);

//draw_project_bonus.c
void	draw_map_bonus(t_fdf *fdf, t_data *data);
void	iso_project_bonus(t_point p, t_proj_bonus *proj, int proj_point[2]);
int		close_win_bonus(t_data *data);
void	redraw_bonus(t_data *data);

#endif
