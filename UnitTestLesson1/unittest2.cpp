#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lesson2/src/Array.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLesson2
{
	TEST_CLASS( UnitTestArray )
	{
	public:

		TEST_METHOD( TestMethod0 ) //insert(value)
		{
			int testarray[10] = { 0,1,2,3,4,5,6,7,8,9 };

			Array< int > a;
			for( int i = 0; i < 10; ++i )
				a.insert( i );

			for( int i = 0; i < a.size() - 1; i++ )
			{
				Assert::AreEqual( a[i], testarray[i] );
			}
		}

		TEST_METHOD( TestMethod1 ) //insert(index, value)
		{
			int testarray[11] = { 0,111,1,2,3,4,5,6,7,8,9 };

			Array< int > a;
			for( int i = 0; i < 10; ++i )
				a.insert( i );
			a.insert( 1, 111 );
			for( int i = 0; i < a.size() - 1; i++ )
			{
				Assert::AreEqual( a[i], testarray[i] );
			}

			try
			{
				a.insert( -2, 7 );
			}
			catch( const char* msg )
			{
				Assert::AreEqual( msg, "Invalid index!" );
			}
		}

		TEST_METHOD( TestMethod2 ) //remove
		{
			int testarray[9] = { 0,2,3,4,5,6,7,8,9 };

			Array< int > a;
			for( int i = 0; i < 10; ++i )
				a.insert( i );
			a.remove( 2 );
			for( int i = 0; i < a.size() - 1; i++ )
			{
				Assert::AreEqual( a[i], testarray[i] );
			}

			try
			{
				a.remove( -2 );
			}
			catch( const char* msg )
			{
				Assert::AreEqual( msg, "Invalid index!" );
			}
		}

		TEST_METHOD( TestMethod3 ) //size
		{

			Array< int > a;

			Assert::AreEqual( a.size(), 0 );
			for( int i = 0; i < 10; ++i )
				a.insert( i );
			a.remove( 2 );
			Assert::AreEqual( a.size(), 9 );
		}

		TEST_METHOD( TestMethod4 ) //Iterator tests
		{

			int testarray[10] = { 0,1,2,3,4,5,6,7,8,9 };
			Array< int > a;

			for( int i = 0; i < 10; ++i )
				a.insert( i );

			auto it = a.get_iterator();

			Assert::AreEqual( it->get(), 0 );

			it->set( 11 );
			Assert::AreEqual( it->get(), 11 );

			if( it->hasNext() ) {
				it->next();
			}
			it->insert( 12 );
			Assert::AreEqual( it->get(), 12 );

			if( it->hasPrev() ) {
				it->prev();
			}
			it->remove();
			Assert::AreEqual( it->get(), 12 );
		}
	};
}