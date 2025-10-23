/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:04:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/23 12:26:13 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);;
int		ft_isascii(int c);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

int		ft_putchar(int c);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr(char *str);
int		ft_putstr_fd_v(char *s, int fd);
int		ft_putptr(void *ptr, char *base, int i);
int		ft_putptr_fd(void *ptr, char *base, int i, int fd);
int		ft_putnbr_base(long long number, char *base, int i);
int		ft_putnbr_base_fd(long long number, char *base, int i, int fd);
int		ft_putnbr_base_unsigned(unsigned long long number, char *base, int i);
int		ft_putnbr_base_unsigned_fd(unsigned long long number, char *base,
			int i, int fd);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr_char(const char *s, int c);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim_v(char const *s1, char const *set);

int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_gnl(int fd);
char	*ft_gnl_assign(char *buffer, int fd);
void	ft_free_triptr(char ***str);
int		check_format(va_list args, const char *string, int i);
int		check_string(va_list args, const char *string, int i);
int		ft_printf(const char *string, ...);
int		ft_printf_fd(int fd, const char *string, ...);
char	**ft_matrix_dup(char **matrix, int row);
char	*ft_strdup_char(const char *s1);
size_t	ft_strlen_v(const char *s);

char	*get_next_line(int fd);
char	*ft_readfile(int fd, char *temp);
char	*ft_line(char *temp);
char	*ft_remain(char *temp);

// int		ft_isalnum(int c);
// size_t	ft_strlcpy(char *dest, const char *src, size_t size);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
//char	**ft_split(char const *s, char c);
#endif
