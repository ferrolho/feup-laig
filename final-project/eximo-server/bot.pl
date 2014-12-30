letRandomBotPlay(Game, ResultantGame):-
	% get moveable piece
	repeat,
	random(0, 8, Row), random(0, 8, Col),
	currentPlayerCanMovePieceAt(Row, Col, Game), !,

	getGamePlayerTurn(Game, Player),
	(Player == whitePlayer -> Delta is 1; Delta is -1),

	NewRow1 is Row + Delta,
	NewRow2 is Row + 2 * Delta,
	NewColL1 is Col - 1,
	NewColR1 is Col + 1,
	NewColL2 is Col - 2,
	NewColR2 is Col + 2,

	% check if that piece can make any move
	(
		testOrdinaryMove(Row, Col, NewRow1, NewColL1, Game);
		testOrdinaryMove(Row, Col, NewRow1, Col, Game);
		testOrdinaryMove(Row, Col, NewRow1, NewColR1, Game);
		testJumpMove(Row, Col, NewRow2, NewColL2, Game);
		testJumpMove(Row, Col, NewRow2, Col, Game);
		testJumpMove(Row, Col, NewRow2, NewColR2, Game);
		testCaptureMove(Row, Col, Row, NewColL2, Game);
		testCaptureMove(Row, Col, NewRow2, NewColL2, Game);
		testCaptureMove(Row, Col, NewRow2, Col, Game);
		testCaptureMove(Row, Col, NewRow2, NewColR2, Game);
		testCaptureMove(Row, Col, Row, NewColR2, Game)
	), !,

	% make a random move
	repeat,
	random(0, 11, Move),
	(
		(Move =:= 0, validateMove(Row, Col, NewRow1, NewColL1, Game, TempGame));
		(Move =:= 1, validateMove(Row, Col, NewRow1, Col, Game, TempGame));
		(Move =:= 2, validateMove(Row, Col, NewRow1, NewColR1, Game, TempGame));
		(Move =:= 3, validateMove(Row, Col, NewRow2, NewColL2, Game, TempGame));
		(Move =:= 4, validateMove(Row, Col, NewRow2, Col, Game, TempGame));
		(Move =:= 5, validateMove(Row, Col, NewRow2, NewColR2, Game, TempGame));
		(Move =:= 6, validateMove(Row, Col, Row, NewColL2, Game, TempGame));
		(Move =:= 7, validateMove(Row, Col, NewRow2, NewColL2, Game, TempGame));
		(Move =:= 8, validateMove(Row, Col, NewRow2, Col, Game, TempGame));
		(Move =:= 9, validateMove(Row, Col, NewRow2, NewColR2, Game, TempGame));
		(Move =:= 10, validateMove(Row, Col, Row, NewColR2, Game, TempGame));
		fail
	), !,

	changePlayer(TempGame, ResultantGame), !.

letGreedyBotPlay(Game, ResultantGame):-
	% get moveable piece
	repeat,
	random(0, 8, Row), random(0, 8, Col),
	currentPlayerCanMovePieceAt(Row, Col, Game), !,

	getGamePlayerTurn(Game, Player),
	(Player == whitePlayer -> Delta is 1; Delta is -1),

	NewRow1 is Row + Delta,
	NewRow2 is Row + 2 * Delta,
	NewColL1 is Col - 1,
	NewColR1 is Col + 1,
	NewColL2 is Col - 2,
	NewColR2 is Col + 2,

	% check if that piece can make any move
	(
		testOrdinaryMove(Row, Col, NewRow1, NewColL1, Game);
		testOrdinaryMove(Row, Col, NewRow1, Col, Game);
		testOrdinaryMove(Row, Col, NewRow1, NewColR1, Game);
		testJumpMove(Row, Col, NewRow2, NewColL2, Game);
		testJumpMove(Row, Col, NewRow2, Col, Game);
		testJumpMove(Row, Col, NewRow2, NewColR2, Game);
		testCaptureMove(Row, Col, Row, NewColL2, Game);
		testCaptureMove(Row, Col, NewRow2, NewColL2, Game);
		testCaptureMove(Row, Col, NewRow2, Col, Game);
		testCaptureMove(Row, Col, NewRow2, NewColR2, Game);
		testCaptureMove(Row, Col, Row, NewColR2, Game)
	), !,

	% make a random move
	repeat,
	random(0, 11, Move),
	(
		(Move =:= 0, validateMove(Row, Col, NewRow1, NewColL1, Game, TempGame));
		(Move =:= 1, validateMove(Row, Col, NewRow1, Col, Game, TempGame));
		(Move =:= 2, validateMove(Row, Col, NewRow1, NewColR1, Game, TempGame));
		(Move =:= 3, validateMove(Row, Col, NewRow2, NewColL2, Game, TempGame));
		(Move =:= 4, validateMove(Row, Col, NewRow2, Col, Game, TempGame));
		(Move =:= 5, validateMove(Row, Col, NewRow2, NewColR2, Game, TempGame));
		(Move =:= 6, validateMove(Row, Col, Row, NewColL2, Game, TempGame));
		(Move =:= 7, validateMove(Row, Col, NewRow2, NewColL2, Game, TempGame));
		(Move =:= 8, validateMove(Row, Col, NewRow2, Col, Game, TempGame));
		(Move =:= 9, validateMove(Row, Col, NewRow2, NewColR2, Game, TempGame));
		(Move =:= 10, validateMove(Row, Col, Row, NewColR2, Game, TempGame));
		fail
	), !,

	changePlayer(TempGame, ResultantGame), !.

getGreedyMove(Game, CheckerCoords, MovesList):-
	getGreedyCapture(Game, CheckerCoords, MovesList);
	getRandomMove(Game, CheckerCoords, MovesList).

getGreedyCapture(Game, CheckerCoords, MovesList):-
	% initialize Best with (-1, -1)
	createPoint2D(-1, -1, Best),
	BestMoves = [],

	% scan entire board to find the best greedy capture
	lookForBestGreedyCapture(Game, Best, BestMoves, NewBest, NewBestMoves),

	getPoint2Dx(NewBest, X), getPoint2Dx(NewBest, Y),
	(
		% if best is still (-1, -1), there is no greedy capture
		(X =:= -1, Y =:= -1) -> fail;

		% else, return best and its moves list
		(CheckerCoords = NewBest, MovesList = NewBestMoves)
	).

lookForBestGreedyCapture(Game, Best, BestMoves, NewBest, NewBestMoves):-
	lookForBestGreedyCapture(Game, 7, Best, BestMoves, NewBest, NewBestMoves).
lookForBestGreedyCapture(Game, Row, Best, BestMoves, NewBest, NewBestMoves):-
	Row >= 0, Row1 is Row - 1,
	(
		lookForBestGreedyCapture(Game, Row, 7, Best, BestMoves, NewBest, NewBestMoves);
		lookForBestGreedyCapture(Game, Row1, Best, BestMoves, NewBest, NewBestMoves)
	).
lookForBestGreedyCapture(Game, Row, Col, Best, BestMoves, NewBest, NewBestMoves):-
	Col >= 0, Col1 is Col - 1,
	(
		(
			currentPlayerOwnsCell(Row, Col, Game),

			checkerCanCapture(Row, Col, Game, TestCellMoves),

			getListSize(BestMoves, BestMovesSize),
			getListSize(TestCellMoves, TestCellMovesSize),

			% if no best yet or a new best was found, return it
			(BestMovesSize =:= 0; (TestCellMovesSize > BestMovesSize)) ->
				(createPoint2D(Row, Col, NewBest), NewBestMoves = TestCellMoves)
		);
		lookForBestGreedyCapture(Game, Row, Col1, Best, BestMoves, NewBest, NewBestMoves)
	).

checkerCanCapture(Row, Col, Game, LargestMovesList):-
	% get piece on cell, confirm it is a piece
	getGameBoard(Game, Board), getMatrixElemAt(Row, Col, Board, Cell), piece(Cell),
	checkerCanCapture(Row, Col, Cell, Game, LargestMovesList).
checkerCanCapture(Row, Col, Cell, Game, LargestMovesList):-
	% calculate delta: sense the checker can move
	(Cell == whitePiece -> Delta is 1; Delta is -1),

	TestRow is Row + 2 * Delta,
	TestLeftCol is Col - 2,
	TestRightCol is Col + 2,

	% check if that piece can make any move
	(
		(
			checkerCanCapture(Row, Col, Row, TestLeftCol, Cell, Game, MovesList1) ->
			TempMovesList1 = MovesList1;
			TempMovesList1 = []
		), (
			checkerCanCapture(Row, Col, TestRow, TestLeftCol, Cell, Game, MovesList2) ->
			largestList(TempMovesList1, MovesList2, TempMovesList2);
			TempMovesList2 = TempMovesList1
		), (
			checkerCanCapture(Row, Col, TestRow, Col, Cell, Game, MovesList3) ->
			largestList(TempMovesList2, MovesList3, TempMovesList3);
			TempMovesList3 = TempMovesList2
		), (
			checkerCanCapture(Row, Col, TestRow, TestRightCol, Cell, Game, MovesList4) ->
			largestList(TempMovesList3, MovesList4, TempMovesList4);
			TempMovesList4 = TempMovesList3
		), (
			checkerCanCapture(Row, Col, Row, TestRightCol, Cell, Game, MovesList5) ->
			largestList(TempMovesList4, MovesList5, LargestMovesList);
			LargestMovesList = TempMovesList4
		)
	).
%checkerCanCapture(SrcRow, SrcCol, DestRow, DestCol, Cell, Game, LargestMovesList):-
checkerCanCapture(SrcRow, SrcCol, DestRow, DestCol, Cell, Game, _):-
	getGameBoard(Game, Board),

	% calculate delta: sense the checker can move
	(Cell == whitePiece -> Delta is 1; Delta is -1),

	% validate vertical movement
	DeltaRow is DestRow - SrcRow,
	(DeltaRow =:= 0; DeltaRow =:= 2 * Delta),

	% validate horizontal movement
	DeltaCol is abs(DestCol - SrcCol),
	(DeltaCol =:= 0; DeltaCol =:= 2),

	% assert destiny cell is empty
	getMatrixElemAt(DestRow, DestCol, Board, DestCell), not(piece(DestCell)),

	% assert cell between source and destiny is owned by the oponent
	MiddleCellRow is SrcRow + DeltaRow // 2,
	MiddleCellCol is SrcCol + (DestCol - SrcCol) // 2,
	getMatrixElemAt(MiddleCellRow, MiddleCellCol, Board, MiddleCell),
	piece(MiddleCell), MiddleCell \== Cell,

	% push back coords to moves list
	!.
