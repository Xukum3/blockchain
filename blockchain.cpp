#include "blockchain.h"

std::string Block::calculate_hash() const {
	char* tmp_hash = new char[65];
	tmp_hash[64] = '\0';
	std::stringstream ss;
	ss << _prev_hash << _timestamp << _info << _nonce;
	sha256_easy_hash_hex(ss.str().c_str(), ss.str().size(), tmp_hash);
	return tmp_hash;
}

bool Block::check_difficulty(std::string& tmp_hash)
{
	for (size_t i = 0;  i < _difficulty; ++i) {
		if (tmp_hash[i] != '0') return false;
	}
	return true;
}

Block::Block(std::string info, std::string prev_hash, uint32_t difficulty): _info(info), _prev_hash(prev_hash), _nonce(0), _difficulty(difficulty) {
	_timestamp = time(nullptr);
	mine_block(difficulty);
}

void Block::mine_block(uint32_t difficulty) {
	_difficulty = difficulty;
	std::string tmp_hash;
	while (1) {
		tmp_hash = calculate_hash();
		if (check_difficulty(tmp_hash)) {
			_hash = tmp_hash;
			return;
		}
		else {
			_nonce += 1;
		}
	}
}

void Block::print(std::ostream& out)
{
	std::cout << _info << " " << _prev_hash << " " << _hash << " " << _nonce << "\n";
}

Blockchain::Blockchain(uint32_t difficulty) : difficulty(difficulty) {
	std::string first_hash(64, '0');
	chain.emplace_back("Genesis", first_hash, difficulty);
}

void Blockchain::add_block(std::string info, uint32_t difficulty) {
	Block new_block(info, chain[chain.size() - 1].hash(), 4);
	chain.push_back(new_block);
}

void Blockchain::print_chain(std::ostream& out) {
	for (auto it : chain) {
		it.print();
	}
}
