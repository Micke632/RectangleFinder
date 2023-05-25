#include "rect.h"
#include <memory_resource>

rect::rect()
{

}

int rect::countColAt(int start, const std::vector<int> &col, int row, std::set<std::pair<int, int>> &set)
{
    int c = 0;
    auto it = set.begin();
    for (int m = start; m < col.size(); m++)
    {
        auto p = std::make_pair(row, m);
        if (col[m] == 1 || m_checkedPoints.count(p))
        {
            break;
        }
        else
        {
            //  m_used.insert( p);            
            it = set.emplace_hint(it, p);
        }
        c++;
    }

    return c;
}

int rect::countRowAt(int start, int col, const std::vector<std::vector<int>> &a)
{
    int c = 0;
    int y = a.size();
    for (int m = start; m < y; m++)
    {

        if (a[m][col] == 1 || m_checkedPoints.count({ m,col }))
        {
            break;
        }

        c++;
    }

    return c;
}


void rect::setChecked(int i, int i2, int j, int j2)
{
    auto it = m_checkedPoints.begin();

    for (int k = i; k <= i2; k++)
    {
        for (int l = j; l <= j2; l++)
        {
            it = m_checkedPoints.emplace_hint(it, std::make_pair(k, l));
        }
    }
}

void rect::findend(const int i,           //start position row
    const int j,                    //start position column               
    const std::vector<std::vector<int>> &a,         //data
    int &outI,                       //out end pos row                           
    int &outJ)                      //out end pos col                   
{

    //set for first column so we can skip that later
    std::set<std::pair<int, int>> firstColumn;

    int countCol = countColAt(j, a.at(i), i, firstColumn);

    int countRow = countRowAt(i, j, a);


    //one item
    if (countCol == 1 && countRow == 1)
    {
        outI = i;
        outJ = j;

        m_checkedPoints.insert(firstColumn.begin(), firstColumn.end());

        return;
    }
    else if (countCol > 1 && countRow == 1)
    {
        //a column
        outI = i;
        outJ = j + countCol - 1;

        setChecked(i, i, j, j + countCol - 1);
        return;
    }
    else if (countRow > 1 && countCol == 1)
    {
        //a row
        outI = i + countRow - 1;
        outJ = j;

        setChecked(i, i + countRow - 1, j, j);

        return;
    }

    bool fullRect = true;

    //playing around with pmr
    std::array<std::byte, 1024> buffer;
    std::pmr::monotonic_buffer_resource mbr(&buffer, buffer.size());
    std::pmr::unsynchronized_pool_resource ups(&mbr);

    //checked points to check wether there is a rectangle
    std::pmr::set<std::pair<int, int>> checked(&ups);

    //include the already checked first column
    checked.insert(firstColumn.begin(), firstColumn.end());

    auto it = checked.begin();
    
    for (int n = i + 1; n < countRow + i; n++)  //skip first column
    {
        const auto &col = a[n];

        for (int m = j; m < countCol + j; m++)
        {
            if (col[m] == 1)
            {
                fullRect = false;
                break;
            }

            it = checked.emplace_hint(it, std::make_pair(n, m));

        }
        if (!fullRect) break;
    }



    if (fullRect)
    {
        m_checkedPoints.insert(checked.begin(), checked.end());

        //get the last point
        auto it = m_checkedPoints.rbegin();
        outI = it->first;
        outJ = it->second;
    }
    else
    {

        // not a full rectacle , pick one part of it 
        auto it = checked.end();
        --it;       //last "in a row"

        it = countCol > countRow ? it : --it;       //need the second last when row > col

        outI = it->first;
        outJ = it->second;

        setChecked(i, it->first, j, it->second);

    }


}

std::vector<std::array<int, 4>> rect::get_rectangle_coordinates(const std::vector<std::vector<int>> &a)
{

    int size_of_array = a.size();

    //we assume all columns have the same size
    int size_of_col = a[0].size();
    // output array where we are going
    // to store our output
    std::vector<std::array<int, 4>> output;
    output.reserve(1024);

    for (int i = 0; i < size_of_array; i++)
    {
        for (int j = 0; j < size_of_col; j++)
        {
            int c = m_checkedPoints.count({ i,j });
            if (c == 0 && a[i][j] == 0)
            {
                int endi, endj;

                findend(i, j, a, endi, endj);

                output.push_back({ i, j, endi, endj });

            }
        }
    }
    m_checkedPoints.clear();
    return output;
}

