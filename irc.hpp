#ifndef IRC_HPP
# define IRC_HPP

/*	includes	*/
# include <iostream>
# include <sys/socket.h>
# include <cerrno>	// errno
# include <cstring>	// strerror

//for tests
# include <netinet/in.h>
# include <unistd.h>

/*	defines	*/
# define NEWLINE()	std::cout << std::endl

/*	structs	*/
typedef struct s_data
{
	struct sockaddr_in	address;
} t_data;

/*	init.cpp	*/
int	initialization(t_data* data);

/*	loop.cpp	*/
int	irc_loop(t_data* data);

/*	clean.cpp	*/
int	clean_up(t_data* data);

/*	utils.cpp	*/
int		error(int errno_code);
int		error(const char* error_msg);
void	ft_exit(int exit_code);

/*	colors	*/
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m" 
# define RESET "\e[0m"

# endif