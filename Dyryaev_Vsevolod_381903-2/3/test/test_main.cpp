#include <gtest/gtest.h>
#include "test_leks.cpp"
#include "test_synt.cpp"
#include "test_broadcast.cpp"
#include "test_full_analiz.cpp"


using namespace std;

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
