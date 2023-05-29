#pragma once

#include <set>
#include <vector>
#include <array>
#include <cstddef>
#include "../Util/itlib/flat_set.hpp"

/*
We have one 2D array filled with zeros and ones.
We have to find the starting point and ending point of all rectangles filled with 0. 
Rectangles dont have to be separated and can just contain one element.
No intention to find the biggest rectangle. 

*/

class rect
{

    using Set_type = itlib::flat_set<std::pair<int, int>>;      //sorted vector  , but a std::set will work just fine
private:


    Set_type m_visited;
    std::vector<std::array<int, 4>> m_output;
  
    int countColAt(int start, const std::vector<int> &col, int row, Set_type &);

    int countRowAt(int start, int col, const std::vector<std::vector<int>> &a) ;
       
    void setVisited(int i, int i2, int j, int j2);

    
    void findend(const int i,           //start position row
        const int j,                    //start position column               
        const std::vector<std::vector<int>> &a);         //data
               

    void setOut(int startI, int startJ, int outI,
        int outJ);

    int m_lastJ = 0;

public:
    rect();
    std::vector<std::array<int, 4>> get_rectangle_coordinates(const std::vector<std::vector<int>> &a);



};

