#include<Collection.h>

#include<gtest.h>

TEST(Stack, can_create_stack_with_positive_number_of_elements)
{
    ASSERT_NO_THROW(Stack<int> s(50));
}

TEST(Stack, cant_create_stack_with_negative_number_of_elements)
{
    ASSERT_ANY_THROW(Stack<int> s(-5));
}

TEST(Stack, created_stack_is_empty)
{
    Stack<int> s(10);
    EXPECT_EQ(true, s.isEmpty());
}

TEST(Stack, isFull_filled_stack_return_true)
{
    Stack<int> s(5);
    for (int i = 0; i < 5; i++)
    {
        s.push(3);
    }
    EXPECT_EQ(true, s.isFull());
}


TEST(Stack, can_create_copied_stack)
{
    Stack<int> s(10);
    ASSERT_NO_THROW(Stack<int> s1(s));
}

TEST(Stack, copied_stack_is_equal_to_source_one)
{
	Stack<int> s(10);
    s.push(1);
    s.push(2);
    s.push(4);

	Stack<int> s1(s);

	EXPECT_EQ(true,s == s1);
}

TEST(Stack, can_assign_stacks_of_equal_size)
{
	Stack<int> s(5);
    Stack<int> s1(5);

	ASSERT_NO_THROW(s1 = s);
}

TEST(Stack, can_assign_stacks_of_different_size)
{
	Stack<int> s(7);
    Stack<int> s1(5);

	ASSERT_NO_THROW(s1 = s);
}

TEST(Stack, can_assign_stack_to_itself)
{
	Stack<int> s(5);
	ASSERT_NO_THROW(s = s);
}

TEST(Stack, assign_operator_change_stack_size)
{
	Stack<int> s(7);
    Stack<int> s1(5);
	s1 = s;
	EXPECT_EQ(7, s1.getSize());
}

TEST(Stack, compare_equal_stacks_return_true)
{
	Stack<int> s(7);
    s.push(1);
    s.push(3);
    s.push(4);
    Stack<int> s1(s);

	EXPECT_EQ(true, s == s1);
}

TEST(Stack, compare_not_equal_stacks_return_false)
{
	Stack<int> s(7);
    s.push(1);
    s.push(3);
    s.push(4);
    Stack<int> s1(7);
    s.push(7);
    s.push(9);

	EXPECT_NE(true, s == s1);
}

TEST(Stack, compare_stack_with_itself_return_true)
{
	Stack<int> s(7);
    s.push(1);
    s.push(3);
    s.push(4);

	EXPECT_EQ(true, s == s);
}

TEST(Stack, stacks_with_different_size_are_not_equal)
{
	Stack<int> s(5), s1(7);
	EXPECT_EQ(false, s == s1);
}

TEST(Stack, can_push_element_to_not_full_stack)
{
	Stack<int> s(5);

	ASSERT_NO_THROW(s.push(3));
}

TEST(Stack, cant_push_element_to_full_stack)
{
	Stack<int> s(5);
    for (int i = 0; i < 5; i++)
    {
        s.push(3);
    }

	ASSERT_ANY_THROW(s.push(3));
}

TEST(Stack, can_pop_element_from_not_empty_stack)
{
	Stack<int> s(5);
    s.push(3);

	ASSERT_NO_THROW(s.pop());
}

TEST(Stack, cant_pop_element_from_empty_stack)
{
	Stack<int> s(5);

	ASSERT_ANY_THROW(s.pop());
}