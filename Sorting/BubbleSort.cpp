#include <bits/stdc++.h>
using namespace std;

void Bubblesort(vector<int>&v,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int flag=0;
        for(int j=0;j<n-1-i;j++)
        {
            if(v[j]>v[j+1])
            {
                flag=1;
                swap(v[j],v[j+1]);
            }
        }
        if(!flag)break;
    }
}

int main()
{
    int n;cin >> n;
    vector<int>v(n);
    for(auto &x:v) cin >> x;

    Bubblesort(v,n);    

    for(auto &x:v)cout<<x<<" ";

    return 0;
}