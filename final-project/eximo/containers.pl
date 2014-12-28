%======================================%
%= @@ lists and matrices constructors =%
%======================================%
createMatrixSizeN(0, [[]]).
createMatrixSizeN(N, M):-
	createMatrixSizeN(N, N, M).

createMatrixSizeN(_, 0, []).
createMatrixSizeN(N, I, [Line | RT]):-
	createListSizeN(N, Line),
	I1 is I-1,
	createMatrixSizeN(N, I1, RT).

createListSizeN(0, []).
createListSizeN(N, ['0' | Ls]):-
	N1 is N-1,
	createListSizeN(N1, Ls).

listPushBack([], Elem, [Elem]).
listPushBack([Head|Tail], Elem, [Head|NewTail]):-
	listPushBack(Tail, Elem, NewTail).

getListSize([], 0).
getListSize([_|Tail], Size):-
	getListSize(Tail, TailSize),
	Size is TailSize + 1.

largestList(List1, List2, List1):-
	getListSize(List1, List1Size),
	getListSize(List2, List2Size),
	List1Size > List2Size.
largestList(_, List2, List2).

getLargestListInListOfLists(ListOfLists, LargestList):-
	getLargestListInListOfLists(ListOfLists, [], LargestList).
getLargestListInListOfLists([Head|[]], LargestListSoFar, Head):-
	getListSize(Head, HeadSize),
	getListSize(LargestListSoFar, LargestListSoFarSize),
	HeadSize > LargestListSoFarSize.
getLargestListInListOfLists([_|[]], LargestListSoFar, LargestListSoFar).
getLargestListInListOfLists([Head|Tail], LargestListSoFar, LargestList):-
	getListSize(Head, HeadSize),
	getListSize(LargestListSoFar, LargestListSoFarSize),
	(
		(HeadSize > LargestListSoFarSize) ->
		getLargestListInListOfLists(Tail, Head, LargestList);
		getLargestListInListOfLists(Tail, LargestListSoFar, LargestList)
	).

%======================================%
%= @@ lists and matrices manipulation =%
%======================================%
%%% 1. container; 2. elem at the front.
peekFront([ElemAtTheHead|_], ElemAtTheHead).

%%% 1. element row; 2. element column; 3. matrix; 4. query element.
getMatrixElemAt(0, ElemCol, [ListAtTheHead|_], Elem):-
	getListElemAt(ElemCol, ListAtTheHead, Elem).
getMatrixElemAt(ElemRow, ElemCol, [_|RemainingLists], Elem):-
	ElemRow > 0,
	ElemRow1 is ElemRow-1,
	getMatrixElemAt(ElemRow1, ElemCol, RemainingLists, Elem).

%%% 1. element position; 2. list; 3. query element.
getListElemAt(0, [ElemAtTheHead|_], ElemAtTheHead).
getListElemAt(Pos, [_|RemainingElems], Elem):-
	Pos > 0,
	Pos1 is Pos-1,
	getListElemAt(Pos1, RemainingElems, Elem).

%%% 1. element row; 2. element column; 3. element to use on replacement; 3. current matrix; 4. resultant matrix.
setMatrixElemAtWith(0, ElemCol, NewElem, [RowAtTheHead|RemainingRows], [NewRowAtTheHead|RemainingRows]):-
	setListElemAtWith(ElemCol, NewElem, RowAtTheHead, NewRowAtTheHead).
setMatrixElemAtWith(ElemRow, ElemCol, NewElem, [RowAtTheHead|RemainingRows], [RowAtTheHead|ResultRemainingRows]):-
	ElemRow > 0,
	ElemRow1 is ElemRow-1,
	setMatrixElemAtWith(ElemRow1, ElemCol, NewElem, RemainingRows, ResultRemainingRows).

%%% 1. position; 2. element to use on replacement; 3. current list; 4. resultant list.
setListElemAtWith(0, Elem, [_|L], [Elem|L]).
setListElemAtWith(I, Elem, [H|L], [H|ResL]):-
	I > 0,
	I1 is I-1,
	setListElemAtWith(I1, Elem, L, ResL).

%%% 1. element to be replaced; 2. element to use on replacements; 3. current matrix; 4. resultant matrix.
replaceMatrixElemWith(_, _, [], []).
replaceMatrixElemWith(A, B, [Line|RL], [ResLine|ResRL]):-
	replaceListElemWith(A, B, Line, ResLine),
	replaceMatrixElemWith(A, B, RL, ResRL).

%%% 1. element to be replaced; 2. element to use on replacements; 3. current list; 4. resultant list.
replaceListElemWith(_, _, [], []).
replaceListElemWith(A, B, [A|L1], [B|L2]):-
	replaceListElemWith(A, B, L1, L2).
replaceListElemWith(A, B, [C|L1], [C|L2]):-
	C \= A,
	replaceListElemWith(A, B, L1, L2).

%=========================================%
%= @@ lists and matrices print functions =%
%=========================================%
printMatrix([], _).
printMatrix([Line | Tail], Separator):-
	printList(Line, Separator), nl,
	printMatrix(Tail, Separator).

printList([], _).
printList([Head | Tail], Separator):-
	write(Head), write(Separator),
	printList(Tail, Separator).

printMatrix([]).
printMatrix([Line | Tail]):-
	printList(Line), nl,
	printMatrix(Tail).

printList([]).
printList([Head | Tail]):-
	write(Head),
	printList(Tail).
