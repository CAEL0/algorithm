nexthouse(L, R, [L, R|_]).
nexthouse(L, R, [_|Rest]) :-
    nexthouse(X, Y, Houses);
    nexthouse(Y, X, Houses).

isin(X, [X|_]).
isin(X, [_|Y]) :-
    isin(X, Y).
