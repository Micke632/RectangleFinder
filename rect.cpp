#include "rect.h"


rect::rect()
{

}

int rect::countColAt(int start, const std::vector<int> &col, int row, Set_type &set)
{
    int c = 0;

    for (int m = start; m < col.size(); m++)
    {
        auto p = std::make_pair(row, m);
        if (col[m] == 1 || m_checkedPoints.count(p))
        {
            break;
        }      

        set.insert(p);        
        c++;
    }

    return c;
}

int rect::countRowAt(int start, int col, const std::vector<std::vector<int>> &a, Set_type &set)
{
    int c = 0;
    int y = a.size();
    auto it = set.begin();
    for (int m = start; m < y; m++)
    {
        auto p = std::make_pair(m, col);
        if (a[m][col] == 1 || m_checkedPoints.count(p))
        {
            break;
        }

        set.insert(p);
        c++;
    }

    return c;
}


void rect::setChecked(int i, int i2, int j, int j2)
{
    for (int k = i; k <= i2; k++)
    {
        for (int l = j; l <= j2; l++)
        {
            m_checkedPoints.emplace(std::make_pair(k, l));
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
    Set_type firstColumn;

    const int countCol = countColAt(j, a.at(i), i, firstColumn);

    //set for first row so we can skip that later
    Set_type firstRow;

    const int countRow = countRowAt(i, j, a , firstRow);


    auto insertFrom = [&](const Set_type &from) {

        for (auto &p : from)
        {
            m_checkedPoints.insert(p);
        }

    };
    //one item
    if (countCol == 1 && countRow == 1)
    {
        outI = i;
        outJ = j;

        insertFrom(firstColumn);

        
        return;
    }
    else if (countCol > 1 && countRow == 1)
    {
        //a column
        outI = i;
        outJ = j + countCol - 1;   
        
        insertFrom(firstColumn);

     
        return;
    }
    else if (countRow > 1 && countCol == 1)
    {
        //a row
        outI = i + countRow - 1;
        outJ = j;
        
        insertFrom(firstRow);

        return;
    }

 

    //checked points to check wether there is a rectangle
    Set_type  checked;

    auto checkRect = [&]()
    {
        for (int n = i + 1; n < countRow + i; n++)  //skip first column
        {
            const auto &col = a[n];

            for (int m = j + 1; m < countCol + j; m++)      //dont check first point each col , it'a already done
            {
                if (col[m] == 1)
                {
                    return false;
                }

                checked.insert(std::make_pair(n, m));
            }        
        }
        return true;
    };


    bool fullRect = checkRect();
     
    if (fullRect)
    {
  
        insertFrom(firstColumn);
        insertFrom(firstRow);
        insertFrom(checked);
           
        auto it = m_checkedPoints.rbegin();
        outI = it->first;
        outJ = it->second;

    }
    else
    {

        // not a full rectangle , pick one part of it 
        auto it = checked.end();
        --it;       //last point in order . 

        outI = it->first;
        outJ = it->second;

        //fill the m_checkedPoints correctly
        setChecked(i, outI, j, outJ);
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
           
            if (a[i][j] == 0)
            {
                //rect here , check if the point is already handled
                auto p = std::make_pair(i, j);
                int c = m_checkedPoints.count(p);
                if (c == 0)
                {
                    int endi, endj;

                    findend(i, j, a, endi, endj);

                    output.push_back({ i, j, endi, endj });
                }

            }
        }
    }

    m_checkedPoints.clear();
    return output;
}

