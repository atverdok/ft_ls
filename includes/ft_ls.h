/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 14:42:50 by atverdok          #+#    #+#             */
/*   Updated: 2017/04/04 09:48:47 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdio.h>
# include <time.h>
# include <grp.h>
# include <sys/types.h>
# include <pwd.h>

# include "../srcs/libft/libft.h"

typedef int			t_boolean;

# define TRUE 1
# define FALSE 0

typedef struct		s_stack
{
	char			*path;
	struct s_stack	*next;
}					t_stack;

typedef struct		s_options
{
	t_boolean			l;
	t_boolean			up_r;
	t_boolean			a;
	t_boolean			r;
	t_boolean			t;
}					t_options;

typedef struct		s_max_fileds
{
	size_t			max_nlink;
	size_t			max_group;
	size_t			max_size;
	size_t			max_time;
	size_t			max_name;
	size_t			max_major;
	size_t			max_minor;
}					t_max_fileds;

typedef struct		s_fileds_l
{
	char			*file_type;
	char			*permission;
	char			*st_nlink;
	char			*author;
	char			*group_name;
	char			*major_st_rdev;
	char			*minor_st_rdev;
	char			*st_size;
	char			*date;
	char			*d_name;
	char			*ful_path;
	char			*target_name;
	struct timespec	st_mtimespec;
	blkcnt_t		st_blocks;
}					t_fileds_l;

typedef struct		s_node
{
	t_fileds_l		*fileds_l;
	struct s_node	*next;
}					t_node;

typedef struct		s_main
{
	t_options		*options;
	t_max_fileds	*max_fileds;
	t_node			*head;
	blkcnt_t		total;
}					t_main;

t_fileds_l			*list_pop(t_node **head);
void				del_t_fileds_l(t_fileds_l *fileds_l);
void				sorted_insert(t_node **head, t_node *new_node, t_boolean r,
		int (*cmp)(t_fileds_l *, t_fileds_l *, t_boolean));
t_node				*new_node(t_fileds_l *fileds_l);

void				print_list(t_node *head, t_stack **stack,
		t_main *main_struct, void (*print)(t_fileds_l *, t_main *));
void				print_name(t_fileds_l *l_fileds, t_main *main_struct);
void				print_file_stat(t_fileds_l *l_fileds, t_main *main_struct);
void				print_total_l(t_main *main_struct);
void				print_path_l(const char *path);
void				fill_spase_before(size_t len, size_t n);

void				check_max_size_and_size(t_main *main_struct);
void				fill_spase_after(size_t len, size_t n);
void				insert_spase(t_fileds_l *l_fileds, size_t len, size_t n);
void				print_st_rdev(t_fileds_l *l_fileds, t_main *main_struct);
void				print_file_stat(t_fileds_l *l_fileds, t_main *main_struct);

void				push_stack(t_stack **head, char *path);
char				*pop_stack(t_stack **head);
void				push_global_stack(t_stack **stack, t_stack	**stack_tmp);

void				usage_error(void);
void				illegal_options_error(char *str);
void				print_perror(void *value);

t_main				*create_main_struct(void);

void				parse_options(char *str, t_main	*main_struct);
char				*make_parce_options(t_stack **tmp_arg,
								t_main *main_struct);
t_boolean			parse_argument(int *i_err, char *arg,
							t_main *main_struct, t_stack **tmp);

t_fileds_l			*get_stat_file(const char *path, struct dirent	*dp);
void				get_make_stat(t_main *main_struct, t_node **head,
		char *ful_path, struct dirent *dp);
char				*make_full_path(const char *path, struct dirent	*dp);
t_node				*ft_list_dir(const char *path, t_main *main_struct);
void				get_rdev_or_size(t_fileds_l *fileds_l, struct stat stat_f);
char				*set_target(char *path_name);
char				*get_date(struct stat statv);
char				*get_permission(int st_mode);
char				*get_file_type(int st_mode);

int					cmp_name(t_fileds_l *e1, t_fileds_l *e2, t_boolean r);
int					cmp_date(t_fileds_l *e1, t_fileds_l *e2, t_boolean r);

void				sorted_insert_stack(t_stack **head, t_stack *new_node);
t_stack				*create_stack_node(char *path);
size_t				get_len_stack(t_stack *stack);

void				make_priint_stack(t_main *main_struct,
		t_stack *stack_head, int err);

t_fileds_l			*get_stat_single_file(char *path, struct stat stat_f);
char				*ft_itoa_off_t(off_t nbr);

#endif
