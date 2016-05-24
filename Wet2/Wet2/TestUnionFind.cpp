#include "UnionFind.h"
#include <iostream>
using std::cout;

int main() {
	UnionFind UF(8);
	bool flag = false;
	flag = UF.getNumOfGroups() == 8;
	UF.Union(1, 3);
	flag = UF.getNumOfGroups() == 7;
	UF.Union(6, 4);
	flag = UF.getNumOfGroups() == 6;
	UF.Union(6, 2);
	flag = UF.getNumOfGroups() == 5;
	UF.Union(6, 7);
	flag = UF.getNumOfGroups() == 4;
	if (!flag) {
		cout << "EROOR\n";
	}

	flag = UF.Find(3) == 1;
	flag = UF.Find(1) == 1;
	flag = UF.Find(5) == 5;
	flag = UF.Find(4) == 6;
	flag = UF.Find(2) == 6;
	flag = UF.Find(7) == 6;
	flag = UF.Find(6) == 6;
	flag = UF.Find(4) == 6;
	flag = UF.Find(2) == 6;
	flag = UF.Find(7) == 6;
	flag = UF.Find(6) == 6;
	if (!flag) {
		cout << "EROOR\n";
	}

	UF.Union(5, 6);
	flag = UF.getNumOfGroups() == 3;
	flag = UF.Find(5) == 5;
	flag = UF.Find(4) == 5;
	flag = UF.Find(2) == 5;
	flag = UF.Find(7) == 5;
	flag = UF.Find(6) == 5;
	if (!flag) {
		cout << "EROOR\n";
	}

	int* names = UF.getGroupName();
	int* parents = UF.getParent();
	int* sizes = UF.getNumOfEelements();
	cout << "team names:\n";
	for (int i = 0; i < 8; i++) {
		cout << names[i] << " ";
	}
	cout << "\n roots:\n";
	for (int i = 0; i < 8; i++) {
		cout << parents[i] << " ";
	}
	cout << "\n sizes:\n";
	for (int i = 0; i < 8; i++) {
		cout << sizes[i] << " ";
	}
	cout << "\n";

	if (flag) {
		cout << "OK";
	}
	return 0;
}
