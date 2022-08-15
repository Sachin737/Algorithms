#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node *links[26];
    bool flag = false;

    bool havekey(char x)
    {
        return (links[x-'a']!=NULL);
    }

    void put(char c,Node *nxt)
    {
        links[c-'a'] = nxt;
    }

    Node* get(char c)
    {
        return links[c-'a'];
    }

    void setflag()
    {
        flag=true;
    }

    bool getflag()
    {
        return flag;
    }
};


class Trie
{
private:
    Node *root;

public:
    
    // initialize trie data structure
    Trie()
    {
        root = new Node();
    }

    // Insertion of word in trie
    void insert(string word)
    {
        Node* cur = root;
        for(int i=0;i<word.size();i++)
        {
            if(!cur->havekey(word[i]))
            {
                cur->put(word[i],new Node()); 
            }
            cur = cur->get(word[i]);
        }
        cur->setflag();
    }

    // Searching full word in trie
    bool search(string word)
    {
        Node* cur = root;
        for(int i=0;i<word.size();i++)
        {
            if(!cur->havekey(word[i]))return false;
            cur = cur->get(word[i]);
        }
        return cur->getflag();
    }

    // Searching if there exist word which starts with prefix
    bool startswith(string prefix)
    {
        Node* cur = root;
        for(int i=0;i<prefix.size();i++)
        {
            if(!cur->havekey(prefix[i]))return false;
            cur = cur->get(prefix[i]);
        }
        return true;
    }

};

int main()
{



    return 0;
}