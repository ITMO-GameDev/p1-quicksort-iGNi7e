#include <iostream>
#include "windows.h"
#include "FixedSizeAllocator.h"
#include "FreeListAllocator.h"


int main()
{
	auto allocator = new FixedSizeAllocator( sizeof( int ) );

	auto first = allocator->Alloc();
	auto second = allocator->Alloc();

	*static_cast<int*>( first ) = 228;

	*static_cast<int*>( second ) = 322;

	auto third = allocator->Alloc();

	*static_cast<int*>( third ) = 55;

	delete allocator;


	auto listAllocator = new FreeListAllocator( 4096 * 40, FreeListAllocator::FIND_FIRST );

	listAllocator->Init();

	auto ptr = listAllocator->Allocate( 512, 8 );

	listAllocator->Free( ptr );

	delete listAllocator;

}
