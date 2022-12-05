#include "irc.hpp"

/*********************** CONSTRUCTION / DESTRUCTION ****************************/

User::User(void) : _fd(0) {}

User::User(int fd) : _fd(fd), _first_msg(true) {}

User::~User(void) {}


/**************************** GETTER / SETTER **********************************/

int	User::getFd(void) const {return _fd;}

std::string	User::getClientMsg(void) const {return _client_msg;}


/**************************** PRIVATE METHODS **********************************/

int	User::send_welcome_reply(void)
{
	int			return_code;
	std::string	msg;
	
	msg = RPL_WELCOME + RPL_YOURHOST + RPL_CREATED;
	return_code = send(_fd, msg.c_str(), msg.length(), 0);
	if (return_code < 0)
		return (error(errno));
	return EXIT_SUCCESS;
}

void	User::remove_line(int times)
{
	size_t					crlf_pos;
	std::string::iterator	from;
	std::string::iterator	to;

	for (int i = 0; i < times; i++)
	{
		crlf_pos = _client_msg.find("\r\n", 0) + 2;
		from = _client_msg.begin();
		to = _client_msg.begin() + crlf_pos;
		_client_msg.erase(from, to);
	}
}		

/* NOTE:	This requires 3x'crlf' and probably won't work with only one	*/
/*			yet, so this may result in an occasional undefined behaviour	*/
int	User::process_handshake(void)
{
	size_t	pre_pos;
	size_t	suf_pos;

	/* NICK_NAME */
	pre_pos = _client_msg.find("NICK") + static_cast<std::string>("NICK ").length();
	suf_pos = _client_msg.find("\r\n", pre_pos);
	_nick_name = _client_msg.substr(pre_pos, suf_pos - pre_pos);
	// std::cout << "_nick_name:\t";										//debug
	// print_str_with_crlf(_nick_name.c_str());							//debug
	// NEWLINE();															//debug

	/* USER_NAME */
	pre_pos = _client_msg.find("USER") + static_cast<std::string>("USER ").length();
	suf_pos = _client_msg.find(" ", pre_pos);
	_user_name = _client_msg.substr(pre_pos, suf_pos - pre_pos);
	// std::cout << "_user_name:\t";										//debug
	// print_str_with_crlf(_user_name.c_str());							//debug
	// NEWLINE();															//debug

	/* USER_MODE */
	_user_mode = std::strtod(&_client_msg[suf_pos + 1], NULL);
	// std::cout << "_user_mode:\t" << _user_mode << std::endl;			//debug

	/* REAL_NAME */
	pre_pos = _client_msg.find(":", pre_pos) + 1;
	suf_pos = _client_msg.find("\r\n", pre_pos);
	_real_name = _client_msg.substr(pre_pos, suf_pos - pre_pos);
	// std::cout << "_real_name:\t";										//debug
	// print_str_with_crlf(_real_name.c_str());							//debug
	// NEWLINE();															//debug
	remove_line(3);
	if (send_welcome_reply() == EXIT_FAILURE)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int	User::initiate_handshake(std::string msg)
{
	int		crlf_count = 0;
	int		cmd_count = 0;
	u_long	pos = 0;

	while (pos != NPOS)
	{
		pos = msg.find("\r\n", pos);
		if (pos != NPOS)
		{
			crlf_count++;
			pos += 2;
		}
	}
	if (crlf_count == 1 || crlf_count == 3)
	{
		if (msg.find("CAP") != NPOS)
			cmd_count++;
		if (msg.find("NICK") != NPOS)
			cmd_count++;
		if (msg.find("USER") != NPOS)
			cmd_count++;
	}
	if (cmd_count == 3)
	{
		if (process_handshake() == EXIT_FAILURE)
			return EXIT_FAILURE;
		_first_msg = false;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}


/***************************** PUBLIC METHODS **********************************/

int	User::process_msg(const char* msg)
{
	_client_msg.append(msg);
	if (_first_msg == true && initiate_handshake(_client_msg) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}