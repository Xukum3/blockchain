/*	
	sha256 realization:
	MIT License
    Copyright (c) 2020 LekKit https://github.com/LekKit
*/

#include "Merkle_Tree.h"
#include "blockchain.h"
#include <iostream>
#include <vector>

int main() {
	Blockchain chain(3);
	std::cout << "Default chain:\n";
	chain.print_chain();
	std::cout << "\n\n";
	chain.add_block("first block", 4);
	chain.add_block("second block", 4);
	chain.add_block("third block", 4);
	std::cout << "Updated chain:\n";
	chain.print_chain();
}