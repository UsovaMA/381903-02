#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, cant_create_too_large_stack)
{
    ASSERT_ANY_THROW(TStack<int> s(MaxStackSize + 1));
}

TEST(TStack, can_pop_element)
{
    TStack<int> st(4);
    st.push(10);
    EXPECT_EQ(10, st.pop());
}

TEST(TStack, cant_pop_element_from_empty_stack)
{
    TStack<int> s(5);

    ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, can_push_element_to_not_full_stack)
{
    TStack<int> s(5);

    ASSERT_NO_THROW(s.push(3));
}

TEST(TStack, cant_push_element_to_full_stack)
{
    TStack<int> s(5);
    for (int i = 0; i < 5; i++)
    {
        s.push(3);
    }

    ASSERT_ANY_THROW(s.push(3));
}

TEST(TStack, isfull_returns_true)
{
    TStack<int> s(5);

    for (int i = 0; i < 5; i++)
    {
        s.push(i);
    }

    EXPECT_EQ(true, s.full());
}

TEST(TStack, isempty_returns_true)
{
    TStack<int> s(5);

    EXPECT_EQ(true, s.empty());
}