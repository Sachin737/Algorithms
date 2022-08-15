#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node* links[26];
    int prefcnt[26] = {0};
    int cnt=0;
    
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
    
    void setcnt(int i)
    {
        cnt+=i;
    }
    
    void increase_prefcnt(char c)
    {
        prefcnt[c-'a']++;
    }

    int get_prefcnt(char c)
    {
        return prefcnt[c-'a'];
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
            cur->increase_prefcnt(word[i]);
            cur = cur->next(word[i]);
        }
        cur->setcnt(1);
    }

    int countWordsEqualTo(string &word){
        Node* cur = root;
        for(int i=0;i<word.size();i++)
        {
            if(!cur->havekey(word[i]))return 0;
            cur = cur->next(word[i]);
        }
        return cur->cnt;
    }


    int countWordsStartingWith(string &word){
        Node* cur = root;
        for(int i=0;i<word.size();i++)
        {
            if(!cur->havekey(word[i]))
            {
                return 0;
            }
            
            if(i==word.size()-1)
            {
                return cur->get_prefcnt(word[i]);
            }
            cur = cur->next(word[i]);
        }
    }

    void erase(string &word){
        Node *cur = root;
        for (int i = 0; i < word.size(); i++)
        {
            cur->prefcnt[word[i]-'a']--;
            cur = cur->next(word[i]);
        }
        cur->setcnt(-1);
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