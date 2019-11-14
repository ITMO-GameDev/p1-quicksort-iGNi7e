#include "stdafx.h"
#include <string>
#include "CppUnitTest.h"
#include "../Lesson3/src/LLRBTreeDictionary.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLesson3
{
	TEST_CLASS( UnitTestTree )
	{
	public:

		TEST_METHOD( TestMethod0 ) //put and search
		{
			LLRBTreeDictionary<int, std::string> test;
			std::string one = "one";
			std::string two = "two";
			std::string three = "three";
			std::string four = "four";
			std::string five = "five";
			std::string six = "six";
			std::string seven = "seven";
			std::string eight = "eight";
			std::string nine = "nine";
			std::string ten = "ten";
			test.put( 1, "one" );
			test.put( 2, "two" );
			test.put( 3, "three" );
			test.put( 4, "four" );
			test.put( 5, "five" );
			test.put( 6, six );
			test.put( 7, seven );
			test.put( 8, eight );
			test.put( 9, nine );
			test.put( 10, ten );

			Assert::AreEqual( ToString( test.search( 1 )->val ), ToString( one ) );
			Assert::AreEqual( ToString( test.search( 2 )->val ), ToString( two ) );
			Assert::AreEqual( ToString( test.search( 3 )->val ), ToString( three ) );
			Assert::AreEqual( ToString( test.search( 4 )->val ), ToString( four ) );
			Assert::AreEqual( ToString( test.search( 5 )->val ), ToString( five ) );

			//сверка построения дерева
			Assert::AreEqual( ToString( test.search( 8 )->left->val ), ToString( six ) );
			Assert::AreEqual( ToString( test.search( 2 )->right->val ), ToString( three ) );
			Assert::AreEqual( ToString( test.search( 6 )->right->val ), ToString( seven ) );

			//проверка замены значения
			test.put( 7, one );
			Assert::AreEqual( ToString( test.search( 7 )->val ), ToString( one ) );
		}

		TEST_METHOD( TestMethod1 ) { //remove, contains
			LLRBTreeDictionary<int, std::string> test;
			std::string one = "one";
			std::string two = "two";
			std::string three = "three";
			std::string four = "four";
			std::string five = "five";
			std::string six = "six";
			std::string seven = "seven";
			std::string eight = "eight";
			std::string nine = "nine";
			std::string ten = "ten";
			test.put( 1, "one" );
			test.put( 2, "two" );
			test.put( 3, "three" );
			test.put( 4, "four" );
			test.put( 5, "five" );
			test.put( 6, six );
			test.put( 7, seven );
			test.put( 8, eight );
			test.put( 9, nine );
			test.put( 10, ten );

			Assert::AreEqual( test.contains( 5 ), true );
			Assert::AreEqual( test.contains( 11 ), false );

			test.remove( 1 );
			test.remove( 3 );
			test.remove( 1 );

			Assert::AreEqual( test.contains( 1 ), false );
			Assert::AreEqual( test.contains( 3 ), false );
		}
		TEST_METHOD( TestMethod2 ) { //test iterator
			LLRBTreeDictionary<std::string, int> npc;
			npc.put( "health", 10 );
			npc.put( "armor", 20 );
			auto it = npc.get_iterator();
			Assert::AreEqual( it->get(), 10 );
			Assert::AreEqual( it->hasPrev(), false );
			Assert::AreEqual( it->hasNext(), true );

			it->set( 15 );
			Assert::AreEqual( it->get(), 15 );
			it->next();
			Assert::AreEqual( it->hasPrev(), true );
			it->next();
			Assert::AreEqual( it->hasNext(), false );
			it->prev();
			it->prev();
			Assert::AreEqual( it->get(), 15 );

		}
	};
}