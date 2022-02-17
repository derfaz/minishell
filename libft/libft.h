/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eosfryd <eosfryd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:23:35 by eosfryd           #+#    #+#             */
/*   Updated: 2021/10/06 18:54:24 by eosfryd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termcap.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define B0000_0000 0
# define B0000_0001 1
# define B0000_0010 2
# define B0000_0100 4
# define B0000_1000 8
# define FLAG_ZERO B0000_0000
# define FLAG_ONE B0000_0001
# define FLAG_TWO B0000_0010
# define FLAG_FOUR B0000_0100
# define FLAG_EIGHT B0000_1000

void				ft_memdel(void **str);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_bzero(void *dest, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *src, int c, size_t n);
int					ft_memcmp(const void *dst, const void *src, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dst, char *src);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle, \
					size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
long				ft_atoi(const char *str);
long long			ft_atoi_ll(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isint(char *str);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
void				*ft_realloc(void *ptr, size_t size);
char				*ft_strdup(const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, char *s2, int free1, int free2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
void				ft_clean(char **s);
char				*ft_itoa(int n);
char				*ft_itoa_ll(long long int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstallfree(t_list **lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));

typedef struct s_list_p
{
	int				flag;
	int				width;
	int				accuracy;
	int				type;
	int				length;
}					t_list_p;

void				ft_clean_str_by_adress(char **str);
int					ft_len(long long int argumento, int i);

int					get_next_line(int fd, char **line);
int					ft_isnumber(char *str);

#endif
