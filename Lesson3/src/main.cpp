#include <string>
#include <iostream>
#include "LLRBTreeDictionary.cpp"

int main() {
	LLRBTreeDictionary<std::string, int> npc;
	npc.put( "health", 10 );
	npc.put( "armor", 20 );
	npc.put( "ammo", 5 );
	for( auto it = npc.get_iterator();
		it->hasNext();
		it->next() ) {
		std::cout << it->key() << " " << it->get() << std::endl;
	}

	auto it = npc.get_iterator();
	std::cout << it->hasPrev() << std::endl;


	npc.remove( "ammo" );
	std::cout << npc.contains( "ammo" ) << std::endl;

	system( "pause" );
}