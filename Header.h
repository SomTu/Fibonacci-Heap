#ifndef __HEADER_H__
#define __HEADER_H__
#include <iostream>
#include <list>
#include <vector>
#include <cmath>

const bool max_node_degree_equal_to_num_of_nodes = false;

namespace fib {
	int max_node_degree(int num_of_nodes) {
		// degree <= log(phi)number_of_nodes
		constexpr unsigned long long not_at_all_randomly_but_instead_very_expertly_choden_magic_number = 5;
		if (num_of_nodes < not_at_all_randomly_but_instead_very_expertly_choden_magic_number) return not_at_all_randomly_but_instead_very_expertly_choden_magic_number;
		if (max_node_degree_equal_to_num_of_nodes) {
			return num_of_nodes;
		}
		int result;
		const double phi = 1.618;
		double x = log((double)num_of_nodes) / log(phi);
		result = (int)floor(x) + 2;
		return result;
	}
	template <typename T> class Node;
	template <typename T> class Fib_Heap;
	template <typename T> using N_ptr = std::unique_ptr<Node<T>>;
	template <typename T> void merge_in_vector(std::vector<N_ptr<T>>& vector, N_ptr<T> incoming_node) {
		//if (incoming_node == nullptr) return;
		int incoming_degree = incoming_node->get_degree();
		if (vector[incoming_degree] == nullptr) {
			vector[incoming_degree] = std::move(incoming_node);
			return;
		}
		N_ptr<T> node_inside	= std::move(vector[incoming_degree]);
		int key_inside			= node_inside->get_key();
		int key_incoming		= incoming_node->get_key();
		if (key_inside < key_incoming) {
			node_inside->add_child(std::move(incoming_node));
			merge_in_vector<T>(vector, std::move(node_inside));
		}
		else {
			incoming_node->add_child(std::move(node_inside));
			merge_in_vector<T>(vector, std::move(incoming_node));
		}
	}

	template <typename T> class Node {
	public:
		T data;
		int key;
		int degree;
		std::list<N_ptr<T>> children;
		Node(T data, int key);
		void add_child(N_ptr<T> other_node);
		T get_data();
		int get_key();
		int get_degree();
	};
	template <typename T> class Fib_Heap {
	private:
		Node<T>* min;
		T null_data;
		unsigned int num_of_nodes;
		std::list<N_ptr<T>> root_list;
		Node<T>* merge_node_return_new_min(std::vector<N_ptr<T>>& vector, N_ptr<T> node, Node<T>* current_min);
	public:
		Fib_Heap(T null_data);
		void insert(T data, int key);
		T minimum();
		T extract_min();
		bool empty();
	};

	template <typename T> fib::Node<T>::Node(T _data, int _key) {
		data	= _data;
		key		= _key;
		degree	= 0;
	}
	template <typename T> void fib::Node<T>::add_child(N_ptr<T> other_node) {
		this->degree++;
		this->children.push_back(std::move(other_node));
	}
	template <typename T> T fib::Node<T>::get_data() {
		return data;
	}
	template <typename T> int fib::Node<T>::get_key() {
		return key;
	}
	template <typename T> int fib::Node<T>::get_degree() {
		return degree;
	}
		
	template <typename T> fib::Node<T>* fib::Fib_Heap<T>::merge_node_return_new_min(std::vector<N_ptr<T>>& vector, N_ptr<T> node, Node<T>* current_min) {
		if (current_min == nullptr || node.get()->get_key() < current_min->get_key()) current_min = node.get();
		merge_in_vector<T>(vector, std::move(node));
		return current_min;
	}
	template <typename T> fib::Fib_Heap<T>::Fib_Heap(T _null_data) {
		min				= nullptr;
		null_data		= _null_data;
		num_of_nodes	= 0;
	}
	template <typename T> void fib::Fib_Heap<T>::insert(T data, int key) {
		N_ptr<T> new_node = std::make_unique<Node<T>>(data, key);
		if (min == nullptr || key < min->get_key()) min = new_node.get();
		root_list.push_back(std::move(new_node));
		num_of_nodes++;
	}
	template <typename T> T fib::Fib_Heap<T>::minimum() {
		if (min != nullptr) return min->get_data();
		return null_data;
	}
	template <typename T> T fib::Fib_Heap<T>::extract_min() {
		const T ret_data = this->minimum();
		std::vector<N_ptr<T>> node_vector;
		int max_degree = max_node_degree(num_of_nodes);
		for (int i = 0; i < max_degree; ++i) node_vector.push_back(nullptr);
		Node<T>* new_min = nullptr;

		while (!root_list.empty()) {
			N_ptr<T> current_node = std::move(root_list.front());
			root_list.pop_front();
			if (current_node.get() == min) {
				while (!current_node->children.empty()) {
					N_ptr<T> current_child_node = std::move(current_node->children.front());
					current_node->children.pop_front();
					new_min = merge_node_return_new_min(node_vector, std::move(current_child_node), new_min);
				}
				current_node.reset();
				continue;
			}
			new_min = merge_node_return_new_min(node_vector, std::move(current_node), new_min);
		}
		for (int i = 0; i < node_vector.size(); ++i) if (node_vector[i] != nullptr) root_list.push_front(std::move(node_vector[i]));
		--num_of_nodes;
		min = new_min;
		return ret_data;
	}
	template <typename T> bool fib::Fib_Heap<T>::empty() {
		return root_list.empty();
	}
}

#endif