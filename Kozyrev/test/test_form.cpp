#include "form.h"
#include <gtest.h>

TEST(TForm, can_create_form)
{
    ASSERT_NO_THROW(Form f);
}

TEST(TForm, cant_create_post_with_exeptions)
{
    ASSERT_ANY_THROW(Form f("x$x#x&x"));
}

TEST(TForm, convert_vir_to_post)
{
    Form f("x^2+y^2");

    f.post_vir();

    EXPECT_EQ(f.getPost(), "x2 ^y2 ^+");
}

TEST(TForm, mul_has_better_priority_than_add)
{
    Form f("3+3*3");

    double res = f.calc();

    EXPECT_EQ(res, 12.0);
}

TEST(TForm, mul_has_better_priority_than_sub)
{
    Form f("10-3*3");

    double res = f.calc();

    EXPECT_EQ(res, 1.0);
}

TEST(TForm, div_has_better_priority_than_add)
{
    Form f("3+3/3");

    double res = f.calc();

    EXPECT_EQ(res, 4.0);
}

TEST(TForm, div_has_better_priority_than_sub)
{
    Form f("3-3/3");

    double res = f.calc();

    EXPECT_EQ(res, 2.0);
}

TEST(TForm, pow_has_the_best_priority)
{
    Form f("3*3^3-3^2");

    double res = f.calc();

    EXPECT_EQ(res, 72.0);
}

TEST(TForm, throws_when_wrong_num_of_brackets)
{
    ASSERT_ANY_THROW(Form f("(1+(1*1)"));
}

TEST(TForm, throws_when_vir_is_empty)
{
    ASSERT_ANY_THROW(Form f(" "));
}

TEST(TForm, throws_when_variables_have_long_names)
{
    ASSERT_ANY_THROW(Form f("ab+cd"));
}

TEST(TForm, convert_vir_with_brackets)
{
    Form f("(1+2)*3");

    f.post_vir();

    EXPECT_EQ(f.getPost(), "1 2 +3 *");
}

TEST(TForm, convert_equal_vir)
{
    Form f1("(a+b)");
    f1.post_vir();

    Form f2("a+b");
    f2.post_vir();

    EXPECT_EQ(f1.getPost(), f2.getPost());
}

TEST(TForm, calc_is_correct)
{
    Form f("(1+2)*3-4");

    EXPECT_EQ(f.calc(), 5.0);
}
