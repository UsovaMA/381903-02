#include<Collection.h>

#include<gtest.h>

TEST(Queue, can_create_queue_with_positive_number_of_elements)
{
    ASSERT_NO_THROW(Queue<int> q(50));
}

TEST(Queue, cant_create_queue_with_negative_number_of_elements)
{
    ASSERT_ANY_THROW(Queue<int> q(-5));
}

TEST(Queue, created_queue_is_empty)
{
    Queue<int> q(10);
    EXPECT_EQ(true, q.isEmpty());
}

TEST(Queue, isFull_filled_stack_return_true)
{
    Stack<int> q(5);
    for (int i = 0; i < 5; i++)
    {
        q.push(3);
    }
    EXPECT_EQ(true, q.isFull());
}

TEST(Queue, can_create_copied_queue)
{
    Queue<int> q(10);
    ASSERT_NO_THROW(Queue<int> q1(q));
}

TEST(Queue, copied_queue_is_equal_to_source_one)
{
	Queue<int> q(10);
    q.push(1);
    q.push(2);
    q.push(4);

	Queue<int> q1(q);

	EXPECT_EQ(true, q == q1);
}

TEST(Queue, can_assign_queues_of_equal_size)
{
	Queue<int> q(5);
    Queue<int> q1(5);

	ASSERT_NO_THROW(q1 = q);
}

TEST(Queue, can_assign_queues_of_different_size)
{
	Queue<int> q(7);
    Queue<int> q1(5);

	ASSERT_NO_THROW(q1 = q);
}

TEST(Queue, can_assign_queue_to_itself)
{
	Queue<int> q(5);
	ASSERT_NO_THROW(q = q);
}

TEST(Queue, assign_operator_change_queue_size)
{
	Queue<int> q(7);
    Queue<int> q1(5);
	q1 = q;
	EXPECT_EQ(7, q1.getSize());
}

TEST(Queue, compare_equal_queues_return_true)
{
	Queue<int> q(7);
    q.push(1);
    q.push(3);
    q.push(4);
    Queue<int> q1(q);

	EXPECT_EQ(true, q == q1);
}

TEST(Queue, compare_not_equal_queues_return_false)
{
	Queue<int> q(7);
    q.push(1);
    q.push(3);
    q.push(4);
    Queue<int> q1(7);
	q.push(6);
    q.push(8);

	EXPECT_NE(true, q == q1);
}

TEST(Queue, compare_queue_with_itself_return_true)
{
	Queue<int> q(7);
    q.push(1);
    q.push(3);
    q.push(4);

	EXPECT_EQ(true, q == q);
}

TEST(Queue, queues_with_different_size_are_not_equal)
{
	Queue<int> q(5), q1(7);
	EXPECT_EQ(false, q == q1);
}

TEST(Queue, can_push_element_to_not_full_queue)
{
	Queue<int> q(5);

	ASSERT_NO_THROW(q.push(3));
}

TEST(Queue, cant_push_element_to_full_queue)
{
	Queue<int> q(5);
    for (int i = 0; i < 5; i++)
    {
        q.push(3);
    }

	ASSERT_ANY_THROW(q.push(3));
}

TEST(Queue, can_pop_element_from_not_empty_queue)
{
	Queue<int> q(5);
    q.push(3);

	ASSERT_NO_THROW(q.pop());
}

TEST(Queue, cant_pop_element_from_empty_queue)
{
	Queue<int> q(5);

	ASSERT_ANY_THROW(q.pop());
}