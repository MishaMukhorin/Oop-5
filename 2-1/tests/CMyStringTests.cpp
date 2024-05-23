//
// Created by mrLogic on 5/16/2024.
//

#include "../CMyString.h"
#include <gtest/gtest.h>

TEST(CreateTest, EmptyCreated)
{
    CMyString str;
    EXPECT_EQ(str.GetLength(), 0);
    EXPECT_EQ(str.GetCapacity(), 1);
    EXPECT_STREQ(str.GetStringData(), "");
}

TEST(CreateTest, NotEmptyCreated)
{
    CMyString str("test");
    EXPECT_EQ(str.GetLength(), 4);
    EXPECT_EQ(str.GetCapacity(), 5);
    EXPECT_STREQ(str.GetStringData(), "test");
}

TEST(CreateTest, CreatedWithLength)
{
    CMyString str("test string", 4);
    EXPECT_EQ(str.GetLength(), 4);
    EXPECT_EQ(str.GetCapacity(), 5);
    EXPECT_STREQ(str.GetStringData(), "test");
}

TEST(CreateTest, CreatedEndPoint)
{
    CMyString str("test\0 string");
    //EXPECT_EQ(str.GetLength(), 12); //todo
   // EXPECT_EQ(str.GetCapacity(), 13);
   // XPECT_STREQ(str.GetStringData(), "test\0 string");
}

TEST(CreateTest, CreatedWithLengthLess)
{
    CMyString str("test\0 string", 10);
    EXPECT_EQ(str.GetLength(), 10);
    EXPECT_EQ(str.GetCapacity(), 11);
    EXPECT_STREQ(str.GetStringData(), "test\0 stri");
}

TEST(CreateTest, CreateStringLessThenLength)
{
    CMyString str("test st", 10);
    EXPECT_EQ(str.GetLength(), 10);
    EXPECT_EQ(str.GetCapacity(), 11);
    EXPECT_STREQ(str.GetStringData(), "test st");
}

TEST(CreateTest, CreatedFromSTDString)
{
    std::string stdString = "test";
    CMyString str(stdString);
    EXPECT_EQ(str.GetLength(), 4);
    EXPECT_EQ(str.GetCapacity(), 5);
    EXPECT_STREQ(str.GetStringData(), "test");
}

TEST(CreateTest, CreatedByCopy)
{
    CMyString str1("test");
    const CMyString& str2(str1);
    EXPECT_EQ(str2.GetLength(), 4);
    EXPECT_EQ(str2.GetCapacity(), 5);
    EXPECT_STREQ(str2.GetStringData(), "test");
}

TEST(CreateTest, CreatedByTempObject)
{
    CMyString str(CMyString("test"));
    EXPECT_EQ(str.GetLength(), 4);
    EXPECT_EQ(str.GetCapacity(), 5);
    EXPECT_STREQ(str.GetStringData(), "test");
}

TEST(FunctionTest, GetSubstring)
{
    CMyString str1;
    CMyString str2 = CMyString("data");

    CMyString substr1 = str1.SubString(0);
    CMyString substr2 = str2.SubString(1, 2);
    CMyString substr3 = str2.SubString(0);
    CMyString substr4 = str2.SubString(4);
    CMyString substr5 = str2.SubString(0, 10);

    EXPECT_STREQ(substr1.GetStringData(), "");
    EXPECT_STREQ(substr2.GetStringData(), "at");
    EXPECT_STREQ(substr3.GetStringData(), "data");
    EXPECT_STREQ(substr4.GetStringData(), "");
    EXPECT_STREQ(substr5.GetStringData(), "data");
}

TEST(FunctionTest, Clean)
{
    CMyString str = CMyString("test");
    str.Clear();
    EXPECT_EQ(str.GetLength(), 0);
    EXPECT_EQ(str.GetCapacity(), 1);
    EXPECT_STREQ(str.GetStringData(), "");
}

TEST(LogicTest, RecalculateCapacity)
{
    CMyString str1 = CMyString("test");
    CMyString str2 = CMyString("more tests abc");
    str1 += str2;
    EXPECT_EQ(str1.GetCapacity(), 38);
    str2 += str1;
    EXPECT_EQ(str2.GetCapacity(), 66);
}

TEST(OperationTest, ReadBySquareBrackets)
{
    CMyString str1 = CMyString("s");
    CMyString str2 = CMyString("data");
    EXPECT_EQ(str1[0], 's');
    EXPECT_EQ(str2[0], 'd');
    EXPECT_EQ(str2[3], 'a');
}

TEST(OperationTest, ReadBySquareBracketsError)
{
    CMyString str = CMyString("data");
    EXPECT_THROW(str[4], std::range_error);
}

TEST(OperationTest, WriteBySquareBrackets)
{
    CMyString str = CMyString("data");
    str[3] = 'e';
    EXPECT_STREQ(str.GetStringData(), "date");
}

TEST(OperationTest, WriteBySquareBracketsError)
{
    CMyString str = CMyString("data");
    EXPECT_THROW(str[4] = 'e', std::range_error);
}

TEST(OperationTest, CopyAssignment)
{
    CMyString str1 = CMyString("test");
    CMyString str2 = CMyString("data's");

    str1 = str2;
    EXPECT_EQ(str1.GetLength(), str2.GetLength());
    EXPECT_STREQ(str1.GetStringData(), str2.GetStringData());

    str2 = str2;
    EXPECT_EQ(str2.GetLength(), str2.GetLength());
    EXPECT_STREQ(str2.GetStringData(), str2.GetStringData());
}

TEST(OperationTest, AssignmentHimself)
{
    CMyString str = CMyString("data's");

    str = str;
    EXPECT_EQ(str.GetLength(), 6);
    EXPECT_EQ(str.GetCapacity(), 7);
    EXPECT_STREQ(str.GetStringData(), "data's");
}

TEST(OperationTest, MoveAssignment)
{
    CMyString str;
    str = CMyString("test");
    EXPECT_EQ(str.GetLength(), 4);
    EXPECT_EQ(str.GetCapacity(), 5);
    EXPECT_STREQ(str.GetStringData(), "test");
}

TEST(OperationTest, Concatenate)
{
    CMyString str1;
    CMyString str2 = CMyString("s");
    CMyString str3 = CMyString("data");
    EXPECT_STREQ((str1 + str1).GetStringData(), "");
    EXPECT_STREQ((str1 + str2).GetStringData(), "s");
    EXPECT_STREQ((str2 + str3).GetStringData(), "sdata");
    EXPECT_STREQ((str3 + str2).GetStringData(), "datas");
}

TEST(OperationTest, ConcatenateWithSTDString)
{
    CMyString str1 = CMyString("data");
    std::string str2 = "s";
    EXPECT_STREQ((str1 + str2).GetStringData(), "datas");
    EXPECT_STREQ((str2 + str1).GetStringData(), "sdata");
}

TEST(OperationTest, ConcatenateWithArrayOfChar)
{
    CMyString str1 = CMyString("data");

    EXPECT_STREQ((str1 + "ab").GetStringData(), "dataab");
    EXPECT_STREQ(("ab" + str1).GetStringData(), "abdata");
}

TEST(OperationTest, ConcatenateWithAssignment)
{
    CMyString str1 = CMyString("data");
    CMyString str2 = CMyString("s");
    str1 += str2;
    EXPECT_STREQ(str1.GetStringData(), "datas");
    str1 += str1;
    EXPECT_STREQ(str1.GetStringData(), "datasdatas");
}

TEST(OperationTest, Equality)
{
    CMyString str1 = CMyString("s");
    CMyString str2 = CMyString("data");
    EXPECT_TRUE(str1 == str1);
    EXPECT_FALSE(str1 == str2);
}

TEST(OperationTest, NotEquality)
{
    CMyString str1 = CMyString("s");
    CMyString str2 = CMyString("data");
    EXPECT_FALSE(str1 != str1);
    EXPECT_TRUE(str1 != str2);
}

TEST(OperationTest, Less)
{
    CMyString str1 = CMyString("s");
    CMyString str2 = CMyString("data");
    EXPECT_TRUE(str1 < str2);
    EXPECT_FALSE(str2 < str1);
}

TEST(OperationTest, More)
{
    CMyString str1 = CMyString("s");
    CMyString str2 = CMyString("data");
    EXPECT_FALSE(str1 > str2);
    EXPECT_TRUE(str2 > str1);
}

TEST(OperationTest, LessEqual)
{
    CMyString str1 = CMyString("s");
    CMyString str2 = CMyString("data");
    EXPECT_TRUE(str1 <= str1);
    EXPECT_TRUE(str1 <= str2);
    EXPECT_FALSE(str2 <= str1);
}

TEST(OperationTest, MoreEqual)
{
    CMyString str1 = CMyString("s");
    CMyString str2 = CMyString("data");
    EXPECT_TRUE(str1 >= str1);
    EXPECT_TRUE(str2 >= str1);
    EXPECT_FALSE(str1 >= str2);
}

TEST(StreamTest, ReadFromStream)
{
    CMyString str1;
    std::istringstream input("");
    input >> str1;
    EXPECT_STREQ(str1.GetStringData(), "");

    input.clear();
    input.str("  word1 word2");
    input >> str1;
    EXPECT_STREQ(str1.GetStringData(), "word1");
}

TEST(StreamTest, WriteToStream)
{
    CMyString str = CMyString("data");
    std::ostringstream output;
    output << str;
    EXPECT_EQ(output.str(), "data");
    output << " " << str;
    EXPECT_EQ(output.str(), "data data");
}

TEST(IteratorTest, Iterator)
{
    CMyString str1;
    CMyString str2 = CMyString("s");
    CMyString str3 = CMyString("data");

    EXPECT_TRUE(str1.begin() == str1.end());
    EXPECT_TRUE(str2.begin() != str2.end());
    EXPECT_TRUE(str3.begin() != str3.end());

    EXPECT_FALSE(str2.begin() == str2.end());
    EXPECT_TRUE(str2.begin() == str2.begin());
    EXPECT_TRUE(str2.begin() != str2.end());
    EXPECT_FALSE(str2.begin() != str2.begin());

    EXPECT_EQ(*--str3.end(), 'a');
    EXPECT_EQ(*(str3.end() - 1), 'a');
    EXPECT_EQ(*(str3.end() - 1)--, 'a');

    EXPECT_EQ(*++str3.begin(), 'a');
    EXPECT_EQ(*(str3.begin() + 1), 'a');
    EXPECT_EQ(*str3.begin()++, 'd');

    EXPECT_EQ(str1.end() - str1.begin(), 0);
    EXPECT_EQ(str2.end() - str2.begin(), 1);
    EXPECT_EQ(str3.end() - str3.begin(), 4);
    EXPECT_EQ(str3.begin() - str3.end(), -4);

    EXPECT_EQ(*str2.begin(), 's');
    EXPECT_EQ(str3.begin()[2], 't');
    str3.begin()[3] = 'e';
    EXPECT_STREQ(str3.GetStringData(), "date");
}

TEST(IteratorTest, ConstIterator)
{
    const CMyString str1;
    const CMyString str2 = CMyString("s");
    const CMyString str3 = CMyString("data");

    EXPECT_TRUE(str1.begin() == str1.end());
    EXPECT_TRUE(str2.begin() != str2.end());
    EXPECT_TRUE(str3.begin() != str3.end());

    EXPECT_FALSE(str2.begin() == str2.end());
    EXPECT_TRUE(str2.begin() == str2.begin());
    EXPECT_TRUE(str2.begin() != str2.end());
    EXPECT_FALSE(str2.begin() != str2.begin());

    EXPECT_EQ(*--str3.end(), 'a');
    EXPECT_EQ(*(str3.end() - 1), 'a');
    EXPECT_EQ(*(str3.end() - 1)--, 'a');

    EXPECT_EQ(*++str3.begin(), 'a');
    EXPECT_EQ(*(str3.begin() + 1), 'a');
    EXPECT_EQ(*str3.begin()++, 'd');

    EXPECT_EQ(str1.end() - str1.begin(), 0);
    EXPECT_EQ(str2.end() - str2.begin(), 1);
    EXPECT_EQ(str3.end() - str3.begin(), 4);
    EXPECT_EQ(str3.begin() - str3.end(), -4);

    EXPECT_EQ(*str2.begin(), 's');
    EXPECT_EQ(str3.begin()[2], 't');
}

TEST(IteratorTest, RangeBasedLoop)
{
    CMyString str1("data");
    const CMyString str2("data");

    std::string stlStr1;
    for (auto ch : str1)
    {
        stlStr1 += ch;
    }

    std::string stlStr2;
    for (auto ch : str1)
    {
        stlStr2 += ch; //todo copy, sort, min_val, max_val...
    }
    EXPECT_EQ(stlStr1, "data");
    EXPECT_EQ(stlStr2, "data");
}

TEST(IteratorTest, ReverseIteration)
{
    CMyString str1("data");
    const CMyString str2("data");

    std::string reversed1;
    for (auto it = str1.rbegin(); it != str1.rend(); ++it)
    {
        reversed1 += *it;
    }

    std::string reversed2;
    for (auto it = str2.rbegin(); it != str2.rend(); ++it)
    {
        reversed2 += *it;
    }

    EXPECT_EQ(reversed1, "atad");  //
    EXPECT_EQ(reversed2, "atad");
}

TEST(IteratorTest, TransformToUppercase)
{
    CMyString str1("test");

    std::transform(str1.begin(), str1.end(), str1.begin(), ::toupper);

    EXPECT_STREQ(str1.GetStringData(), "TEST");
}

GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}