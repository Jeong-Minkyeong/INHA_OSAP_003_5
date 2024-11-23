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
			tree.insert(x);
		}

		else if (command == "find") {
			int x;
			cin >> x;
			cout<<tree.find(x)<<endl;
		}

		else if (command == "size") {
			tree.size();
		}

		/*else if (command == "empty") {
			tree.Empty();
		}

		else if (command == "size") {
			tree.Size();
		}

		else if (command == "erase") {
			int x;
			cin >> x;
			tree.erase(x);
		}

		else if (command == "average") {
			int x;
			cin >> x;
			tree.average(x);
		}*/
	}
}


/*#include <iostream>
#include "avl_tree.h"

int main() {
    

    // 트리에 노드를 직접 삽입
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);


    // Find 테스트
    std::cout << "Find (Depth + Height) of 10: " << tree.find(10) << "\n";
    std::cout << "Find (Depth + Height) of 5: " << tree.find(5) << "\n";
    std::cout << "Find (Depth + Height) of 2: " << tree.find(2) << "\n";
    std::cout << "Find (Depth + Height) of 20: " << tree.find(20) << "\n"; // 없는 노드

    // Size 테스트
    std::cout << "Size of tree: " << tree.size() << "\n";

    return 0;
}
*/