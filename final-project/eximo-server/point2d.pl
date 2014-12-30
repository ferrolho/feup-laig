%===============%
%= @@ point 2d =%
%===============%
createPoint2D(NewPoint):-
	Point = [0, 0], !.
createPoint2D(X, Y, NewPoint):-
	Point = [X, Y], !.

getPoint2Dx(Point, X):-
	getListElemAt(0, Point, X).
getPoint2Dy(Point, Y):-
	getListElemAt(1, Point, Y).

setPoint2Dx(Point, X, NewPoint):-
	setListElemAt(0, X, Point, NewPoint).
setPoint2Dy(Point, Y, NewPoint):-
	setListElemAt(1, Y, Point, NewPoint).
