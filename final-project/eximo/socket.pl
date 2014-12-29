%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 Sockets                   %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-use_module(library(sockets)).

port(60070).

% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('*SERVER MESSAGE* Connection established.'), nl,
	serverLoop(Stream),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream) :-
	repeat,

	%% receiving message
	read(Stream, ClientMsg),
	write('*SERVER MESSAGE* Received: '), write(ClientMsg), nl, nl,

	%% parsing message
	parseInput(ClientMsg, Reply),
	format(Stream, '~q.~n', [Reply]),

	%% sending message answer
	write('*SERVER MESSAGE* Sent: '), write(Reply), nl, nl,
	flush_output(Stream),

	%% repeat until quit message is received or end of file is reached
	(ClientMsg == quit; ClientMsg == end_of_file), !.

%=============%
%= @@ inputs =%
%=============%
parseInput(add(Arg1, Arg2), Answer) :-
	add(Arg1, Arg2, Answer).

parseInput(quit, 'OK. Connection terminated.'):- !.

%===============%
%= @@ commands =%
%===============%
add(Arg1, Arg2, Answer):-
	Answer is Arg1 + Arg2,
	write('add('), write(Arg1), write(', '), write(Arg2), write(') = '), write(Answer), nl.
