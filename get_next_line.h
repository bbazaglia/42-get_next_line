/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:22:34 by bbazagli          #+#    #+#             */
/*   Updated: 2023/08/24 10:28:43 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE  
# define BUFFER_SIZE 1024
#endif

char *get_next_line(int fd);
char    *read_fd(int fd, char *unfiltered_line);
char    *ft_filter_line(char *unfiltered_line);
char    *ft_rest_unfiltered(char *unfiltered_line);
size_t  ft_strlen(const char *s);
char    *ft_strchr(const char *s, int c);
char    *ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nelem, size_t elsize);
void	*ft_memset(void *str, int c, size_t n);
#endif