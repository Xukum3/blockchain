#pragma once


#include <vector>
#include <iostream>
#include "sha.h"

template <typename T>
class Merkle_Tree {
private:
	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		char hash[65];
		Node(char hash[65], Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr): left(left), right(right), parent(parent) {
			for (int i = 0; i < 65; ++i) { this->hash[i] = hash[i]; }
			if (left) left->parent = this;
			if (right) right->parent = this;
		}
	};

private:
	std::vector<T> elems;
	size_t size;
	Node* root;

private:
	void next_lvl_hash(const std::vector<Node*>& nodes, size_t first_index, size_t sec_index, char hash[65]) {
		char new_hash[65];
		for (int i = 0; i < 65; ++i) {
			new_hash[i] = nodes[first_index]->hash[i] & nodes[sec_index]->hash[i];
		}
		sha256_easy_hash_hex(new_hash, 65, hash);
	}


public:
	
	Merkle_Tree(const std::vector<std::string>& elements) : size(elements.size()) {
		elems = elements;
		std::vector<Node*> nodes(size);
		size_t num_of_nodes = size;

		for (int i = 0; i < size; ++i) {
			char hash[65];
			sha256_easy_hash_hex(elements[i].c_str(), elements[i].size(), hash);
			nodes[i] = new Node(hash);
		}
		while (num_of_nodes != 1) {
			for (int i = 0; i < num_of_nodes / 2; i++) {
				char new_hash[65];
				next_lvl_hash(nodes, 2*i, 2*i + 1, new_hash);
				Node* higher_node = new Node(new_hash, nodes[2*i], nodes[2*i + 1]);
				nodes[i] = higher_node;
			}
			if (num_of_nodes % 2 == 1) {
				size_t index = num_of_nodes / 2 + 1;
				char new_hash[65];
				next_lvl_hash(nodes, num_of_nodes - 1, num_of_nodes - 1, new_hash);
				Node* higher_node = new Node(new_hash, nodes[num_of_nodes - 1], nodes[num_of_nodes - 1, num_of_nodes - 1]);
				nodes[num_of_nodes / 2 + 1] = higher_node;
			}
			num_of_nodes = (num_of_nodes + 1) / 2;
		}
		
		this->root = nodes[0];
	}

	void print_tree(Node* node, int lvl) {
		for (int i = 0; i < lvl; i++)
			printf("|  ");
		if (node == NULL)
			printf("|->NULL\n");
		else {
			printf("|->%.64s\n", node->hash);
			if (node->left != NULL || node->right != NULL) {
				print_tree(node->left, lvl + 1);
				print_tree(node->right, lvl + 1);
			}
		}
		for (int i = 0; i <= lvl; i++)
			printf("|  ");
		printf("\n");
	}

	void print() {
		print_tree(root, 0);
	}
};



//template <typename T, char* (hash_func)(const T&), size_t hash_len>
//class MerkleNode {
//	...
//}
