#include <gtest/gtest.h>
#include "../primes.cpp"

TEST(PrimesTests, mSize) 
{
    class Primes testCont1(100,'q');
    EXPECT_EQ(100, testCont1.size());
    class Primes testCont2(150,'q');
    EXPECT_EQ(150, testCont2.size());
    class Primes testCont3(200,'q');
    EXPECT_EQ(200, testCont3.size());
    class Primes testCont4(300,'q');
    EXPECT_EQ(300, testCont4.size());
}
TEST(PrimesTests, operator)
{
    class Primes testCont1(1,'q');
    EXPECT_EQ(2, testCont1[testCont1.size()-1]);
    EXPECT_EQ(2, testCont1[0]);
    EXPECT_ANY_THROW(testCont1[4]);
}
TEST(PrimesTests, ConstructorRange) 
{
    uint32_t size = 100;
    class Primes testCont(size,'r');
    EXPECT_EQ(25, testCont.size());
    EXPECT_EQ(2,testCont[0]);
    EXPECT_EQ(97,testCont[testCont.size()-1]);
}
TEST(PrimesTests, ConstructorQuantity) 
{
    uint32_t size = 100;
    class Primes testCont(size,'q');
    EXPECT_EQ(100, testCont.size());
    EXPECT_EQ(2,testCont[0]);
    EXPECT_EQ(541,testCont[testCont.size()-1]);
}
TEST(PrimesTests, ConstructorCopy) 
{
    uint32_t size = 100;
    class Primes testCont(size,'q');
    class Primes copyCont(testCont);
    for (uint32_t i = 0; i < testCont.size(); i++)
    {
        EXPECT_EQ(copyCont[i], testCont[i]);
    }
    EXPECT_EQ(copyCont.size(), testCont.size());
}
TEST(PrimesTests, ConstructorMove) 
{
    uint32_t size = 100;
    class Primes testCont(size,'q');
    class Primes copyCont(testCont);
    class Primes moveCont(std::move(testCont));
    EXPECT_EQ(100, moveCont.size());
    for (uint32_t i = 0; i < moveCont.size(); i++)
    {
        EXPECT_EQ(copyCont[i], moveCont[i]);
    }
    EXPECT_EQ(copyCont.size(), moveCont.size());
    EXPECT_EQ(0, testCont.size());
    EXPECT_ANY_THROW(testCont[0]);
}
TEST(PrimesTests, begin) 
{
    uint32_t size = 100;
    class Primes testCont(size,'q');
    EXPECT_EQ(2,*(testCont.begin()));
}
TEST(PrimesTests, end) 
{
    uint32_t size = 100;
    class Primes testCont(size,'q');
    EXPECT_EQ(541,*(testCont.end() - 1));
}
TEST(IteratorTests, operatorStar)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr + 2);
    EXPECT_EQ(arr[2], *it);
}
TEST(IteratorTests, constructor)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr);
    EXPECT_EQ(arr[0], *it);
}
TEST(IteratorTests, operatorPlus)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr);
    EXPECT_EQ(arr[2], *(it + 2));
}
TEST(IteratorTests, operatorMinus)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr + 2);
    EXPECT_EQ(arr[0], *(it - 2));
}
TEST(IteratorTests, postIncrement)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr + 2);
    EXPECT_EQ(arr[2], *(it++));
}
TEST(IteratorTests, preIncrement)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr + 2);
    EXPECT_EQ(arr[3], *(++it));
}
TEST(IteratorTests, postDecrement)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr + 2);
    EXPECT_EQ(arr[2], *(it--));
}
TEST(IteratorTests, preDecrement)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it(arr + 2);
    EXPECT_EQ(arr[1], *(--it));
}
TEST(IteratorTests, operatorComp1)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it1(arr);
    Primes::Iterator it2(arr);
    Primes::Iterator it3(arr + 2);
    EXPECT_EQ(true, it1 == it2);
    EXPECT_EQ(false, it1 == it3);
    
}
TEST(IteratorTests, operatorComp2)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it1(arr);
    Primes::Iterator it2(arr);
    Primes::Iterator it3(arr + 2);
    EXPECT_EQ(true, it1 != it3);
    EXPECT_EQ(false, it1 != it2);
}
TEST(IteratorTests, operatorComp3)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it1(arr);
    Primes::Iterator it3(arr + 2);
    EXPECT_EQ(true, it1 < it3);
    EXPECT_EQ(false, it3 < it1);
}
TEST(IteratorTests, operatorComp4)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it1(arr);
    Primes::Iterator it3(arr + 2);
    EXPECT_EQ(true, it3 > it1);
    EXPECT_EQ(false, it1 > it3);
}
TEST(IteratorTests, operatorComp5)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it1(arr);
    Primes::Iterator it2(arr);
    Primes::Iterator it3(arr + 2);
    EXPECT_EQ(true, it3 >= it1);
    EXPECT_EQ(false, it1 >= it3);
    EXPECT_EQ(true, it1 >= it2);
}
TEST(IteratorTests, operatorComp6)
{
    uint32_t arr[] = {1, 2, 3, 4, 5, 6};
    Primes::Iterator it1(arr);
    Primes::Iterator it2(arr);
    Primes::Iterator it3(arr + 2);
    EXPECT_EQ(true, it1 <= it3);
    EXPECT_EQ(false, it3 <= it1);
    EXPECT_EQ(true, it1 <= it2);
}

int main(int argc, char **argv) 
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}