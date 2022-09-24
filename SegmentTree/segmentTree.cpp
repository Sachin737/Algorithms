// Sachin Mahawar
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Example Segtree for rangeSum
struct SegTree{

    ll size;
    vector<ll>v;
    vector<ll> seg;

    SegTree(vector<ll>vec){
        size = 1;
        while (size < vec.size()) size *= 2;
        seg.assign(2*size, 0LL);
        for(auto &x:vec)v.push_back(x);
    } 


    void build(ll node,ll l,ll r)
    {
        if(l==r)
        {
            seg[node] = v[l];
            return;
        }

        ll m = (l+r)/2;
        build(2*node+1,l,m);
        build(2*node+2,m+1,r);
        seg[node] = seg[2*node+1] + seg[2*node+2];
    }

    ll query(ll node,ll l,ll r,ll ql,ll qr)
    {
        if(r < ql || l > qr)
        {
            return 0;
        }
        if(l==ql && r==qr)
        {
            return seg[node];
        }

        ll m = (l + r)/2;
        ll left = query(2*node+1,l,m,ql,min(qr,m));
        ll right = query(2*node+2,m+1,r,max(ql,m+1),qr);
        return left + right;
    }

    void update(ll node,ll l,ll r,ll idx,ll nval)
    {
        if(l>r)
        {
            return;
        }

        if(l==r)
        {
            seg[node] = v[idx] = nval;
            return;
        }

        ll m = (l + r)/2;
        if(idx <= m)
        {
            update(2*node+1,l,m,idx,nval);
        }else
        {
            update(2*node+2,m+1,r,idx,nval);
        }

        seg[node] = seg[2*node+1] + seg[2*node+2];
    }


};


int main()
{   
    ll n,q;cin >> n >> q;
    vector<ll>v(n);
    for(auto &x:v)cin>>x;

    SegTree st(v);
    st.build(0,0,n-1);

    for(ll i=0;i<q;i++)
    {
        ll a,b,c;cin>>a>>b>>c;
        if(a==1)
        {
            st.update(0,0,n-1,b,c);
        }else
        {
            cout<<st.query(0,0,n-1,b,c-1)<<"\n";
        }
    }
    

    return 0;
}
