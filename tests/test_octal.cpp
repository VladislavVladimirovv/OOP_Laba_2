#include <gtest/gtest.h>
#include <sstream>
#include "../include/octal.h"

TEST(OctalTest, DefaultConstructor)
{
    Octal oct;
    EXPECT_EQ(oct.getSize(), 0);
}

TEST(OctalTest, FillConstructor)
{
    Octal oct(3, '5');
    EXPECT_EQ(oct.getSize(), 3);

    std::stringstream ss;
    oct.print(ss);
    EXPECT_EQ(ss.str(), "555");
}

TEST(OctalTest, FillConstructorWithZero)
{
    Octal oct(4, '0');
    EXPECT_EQ(oct.getSize(), 4);

    std::stringstream ss;
    oct.print(ss);
    EXPECT_EQ(ss.str(), "0000");
}

TEST(OctalTest, InitializerListConstructor)
{
    Octal oct({'1', '2', '3'});
    EXPECT_EQ(oct.getSize(), 3);

    std::stringstream ss;
    oct.print(ss);
    EXPECT_EQ(ss.str(), "123");
}

TEST(OctalTest, StringConstructor)
{
    Octal oct("4567");
    EXPECT_EQ(oct.getSize(), 4);

    std::stringstream ss;
    oct.print(ss);
    EXPECT_EQ(ss.str(), "4567");
}

TEST(OctalTest, StringConstructorWithLeadingZeros)
{
    Octal oct("007");
    EXPECT_EQ(oct.getSize(), 3);

    std::stringstream ss;
    oct.print(ss);
    EXPECT_EQ(ss.str(), "007");
}

TEST(OctalTest, CopyConstructor)
{
    Octal original("12345");
    Octal copy(original);

    EXPECT_EQ(original.getSize(), copy.getSize());
    EXPECT_TRUE(original.equals(copy));

    std::stringstream ss1, ss2;
    original.print(ss1);
    copy.print(ss2);
    EXPECT_EQ(ss1.str(), ss2.str());
}

TEST(OctalTest, MoveConstructor)
{
    Octal original("789");
    size_t original_size = original.getSize();

    Octal moved(std::move(original));

    EXPECT_EQ(moved.getSize(), original_size);
    EXPECT_EQ(original.getSize(), 0);

    std::stringstream ss;
    moved.print(ss);
    EXPECT_EQ(ss.str(), "789");
}

TEST(OctalTest, AddOperationSameSize)
{
    Octal oct1("123");
    Octal oct2("456");

    Octal result = oct1.add(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "601");
}

TEST(OctalTest, AddOperationDifferentSizes)
{
    Octal oct1("777");
    Octal oct2("1");

    Octal result = oct1.add(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "1000");
}

TEST(OctalTest, AddOperationWithCarry)
{
    Octal oct1("7");
    Octal oct2("1");

    Octal result = oct1.add(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "10");
}

TEST(OctalTest, SubstructOperationSameSize)
{
    Octal oct1("456");
    Octal oct2("123");

    Octal result = oct1.substruct(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "333");
}

TEST(OctalTest, SubstructOperationWithBorrow)
{
    Octal oct1("100");
    Octal oct2("1");

    Octal result = oct1.substruct(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "77");
}

TEST(OctalTest, SubstructOperationResultSingleDigit)
{
    Octal oct1("10");
    Octal oct2("1");

    Octal result = oct1.substruct(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "7");
}

TEST(OctalTest, SubstructThrowsWhenFirstSmaller)
{
    Octal oct1("123");
    Octal oct2("456");

    EXPECT_THROW(oct1.substruct(oct2), std::invalid_argument);
}

TEST(OctalTest, SubstructEqualNumbersReturnsZero)
{
    Octal oct1("777");
    Octal oct2("777");

    Octal result = oct1.substruct(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "0");
    EXPECT_EQ(result.getSize(), 1);
}

TEST(OctalTest, AddAssignOperation)
{
    Octal oct1("12");
    Octal oct2("34");

    Octal result = oct1.add_assign(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "46");
}

TEST(OctalTest, SubstructAssignOperation)
{
    Octal oct1("100");
    Octal oct2("1");

    Octal result = oct1.substruct_assign(oct2);

    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "77");
}

TEST(OctalTest, CopyOperationSameSize)
{
    Octal oct1(3, '0');
    Octal oct2("123");

    oct1.copy(oct2);

    std::stringstream ss;
    oct1.print(ss);
    EXPECT_EQ(ss.str(), "123");
    EXPECT_TRUE(oct1.equals(oct2));
}

TEST(OctalTest, CopyOperationToSelf)
{
    Octal oct("456");

    EXPECT_NO_THROW(oct.copy(oct));

    std::stringstream ss;
    oct.print(ss);
    EXPECT_EQ(ss.str(), "456");
}

TEST(OctalTest, CopyThrowsWhenSizesDifferent)
{
    Octal oct1(2, '0');
    Octal oct2("123");

    EXPECT_THROW(oct1.copy(oct2), std::invalid_argument);
}

TEST(OctalTest, EqualsMethodSameNumbers)
{
    Octal oct1("123");
    Octal oct2("123");

    EXPECT_TRUE(oct1.equals(oct2));
    EXPECT_TRUE(oct2.equals(oct1));
}

TEST(OctalTest, EqualsMethodDifferentNumbers)
{
    Octal oct1("123");
    Octal oct2("124");

    EXPECT_FALSE(oct1.equals(oct2));
    EXPECT_FALSE(oct2.equals(oct1));
}

TEST(OctalTest, EqualsMethodDifferentSizes)
{
    Octal oct1("123");
    Octal oct2("1234");

    EXPECT_FALSE(oct1.equals(oct2));
}

TEST(OctalTest, LargestMethodFirstLarger)
{
    Octal oct1("200");
    Octal oct2("100");

    EXPECT_TRUE(oct1.largest(oct2));
    EXPECT_FALSE(oct2.largest(oct1));
}

TEST(OctalTest, LargestMethodSameSizeDifferentValues)
{
    Octal oct1("123");
    Octal oct2("122");

    EXPECT_TRUE(oct1.largest(oct2));
    EXPECT_FALSE(oct2.largest(oct1));
}

TEST(OctalTest, LargestMethodEqualNumbers)
{
    Octal oct1("123");
    Octal oct2("123");

    EXPECT_FALSE(oct1.largest(oct2));
    EXPECT_FALSE(oct2.largest(oct1));
}

TEST(OctalTest, SmallestMethodFirstSmaller)
{
    Octal oct1("100");
    Octal oct2("200");

    EXPECT_TRUE(oct1.smallest(oct2));
    EXPECT_FALSE(oct2.smallest(oct1));
}

TEST(OctalTest, SmallestMethodSameSizeDifferentValues)
{
    Octal oct1("122");
    Octal oct2("123");

    EXPECT_TRUE(oct1.smallest(oct2));
    EXPECT_FALSE(oct2.smallest(oct1));
}

TEST(OctalTest, SmallestMethodEqualNumbers)
{
    Octal oct1("123");
    Octal oct2("123");

    EXPECT_FALSE(oct1.smallest(oct2));
    EXPECT_FALSE(oct2.smallest(oct1));
}

TEST(OctalTest, ZeroOperationsAdd)
{
    Octal zero(1, '0');
    Octal number("123");

    Octal result = number.add(zero);
    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "123");
    EXPECT_TRUE(result.equals(number));
}

TEST(OctalTest, ZeroOperationsSubstruct)
{
    Octal zero(1, '0');
    Octal number("123");

    Octal result = number.substruct(zero);
    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "123");
    EXPECT_TRUE(result.equals(number));
}

TEST(OctalTest, ZeroOperationsSubstructFromZeroThrows)
{
    Octal zero(1, '0');
    Octal number("123");

    EXPECT_THROW(zero.substruct(number), std::invalid_argument);
}

TEST(OctalTest, SingleDigitOperationsAdd)
{
    Octal oct1("7");
    Octal oct2("1");

    Octal result = oct1.add(oct2);
    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "10");
}

TEST(OctalTest, SingleDigitOperationsSubstruct)
{
    Octal oct1("7");
    Octal oct2("1");

    Octal result = oct1.substruct(oct2);
    std::stringstream ss;
    result.print(ss);
    EXPECT_EQ(ss.str(), "6");
}

TEST(OctalTest, MaximumSingleDigitOperations)
{
    Octal oct1("7");
    Octal oct2("7");

    Octal add_result = oct1.add(oct2);
    std::stringstream ss1;
    add_result.print(ss1);
    EXPECT_EQ(ss1.str(), "16");

    Octal sub_result = oct1.substruct(oct2);
    std::stringstream ss2;
    sub_result.print(ss2);
    EXPECT_EQ(ss2.str(), "0");
}

TEST(OctalTest, DataIntegrityAfterOperations)
{
    Octal original1("123");
    Octal original2("456");

    size_t original_size1 = original1.getSize();
    size_t original_size2 = original2.getSize();

    Octal result = original1.add(original2);

    EXPECT_EQ(original1.getSize(), original_size1);
    EXPECT_EQ(original2.getSize(), original_size2);

    std::stringstream ss1, ss2;
    original1.print(ss1);
    original2.print(ss2);
    EXPECT_EQ(ss1.str(), "123");
    EXPECT_EQ(ss2.str(), "456");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}