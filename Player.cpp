// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <map>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    
    if(s.numberEmpty() > 0)
    {
        int col;
        while(1)
        {
            cout << "Please make valid move." << endl;
            cin >> col;
            cin.ignore();
            if(col >=1 && col <= s.cols() && s.checkerAt(col, s.levels()) == VACANT)
                break;
        }
        return col;
    }
    return -1;
}


//a badplayer chooses leftmost non-full column to move
int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if(s.numberEmpty() > 0)
    {
        for(int i = 1; i <= s.cols(); i++)
            if(s.checkerAt(i, s.levels()) == VACANT)
                return i;
    }
    return -1;
}

int rating(const Scaffold& s, int g, int level)
{
    Scaffold ss = s;
    int color;
    if(win(ss, g, color)) //win
        return 1000-level;
    if(ss.numberEmpty() == 0) //tie
        return 0;
    return -1; //unfinished
}

void switchcolor(int &color)
{
    switch(color)
    {
        case RED: color = BLACK; break;
        case BLACK: color = RED; break;
    }
}

int determine(Scaffold& s, int N, int color, int &rate, int level)
{
    map<int, int> ri;
    for(int i = 1; i <= s.cols(); i++)
        if(s.checkerAt(i, s.levels()) == VACANT)
        {
            s.makeMove(i, color);
            int r = rating(s, N, level);
            if(r != -1)
            {
                ri[r] = i;
                rate = r;
                s.undoMove();
                return i;
            }
            switchcolor(color);
            int col = determine(s, N, color, r, level+1);
            switchcolor(color);
            ri[r] = col;
            s.undoMove();
        }
    map<int, int>::iterator it = ri.end();
    it--;
    rate = it->first;
    return it->second;
}


int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int r = -1;
    Scaffold ss = s;
    return determine(ss, N, color, r, 0);
}


//========================================================================
// Timer t;                 // create a timer and start it
// t.start();               // start the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

//#include <chrono>
//
//class Timer
//{
//public:
//    Timer()
//    {
//        start();
//    }
//    void start()
//    {
//        m_time = std::chrono::high_resolution_clock::now();
//    }
//    double elapsed() const
//    {
//        std::chrono::duration<double,std::milli> diff =
//        std::chrono::high_resolution_clock::now() - m_time;
//        return diff.count();
//    }
//private:
//    std::chrono::high_resolution_clock::time_point m_time;
//};

//Timer timer;
//Scaffold s(3, 5);
//
//void f(bool& startWrappingItUp)
//{
//    if (!startWrappingItUp)
//    {
//        int callcount = 0;
//        for (int k = 0; k < 1000000; k++)
//        {
//            if (++callcount == 1000)
//            {
//                if (timer.elapsed() > 9000)  // have 9.9 seconds elapsed?
//                {
//                    startWrappingItUp = true;
//                    return;
//                }
//                callcount = 0;
//            }
//            // ... do some computation here ...
//            int r = -1;
//            Scaffold ss = s;
//            int a = determine(s, 5, RED, r, 0);
//        }
//    }
//}
//
//int main()
//{
//    bool shouldWrapUp = false;
//    timer.start();
//    int ncalls;
//    for (ncalls = 0; !shouldWrapUp; ncalls++)
//        f(shouldWrapUp);
//    cout << "f was called " << ncalls << " times\n";
//}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
