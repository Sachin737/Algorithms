#include <bits/stdc++.h>
using namespace std;


// Time complexity : 
//     randomized pivot : worst case O(n*n)
//                      : average case O(n*logn)   


int partition(vector<int>&v,int st,int en)
{
    int pivot = v[en];
    int pindex = st;

    for(int i=st;i<en;i++)
    {
        if(v[i]<=pivot)
        {
            swap(v[i],v[pindex]);
            pindex++;
        }
    }
    swap(v[pindex],v[en]);
    return pindex;
}

int partition_r(vector<int>&v,int low,int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low);

    swap(v[random], v[low]);
  
    return partition(v, low, high);
}
void Quicksort(vector<int>&v,int i,int j)
{
    if(i<j)
    {
        int pivot = partition_r(v,i,j);
        Quicksort(v,i,pivot-1);
        Quicksort(v,pivot+1,j);
    }
}

int main()
{
    int n;cin >> n;
    vector<int>v(n);
    for(auto &x:v) cin >> x;

    Quicksort(v,0,n-1);    

    for(auto &x:v)cout<<x<<" ";

    return 0;
}
