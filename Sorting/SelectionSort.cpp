#include <bits/stdc++.h>
using namespace std;

void selectionsort(vector<int>&v,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int min_id = i, mn = INT_MAX;
        for(int j=i+1;j<n;j++)
        {
            if(v[j] < mn)
            {
                mn = v[j];
                min_id = j;
            }
        }
        swap(v[i],v[min_id]);
    }
}

int main()
{
    int n;cin >> n;
    vector<int>v(n);
    for(auto &x:v) cin >> x;

    selectionsort(v,n);    

    for(auto &x:v)cout<<x<<" ";

    return 0;
}