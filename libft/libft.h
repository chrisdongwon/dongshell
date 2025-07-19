/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:05:50 by cwon              #+#    #+#             */
/*   Updated: 2025/07/17 15:26:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>

# include "ft_printf/ft_printf.h"
# include "ft_string/ft_string.h"
# include "get_next_line/get_next_line.h"

typedef struct s_list	t_list;

struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
};

// char functions
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_ismember(const char c, const char *str);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

// conversion functions
char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
double	ft_atof(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isfloat(const char *nptr);
int		ft_isinteger(const char *nptr);

// int functions
int		ft_abs(int n);
int		ft_greater_than(int a, int b);
int		ft_less_than(int a, int b);

// linked list operations
size_t	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

// memory functions
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);

// put functions
ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// string functions
char	**ft_split(const char *s, char c);
char	*ft_str_realloc(char *ptr, size_t old_size, size_t new_size);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_fnmatch(const char *pattern, const char *string);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *str, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t maxlen);
ssize_t	ft_indexof(char *s, int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

#endif
