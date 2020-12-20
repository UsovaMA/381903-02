#pragma once
#include <gtest/gtest.h>
#include <string>
#include "full_analiz.h"

using namespace std;



TEST(Full_a,create)
{
    ASSERT_NO_THROW(Full_a f1);
}


TEST(Full_a,correct_simpel_expression)
{
    Full_a f1;
    string str={"10+4"};
    int correct_answer=14;
    
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}

TEST(Full_a,simpel_expression)
{
    Full_a f1;
    string str={"10+4"};
    int correct_answer=14;
    
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}

TEST(Full_a,hard_expression)
{
    Full_a f1;
    string str={"10+8/4*(24+18-(100-40)/(14+6))"};
    int correct_answer=88;
    
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}

TEST(Full_a,wrong_plus_expression)
{
    Full_a f1;
    string str={"10+8/4*(24+18+-(100-40)/(14+6))"};
    int correct_answer=0;
    
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}


TEST(Full_a,wrong_skobka_pered_expression)
{
    Full_a f1;
    string str={"10+8/4*((24+18-(100-40)/(14+6))"};
    int correct_answer=0;
    
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}

TEST(Full_a,wrong_skobka2_zad_expression)
{
    Full_a f1;
    string str={"10+8/4*(24+18)-(100-40)/(14+6))"};
    int correct_answer=0;
    
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}


TEST(Full_a,simple_perem)
{
    Full_a f1;
    string str={"10-a+8/4*(24+18-(a-40)/(14+6))"};
    int correct_answer=-12;
    
    //проверка для а=100
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}

TEST(Full_a,madium_perem)
{
    Full_a f1;
    string str={"10+b/a*(24+c-(100-40)/(14+6))"};
    int correct_answer=88;
    
    //проверка для b=8 and a=4 and c=18
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}

TEST(Full_a,hard_perem)
{
    Full_a f1;
    string str={"12-(5+2/2+(5+a*b)^(1/c)-4*(12-4))*4"};
    int correct_answer=96;
    
    //проверка для a=4 b=5 or a=5 b =4 and c=2
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}

TEST(Full_a,wrong_perem)
{
    Full_a f1;
    string str={"12-(5+2/2+(5+a*b)^(1/cd)-4*(12-4))*4"};
    int correct_answer=0;
    
    //проверка для a=4 b=5 or a=5 b =4 and c=2
    EXPECT_EQ(correct_answer,f1.full_analiz(str));
}



