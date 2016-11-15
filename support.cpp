//
//  support.cpp
//  project3
//
//  Created by Ning Wang on 5/18/16.
//  Copyright © 2016 Ning Wang. All rights reserved.
//

#include "support.h"
#include "provided.h"

bool winHorizontally(Scaffold &s, int N, int &color)
{
    int col = s.cols(), lev = s.levels();
    for(int i = 1; i <= lev; i++)
    {
        int j = 1, count = 1;
        while(j < col)
        {
            if(s.checkerAt(j, i) != VACANT && s.checkerAt(j, i) == s.checkerAt(j+1, i))
            {
                count++;
                if( count == N)
                {
                    color = s.checkerAt(j, i);
                    return true;
                }
            }
            else
                count = 1;
            j++;
        }
    }
    return false;
}

bool winVertically(Scaffold &s, int N, int &color)
{
    int col = s.cols(), lev = s.levels();
    for(int i = 1; i <= col; i++)
    {
        int j = 1, count = 1;
        while(s.checkerAt(i, j) != VACANT && j < lev)
        {
            if(s.checkerAt(i, j) == s.checkerAt(i, j+1))
            {
                count++;
                if( count == N)
                {
                    color = s.checkerAt(i, j);
                    return true;
                }
            }
            else
                count = 1;
            j++;
        }
    }
    return false;
    
}

bool winDiagonally(Scaffold &s, int N, int &color)
{
    int col = s.cols(), lev = s.levels();
    int i = 1, j = 1, count = 1, temp;
    while(j < lev)
    {
        temp = j;
        while(i < col && j < lev)
        {
            if(s.checkerAt(i, j) != VACANT && s.checkerAt(i, j) == s.checkerAt(i+1, j+1))
            {
                count++;
                if( count == N)
                {
                    color = s.checkerAt(i, j);
                    return true;
                }
            }
            else
                count = 1;
            i++;  j++;
        }
        i = 1; j = temp + 1; count = 1;
    }
    i = 2; j = 1; count = 1;
    while(i < col)
    {
        temp = i;
        while(i < col && j < lev)
        {
            if(s.checkerAt(i, j) != VACANT && s.checkerAt(i, j) == s.checkerAt(i+1, j+1))
            {
                count++;
                if( count == N)
                {
                    color = s.checkerAt(i, j);
                    return true;
                }
            }
            else
                count = 1;
            i++;  j++;
        }
        i = temp + 1; j = 1; count = 1;
    }
    i = 1; j = lev; count = 1;
    while(i < col)
    {
        temp = i;
        while(i < col && j > 1)
        {
            if(s.checkerAt(i, j) != VACANT && s.checkerAt(i, j) == s.checkerAt(i+1, j-1))
            {
                count++;
                if( count == N)
                {
                    color = s.checkerAt(i, j);
                    return true;
                }
            }
            else
                count = 1;
            i++;  j--;
        }
        i = temp + 1; j = lev; count = 1;
    }
    i = 1; j = lev - 1; count = 1;
    while(j > 1)
    {
        temp = j;
        while(i < col && j > 1)
        {
            if(s.checkerAt(i, j) != VACANT && s.checkerAt(i, j) == s.checkerAt(i+1, j-1))
            {
                count++;
                if( count == N)
                {
                    color = s.checkerAt(i, j);
                    return true;
                }
            }
            else
                count = 1;
            i++;  j--;
        }
        i = 1; j = temp - 1; count = 1;
    }
    return false;
}

bool win(Scaffold &ss, int g, int &wcolor)
{
    if(winHorizontally(ss, g, wcolor) || winVertically(ss, g, wcolor) || winDiagonally(ss, g, wcolor))
        return true;
    return false;
}
