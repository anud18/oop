/* Copyright (c) 2005 by The National Chengchi Univ. All Rights Reserved */

#include "SHGame.h"
#include "SHPlayer.h"
#include "SHDealer.h"
#include<iostream>

// only constructor
// Must be given a valid (initialized) game player and dealer
// Menu is constructed internally to provide basic text interface
// We must use an initialization list here.
SHGame::SHGame(SHPlayer& shp, SHDealer& shd)
    : menu(sizeof(menuItems)/sizeof(char*), menuItems),
    player(shp),dealer(shd)
{
}


// one run of the game
// take and process a user action
// show current hands for both players at the end of a run.
    bool
SHGame::oneRun()
{
    if(first_time){
        restart();
        first_time = false;
    }
    player.showCards();
    dealer.showCards();
    menu.print();
    int command = menu.getAnswer();
    switch(command){
        case 1:
            moreCard();
            break;
        case 2:
            giveUp();
            break;
        case 3:
            restart();
            break;
        case 4:
            return false;
    }
    //to be completed : show name and card
    if(ended)
        dealer.openFirstCard();

    return true; 
}


// give the player and dealer one more card
// check if we can do that first.
// and judge who has win the round if the player have 5 cards
    void
SHGame::moreCard()
{
    if((player.getNumCards() < 5 && !ended)){
        Card tmp(dealer.giveCard());
        player.addCard(tmp);
        dealer.addCard();
        totalBet += betCredit;
    }
    if(player.getNumCards() == 5 && !ended){
        show_win_point();
        ended = true;
    }
    else if(ended || yourCredit <= 0 || myCredit <= 0)
        std::cout << "GAME OVER!" << std::endl;
}


// give up this round,
// and you'll lose your credit
// the bet is equivalent to the number of card you keep
    void
SHGame::giveUp()
{
    dealer.openFirstCard();
    if(!ended){
        myCredit += totalBet;
        yourCredit -= totalBet;
        std::cout << "I win. Try again. ";
        std::cout << "(You have "<< yourCredit <<" points, I Have "<< myCredit <<" points.)" << std::endl;
    }
    else if(ended || yourCredit <= 0 || myCredit <= 0)
        std::cout << "GAME OVER!" << std::endl;
           ended = true;
}


// restart the game by giving each player two new cards
// need to check if any one broke (bankrupt).
    void
SHGame::restart()
{
    if(myCredit <= 0 || yourCredit <= 0)
        std::cout << "Sorry. Game over. No loan here." << std::endl;
    else if(ended){
        ended = false;
        totalBet = 0;
        player.start();
        dealer.start();
        player.openFirstCard();
        for(int i = 0; i < 2; ++i){
            moreCard();
        }
    }
    else
        std::cout << "Game is not over yet. Choose 'give up' to end a game" << std::endl;
}
void SHGame::show_win_point(){
    switch(dealer.judge(player)){
        case WIN:
            std::cout << "You win. Good job.";
            myCredit -= totalBet;
            yourCredit += totalBet;
            break;
        case LOSE:
            std::cout << "I win. Try again. ";
            myCredit += totalBet;
            yourCredit -= totalBet;
            break;
        case TIE:
            break;
    }
    std::cout << "(You have "<< yourCredit <<" points, I Have "<< myCredit <<" points.)" << std::endl;
}
