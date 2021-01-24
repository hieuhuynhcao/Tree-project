#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#define MAX 27

struct TRIE
{
    TRIE *children[MAX];
    bool end;
};

TRIE *getNode()
{
    TRIE *pNode = new TRIE;
    pNode->end = false;

    for (int i = 0; i < MAX; i++)
        pNode->children[i] = NULL;

    return pNode;
}

void insert(TRIE *pRoot, string key)
{
    TRIE *pNode = pRoot;

    for (int i = 0; i < key.length(); i++)
    {
        int j = key[i] - 'a';

        if (!pNode->children[j])
            pNode->children[j] = getNode();

        pNode = pNode->children[j];
    }
    pNode->end = true;
}

bool search(TRIE *pRoot, string key)
{
    TRIE *pNode = pRoot;

    for (int i = 0; i < key.length(); i++)
    {
        int j = key[i] - 'a';
        if (!pNode->children[j])
            return false;

        pNode = pNode->children[j];
    }

    return (pNode != NULL && pNode->end);
}

bool isEmpty(TRIE *pRoot)
{
    for (int i = 0; i < MAX; i++)
        if (pRoot->children[i])
            return false;
    return true;
}

TRIE *remove(TRIE *pRoot, string key, int depth = 0)
{
    if (!pRoot)
        return NULL;

    if (depth == key.size())
    {

        if (pRoot->end)
            pRoot->end = false;

        if (isEmpty(pRoot))
        {
            delete pRoot;
            pRoot = NULL;
        }

        return pRoot;
    }

    int i = key[depth] - 'a';
    pRoot->children[i] = remove(pRoot->children[i], key, depth + 1);

    if (isEmpty(pRoot) && pRoot->end == false)
    {
        delete pRoot;
        pRoot = NULL;
    }

    return pRoot;
}

void travel(TRIE *pRoot, string token, vector<string> &result)
{
    for (int i = 0; i < MAX; i++)
        if (pRoot->children[i])
            travel(pRoot->children[i], token + char('a' + i), result);

    if (pRoot->end)
        result.push_back(token);
}

vector<string> createdWords(TRIE *pRoot, string key)
{
    TRIE *pNode = pRoot;
    vector<string> results;

    if (!pNode)
        return results;

    for (int i = 0; i < key.length(); i++)
    {
        int j = key[i] - 'a';
        if (!pNode->children[j])
            return results;

        pNode = pNode->children[j];
    }

    if (pNode != NULL && pNode->end)
        travel(pNode, key, results);
    return results;
}

void outputWord(TRIE *pRoot)
{
    ifstream ifs("input.txt");
    if (ifs.fail())
    {
        cout << "cant open file" << endl;
        return;
    }

    ofstream ofs("output.txt");
    if (ofs.fail())
    {
        cout << "cant open file" << endl;
        return;
    }

    vector<string> output;
    string str;
    while (!ifs.eof())
    {
        ifs >> str;
        output = createdWords(pRoot, str);
        ofs << output.size() << endl;
        for (int i = 0; i < output.size(); i++)
            ofs << output[i] << endl;
    }

    ifs.close();
    ofs.close();
}