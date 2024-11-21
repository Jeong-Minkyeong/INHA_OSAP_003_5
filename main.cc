#include <iostream>
#include <string>
#include "avl_tree.h"

using namespace std;

void UserTest();

int main() {
	int T;
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++)
	{
		UserTest();
	}
}

void UserTest() {
	AvlTree Avltree;
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; i++)
	{
		string command;
		cin >> command;

		
		if (command == "insert") {
			int x;
			cin >> x;
			Avltree.insert(x);
		}

		else if (command == "find") {
			int x;
			cin >> x;
			Avltree.find(x);
		}

		else if (command == "empty") {
			Avltree.Empty();
		}

		else if (command == "size") {
			Avltree.Size();
		}

		else if (command == "erase") {
			int x;
			cin >> x;
			Avltree.erase(x);
		}

		else if (command == "average") {
			int x;
			cin >> x;
			Avltree.average(x);
		}
	}
}