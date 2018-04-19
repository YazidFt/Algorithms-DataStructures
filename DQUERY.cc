/*
    SPOJ: http://www.spoj.com/problems/DQUERY/
    Segment Tree + Offline processing + Fast I/O
*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>

#define f first 
#define s second

using namespace std;

int a[1000005];
int res[1000005];
int seg[4*1000005];
int pr[1000005];


bool cmp(pair<int, pair<int, int> > &a, pair<int, pair<int, int> > &b){
           return a.s.f < b.s.f;
        }


void update(int nd, int s, int e, int pos, int v){

         if(s == e){
              seg[nd] = v;
              return;
           }
         
         int mid = (s + e)/2;

         if(pos <= mid){
              update(2*nd, s, mid, pos, v);
         }
         else{
              update(2*nd+1, mid+1, e, pos, v);
         }

         seg[nd] = seg[2*nd] + seg[2*nd + 1];

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

   for(int i = 1; i <= n; i++){
         scanf("%d", &a[i]);
    }
   
   scanf("%d", &m);
   vector<pair<int, pair<int, int> > > q(m);

   for(int i = 0; i < m; i++){
         scanf("%d%d", &q[i].f, &q[i].s.f);
         q[i].s.s = i;     
      }

   sort(q.begin(), q.end(), cmp);
   
   int j = 0;

   for(int i = 1; i<=n && j<m; i++){

        int idx = a[i];
        if(pr[idx] != 0){
            update(1, 1, n, pr[idx], 0);
          }
        
        update(1, 1, n, i, 1);
        pr[idx] = i;

        while(j < m && q[j].s.f <= i){
            res[q[j].s.s] = query(1, 1, n, q[j].f, q[j].s.f);
            j++;
          }    
     }


    for(int i = 0; i < m; i++){
          printf("%d\n", res[i]);
        }


   
   return 0;
}





