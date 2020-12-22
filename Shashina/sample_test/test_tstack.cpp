#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, cant_push_if_stack_full)
{
	TStack<int> st(5);
	for (int i = 0; i < 5; i++)
		st.push(i);
	ASSERT_ANY_THROW(st.push(6));
}

TEST(TStack, cant_pop_if_stack_empty)
{
	TStack<int> st(3);
	ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, can_push_and_pop_element)
{
	TStack<int> st(4);
	st.push(10);
	EXPECT_EQ(10,st.pop());
}

TEST(TStack, function_full_is_correct)
{
	TStack<int> st(2);
	EXPECT_EQ(st.full(), false);
	st.push(0);
	st.push(1);
	EXPECT_EQ(st.full(), true);
}

TEST(TStack, function_empty_is_correct)
{
	TStack<int> st(2);
	EXPECT_EQ(st.empty(), true);
	st.push(0);
	EXPECT_EQ(st.empty(), false);
}
