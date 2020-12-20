#pragma once
#include <gtest/gtest.h>
#include "leks.h"
#include <string>


using namespace std;

TEST(Leks,right_create_obj)
{
    ASSERT_NO_THROW(Leks s1);
}

TEST(Leks,working_with_correct_expression)
{
    Leks l1;
    string s1={"10+12*2/(1+2-12*8)"};

    EXPECT_EQ(true,l1.leks_analiz(s1));
}

TEST(Leks,working_with_incorrect_expression_double_sign)
{
    Leks l1;
    string s1={"10++12*2/(1+2-12*8)"};

    EXPECT_EQ(false,l1.leks_analiz(s1));
}

TEST(Leks,working_with_correct_expression_with_variety_brackets)
{
    Leks l1;
    string s1={"{10+12}*2/([1+2-12]*8)"};

    EXPECT_EQ(true,l1.leks_analiz(s1));
}

TEST(Leks,working_with_incorrect_expression_with_variety_brackets)
{
    Leks l1;
    string s1={"10+12*2/{(1+2}-12*8)"};

    EXPECT_EQ(false,l1.leks_analiz(s1));
}



TEST(Leks,working_with_incorrect_expression_with_variety_brackets1)
{
    Leks l1;
    string s1={"10+12*2/((1+2)-12)*8)"};

    EXPECT_EQ(false,l1.leks_analiz(s1));
}


TEST(Leks,working_with_incorrect_expression_with_variety_brackets2)
{
    Leks l1;
    string s1={"10+12*2/(((1+2-12)*8)"};

    EXPECT_EQ(false,l1.leks_analiz(s1));
}
