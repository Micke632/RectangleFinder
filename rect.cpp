#include "rect.h"
#include <optional>

rect::rect()
{
    m_output.reserve(1024);
}

int rect::countColAt(int start, const std::vector<int> &col, int row, Set_type &set)
{
    int c = 0;

    for (int m = start; m < col.size(); m++)
    {
        auto p = std::make_pair(row, m);
        if (col[m] == 1 || m_vistited.count(p))
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
      
        if (a[m][col] == 1 || m_vistited.count(std::make_pair(m, col)))
        {
            break;
        }

        c++;
    }

    return c;
}


void rect::setVisited(int i, int i2, int j, int j2)
{
    for (int k = i; k <= i2; k++)
    {
        for (int l = j; l <= j2; l++)
        {
            m_vistited.emplace(std::make_pair(k, l));
        }
    }
}


void rect::findend(const int i,     //start position row
    const int j,                    //start position column               
    const std::vector<std::vector<int>> &data)
{

    auto setVisitedFrom = [&](const Set_type &from) {

        for (const auto &p : from)
        {
            m_vistited.insert(p);
        }

    };
    //set for first column so we can skip that later
    Set_type firstColumn;


    const int countCol = countColAt(j, data[i], i, firstColumn);  

    const int countRow = countRowAt(i, j, data);

 
    //one item
    if (countCol == 1 && countRow == 1)
    {

        setVisitedFrom(firstColumn);
   
        setOut(i, j, i, j);
        return;
    }
    else if (countCol > 1 && countRow == 1)
    {
        //a column
        
        setVisitedFrom(firstColumn);
   
        setOut(i, j, i, j + countCol - 1);
        return;
    }
    else if (countRow > 1 && countCol == 1)
    {
        //a row
        
        setVisited(i, i + countRow - 1, j, j);
   
        setOut(i, j, i + countRow - 1, j);
        return;
    }

 
    //visited points to check wether there is a rectangle
    Set_type  visited;

    std::optional<std::pair<int, int>> fullColumnAt;
    auto checkRect = [&]()
    {
        for (int n = i + 1; n < countRow + i; n++)  //skip first column
        {
            const auto &col = data[n];
            int m = j;
            for (; m < countCol + j; m++)
            {
                if (col[m] == 1)
                {
                    return false;
                }

                visited.insert(std::make_pair(n, m));
            }
            fullColumnAt = { n, m - 1 };
        }
        return true;
    };


    bool fullRect = checkRect();
     
    if (fullRect)
    {
        
        setVisitedFrom(firstColumn);
        setVisitedFrom(visited);
           
        auto it = visited.rbegin();          

        setOut(i, j, it->first, it->second);
    }
    else
    {

        // not a full rectangle , pick what we got
      
        if (fullColumnAt)
        { 
   
            setOut(i, j, fullColumnAt->first , fullColumnAt->second);
            setVisited(i, fullColumnAt->first, j, fullColumnAt->second);
            
        }
        else
        {
            auto it = visited.rbegin();                       
            setOut(i, j, it->first, it->second);

                                
            {
                //use firstColumn as out
                //find not used part
                int t = it->second - j + 1;

                auto it = firstColumn.begin() + t;
                auto itend = firstColumn.rbegin();

                setOut(it->first, it->second, it->first, itend->second);

                while (it != firstColumn.end())
                {
                    m_vistited.insert(*it);
                    ++it;
                }

                
            }
            //insert here for faster insert (sorting)
            setVisited(i, it->first, j, it->second);
        }   
   
    }

   
}

void rect::setOut(int startI, int startJ,int endI,                                                 
                  int endJ  )
{
    m_output.push_back({ startI, startJ, endI, endJ });
    m_lastJ = endJ;
}

std::vector<std::array<int, 4>> rect::get_rectangle_coordinates(const std::vector<std::vector<int>> &a)
{

    int size_of_array = a.size();

    //we assume all columns have the same size
    int size_of_col = a[0].size();
    // output array where we are going
    // to store our output
    m_output.clear();

    for (int i = 0; i < size_of_array; i++)
    {
        for (int j = 0; j < size_of_col; j++)
        {
           
            if (a[i][j] == 0)
            {
                //rect here , check if the point is already handled
                auto p = std::make_pair(i, j);
                int c = m_vistited.count(p);
                if (c == 0)
                {                 
                   findend(i, j, a);
                   j = m_lastJ;         //jump forward
                }
            }
          
        }

      
    }

    m_vistited.clear();
    return m_output;
}

