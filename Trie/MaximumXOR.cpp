#include <bits/stdc++.h>
using namespace std;


struct Node{
    Node* links[2];
    
    bool havekey(int bit)
    {
        return links[bit]!=NULL;
    }
    
    void setNode(int bit)
    {
        links[bit] = new Node();
    }
    
    Node* nextNode(int bit)
    {
        return links[bit];
    }
};

class Trie
{
public:
    Node* root;
    
    Trie(){
        root = new Node();
    }
    
    void insert(int num)
    {
        Node* cur = root;
        for(int i=31;i>=0;i--)
        {
            int bit = (num >> i) & 1;
            if(!cur->havekey(bit))
            {
                cur->setNode(bit);
            }
            cur = cur->nextNode(bit);
        }
    }
    
    int getmaxXor(int num)
    {
        int answer = 0;
        Node* cur = root;
        for(int i=31;i>=0;i--)
        {
            int bit = (num >> i) & 1;
             
            if(cur->havekey(1-bit))
            {
               cur = cur->nextNode(1-bit); 
               answer = (1<<i) | answer;
            }else
            {
                cur = cur->nextNode(bit);
            }
        }
        return answer;
    }
    
};

int maxXOR(int n, int m, vector<int> &arr1, vector<int> &arr2) 
{
    Trie trie;
    for(auto &x:arr1)
    {
        trie.insert(x);
    }
    int res=0;
    for(auto &x:arr2)
    {
        res=max(res,trie.getmaxXor(x));
    }
    return res;
    
    
    
}


int main()
{
    int n;cin>>n;
    vector<string>v(n);
    for(auto &x:v)cin>>x;

    cout << completeString(n,v);
    return 0;
}