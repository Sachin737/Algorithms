#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node *links[26];
    bool flag = false;

    bool havekey(char c)
    {
        return links[c - 'a'] != NULL;
    }

    void setnewNode(char c)
    {
        links[c - 'a'] = new Node();
    }

    Node *next(char c)
    {
        return links[c - 'a'];
    }

    void setflag()
    {
        flag = true;
    }
};

class Trie
{
public:
    Node *root;

    Trie()
    {
        root = new Node();
    }

    void insert(string &word)
    {
        Node *cur = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (!cur->havekey(word[i]))
            {
                cur->setnewNode(word[i]);
            }
            cur = cur->next(word[i]);
        }
        cur->setflag();
    }

    bool CheckAllPrefixExist(string &word)
    {
        Node * cur = root;
        for(int i=0;i<word.size();i++)
        {
            if(!cur->havekey(word[i]))return false;
    
            cur=cur->next(word[i]);

            if(!cur->flag)
            {
                return false;
            }
        }
        return true;
    }
};

string completeString(int n, vector<string> &a)
{
    Trie v;
    for (auto &x : a)
    {
        v.insert(x);
    }
    string result = "";

    for (auto &x : a)
    {
        cout<< v.CheckAllPrefixExist(x);
        if (v.CheckAllPrefixExist(x))
        {
            if (x.size() > result.size() || (x.size() == result.size() && x < result))
            {
                result = x;
            }
        }
    }
    if(result == "")result="None";
    
    return result;
}

int main()
{
    int n;cin>>n;
    vector<string>v(n);
    for(auto &x:v)cin>>x;

    cout << completeString(n,v);
    return 0;
}