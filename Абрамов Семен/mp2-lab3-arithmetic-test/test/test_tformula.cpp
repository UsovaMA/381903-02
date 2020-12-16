#include<TFormula.h>

#include<gtest.h>

TEST(TFormula, can_create_TFormula_object)
{
    ASSERT_NO_THROW(TForm f);
}

TEST(TFormula, can_create_TFormula_object_and_initialize_it)
{
    TForm f("1+2");
    EXPECT_EQ("1+2", f.get_iForm());
}

TEST(TFormula, can_initialize_TFormula_object)
{
    TForm f;
    f.init("1+2");
    EXPECT_EQ("1+2", f.get_iForm());
}

TEST(TFormula, throws_when_input_string_length_is_zero_1)
{
    string str = "";
    ASSERT_ANY_THROW(TForm f(str));
}

TEST(TFormula, throws_when_input_string_length_is_zero_2)
{
    string str = "";
    TForm f;
    ASSERT_ANY_THROW(f.init(str));
}


TEST(TFormula, can_get_input_string)
{
    string str = "1+2";
    TForm f(str);
    EXPECT_EQ(str, f.get_iForm());
}

TEST(TFormula, cant_get_output_string_if_its_not_ready)
{
    string str = "1+2";
    TForm f(str);
    ASSERT_ANY_THROW(f.get_oForm());
}

TEST(TFormula, can_get_output_string)
{
    string str = "1+2";
    TForm f(str);
    EXPECT_EQ(str, f.get_iForm());
}

TEST(TFormula, can_convert_arithmetic_expression_to_reverse_polish_notation)
{
    string str = "1+2";
    string strOut = "1 2 +";
    TForm f(str);
    f.conversToRevPolEnt();

    EXPECT_EQ(strOut, f.get_oForm());
}

TEST(TFormula, the_lexical_analyzer_removes_extra_spaces)
{
    string str = "1 +  2  ";
    string strOut = "1 2 +";
    TForm f(str);
    f.conversToRevPolEnt();

    EXPECT_EQ(strOut, f.get_oForm());
}

TEST(TFormula, throws_when_input_arithmetic_expression_with_unknown_characters)
{
    string str = "1апв+2";
    TForm f(str);

    ASSERT_ANY_THROW(f.conversToRevPolEnt());
}

TEST(TFormula, can_convert_arithmetic_expression_with_unary_minus_to_reverse_polish_notation)
{
    string str = "-(1+2)";
    string strOut = "1 2 +-";
    TForm f(str);
    f.conversToRevPolEnt();

    EXPECT_EQ(strOut, f.get_oForm());
}

TEST(TFormula, can_convert_arithmetic_expression_with_two_digit_and_multi_digit_numbers_to_reverse_polish_notation)
{
    string str = "123+25";
    string strOut = "123 25 +";
    TForm f(str);
    f.conversToRevPolEnt();

    EXPECT_EQ(strOut, f.get_oForm());
}

TEST(TFormula, can_convert_difficult_arithmetic_expression_to_reverse_polish_notation)
{
    string str = "(1+2*(4+25))+(45*34/(13+4))";
    string strOut = "1 2 4 25 +*+45 34 *13 4 +/+";
    TForm f(str);
    f.conversToRevPolEnt();

    EXPECT_EQ(strOut, f.get_oForm());
}

TEST(TFormula, cant_convert_arithmetic_expression_to_reverse_polish_notation_if_input_string_not_initialized)
{
    TForm f;

    ASSERT_ANY_THROW(f.conversToRevPolEnt());
}

TEST(TFormula, throws_when_input_arithmetic_expression_is_invalid)
{
    string str = "(1+)2";
    TForm f(str);
    ASSERT_ANY_THROW(f.conversToRevPolEnt());
}


TEST(TFormula, can_calculate_an_expression_in_postfix_form)
{
    string str = "1+2";
    TForm f(str);
    f.conversToRevPolEnt();
    int ans = f.calcArithmExp();
    EXPECT_EQ(3, ans);
}

TEST(TFormula, cant_calculate_an_expression_in_postfix_form_if_it_not_ready)
{
    string str = "1+2";
    TForm f(str);
    ASSERT_ANY_THROW(f.calcArithmExp());
}


