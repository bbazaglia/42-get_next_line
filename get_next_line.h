/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:22:34 by bbazagli          #+#    #+#             */
/*   Updated: 2023/08/24 12:26:32 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*ft_read_fd(int fd, char *unfiltered_line, int *bytes_read);
char	*ft_filter_line(char *unfiltered_line);
char	*ft_rest_unfiltered(char *unfiltered_line);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nelem, size_t elsize);
void	*ft_memset(void *str, int c, size_t n);
char	*get_next_line(int fd);

#endif
