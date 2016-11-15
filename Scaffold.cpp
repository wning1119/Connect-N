// Scaffold.cpp


#include "provided.h"
#include "support.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    ~ScaffoldImpl();
    ScaffoldImpl(const ScaffoldImpl &other);
    ScaffoldImpl& operator=(const ScaffoldImpl &rhs);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
    void swap(ScaffoldImpl &other);
 private:
    int m_ncol, m_nlev;
    vector<int> *m_col;
    stack<int> m_step;  //record move
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    m_ncol = nColumns;
    m_nlev = nLevels;
    m_col = new vector<int>[m_ncol];
}

ScaffoldImpl::~ScaffoldImpl()
{
    delete [] m_col;
}

ScaffoldImpl::ScaffoldImpl(const ScaffoldImpl &other)
{
    m_ncol = other.m_ncol;
    m_nlev = other.m_nlev;
    m_step = other.m_step;
    m_col = new vector<int>[m_ncol];
    for (int i = 0; i < m_ncol; i++)
        m_col[i] = other.m_col[i];
}

ScaffoldImpl& ScaffoldImpl::operator=(const ScaffoldImpl &rhs)
{
    if (this != &rhs)
    {
        ScaffoldImpl temp(rhs);
        swap(temp);
    }
    return *this;
}

void ScaffoldImpl::swap(ScaffoldImpl &other)
{
    int temp1 = m_ncol;
    m_ncol = other.m_ncol;
    other.m_ncol = temp1;
    
    int temp2 = m_nlev;
    m_nlev = other.m_nlev;
    other.m_nlev = temp2;
    
    stack<int> temp3 = m_step;
    m_step = other.m_step;
    other.m_step = temp3;
    
    vector<int> *temp4 = m_col;
    m_col = other.m_col;
    other.m_col = temp4;
}

int ScaffoldImpl::cols() const
{
    return m_ncol;
}

int ScaffoldImpl::levels() const
{
    return m_nlev;
}

int ScaffoldImpl::numberEmpty() const
{
    int nmax = m_ncol * m_nlev, count = 0;
    for (int i = 0; i < m_ncol; i++)
        count += m_col[i].size();
    return nmax-count;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column < 1 || column > m_ncol || level < 1 || level > m_nlev)
    {
        cerr << "out of range" << endl;
        exit(1);
    }
    if (level > m_col[column-1].size())
        return VACANT;
    else
        return m_col[column-1][level-1];
}

void ScaffoldImpl::display() const
{
    for (int i = m_nlev; i >= 1; i--)
    {
        for (int j = 1; j <= m_ncol; j++)
        {
            switch (checkerAt(j, i))
            {
                case RED:
                    cout << "|R"; break;
                case BLACK:
                    cout << "|B"; break;
                case VACANT:
                    cout << "| "; break;
            }
        }
        cout << "|" << endl;

    }
    for (int i = 0; i < m_ncol; i++)
        cout << "+-";
    cout << "+" << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column >= 1 && column <= m_ncol && m_col[column-1].size() < m_nlev
        && (color == RED || color == BLACK)) //check if valid
    {
        m_col[column-1].push_back(color); // push the color to certain vector
        m_step.push(column); // record column of the move
        return true;
    }
    return false;

}

int ScaffoldImpl::undoMove()
{
    if (m_step.empty())
        return 0;
    int col = m_step.top();  // get the column of last move
    m_step.pop();
    m_col[col-1].pop_back(); // pop out the last checker
    return col;
}


//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
