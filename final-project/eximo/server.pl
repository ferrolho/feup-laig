%===========================================%
%=         ..:: EXIMO SERVER ::..          =%
%=                                         =%
%=   Type 'server.' to launch the server   =%
%=                                         =%
%===========================================%
%=                                         =%
%=            ..:: Authors ::..            =%
%=                                         =%
%=    Henrique Ferrolho && Joao Pereira    =%
%=               FEUP - 2014               =%
%=                                         =%
%===========================================%

%===============%
%= @@ includes =%
%===============%
:-use_module(library(sockets)).
:- include('eximo.pl').

port(60070).

%======================%
%= @@ server launcher =%
%======================%
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('*SERVER MESSAGE* Connection established.'), nl,
	serverLoop(Stream, _),
	socket_server_close(Socket).

%==================%
%= @@ server REPL =%
%==================%
serverLoop(Stream, Game):-
	repeat,

	%% receiving message
	read(Stream, ClientMsg),
	write('*SERVER MESSAGE* Received: '), write(ClientMsg), nl, nl,

	%% parsing message
	parseInput(ClientMsg, Reply, Game),
	format(Stream, '~q.~n', [Reply]),

	%% sending message answer
	write('*SERVER MESSAGE* Sent: '), write(Reply), nl, nl,
	flush_output(Stream),

	%% repeat until quit message is received or end of file is reached
	(ClientMsg == quit; ClientMsg == end_of_file), !.

%=============%
%= @@ inputs =%
%=============%
parseInput(initialize, Answer, _):-
	initialize(Answer), !.

parseInput(move(Source, Destiny), Answer, _):-
	move(Source, Destiny, Answer), !.

parseInput(quit, 'OK. Connection terminated.', _):- !.

parseInput(_, 'Unknown command.', _):-
	write('Unknown command received. Command ignored.'), nl, !.

%===============%
%= @@ commands =%
%===============%
initialize(Game):-
	createPvPGame(Game).

move(Source, Destiny, Answer):-
	Answer is Arg1 + Arg2,
	write('add('), write(Arg1), write(', '), write(Arg2), write(') = '), write(Answer), nl.
