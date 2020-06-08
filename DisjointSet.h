#pragma once
#include <unordered_map>

using namespace std;

template<typename T>
struct Node {
	T _val;
	int _rank;
	Node* _parent;

	Node(T val, int rank, Node* parent = nullptr) :
		_val(val), _rank(rank), _parent(parent) {}
};

template<typename T>
class DisjointSet
{
	private:
		unordered_map<T, Node<T>*> _map;
	public:
		DisjointSet() { }

		void makeSet(const T& data) {
			auto node = new Node<T>(data, 0);
			node->_parent = node;
			_map[data] = node;
		}

		void doUnion(const T& data1, const T& data2) {
			Node<T>* node1 = _map[data1];
			Node<T>* node2 = _map[data2];

			Node<T>* parent1 = findSet(node1), *parent2 = findSet(node2);
			if (parent1->_val == parent2->_val)
				return;

			if (parent1->_rank >= parent2->_rank) {
				parent1->_rank += parent1->_rank == parent2->_rank;
				parent2->_parent = parent1;
			}
			else
				parent1->_parent = parent2;
		}

		T findSet(const T& data) {
			return findSet(_map[data])->_val;
		}

		size_t size() const {
			return _map.size();
		}

		bool contains(const T& data) const {
			return _map.find(data) != _map.end();
		}

		Node<T>* findSet(Node<T>* node) {
			if (node == node->_parent)
				return node;
			node->_parent = findSet(node->_parent);
			return node->_parent;
		}
};
