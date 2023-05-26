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

int rect::countRowAt(int start, int col, const std::vector<std::vector<int>> &a)
{
    int c = 0;
    int y = a.size();
 
    for (int m = start; m < y; m++)
    {
      
        if (a[m][col] == 1 || m_checkedPoints.count(std::make_pair(m, col)))
        {
            break;
        }

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

void rect::findend(const int i,     //start position row
    const int j,                    //start position column               
    const std::vector<std::vector<int>> &data,
    int &outI,                       //out end pos row                           
    int &outJ)                      //out end pos col                   
{

    //set for first column so we can skip that later
    Set_type firstColumn;

    const int countCol = countColAt(j, data[i], i, firstColumn);  

    const int countRow = countRowAt(i, j, data);

    auto insertFrom = [&](const Set_type &from) {

        for (const auto &p : from)
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
        
        setChecked(i, outI, j, outJ);
        return;
    }

 

    //checked points to check wether there is a rectangle
    Set_type  checked;

    auto checkRect = [&]()
    {
        for (int n = i + 1; n < countRow + i; n++)  //skip first column
        {
            const auto &col = data[n];

            for (int m = j ; m < countCol + j; m++)     
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
        insertFrom(checked);
           
        auto it = m_checkedPoints.rbegin();

        //last point is the end
        outI = it->first;
        outJ = it->second;

    }
    else
    {

        // not a full rectangle , pick what we got
        auto it = checked.end();
        --it;
        it = countRow > countCol ? --it : it;

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

