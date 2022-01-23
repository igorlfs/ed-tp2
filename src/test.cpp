#include "fita.hpp"
#include "heap.hpp"
#include "memlog.hpp"
#include <gtest/gtest.h>

memlog ml;
std::ifstream inputFile;
std::ofstream outputFile;
int roundTracker = 0;

TEST(fita, quicksort) {
    static constexpr unsigned SIZE = 6;
    Page p[SIZE] = {{"aaa", 10}, {"bbb", 10}, {"ccc", 12},
                    {"aaa", 8},  {"ddd", 10}, {"xxx", 7}};
    Page q[SIZE] = {{"ccc", 12}, {"aaa", 10}, {"bbb", 10},
                    {"ddd", 10}, {"aaa", 8},  {"xxx", 7}};
    Fita f;
    f.quickSort(p, SIZE);
    for (uint i = 0; i < SIZE; ++i) {
        EXPECT_EQ(p[i].URL, q[i].URL);
        EXPECT_EQ(p[i].visits, q[i].visits);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
