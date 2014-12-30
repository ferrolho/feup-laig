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
	serverLoop(Stream),
	socket_server_close(Socket).

%==================%
%= @@ server REPL =%
%==================%
serverLoop(Stream):-
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
parseInput(initialize, Answer):-
	initialize(Game),
	Answer = ok(Game), !.

parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	assertBothPlayersHavePiecesOnTheBoard(Game),
	assertCurrentPlayerCanMove(Game),

	getGameBoard(Game, Board), getGamePlayerTurn(Game, Player),

	repeat,

	clearConsole,
	printBoard(Board),
	printTurnInfo(Player), nl, nl,
	validateChosenPieceOwnership(SrcRow, SrcCol, Board, Player),

	clearConsole,
	printBoard(Board),
	printTurnInfo(Player), nl, nl,
	validateDifferentCoordinates(SrcRow, SrcCol, DestRow, DestCol),

	validateMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	changePlayer(TempGame, ResultantGame),

	Answer = ok(ResultantGame), !.

parseInput(quit, Answer):-
	Answer = ok(connection_terminated), !.

parseInput(_, Answer):-
	write('Unknown command received. Command ignored.'), nl,
	Answer = invalid(unknown_command), !.

%===============%
%= @@ commands =%
%===============%
initialize(Game):-
	createPvPGame(Game).

move(Source, Destiny, Answer):-
	Answer is Arg1 + Arg2,
	write('add('), write(Arg1), write(', '), write(Arg2), write(') = '), write(Answer), nl.
