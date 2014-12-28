%=======================================%
%=           ..:: EXIMO ::..           =%
%=                                     =%
%=   Type 'eximo.' to start the game   =%
%=                                     =%
%=======================================%
%=                                     =%
%=          ..:: Authors ::..          =%
%=                                     =%
%=  Henrique Ferrolho && Joao Pereira  =%
%=             FEUP - 2014             =%
%=                                     =%
%=======================================%

%===============%
%= @@ includes =%
%===============%
:- use_module(library(random)).
:- use_module(library(system)).
:- include('bot.pl').
:- include('containers.pl').
:- include('gameClass.pl').
:- include('menus.pl').
:- include('utilities.pl').

%====================%
%= @@ game launcher =%
%====================%
eximo:-
	initializeRandomSeed,
	mainMenu.

%===============================%
%= @@ player, pieces and cells =%
%===============================%
player(whitePlayer).
player(blackPlayer).

getPlayerName(whitePlayer, 'White').
getPlayerName(blackPlayer, 'Black').

piece(whitePiece).
piece(blackPiece).

getCellSymbol(emptyCell, ' ').
getCellSymbol(whiteCell, 'O').
getCellSymbol(blackCell, '#').
getCellSymbol(_, '?').

pieceIsOwnedBy(whiteCell, whitePlayer).
pieceIsOwnedBy(blackCell, blackPlayer).

currentPlayerOwnsCell(Row, Col, Game):-
	getGameBoard(Game, Board), getGamePlayerTurn(Game, Player),
	getMatrixElemAt(Row, Col, Board, Cell), pieceIsOwnedBy(Cell, Player).

gameMode(pvp).
gameMode(pvb).
gameMode(bvb).

%======================%
%= @@ main game cycle =%
%======================%
playGame(Game):-
	assertBothPlayersHavePiecesOnTheBoard(Game),
	assertCurrentPlayerCanMove(Game),
	(
		% bot vs. bot
		(getGameMode(Game, Mode), Mode == bvb) -> (
			getGameBoard(Game, Board), getGamePlayerTurn(Game, Player),
			clearConsole, printBoard(Board), printTurnInfo(Player), nl, nl,
			%pressEnterToContinue,
			letRandomBotPlay(Game, TempGame), !,

			getGameBoard(TempGame, TempBoard), getGamePlayerTurn(TempGame, TempPlayer),
			clearConsole, printBoard(TempBoard), printTurnInfo(TempPlayer), nl, nl,
			%pressEnterToContinue,
			letGreedyBotPlay(TempGame, ResultantGame), !,
			playGame(ResultantGame), !
		);
		% player vs. player or player vs. bot
		(
			letHumanPlay(Game, ResultantGame),
			(
				% player vs. player
				(getGameMode(ResultantGame, Mode), Mode == pvp) -> (playGame(ResultantGame), !);

				% player vs. bot
				(letGreedyBotPlay(ResultantGame, BotResultantGame), playGame(BotResultantGame), !)
			)
		)
	).

% game is over when one of the players can not make any kind of move - stalemate
playGame(Game):-
	clearConsole,
	getGameBoard(Game, Board), printBoard(Board),

	% confirm that both players have at least one checker, else the game over is not due to a stalemate
	getGameNumWhitePieces(Game, NumWhitePieces),
	getGameNumBlackPieces(Game, NumBlackPieces),
	NumWhitePieces > 0, NumBlackPieces > 0,

	% check which player won
	getGamePlayerTurn(Game, Player),
	(
		Player == whitePlayer ->
			(write('# Game over. Black player won by stalemating white player, congratulations!'), nl);
		Player == blackPlayer ->
			(write('# Game over. White player won by stalemating black player, congratulations!'), nl);
		(write('# ERROR: unexpected game over and both players have at least one checker.'), nl)
	),
	nl,
	pressEnterToContinue, !.

% game is over when one of the players has no checkers left
playGame(Game):-
	clearConsole,
	getGameBoard(Game, Board), printBoard(Board),

	% get the number of checkers of each player to know who has lost
	getGameNumWhitePieces(Game, NumWhitePieces),
	getGameNumBlackPieces(Game, NumBlackPieces),
	(
		(NumWhitePieces =:= 0, NumBlackPieces > 0) ->
			(write('# Game over. Black player won, congratulations!'), nl);
		(NumWhitePieces > 0, NumBlackPieces =:= 0) ->
			(write('# Game over. White player won, congratulations!'), nl);
		(write('# ERROR: unexpected game over.'), nl)
	),
	nl,
	pressEnterToContinue, !.

letHumanPlay(Game, ResultantGame):-
	getGameBoard(Game, Board), getGamePlayerTurn(Game, Player),

	repeat,

	clearConsole,
	printBoard(Board),
	printTurnInfo(Player), nl, nl,
	getPieceToBeMovedSourceCoords(SrcRow, SrcCol),
	validateChosenPieceOwnership(SrcRow, SrcCol, Board, Player),

	clearConsole,
	printBoard(Board),
	printTurnInfo(Player), nl, nl,
	getPieceToBeMovedDestinyCoords(DestRow, DestCol),
	validateDifferentCoordinates(SrcRow, SrcCol, DestRow, DestCol),

	validateMove(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame),
	changePlayer(TempGame, ResultantGame), !.

%===========================%
%= @@ game input functions =%
%===========================%
getPieceToBeMovedSourceCoords(SrcRow, SrcCol):-
	write('Please insert the coordinates of the piece you wish to move and press <Enter> - example: 3f.'), nl,
	inputCoords(SrcRow, SrcCol), nl.

getPieceToBeMovedDestinyCoords(DestRow, DestCol):-
	write('Please insert the DESTINY coordinates of that piece and press <Enter>.'), nl,
	inputCoords(DestRow, DestCol), nl.

getPieceToBeInsertedDestinyCoords(Row, Col):-
	write('Please insert the coordinates where to place an extra checker and press <Enter>.'), nl,
	inputCoords(Row, Col), nl.

inputCoords(SrcRow, SrcCol):-
	% read row
	getInt(RawSrcRow),

	% read column
	getInt(RawSrcCol),

	% discard enter
	discardInputChar,

	% process row and column
	SrcRow is RawSrcRow-1,
	SrcCol is RawSrcCol-49.

%==============================================%
%= @@ board validation/manipulation functions =%
%==============================================%
assertBothPlayersHavePiecesOnTheBoard(Game):-
	getGameNumWhitePieces(Game, NumWhitePieces),
	getGameNumBlackPieces(Game, NumBlackPieces),
	NumWhitePieces > 0,
	NumBlackPieces > 0, !.

assertCurrentPlayerCanMove(Game):-
	assertCurrentPlayerCanMove(7, Game).
assertCurrentPlayerCanMove(Row, Game):-
	Row >= 0,
	Row1 is Row - 1,
	(
		assertCurrentPlayerCanMove(Row, 7, Game);
		assertCurrentPlayerCanMove(Row1, Game)
	).
assertCurrentPlayerCanMove(Row, Column, Game):-
	Column >= 0,
	Column1 is Column - 1,
	(
		currentPlayerCanMovePieceAt(Row, Column, Game);
		assertCurrentPlayerCanMove(Row, Column1, Game)
	).

currentPlayerCanMovePieceAt(Row, Column, Game):-
	getGamePlayerTurn(Game, Player),
	getGameBoard(Game, Board),

	% check if the piece on this cell is from the current player
	getMatrixElemAt(Row, Column, Board, Cell),
	(
		Player == whitePlayer -> (Cell == whiteCell, Delta is 1);
		Player == blackPlayer -> (Cell == blackCell, Delta is -1)
	),

	NewRow1 is Row + Delta,
	NewRow2 is Row + 2 * Delta,
	NewColL1 is Column - 1,
	NewColR1 is Column + 1,
	NewColL2 is Column - 2,
	NewColR2 is Column + 2,

	% check if that piece can make any move
	(
		testOrdinaryMove(Row, Column, NewRow1, NewColL1, Game);
		testOrdinaryMove(Row, Column, NewRow1, Column, Game);
		testOrdinaryMove(Row, Column, NewRow1, NewColR1, Game);
		testJumpMove(Row, Column, NewRow2, NewColL2, Game);
		testJumpMove(Row, Column, NewRow2, Column, Game);
		testJumpMove(Row, Column, NewRow2, NewColR2, Game);
		testCaptureMove(Row, Column, Row, NewColL2, Game);
		testCaptureMove(Row, Column, NewRow2, NewColL2, Game);
		testCaptureMove(Row, Column, NewRow2, Column, Game);
		testCaptureMove(Row, Column, NewRow2, NewColR2, Game);
		testCaptureMove(Row, Column, Row, NewColR2, Game)
	).

validateChosenPieceOwnership(SrcRow, SrcCol, Board, Player):-
	getMatrixElemAt(SrcRow, SrcCol, Board, Piece),
	pieceIsOwnedBy(Piece, Player), !.
validateChosenPieceOwnership(_, _, _, _):-
	write('INVALID PIECE!'), nl,
	write('A player can only move his/her own pieces.'), nl,
	pressEnterToContinue, nl,
	fail.

validateDifferentCoordinates(SrcRow, SrcCol, DestRow, DestCol):-
	(SrcRow \= DestRow ; SrcCol \= DestCol), !.
validateDifferentCoordinates(_, _, _, _):-
	write('INVALID INPUT!'), nl,
	write('The source and destiny coordinates must be different.'), nl,
	pressEnterToContinue, nl,
	fail.

% tries to validate a move according to it properties
validateMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame):-
	validateOrdinaryMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame);
	validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame);
	validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame);
	(
		getGamePlayerTurn(Game, Player),
		(
			(Mode == pvp; (Mode == pvb, Player == whitePlayer)) -> invalidMove
		)
	).

% ordinary move
validateOrdinaryMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame):-
	getGameBoard(Game, Board),
	getGamePlayerTurn(Game, Player),

	% check if destiny is a forward or diagonally forward adjacent empty cell
	DeltaRow is DestRow - SrcRow,
	DeltaCol is abs(DestCol - SrcCol),
	(
		Player == whitePlayer -> DeltaRow =:= 1, DeltaCol =< 1;
		Player == blackPlayer -> DeltaRow =:= -1, DeltaCol =< 1
	),

	% check if destiny cell is empty
	getMatrixElemAt(DestRow, DestCol, Board, Cell),
	Cell == emptyCell,

	% actually move the checker
	movePiece(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame), !.

% jump move
validateJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame):-
	testJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game),

	% actually move the checker
	DeltaRow is DestRow - SrcRow,
	movePiece(SrcRow, SrcCol, DestRow, DestCol, Game, TempGame), !,

	getGamePlayerTurn(TempGame, Player),
	getGameBoard(TempGame, TempBoard),

	% if that piece can continue to jump, then it must do so
	NewRow is DestRow + DeltaRow,
	NewColL is DestCol - 2,
	NewColR is DestCol + 2,
	(
		(
			testJumpMove(DestRow, DestCol, NewRow, NewColL, TempGame);
			testJumpMove(DestRow, DestCol, NewRow, DestCol, TempGame);
			testJumpMove(DestRow, DestCol, NewRow, NewColR, TempGame)
		) ->
		(
			repeat,

			clearConsole,
			printBoard(TempBoard),
			printTurnInfo(Player),
			write('# If a checker can continue to jump, then it must do so.'), nl, nl,

			getGameMode(Game, Mode), !,
			(
				(Mode == bvb; (Mode == pvb, Player == blackPlayer)) ->
					(random(0, 8, NextDestRow), random(0, 8, NextDestCol));
				getPieceToBeMovedDestinyCoords(NextDestRow, NextDestCol)
			),
			validateDifferentCoordinates(DestRow, DestCol, NextDestRow, NextDestCol),

			setGameBoard(TempBoard, TempGame, ItGame),
			(
				validateJumpMove(DestRow, DestCol, NextDestRow, NextDestCol, ItGame, ResultantGame);
				((Mode == pvp; (Mode == pvb, Player == whitePlayer)) -> invalidMove)
			), !
		);
		ResultantGame = TempGame
	), !.

% capture move
validateCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame):-
	testCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game),

	% actually move the checker and capture the oponent checker
	DeltaRow is DestRow - SrcRow,
	MiddleCellRow is SrcRow + DeltaRow // 2,
	MiddleCellCol is SrcCol + (DestCol - SrcCol) // 2,
	capturePieceAt(MiddleCellRow, MiddleCellCol, Game, CaptTempGame),
	movePiece(SrcRow, SrcCol, DestRow, DestCol, CaptTempGame, TempGame), !,

	getGamePlayerTurn(TempGame, Player),
	getGameBoard(TempGame, TempBoard),

	% if that piece can continue to capture, then it must do so
	(Player == whitePlayer -> NewRow is DestRow + 2; Player == blackPlayer -> NewRow is DestRow - 2),
	NewColL is DestCol - 2,
	NewColR is DestCol + 2,
	(
		(
			testCaptureMove(DestRow, DestCol, DestRow, NewColL, TempGame);
			testCaptureMove(DestRow, DestCol, NewRow, NewColL, TempGame);
			testCaptureMove(DestRow, DestCol, NewRow, DestCol, TempGame);
			testCaptureMove(DestRow, DestCol, NewRow, NewColR, TempGame);
			testCaptureMove(DestRow, DestCol, DestRow, NewColR, TempGame)
		) ->
		(
			repeat,

			clearConsole,
			printBoard(TempBoard),
			printTurnInfo(Player),
			write('# If a checker can continue to capture, then it must do so.'), nl, nl,

			getGameMode(Game, Mode), !,
			(
				(Mode == bvb; (Mode == pvb, Player == blackPlayer)) ->
					(random(0, 8, NextDestRow), random(0, 8, NextDestCol));
				getPieceToBeMovedDestinyCoords(NextDestRow, NextDestCol)
			),
			validateDifferentCoordinates(DestRow, DestCol, NextDestRow, NextDestCol),

			setGameBoard(TempBoard, TempGame, ItGame),
			(
				validateCaptureMove(DestRow, DestCol, NextDestRow, NextDestCol, ItGame, ResultantGame);
				((Mode == pvp; (Mode == pvb, Player == whitePlayer)) -> invalidMove)
			), !
		);
		ResultantGame = TempGame
	), !.

% invalid move
invalidMove:-
	write('INVALID MOVE!'), nl,
	write('A checker can only move to a forward or a diagonally forward (north, north-east or north-west) adjacent empty cell.'), nl,
	write('A checker can jump over a friendly checker if the next cell in the same direction of the jump is empty.'), nl,
	write('Finally, a checker can capture an oponent\'s checker by jumping over them, similarly to the jumping move.'), nl,
	write('In addition to the three possible move/jumping directions, a capture can also occur to the sides (left or right).'), nl,
	pressEnterToContinue, nl,
	fail.

testOrdinaryMove(SrcRow, SrcCol, DestRow, DestCol, Game):-
	getGameBoard(Game, Board),
	getGamePlayerTurn(Game, Player),

	% validate vertical movement
	DeltaRow is DestRow - SrcRow,
	(
		Player == whitePlayer -> DeltaRow =:= 1;
		Player == blackPlayer -> DeltaRow =:= -1
	),

	% validate horizontal movement
	DeltaCol is abs(DestCol - SrcCol),
	DeltaCol =< 1,

	% check if destiny cell is empty
	getMatrixElemAt(DestRow, DestCol, Board, Cell),
	Cell == emptyCell.

testJumpMove(SrcRow, SrcCol, DestRow, DestCol, Game):-
	getGameBoard(Game, Board),
	getGamePlayerTurn(Game, Player),

	% validate vertical movement
	DeltaRow is DestRow - SrcRow,
	(
		Player == whitePlayer -> DeltaRow =:= 2;
		Player == blackPlayer -> DeltaRow =:= -2
	),

	% validate horizontal movement
	DeltaCol is abs(DestCol - SrcCol),
	(DeltaCol =:= 0; DeltaCol =:= 2),

	% check if destiny cell is empty
	getMatrixElemAt(DestRow, DestCol, Board, Cell),
	Cell == emptyCell,

	% check if cell between source and destiny is friendly
	MiddleCellRow is SrcRow + DeltaRow // 2,
	MiddleCellCol is SrcCol + (DestCol - SrcCol) // 2,
	getMatrixElemAt(MiddleCellRow, MiddleCellCol, Board, MiddleCell),
	(
		Player == whitePlayer -> MiddleCell == whiteCell;
		Player == blackPlayer -> MiddleCell == blackCell
	).

testCaptureMove(SrcRow, SrcCol, DestRow, DestCol, Game):-
	getGameBoard(Game, Board),
	getGamePlayerTurn(Game, Player),

	% validate vertical movement
	DeltaRow is DestRow - SrcRow,
	(
		DeltaRow =:= 0;
		Player == whitePlayer -> DeltaRow =:= 2;
		Player == blackPlayer -> DeltaRow =:= -2
	),

	% validate horizontal movement
	DeltaCol is abs(DestCol - SrcCol),
	(DeltaCol =:= 0; DeltaCol =:= 2),

	% check if destiny cell is empty
	getMatrixElemAt(DestRow, DestCol, Board, Cell),
	Cell == emptyCell,

	% check if cell between source and destiny is owned by the oponent
	MiddleCellRow is SrcRow + DeltaRow // 2,
	MiddleCellCol is SrcCol + (DestCol - SrcCol) // 2,
	getMatrixElemAt(MiddleCellRow, MiddleCellCol, Board, MiddleCell),
	(
		Player == whitePlayer -> MiddleCell == blackCell;
		Player == blackPlayer -> MiddleCell == whiteCell
	).

% moves a piece from source to destiny
movePiece(SrcRow, SrcCol, DestRow, DestCol, Game, ResultantGame):-
	% get current board
	getGameBoard(Game, Board),

	% get piece to be moved
	getMatrixElemAt(SrcRow, SrcCol, Board, SrcElem),

	% empty source cell
	setMatrixElemAtWith(SrcRow, SrcCol, emptyCell, Board, TempBoard),

	% place piece on destiny cell
	setMatrixElemAtWith(DestRow, DestCol, SrcElem, TempBoard, ResultantBoard),

	% save the board
	setGameBoard(ResultantBoard, Game, TempGame),

	% if checker reached the other end of the board
	(
		(DestRow =:= 0; DestRow =:= 7) -> (
			capturePieceAt(DestRow, DestCol, TempGame, CaptResultantGame),
			getGamePlayerTurn(CaptResultantGame, Player),

			repeat,
			clearConsole,
			getGameBoard(CaptResultantGame, NewResultantBoard),
			printBoard(NewResultantBoard),
			write('# Your checker has reached the end of the board and has been removed.'), nl,
			(
				dropZoneHasOneEmptyCell(CaptResultantGame, Player) -> (
					write('# If you have enough empty cells on your drop zone, you can place up to two new checkers there.'), nl, nl,

					getGameMode(CaptResultantGame, Mode), !,
					(
						(Mode == bvb; (Mode == pvb, Player == blackPlayer)) ->
							(random(0, 8, ExtraChecker1Row), random(0, 8, ExtraChecker1Col));
						getPieceToBeInsertedDestinyCoords(ExtraChecker1Row, ExtraChecker1Col)
					),
					validateExtraCheckerCoords(ExtraChecker1Row, ExtraChecker1Col, CaptResultantGame, Player),
					insertPieceAt(ExtraChecker1Row, ExtraChecker1Col, CaptResultantGame, Ins1ResultantGame), !,

					repeat,
					clearConsole,
					getGameBoard(Ins1ResultantGame, Ins1ResultantBoard),
					printBoard(Ins1ResultantBoard),
					write('# An extra checker has been placed on the board.'), nl,
					(
						dropZoneHasOneEmptyCell(Ins1ResultantGame, Player) -> (
							write('# You can still place another extra checker on an empty cell.'), nl, nl,

							!,
							(
								(Mode == bvb; (Mode == pvb, Player == blackPlayer)) ->
									(random(0, 8, ExtraChecker2Row), random(0, 8, ExtraChecker2Col));
								getPieceToBeInsertedDestinyCoords(ExtraChecker2Row, ExtraChecker2Col)
							),
							validateExtraCheckerCoords(ExtraChecker2Row, ExtraChecker2Col, Ins1ResultantGame, Player),
							insertPieceAt(ExtraChecker2Row, ExtraChecker2Col, Ins1ResultantGame, ResultantGame), !
						); (
							write('# There are no more empty cells on your drop zone to place the second checker.'), nl, nl,
							pressEnterToContinue,
							ResultantGame = Ins1ResultantGame
						)
					)
				); (
					write('# There are no empty cells on your drop zone.'), nl,
					pressEnterToContinue
				)
			)
		);
			ResultantGame = TempGame
	).

% remove piece at coordinates and update player piece counter
capturePieceAt(Row, Col, Game, ResultantGame):-
	% get current board
	getGameBoard(Game, Board),

	% save captured piece cell
	getMatrixElemAt(Row, Col, Board, CapturedPieceCell),

	% empty captured piece cell
	setMatrixElemAtWith(Row, Col, emptyCell, Board, ResultantBoard),

	% save the board
	setGameBoard(ResultantBoard, Game, TempGame),

	% decrement player number of pieces according to the captured piece cell type
	(
		CapturedPieceCell == whiteCell -> decNumWhitePieces(TempGame, ResultantGame);
		CapturedPieceCell == blackCell -> decNumBlackPieces(TempGame, ResultantGame);
		CapturedPieceCell == emptyCell -> ResultantGame = TempGame
	), !.

% true when the drop zone of the specified player has at least one empty cell
dropZoneHasOneEmptyCell(Game, Player):-
	getGameBoard(Game, Board),

	(
		Player == whitePlayer -> (
			scanDropZone(0, Board); scanDropZone(1, Board);
			cellIsEmpty(2, 1, Board); cellIsEmpty(2, 2, Board); cellIsEmpty(2, 5, Board); cellIsEmpty(2, 6, Board)
		); Player == blackPlayer -> (
			cellIsEmpty(5, 1, Board); cellIsEmpty(5, 2, Board); cellIsEmpty(5, 5, Board); cellIsEmpty(5, 6, Board);
			scanDropZone(6, Board); scanDropZone(7, Board)
		); (
			write('ERROR: unexpected player at dropZoneHasOneEmptyCell()'), nl
		)
	).

scanDropZone(Row, Board):-
	scanDropZone(Row, 6, Board).
scanDropZone(Row, Col, Board):-
	Col > 0,
	Col1 is Col-1,
	(cellIsEmpty(Row, Col, Board); scanDropZone(Row, Col1, Board)).

validateExtraCheckerCoords(Row, Col, Game, Player):-
	getGameBoard(Game, Board),
	cellIsEmpty(Row, Col, Board),
	(
		Player == whitePlayer -> (
			((Row =:= 0; Row =:= 1), Col > 0, Col < 7);
			(Row =:= 2, (Col =:= 1; Col =:= 2; Col =:= 5; Col =:= 6))
		); Player == blackPlayer -> (
			(Row =:= 5, (Col =:= 1; Col =:= 2; Col =:= 5; Col =:= 6));
			((Row =:= 6; Row =:= 7), Col > 0, Col < 7)
		)
	).
validateExtraCheckerCoords(_, _, Game, Player):-
	getGameMode(Game, Mode),
	(Mode == pvp; (Mode == pvb, Player == whitePlayer)),
	write('INVALID CELL!'), nl,
	write('Extra checkers can only be placed on empty cells inside your drop zone.'), nl,
	pressEnterToContinue,
	fail.

cellIsEmpty(Row, Column, Board):-
	% write('scanning row, col: '), write(Row), write(', '), write(Column), nl,
	getMatrixElemAt(Row, Column, Board, Cell),
	Cell == emptyCell.

% insert piece at coordinates and update player piece counter
insertPieceAt(Row, Col, Game, ResultantGame):-
	% get current board
	getGameBoard(Game, Board),

	% figure which piece to insert based on player turn
	getGamePlayerTurn(Game, Player),
	(
		Player == whitePlayer -> Cell = whiteCell;
		Cell = blackCell
	),

	% insert piece
	setMatrixElemAtWith(Row, Col, Cell, Board, ResultantBoard),

	% save the board
	setGameBoard(ResultantBoard, Game, TempGame),

	% increment player number of pieces according to the captured piece cell type
	(
		Cell == whiteCell -> incNumWhitePieces(TempGame, ResultantGame);
		Cell == blackCell -> incNumBlackPieces(TempGame, ResultantGame);
		Cell == emptyCell -> ResultantGame = TempGame
	), !.

%%% 1. current player; 2. next player.
changePlayer(Game, ResultantGame):-
	getGamePlayerTurn(Game, Player),
	(
		Player == whitePlayer ->
			NextPlayer = blackPlayer;
		NextPlayer = whitePlayer
	),
	setGamePlayerTurn(NextPlayer, Game, ResultantGame).

%===============================%
%= @@ board printing functions =%
%===============================%
%%% prints the name of the player of the current turn
printTurnInfo(Player):-
	getPlayerName(Player, PlayerName),
	write('# It is '), write(PlayerName), write(' player\'s turn to play.'), nl, !.

printBoard([Line | Tail]):-
	printColumnIdentifiers, nl,
	printInitialSeparator, nl,
	rowIdentifiersList(RowIdentifiers),
	printRemainingBoard([Line | Tail], RowIdentifiers),
	nl, !.

printColumnIdentifiers:-
	write('        a     b     c     d     e     f     g     h').

printInitialSeparator:-
	write('      _______________________________________________').

rowIdentifiersList(['  1  ', '  2  ', '  3  ', '  4  ', '  5  ', '  6  ', '  7  ', '  8  ']).

printRemainingBoard([], []).
printRemainingBoard([Line | Tail], [RowIdentifiersListHead | RowIdentifiersListTail]):-
	printBoardRow(Line, RowIdentifiersListHead),
	printRemainingBoard(Tail, RowIdentifiersListTail).

printBoardRow([], []).
printBoardRow(Line, RowIdentifiersListHead):-
	length(Line, Length),
	createSeparatorN(Length, '_____|', Separator),
	createSeparatorN(Length, '     |', Separator2),
	write('     '), write('|'), printList(Separator2), nl,
	write(RowIdentifiersListHead), write('|'), printBoardRowValues(Line), nl,
	write('     '), write('|'), printList(Separator), nl.

createSeparatorN(0, _, []).
createSeparatorN(N, SS, [SS | Ls]):-
	N1 is N-1,
	createSeparatorN(N1, SS, Ls).

printBoardRowValues([]).
printBoardRowValues([Head | Tail]):-
	getCellSymbol(Head, Piece),
	write('  '), write(Piece), write('  |'),
	printBoardRowValues(Tail).
