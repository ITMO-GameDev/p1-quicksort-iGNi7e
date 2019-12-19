#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lesson4/FixedSizeAllocator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLesson4
{
	TEST_CLASS( UnitTestAlloc )
	{
	public:

		TEST_METHOD( TestMethod0 )
		{

			/*auto allocator = new FixedSizeAllocator( sizeof( int ) );

			auto first = allocator->Alloc();
			auto second = allocator->Alloc();

			*(int*)first = 15;

			*(int*)second = 18;

			auto third = allocator->Alloc();

			*(int*)third = 48;

			Assert::AreEqual( 4096- allocator->GetBlockSize()*3, (unsigned)4084 );
			Assert::AreEqual( *(int*)first, 15 );*/
		}
	};
}