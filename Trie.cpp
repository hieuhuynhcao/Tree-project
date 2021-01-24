#include "Trie.h"

int main()
{
	TRIE *tries = getNode();
	string str;

	ifstream ifs("Dict.txt");
	if (ifs.fail())
	{
		cout << "can't open file" << endl;
		return 0;
	}
	while (!ifs.eof())
	{
		getline(ifs, str);
		insert(tries, str);
	}
	ifs.close();

	// search(tries, "aaa")
	// 	? cout << "have" << endl;
	// 	: cout << "dont have" << endl;

	// search(tries, "fuck")
	// 	? cout << "have" << endl
	// 	: cout << "dont have" << endl;

	// tries = remove(tries, "aaa");

	// search(tries, "aa")
	// 	? cout << "have" << endl;
	// 	: cout << "dont have" << endl;

	outputWord(tries);

	return 0;
}