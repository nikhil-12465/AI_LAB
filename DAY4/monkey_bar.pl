% Monkey and Banana Problem (Final Working Version)

% State representation:
% state(MonkeyPosition, BoxPosition, MonkeyOnBox?, HasBanana?)

% Initial and goal states
initial(state(at_door, at_window, on_floor, has_not)).
goal(state(_, _, _, has)).

% --- Moves ---

% Monkey walks on the floor
move(state(at_door, Box, on_floor, Has), walk(at_door, at_window),
     state(at_window, Box, on_floor, Has)).
move(state(at_window, Box, on_floor, Has), walk(at_window, at_middle),
     state(at_middle, Box, on_floor, Has)).
move(state(at_door, Box, on_floor, Has), walk(at_door, at_middle),
     state(at_middle, Box, on_floor, Has)).

% Monkey pushes box (only if at same place)
move(state(Place, Place, on_floor, Has), push(Place, NewPlace),
     state(NewPlace, NewPlace, on_floor, Has)).

% Monkey climbs on the box
move(state(Place, Place, on_floor, Has), climb,
     state(Place, Place, on_box, Has)).

% Monkey grabs the banana if at middle, on box, and doesn’t have it yet
move(state(at_middle, at_middle, on_box, has_not), grab,
     state(at_middle, at_middle, on_box, has)).

% --- Path search with visited check ---
path(State, Path) :- path(State, [], Path).

path(State, _, []) :-
    goal(State), !.

path(State, Visited, [Action | Rest]) :-
    move(State, Action, NextState),
    \+ member(NextState, Visited),
    path(NextState, [NextState | Visited], Rest).