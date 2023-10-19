#include <gtest/gtest.h>

#include "../src/Lecture1/BinModel01.hpp"
#include "../src/Lecture1/BlackScholes.hpp"
#include "../src/Lecture1/Options01.hpp"


TEST(FINENG, riskNeutralProbTest)
{
    double R = 0.02;
    double U = 0.1;
    double D = -0.1;

    double q = lecture1::riskNeutralProb(U,D,R);
    EXPECT_TRUE(std::abs(q - (R-D) / (U-D)) < 0.000001) << "Incorrect risk neutral prob function";
}



double summer(double arr[] , int size)
{
    double sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

//our first unit test
TEST(IntegerInputsSuite, simpleSum)
{
    //first, set up any inputs to your 
    const int SIZE = 3;
    double arr[SIZE]  = {1, 2, 3};
    //then, make an assertion to test
    EXPECT_EQ(summer(arr, SIZE), 6) << "The sum is not correct";
}