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
	AvlTree<int> tree;
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; i++)
	{
		string command;
		cin >> command;

		
		if (command == "insert") {
			int x;
			cin >> x;
			tree.Insert(x);
		}

		else if (command == "find") {
			int x;
			cin >> x;
			cout<<tree.Find(x)<<endl;
		}

		else if (command == "size") {
			tree.Size();
		}

		/*else if (command == "empty") {
			tree.Empty();
		}

		else if (command == "rase") {
			int x;
			cin >> x;
			tree.Erase(x);
		}

		else if (command == "average") {
			int x;
			cin >> x;
			tree.Average(x);
		}*/
	}
}

