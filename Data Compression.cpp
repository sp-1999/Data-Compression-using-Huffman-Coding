#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Node{
	char data;
	int freq;

	Node *left, *right;

	// constructor
	Node (char d, int f, Node *l = nullptr, Node *r = nullptr){
		data = d;
		freq = f;

		left = l;
		right = r;
	}
};

class compare{
public:
	bool operator() (Node *a, Node *b){
		return (a->freq > b->freq);
	}
};

void print_codes (Node *node, string str){
	if (node != nullptr){
		if (node->data != '*')
			cout << node->data << ": " << str << endl;
		
		print_codes(node->left, str+'0');
		print_codes(node->right, str+'1');
	}
}

void cleanup(Node *node){
	// recurse till all the elements are exhausted
	if (node != nullptr){
		cleanup(node->left);
		cleanup(node->right);

		delete node;
	}
}

void huffman_encode (char *arr, int *freq, size_t n){
	Node *left, *right, *top;
	priority_queue<Node *, vector<Node *>, compare> q;

	// first fill the priority queue with data
	for(size_t i = 0;i < n;i++){
		q.push(new Node(arr[i], freq[i]));
	}

	// time to extract minimum element, combine them and reinsert again
	for(size_t i = 1;i < n;i++){
		left = q.top();
		q.pop();

		right = q.top();
		q.pop();

		// '*' acts as dummy character
		top = new Node('*', left->freq + right->freq, left, right);
		q.push(top);
	}

	print_codes(q.top(), "");

	// free up the heap space
	cleanup(q.top());
}

int main (){
	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
	int freq[] = { 5, 9, 12, 13, 16, 45 };

	huffman_encode(arr, freq, sizeof(arr));

	return 0;
}
