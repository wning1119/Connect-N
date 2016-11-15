// Game.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    ~GameImpl();
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
  private:
    Scaffold *m_s;
    Player *m_red, *m_black;
    int goal;
    int turn;
    
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    if(N > nColumns && N > nLevels)
    {
        cerr << "out of range." << endl;
        exit(1);
    }
    m_s = new Scaffold(nColumns, nLevels);
    m_red = red;
    m_black = black;
    goal = N;
    turn = RED;
}

GameImpl::~GameImpl()
{
    delete m_s;
}

bool GameImpl::completed(int& winner) const
{
    if(win(*m_s, goal, winner))
        return true;
    else
    {
        if(m_s->numberEmpty() == 0)
        {
            winner = TIE_GAME;
            return true;
        }
        return false;
    }
}

bool GameImpl::takeTurn()
{
    int winnercolor;
    if(completed(winnercolor))
        return false;
    int move;
    if(turn == RED)
    {
        move = m_red->chooseMove(*m_s, goal, RED);
        m_s->makeMove(move, RED);
        turn = BLACK;
    }
    else
    {
        move = m_black->chooseMove(*m_s, goal, BLACK);
        m_s->makeMove(move, BLACK);
        turn = RED;
    }
    m_s->display();
    return true;
}

void GameImpl::play()
{
    int winnercolor;
    cout << "Press enter to start." << endl;
    cin.ignore();
    while(1)
    {
        takeTurn();
        if(completed(winnercolor))
        {
            if(winnercolor == RED)
                cout << m_red->name() << " wins." << endl;
            else if(winnercolor == BLACK)
                cout << m_black->name() << " wins." << endl;
            else
                cout << "It's a draw." << endl;
            break;
        }
        cout << "Press enter to continue." << endl;
        cin.ignore();
    }

}

int GameImpl::checkerAt(int c, int r) const
{
    return m_s->checkerAt(c, r);
} 

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
