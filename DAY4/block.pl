% --- Representation ---
% A block world state is represented as a list of stacks.
% Example: [[a,b], [c]] means stack1: a on b, stack2: c alone.

% --- Move rules ---

% move(+State, -NextState)
% Move the top block from one stack to another.
move(State, NextState) :-
    select([Top|Rest1], State, Temp),     % Pick a stack with at least one block
    select(Dest, Temp, Temp2),            % Pick a destination stack
    append([[Top|Dest]], [Rest1|Temp2], NextState). % Move block

% --- Goal test ---
goal(State, Goal) :-
    State = Goal.

% --- Example initial and goal states ---
initial([[a,b,c], [d]]).
goal_state([[a,b], [c,d]]).

% --- Search ---
solve :-
    initial(Init),
    goal_state(Goal),
    path(Init, Goal, [Init]).

% --- Recursive path finder ---
path(State, Goal, _) :-
    goal(State, Goal),
    write('Goal reached: '), write(State), nl.

path(State, Goal, Visited) :-
    move(State, Next),
    \+ member(Next, Visited),        % Avoid revisiting states
    write('Moving to: '), write(Next), nl,
    path(Next, Goal, [Next|Visited]).