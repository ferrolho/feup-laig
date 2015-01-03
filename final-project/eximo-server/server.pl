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
%% @@ initialize
parseInput(initialize, Answer):-
	initialize(Game),
	Answer = ok(Game), !.

%% @@ game over
parseInput(gameOver(Game), Answer):-
	assertBothPlayersHavePiecesOnTheBoard(Game),
	assertCurrentPlayerCanMove(Game),
	Answer = invalid, !.

parseInput(gameOver(_), Answer):-
	Answer = ok, !.

%% @@ move
parseInput(validateSrc(SrcRow, SrcCol, _, _, Game), Answer):-
	getGameBoard(Game, Board), getGamePlayerTurn(Game, Player),
	validateChosenPieceOwnership(SrcRow, SrcCol, Board, Player),
	Answer = ok, !.
parseInput(validateSrc(_, _, _, _, _), Answer):-
	Answer = invalid, !.

%%%%%%%%%%%%%%%%%
parseInput(move(SrcRow, SrcCol, DestRow, DestCol, _), Answer):-
	\+ validateDifferentCoordinates(SrcRow, SrcCol, DestRow, DestCol),
	Answer = invalid, !.

parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	getGamePlayerTurn(ResultantGame, Player),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive2Checkers(ResultantGame), !.
parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame),
	complexJumpMovePossible(SrcRow, SrcCol, DestRow, DestCol, ResultantGame),
	Answer = continueJump(ResultantGame), !.

parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	getGamePlayerTurn(ResultantGame, Player),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive2Checkers(ResultantGame), !.
parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame),
	complexCaptureMovePossible(SrcRow, SrcCol, DestRow, DestCol, ResultantGame),
	Answer = continueCapture(ResultantGame), !.

parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	getGamePlayerTurn(ResultantGame, Player),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive2Checkers(ResultantGame), !.
parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(move(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	changePlayer(TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.

%%%%%%%%%%%%%
parseInput(jump(SrcRow, SrcCol, DestRow, DestCol, _), Answer):-
	\+ validateDifferentCoordinates(SrcRow, SrcCol, DestRow, DestCol),
	Answer = invalid, !.

parseInput(jump(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	getGamePlayerTurn(ResultantGame, Player),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive2Checkers(ResultantGame), !.
parseInput(jump(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(jump(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame),
	complexJumpMovePossible(SrcRow, SrcCol, DestRow, DestCol, ResultantGame),
	Answer = continueJump(ResultantGame), !.

parseInput(jump(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	getGamePlayerTurn(ResultantGame, Player),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive2Checkers(ResultantGame), !.
parseInput(jump(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(jump(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	changePlayer(TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.

%%%%%%%%%%%%
parseInput(capture(SrcRow, SrcCol, DestRow, DestCol, _), Answer):-
	\+ validateDifferentCoordinates(SrcRow, SrcCol, DestRow, DestCol),
	Answer = invalid, !.

parseInput(capture(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	getGamePlayerTurn(ResultantGame, Player),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive2Checkers(ResultantGame), !.
parseInput(capture(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(capture(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame),
	complexCaptureMovePossible(SrcRow, SrcCol, DestRow, DestCol, ResultantGame),
	Answer = continueCapture(ResultantGame), !.

parseInput(capture(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	getGamePlayerTurn(ResultantGame, Player),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive2Checkers(ResultantGame), !.
parseInput(capture(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	(DestRow =:= 0; DestRow =:= 7),
	capturePieceAt(DestRow, DestCol, TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(capture(SrcRow, SrcCol, DestRow, DestCol, Game), Answer):-
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	changePlayer(TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.

%% @@ insert checkers
parseInput(place2Checkers(Row, Col, Game), Answer):-
	getGamePlayerTurn(Game, Player),
	validateExtraCheckerCoords(Row, Col, Game, Player),
	insertPieceAt(Row, Col, Game, ResultantGame),
	dropZoneHasOneEmptyCell(ResultantGame, Player),
	Answer = receive1Checker(ResultantGame), !.
parseInput(place2Checkers(Row, Col, Game), Answer):-
	getGamePlayerTurn(Game, Player),
	validateExtraCheckerCoords(Row, Col, Game, Player),
	insertPieceAt(Row, Col, Game, TempGame),
	changePlayer(TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(place2Checkers(_, _, _), Answer):-
	Answer = invalid, !.

parseInput(place1Checker(Row, Col, Game), Answer):-
	getGamePlayerTurn(Game, Player),
	validateExtraCheckerCoords(Row, Col, Game, Player),
	insertPieceAt(Row, Col, Game, TempGame),
	changePlayer(TempGame, ResultantGame),
	Answer = ok(ResultantGame), !.
parseInput(place1Checker(_, _, _), Answer):-
	Answer = invalid, !.

%% @@ quit
parseInput(quit, Answer):-
	Answer = ok(connection_terminated), !.

%% @@ others
parseInput(_, Answer):-
	write('Unknown command received. Command ignored.'), nl,
	Answer = invalid(unknown_command), !.

%===============%
%= @@ commands =%
%===============%
initialize(Game):-
	createPvPGame(Game).
