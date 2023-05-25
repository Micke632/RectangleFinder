#pragma once

#include <set>
#include <vector>
#include <array>
#include <cstddef>

class rect
{

private:

  

    std::set<std::pair<int, int>> m_used;

    int countColAt(int start, const std::vector<int> &col, int row);

    int countRowAt(int start, int col, const std::vector<std::vector<int>> &a);
       
    void setUsed(int i, int i2, int j, int j2);

    
    void findend(const int i,           //start position row
        const int j,                    //start position column               
        const std::vector<std::vector<int>> &a,         //data
        int &outI,                       //out end pos row                           
        int &outJ);                      //out end pos col                   

public:
    rect();
    std::vector<std::array<int, 4>> get_rectangle_coordinates(const std::vector<std::vector<int>> &a);



};

