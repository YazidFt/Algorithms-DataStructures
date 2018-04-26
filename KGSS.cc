#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>

#define fastIO ios_base::sync_with_stdio(false),cin.tie();

using namespace std;

const int mx = 100005;
long long a[mx];


struct node {   

    long long maxv;
    long long maxv2;

    node() {
        maxv = 0; 
        maxv2 = 0;
      };

    node merge(node& l, node& r){
          maxv = max(l.maxv, r.maxv);
          if(maxv == l.maxv){
              maxv2 = max(l.maxv2, r.maxv);
          }
          else{
              maxv2 = max(l.maxv, r.maxv2);
          }
        }

}seg[4*mx];


void build(int nd, int l, int r){

        if(l == r){
             seg[nd].maxv = a[l];
             seg[nd].maxv2 = 0;
             return;
           }

        int mid = (l + r)/2;
        build(2*nd, l, mid);
        build(2*nd+1, mid+1, r);

        seg[nd].merge(seg[2*nd], seg[2*nd+1]);
    }


 void update(int nd, int s, int e, int pos, int v){
           
          if(pos < s || pos > e){
                 return;
              }
              
          if(s == e && pos == s){
                a[s] = v;
                seg[nd].maxv = v;
                seg[nd].maxv2 = 0;   
                return;
               }

           int mid = (s + e)/2;

           if(pos <= mid){
               update(2*nd, s, mid, pos, v);
           }
           else{
               update(2*nd+1, mid+1, e, pos, v);
           }

           seg[nd].merge(seg[2*nd], seg[2*nd+1]);
       }

 
  
  node query(int nd, int s, int e, int l, int r){

            if(s > e || e < l || s > r){
                node o = node();
                return o;
             } 

            if(s >= l && e <= r){
                 return seg[nd];
              }

            int mid = (s + e)/2;

            if(mid < l){
                 return query(2*nd+1, mid+1, e, l, r);
             }
            else if(mid >= r){
                 return query(2*nd, s, mid, l, r);
             }
            else{
                 node rd, rl, rr;
                 rl = query(2*nd, s, mid, l, r);
                 rr = query(2*nd+1, mid+1, e, l, r);
                 rd.merge(rl, rr);
                 return rd;
              }
         }


int main(){
    
    int n, m;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
         scanf("%d", &a[i]);
      }
    
    build(1, 0, n-1);

    scanf("%d", &m);

    for(int i = 0; i < m; i++){
        char c;int l, r;
        cin >> c >> l >> r;
       
        if(c == 'U'){
           l--;
           update(1, 0, n-1, l, r);
         }   
        else{
           l--;r--;
           node res =  query(1, 0, n-1, l, r);
           cout << res.maxv + res.maxv2 << endl;
         }
       }

    return 0;
}



