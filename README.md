# ft_irc
[group project with [@eschirni](https://github.com/eschirni)]

This project was about creating an IRC server in C++, fully compatible with an official client.
The Internet is ruled by solid standards protocols that allow connected computers to interact
with each other. It’s always a good thing to know.

Internet Relay Chat or IRC is a text-based communication protocol on the Internet.
It offers real-time messaging that can be either public or private. Users can exchange
direct messages and join group channels.
IRC clients connect to IRC servers in order to join channels. IRC servers are connected
together to form a network.

![image](https://github.com/cptbboy/irc/assets/68233391/2ed59ec4-d612-43fc-848a-c61aad23f14e)

## Usage
``make``

``./ircserv <port> <password>``

``port``: the port number on which your IRC server will be listening to for incoming
IRC connections.

``password``: The connection password. It will be needed by any IRC client that tries
to connect to your server.

Once the server is running you can connect to it via an IRC-Client such as [this](https://weechat.org/) one
