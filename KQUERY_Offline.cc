/*
   SPOJ: http://www.spoj.com/problems/KQUERY/
   Range sum on a segment tree + Offline processing of the queries
*/

#include<iostream>
#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>

#define mp make_pair
#define f first 
#define s second
#define all(v) v.begin(), v.end()

using namespace std;

int seg[4*30003];
int res[200004];



void build(int nd, int l, int r){

         if(l == r){
             seg[nd] = 1;
             return;
           }
         
         int mid = (l + r)/2;
         build(2*nd, l, mid);
         build(2*nd+1, mid+1, r);
       
         seg[nd] = seg[2*nd] + seg[2*nd+1];
     }


void update(int nd, int s, int e, int pos){

         if(pos < s || pos > e){
             return;
         }

         if(s == e){
             seg[nd] = 0;
             return;
          }

         int mid = (s + e)/2;

         if(pos <= mid){
             update(2*nd, s, mid, pos);
         }
         else{
             update(2*nd+1, mid+1, e, pos);
         }

         seg[nd] = seg[2*nd] + seg[2*nd+1];
   }



int query(int nd, int s, int e, int l, int r){

        if(e < l || s > r){
              return 0;
           }
        
        if(s >= l && e <= r){
             return seg[nd];
           }
       
        int mid = (s + e)/2;
        return query(2*nd, s, mid, l, r) + query(2*nd+1, mid+1, e, l, r);

    }


int main(){

   int n, m;
   scanf("%d", &n);
   vector<pair<int, int> > a;

   for(int i = 0; i < n; i++){
         int x;scanf("%d", &x);
         a.push_back(mp(x,i));
     }
 
   build(1, 0, n-1);


   scanf("%d", &m);
   vector<pair<int ,pair<int, pair<int, int> > > > v;


   for(int i = 0; i < m; i++){
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k); 
        l--;r--;  
        v.push_back(mp(k, mp(l, mp(r, i))));
      }
   
   sort(all(v));
   sort(all(a));


   int j = 0;

   for(int i = 0; i < m; i++){
          
        while(j < n && a[j].f <= v[i].f){
                int pos = a[j].s;
                update(1, 0, n-1, pos);
                j++;   
             }

         res[v[i].s.s.s] = query(1, 0, n-1, v[i].s.f, v[i].s.s.f);
      }
   

   for(int i = 0; i < m; i++){
        printf("%d\n", res[i]);
      }
   

   return 0;

}





