#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node* links[26];
    int pc=0;
    int ew=0;
    
    bool havekey(char c)
    {
        return links[c-'a']!=NULL;
    }
    
    void set(char c)
    {
        links[c-'a'] = new Node();
    }
    
    Node* next(char c)
    {
        return links[c-'a'];
    }
    
    void increaseprefix()
    {
        pc++;
    }

    void decreaseprefix()
    {
        pc--;
    }

    int getPrefcnt()
    {
        return pc;
    }

    void increaseEnd()
    {
        ew++;
    }

    void decreaseEndcnt()
    {
        ew--;
    }

    int getEndcount()
    {
        return ew;
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
                cur->set(word[i]);
            }
            cur = cur->next(word[i]);
            cur->increaseprefix();
        }
        cur->increaseEnd();
    }

    int countWordsEqualTo(string &word){
        Node* cur = root;
        for(int i=0;i<word.size();i++)
        {
            if(!cur->havekey(word[i]))return 0;
            cur = cur->next(word[i]);
        }
        return cur->getEndcount();
    }


    int countWordsStartingWith(string &word){
        Node* cur = root;
        for(int i=0;i<word.size();i++)
        {
            if(!cur->havekey(word[i]))
            {
                return 0;
            }
            cur = cur->next(word[i]);
        }
        return cur->getPrefcnt();
    }

    void erase(string &word){
        Node *cur = root;
        for (int i = 0; i < word.size(); i++)
        {
            cur = cur->next(word[i]);
            cur->decreaseprefix();
        }
        cur->decreaseEndcnt();
    }
   
};

int main()
{
    Trie obj;
    vector<string> v={"apple"};
    v.push_back("apple");
    v.push_back("app");
    v.push_back("appla");
    for(auto x:v)obj.insert(x);
    
    string s="app";
    int f = obj.countWordsEqualTo(s);
    cout<<f;

    return 0;
}