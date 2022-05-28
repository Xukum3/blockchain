#pragma once

#include "Merkle_Tree.h"
#include <vector>
#include <cstdint>
#include <ctime>
#include <sstream>

class Block {
private:
	std::string _hash;
	std::string _prev_hash;
	time_t _timestamp;
	uint32_t _nonce;
	uint32_t _difficulty;
	std::string _info;

private:
	std::string calculate_hash() const;
	bool check_difficulty(std::string& tmp_hash);

public:
	const std::string& hash() { return _hash; }
	const std::string& prev_hash() { return _prev_hash; }
	Block(std::string info, std::string prev_hash, uint32_t difficulty);
	void mine_block(uint32_t _difficulty);
	void print(std::ostream& out = std::cout);
};

class Blockchain {
	uint32_t difficulty;
	std::vector<Block> chain;

public:
	Blockchain(uint32_t difficulty);
	void add_block(std::string info, uint32_t difficulty);
	void print_chain(std::ostream& out = std::cout);
};