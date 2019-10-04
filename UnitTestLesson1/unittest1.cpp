#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lesson1/Functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLesson1
{
	TEST_CLASS( UnitTestSort )
	{
	public:

		TEST_METHOD( TestMethod0 ) //обратно отсортированный массив
		{
			const int length = 10;
			int arrayTest[length] = { 9,8,7,6,5,4,3,2,1,0 };
			int resultArray[length] = { 0,1,2,3,4,5,6,7,8,9 };
			auto lambda = [] ( int a, int b ) { return a > b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}

		TEST_METHOD( TestMethod1 ) //случайный массив менее 25 элементов(экспериментальное значение)
		{
			const int length = 7;
			int arrayTest[length] = { 3,9,10,2,14,27,5 };
			int resultArray[length] = { 2,3,5,9,10,14,27 };
			auto lambda = [] ( int a, int b ) { return a > b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}

		TEST_METHOD( TestMethod2 ) //случайный массив более 25 элементов с повторениями(экспериментальное значение)
		{
			const int length = 28;
			int arrayTest[length] = { 3,9,10,2,14,27,5,3,9,10,2,14,27,5,3,9,10,2,14,27,5,3,9,10,2,14,27,5 };
			int resultArray[length] = { 2,2,2,2,3,3,3,3,5,5,5,5,9,9,9,9,10,10,10,10,14,14,14,14,27,27,27,27 };
			auto lambda = [] ( int a, int b ) { return a > b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}

		TEST_METHOD( TestMethod3 ) //сортировка по убыванию отсортированного массива по возрастанию
		{
			const int length = 10;
			int arrayTest[length] = { 0,1,2,3,4,5,6,7,8,9 };
			int resultArray[length] = { 9,8,7,6,5,4,3,2,1,0 };
			auto lambda = [] ( int a, int b ) { return a < b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}

		TEST_METHOD( TestMethod4 ) //сортировка массива с вещественным типом данных
		{
			const int length = 10;
			float arrayTest[length] = { 9.8,8.8,7.8,6.6,5.5,4.4,3.3,2.2,1.1,0.0 };
			float resultArray[length] = { 0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.8,8.8,9.8 };
			auto lambda = [] ( float a, float b ) { return a > b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}

		TEST_METHOD( TestMethod5 ) //массив заполненный один элементом
		{
			const int length = 1;
			int arrayTest[length] = { 1 };
			int resultArray[length] = { 1 };
			auto lambda = [] ( int a, int b ) { return a > b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}

		TEST_METHOD( TestMethod6 ) //массив с отрицательными значениями
		{
			const int length = 10;
			int arrayTest[length] = { -9,-8,-7,-6,-5,-4,-3,-2,-1,0 };
			int resultArray[length] = { -9,-8,-7,-6,-5,-4,-3,-2,-1,0 };
			auto lambda = [] ( int a, int b ) { return a > b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}

		TEST_METHOD( TestMethod7 ) //пустой массив
		{
			const int length = 1;
			int arrayTest[length] = {};
			int resultArray[length] = {};
			auto lambda = [] ( int a, int b ) { return a > b; };

			sort( arrayTest, arrayTest + length - 1, lambda );

			for( int i = 0; i < length; i++ )
			{
				Assert::AreEqual( arrayTest[i], resultArray[i] );
			}
		}
	};
}