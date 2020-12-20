#pragma once
#include <gtest/gtest.h>
#include <string>
#include "synt.h"

using namespace std;

TEST(Synt,right_create_obj)
{
    ASSERT_NO_THROW(Synt s1;);
}


TEST(Synt,simple_expression)
{
    string str={"5+2"};
    string t={""};
    string correct={"52+"};
    Synt sy1;
    
    Queue<string> tmp=sy1.synt_analiz(str);

    while(!tmp.isEmpty())
    {
        t+=tmp.pop();
    }
    EXPECT_EQ(t,correct);
}

 
    
    
TEST(Synt,medium_expression)
{
    string str={"5+2/2-4*(12-4)"};
    string t={""};
    string correct={"522/+4124-*-"};
    Synt sy1;
    
    Queue<string> tmp=sy1.synt_analiz(str);

    while(!tmp.isEmpty())
    {
        t+=tmp.pop();
    }
    EXPECT_EQ(t,correct);
}

    
    
TEST(Synt,hard_expression)
{
    string str={"12-(5+2/2-4*(12-4))*4"};
    string t={""};
    string correct={"12522/+4124-*-4*-"};
    Synt sy1;
    
    Queue<string> tmp=sy1.synt_analiz(str);

    while(!tmp.isEmpty())
    {
        t+=tmp.pop();
    }
    EXPECT_EQ(t,correct);
}