/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
//TEST(GuesserTest, smoke_test)
//{
//  Guesser object("Secret");
//  ASSERT_EQ( 1+1, 2 );
//}

// === guesser.distance() tests ===

// simple true test
TEST(GuesserTest, simple_distance_true_test)
{
	Guesser guesser("secret");
	
	int expected = 0;
	int actual = guesser.distance("secret");
	
	ASSERT_EQ( expected, actual );
}

// simple false
TEST(GuesserTest, simple_distance_false_test)
{
	Guesser guesser("secret");
	
	int expected = 6;
	int actual = guesser.distance("zzzzzz");
	
	ASSERT_EQ( expected, actual );
}

// full uppercase test
TEST(GuesserTest, full_uppercase_distance_test)
{
	Guesser guesser("SECRET");
	
	int expected = 0;
	int actual = guesser.distance("SECRET");
	
	ASSERT_EQ( expected, actual );
}

// partial uppercase test
TEST(GuesserTest, partial_uppercase_distance_test)
{
	Guesser guesser("SECRET");
	
	int expected = 6;
	int actual = guesser.distance("secret");
	
	ASSERT_EQ( expected, actual );
}

// secret shorter test
TEST(GuesserTest, secret_shorter_distance_test)
{
	Guesser guesser("secretsecret");
	
	int expected = 6;
	int actual = guesser.distance("secret");
	
	ASSERT_EQ( expected, actual );
}

// secret longer test
TEST(GuesserTest, secret_longer_distance_test)
{
	Guesser guesser("secret");
	
	int expected = 6;
	int actual = guesser.distance("secretsecret");
	
	ASSERT_EQ( expected, actual );
}

// empty secret test
TEST(GuesserTest, empty_secret_distance_test)
{
	Guesser guesser("");
	
	int expected = 6;
	int actual = guesser.distance("secret");
	
	ASSERT_EQ( expected, actual );
}

// empty guess test
TEST(GuesserTest, empty_guess_distance_test)
{
	Guesser guesser("secret");
	
	int expected = 6;
	int actual = guesser.distance("");
	
	ASSERT_EQ( expected, actual );
}

//secret padding test
TEST(GuesserTest, secret_padding_distance_test)
{
	Guesser guesser("z z");
	
	int expected = 2;
	int actual = guesser.distance("zz");
	
	ASSERT_EQ( expected, actual );
}

//guess padding test
TEST(GuesserTest, guess_padding_distance_test)
{
	Guesser guesser("zz");
	
	int expected = 2;
	int actual = guesser.distance("z z");
	
	ASSERT_EQ( expected, actual );
}

//secret >32 char test
TEST(GuesserTest, too_long_secret_distance_test)
{
	Guesser guesser("111122223333444455556666777788889999"); //36 characters - supposed to get shortened to 32
	
	int expected = 0;
	int actual = guesser.distance("11112222333344445555666677778888"); //32 characters
	
	ASSERT_EQ( expected, actual );
}

//guess >32 char test
TEST(GuesserTest, too_long_guess_distance_test)
{
	Guesser guesser("11112222333344445555666677778888"); //32 characters - supposed to get shortened to 32
	
	int expected = 4;
	int actual = guesser.distance("111122223333444455556666777788889999"); //36 characters
	
	ASSERT_EQ( expected, actual );
}

// === guesser.match() tests ===

// unlocked simple match
TEST(GuesserTest, unlocked_simple_match)
{
	Guesser guesser("abc");
	
	int expected = true;
	int actual = guesser.match("abc");
	
	ASSERT_EQ( expected, actual );
}

// locked simple match
TEST(GuesserTest, locked_simple_match)
{
	Guesser guesser("abc");
	
	int expected = false;
	
	guesser.match("zzz");
	guesser.match("zzz");
	guesser.match("zzz");
	int actual = guesser.match("abc");
	
	ASSERT_EQ( expected, actual );
}

// almost locked simple match
TEST(GuesserTest, almost_locked_simple_match)
{
	Guesser guesser("abc");
	
	int expected = true;
	
	guesser.match("zzz");
	guesser.match("zzz");
	int actual = guesser.match("abc");
	
	ASSERT_EQ( expected, actual );
}

// distance =1 match
TEST(GuesserTest, distance_1_match)
{
	Guesser guesser("abc");
	
	int expected = true;
	int actual = guesser.match("abcd");
	
	ASSERT_EQ( expected, actual );
}

// distance =2 match
TEST(GuesserTest, distance_2_match)
{
	Guesser guesser("abc");
	
	int expected = true;
	int actual = guesser.match("abcde");
	
	ASSERT_EQ( expected, actual );
}

// distance =3 match
TEST(GuesserTest, distance_3_match)
{
	Guesser guesser("abc");
	
	int expected = false;
	int actual = guesser.match("abcdef");
	
	ASSERT_EQ( expected, actual );
}