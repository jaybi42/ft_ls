/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguthert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 14:10:31 by jguthert          #+#    #+#             */
/*   Updated: 2016/02/18 17:33:21 by jguthert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>

# define BUFF_SIZE 512

# define ERROR ft_error(__FILE__, __FUNCTION__, __LINE__)
# define ERRORNO ft_errorno(__FILE__, __FUNCTION__, __LINE__)
# define ABS(NBR) (((NBR) < 0) ? (-NBR) : (NBR))
# define FTV_INIT(TYPE) ((t_ftv){NULL, 0, 0, sizeof(TYPE)})

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_gnl
{
	int				fd;
	char			*tmp;
	struct s_gnl	*next;
}					t_gnl;

typedef struct		s_ftv
{
	void			*data;
	size_t			capacity;
	size_t			size;
	size_t			element_size;
}					t_ftv;

/*
**	##=-  Print  -=##
*/

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
**	##=-  String  -=##
*/

size_t				ft_strlen(char const *s);
char				*ft_strcpy(char *dst, char const *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);

void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
**	##=-  Adaptator  -=##
*/

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_itoa_base(int nbr, int base);
char				*ft_ulltoa_base(uint64_t nbr, int base, char *str);
int					ft_getnbr(char *str);

/*
**	##=-  Casse  -=##
*/

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
**	##=-  Memory  -=##
*/

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

/*
**	##=-  Simple chained list  -=##
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstadd_last(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
**	##=-  Math  -=##
*/

int					ft_sqrt(int nbr);
int					ft_power(int nbr, int index);

/*
**	##=-  GNL  -=##
*/

int					get_next_line(int const fd, char **line);

/*
**	##=-  Vector  -=##
*/

void				ftv_print(t_ftv *ftv);
int					ftv_pushback(t_ftv *ftv, void const *new_data);
int					ftv_reserve(t_ftv *ftv, size_t new_cap);
void				ftv_del(t_ftv *ftv, void (*del)());
void				ftv_popback(t_ftv *ftv, void (*del)());
void				ftv_del_len(t_ftv *v, size_t s, size_t e, void (*del)());

/*
**	##=-  Error  -=##
*/

int					ft_error(char const *file, char const *function, int line);
int					ft_errorno(char const *file,
								char const *function, int line);

#endif
