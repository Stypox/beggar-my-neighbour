This project contains an algorithm that, given the cards of two players, calculates how many rounds it took a player to win the game.
Basically, the algorithm simulates a two-players Beggar-My-Neighbour game: https://en.wikipedia.org/wiki/Beggar-my-neighbour
I want to find an infinite game: this happens when, after some rounds, the deck of both players is equal to the one they had at the start.
But since there are ~10^20 possible games (See https://math.stackexchange.com/questions/2688331/beggar-my-neighbour-possible-games ), I can't test all of them, so I want to use evolution to get longer games and maybe find an infinite one

File management library: https://github.com/Stypox/Marks-Management-3