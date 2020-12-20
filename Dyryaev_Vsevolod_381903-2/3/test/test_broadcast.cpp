#pragma once
#include <gtest/gtest.h>
#include <string>
#include "synt.h"
#include "broadcast.h"


using namespace std;


TEST(Broadcast,right_create_obj)
{
    ASSERT_NO_THROW(Broadcast s1;);
}


TEST(Broadcast,simple_expression)
{
    string str={"5+2"};
    Synt s1;
    Broadcast b1;
    Queue<string> tmp = s1.synt_analiz(str);
    int t = b1.broadcast(tmp,str);

    EXPECT_EQ(7,t);
}


TEST(Broadcast,medium_expression)
{
    string str={"5+2/2-4*(12-4)"};
    Synt s1;
    Broadcast b1;
    Queue<string> tmp = s1.synt_analiz(str);
    int t = b1.broadcast(tmp,str);

    EXPECT_EQ(-26,t);
}

TEST(Broadcast,hard_expression)
{
    string str={"12-(5+2/2-4*(12-4))*4"};
    Synt s1;
    Broadcast b1;
    Queue<string> tmp = s1.synt_analiz(str);
    int t = b1.broadcast(tmp,str);

    EXPECT_EQ(116,t);
}


