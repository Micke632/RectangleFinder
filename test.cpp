#include "rect.r"
#include <chromo>
#include <iostream>

TEST(TestCaseName, Rect)
{
    {
        vector<vector<int>> tests = {
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 1, 1},
        {1, 0, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1}
        };
        rect r;
        std::vector<std::array<int, 4>> o = r.get_rectangle_coordinates(tests);
        EXPECT_EQ(o.size(), 5);

        EXPECT_EQ(o[0][0], 3);
        EXPECT_EQ(o[0][1], 1);
        EXPECT_EQ(o[0][2], 4);
        EXPECT_EQ(o[0][3], 3);

        EXPECT_EQ(o[1][0], 3);
        EXPECT_EQ(o[1][1], 4);
        EXPECT_EQ(o[1][2], 3);
        EXPECT_EQ(o[1][3], 6);

        EXPECT_EQ(o[2][0], 5);
        EXPECT_EQ(o[2][1], 1);
        EXPECT_EQ(o[2][2], 5);
        EXPECT_EQ(o[2][3], 1);

        EXPECT_EQ(o[3][0], 5);
        EXPECT_EQ(o[3][1], 4);
        EXPECT_EQ(o[3][2], 6);
        EXPECT_EQ(o[3][3], 5);

        EXPECT_EQ(o[4][0], 7);
        EXPECT_EQ(o[4][1], 4);
        EXPECT_EQ(o[4][2], 7);
        EXPECT_EQ(o[4][3], 4);

    }
	
	  {
        //bad scenario
        vector<vector<int>> tests = {
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 1},
        {1, 0, 0, 1, 1, 1, 1},
        {1, 0, 0, 1, 1, 1, 1},
        {1, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1}
        };

        std::vector<std::array<int, 4>> o = r.get_rectangle_coordinates(tests);
        EXPECT_EQ(o.size(), 3);

        EXPECT_EQ(o[0][0], 3);
        EXPECT_EQ(o[0][1], 1);
        EXPECT_EQ(o[0][2], 4);
        EXPECT_EQ(o[0][3], 2);

        EXPECT_EQ(o[1][0], 3);
        EXPECT_EQ(o[1][1], 3);
        EXPECT_EQ(o[1][2], 3);
        EXPECT_EQ(o[1][3], 3);


        EXPECT_EQ(o[2][0], 5);
        EXPECT_EQ(o[2][1], 1);
        EXPECT_EQ(o[2][2], 6);
        EXPECT_EQ(o[2][3], 2);
    }

    {
        vector<vector<int>> tests = {
        {1, 0, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 0, 0, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 0, 0, 0, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 0, 1, 0, 0, 0, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 0, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 0, 1, 0, 0, 0, 0,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 0, 0, 0, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,0,0,0,0,0,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,0,0,0,0,0,1, 1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,1,1,1},
        {0, 1, 0, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,1,1,1},
        {0, 1, 0, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1},
        {1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,0,1, 1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1}
        };

        rect r;
        const auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::array<int, 4>> o = r.get_rectangle_coordinates(tests);

        const auto stop = std::chrono::high_resolution_clock::now();
        const auto secs = std::chrono::duration<double>(stop - start);
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(secs);
        std::cout << " time:" << us.count() << std::endl;
        EXPECT_EQ(o.size(), 12);
        EXPECT_EQ(o[0][0], 0);
        EXPECT_EQ(o[0][1], 1);
        EXPECT_EQ(o[0][2], 1);
        EXPECT_EQ(o[0][3], 1);

        EXPECT_EQ(o[1][0], 1);
        EXPECT_EQ(o[1][1], 2);
        EXPECT_EQ(o[1][2], 1);
        EXPECT_EQ(o[1][3], 2);

        EXPECT_EQ(o[2][0], 2);
        EXPECT_EQ(o[2][1], 3);
        EXPECT_EQ(o[2][2], 3);
        EXPECT_EQ(o[2][3], 5);

        EXPECT_EQ(o[3][0], 3);
        EXPECT_EQ(o[3][1], 1);
        EXPECT_EQ(o[3][2], 5);
        EXPECT_EQ(o[3][3], 1);

        EXPECT_EQ(o[4][0], 5);
        EXPECT_EQ(o[4][1], 3);
        EXPECT_EQ(o[4][2], 6);
        EXPECT_EQ(o[4][3], 5);

        EXPECT_EQ(o[5][0], 5);
        EXPECT_EQ(o[5][1], 6);
        EXPECT_EQ(o[5][2], 5);
        EXPECT_EQ(o[5][3], 6);
    }
}