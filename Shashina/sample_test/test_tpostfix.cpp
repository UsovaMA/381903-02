#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, cant_create_postfix_with_bad_symbols)
{
  ASSERT_ANY_THROW(TPostfix p("a+b&c!d"));
}

TEST(TPostfix, convert_infix_to_postfix)
{
	TPostfix p("a+b/c*d-h+k");
	p.ToPostfix();
	EXPECT_EQ(p.getPostfix(), "abc/d*+h-k+");
}

TEST(TPostfix, throws_when_infix_with_spaces_only)
{
	ASSERT_ANY_THROW(TPostfix p("      "));
}

TEST(TPostfix, throws_when_operation_behind)
{
	ASSERT_ANY_THROW(TPostfix p("a-b*"));
}

TEST(TPostfix, throws_when_operation_ahead)
{
	ASSERT_ANY_THROW(TPostfix p("+a-b"));
}

TEST(TPostfix, throws_when_too_many_left_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(a+(b*c)"));
}

TEST(TPostfix, throws_when_too_many_right_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(a+(b*c))+d))"));
}

TEST(TPostfix, cant_create_postfix_with_long_names)
{
	ASSERT_ANY_THROW(TPostfix p("a+bcd"));
}

TEST(TPostfix, convert_infix_with_brackets)
{
	TPostfix p("(a+b)*c");
	p.ToPostfix();
	EXPECT_EQ(p.getPostfix(), "ab+c*");
}

TEST(TPostfix, convert_equal_expression)
{
	TPostfix p1("(a+b)");
	p1.ToPostfix();
	TPostfix p2("a+b");
	p2.ToPostfix();
	EXPECT_EQ(p1.getPostfix(), p2.getPostfix());
}

TEST(TPostfix, calculation_is_correct)
{
	TPostfix p("(5+6)*2");
	p.ToPostfix();
    EXPECT_EQ(p.Calculate(), 22);
}
