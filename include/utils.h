/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:29:50 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/24 15:29:51 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>

/* Character utilities */
int     is_space(char c);
int     is_delimiter(char c);
int		ft_isalnum(int c);

/* String utilities */
int     ft_strlen(const char *s);
int     ft_strlcpy(char *dst, const char *src, int size);
char    *ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

/* Array utilities */
char	**ft_split(char const *str, char c);
void	free_split(char **split);
int		count_strings(char const *str, char delimiter);

/*Parser utilities*/
int     len_until_delim(char *word);
char	*find_env_value(char *variable, char *env[], int var_len);
int 	find_dollar_pos(char *str);

#endif
