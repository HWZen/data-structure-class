#include <ostream>
#include "leetcode.cpp"
#include "gtest/gtest.h"

//#pragma comment(lib,"gtestd.lib")
//#pragma comment(lib,"gtest_maind.lib")

// TEST(solution_test, minSteps1)
// {
// 	EXPECT_EQ(4, Solution().lengthOfLastWord("   fly me   to   the moon  "));
// }

// TEST(solution_test, minSteps3)
// {
//     EXPECT_EQ(6, Solution().lengthOfLastWord("luffy is still joyboy"));
// }


// TEST(solution_test,minStep2)
// {
//     EXPECT_EQ(5, Solution().lengthOfLastWord("Hello World"));
// }

// TEST(solution_test,minStep3)
// {
//     EXPECT_EQ(1, Solution().lengthOfLastWord("a"));
// }

struct SolutionTest : testing::Test, Solution
{
	
};

template<typename test_ty,typename res_ty>
struct test_data
{
    test_ty test;
    res_ty res;

    friend ostream &operator<<(ostream &os, const test_data &data)
    {
        os << "test: " << data.test << " res: " << (data.res ? "true" : "false");
        return os;
    }
};

struct isPowerOfThreeTest : SolutionTest, testing::WithParamInterface<test_data<int,bool>>
{

};

TEST_P(isPowerOfThreeTest, isPowerOfThree_Test)
{
    EXPECT_EQ(GetParam().res,isPowerOfThree(GetParam().test));
}

INSTANTIATE_TEST_CASE_P(Default, isPowerOfThreeTest,
    testing::Values(
            test_data<int,bool>{27, true},
            test_data<int,bool>{9,true},
            test_data<int,bool>{3,true},
            test_data<int,bool>{27*3, true},
            test_data<int,bool>{45, false}
            )
);

//TEST_F(SolutionTest, isPowerOfThree1)
//{
//	EXPECT_TRUE(isPowerOfThree(27));
//}
//TEST_F(SolutionTest, isPowerOfThree2)
//{
//	EXPECT_TRUE(isPowerOfThree(9));
//	EXPECT_TRUE(isPowerOfThree(3));
//}
//TEST_F(SolutionTest, isPowerOfThree3)
//{
//	EXPECT_TRUE(isPowerOfThree(27 * 3));
//	EXPECT_TRUE(isPowerOfThree(45));
//}

int main(int argc,char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}