#include <bits/stdc++.h>
using namespace std;

/*
Aim: Design a two people TexHold'em Game

Functional Requirment: 
1. Dealing Cards:
    a. deal 2 cards to each player
    b. display 3 cards at flop
    c. display 1 card at turn
    d. display 1 card at river
2. Make Bets:
    a. allow players to bet at pre-flop, flop, turn, and river.
    b. allow players to check
    c. allow players to raise (but has to be twice at least)
    d. allow players to fold
3. Check winner:
    a. find the best hands that each player can have
        Royal Flush->Quads->Full House->Flush->Straight->Trips->Two Pair->One Pair->High Card

Data Table:
<<Enum:Suits>>
Diamond
Heart
Spade
Club
<<Enum:Round>>
Flop = 0 
Turn = 3
River = 4
End
<<Base Cards>>
suit: Suits
Number:int 
<<Player>>
userID: int
nickname: string
email: string
password: string
balance: int
<<GameToPlayer>>
gameID: int
playerID: int
hand: list<Base Cards>[2] 
<<Game>>
gameID: int
cardDeck: list<Base Cards>[52]
commonCards: list<Base Cards>[5]
progress: Round
potSize: int

MVC pattern is used:
Controller: Run the game, calls deal cards, then let player1 make decision , then player2, then player1 again
            If either one folds, or the game concludes, reshuffle the card and restart the game
Model: 
1) dealCards(GameID)
    reshuffle the deck of 52 cards, deal 1st and 3rd card to player 1
    deal 2nd and 4th card to player 2, leave the following 5 cards hidden
2) flipCards(GameID)
    display the next card depends on the progress
3) makeBet(PlayerID, GameID)
    ask for the player to make action, bet of $0 means check, returns how much the player bet
    if the bet is bigger than the other player's bet (as we call it a raise), the other player has to make action again.
4) getBest(GameID, PlayerID)
    get the best combo that this player can obtain
    return in the form of this:
    1. if royal flush, {9, H} (where H is the highest card in that royal flush)
    2. if quads, {8, H} (where H is the quads card)
    3. if full house, {7, A*100+B} (where A is the trip card, B is the pair card)
    4. if flush, {6, H} (where H is the suit)
    5. if straight, {5, H} (where H is the highest card of the straight)
    6. if trips, {4, H} (where H is the )    
4) concludeGame(GameID)
    pick 5 cards out of two
*/


int main() {
} 