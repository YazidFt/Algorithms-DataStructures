/*
   Spoj K-Query Online: http://www.spoj.com/problems/KQUERYO/
   Merge sort segment tree, Online queries.
*/

#include<iostream>
#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>

#define f first 
#define s second
#define all(v) v.begin(), v.end()

using namespace std;

int a[30003];
vector<int> seg[4*30003];



void build(int nd, int l, int r){

         if(l == r){
             seg[nd].push_back(a[l]);
             return;
           }
         
         int mid = (l + r)/2;
         build(2*nd, l, mid);
         build(2*nd+1, mid+1, r);
       
         merge(all(seg[2*nd]), all(seg[2*nd+1]), back_inserter(seg[nd]));
       }


int query(int nd, int s, int e, int l, int r, int k){

        if(e < l || s > r){
              return 0;
           }
        
        if(s >= l && e <= r){
             return seg[nd].end() - upper_bound(all(seg[nd]), k);
           }
       
        int mid = (s + e)/2;
        return query(2*nd, s, mid, l, r, k) + query(2*nd+1, mid+1, e, l, r, k);

    }



int main(){

   int n, m;
   scanf("%d", &n);

   for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

   build(1, 1, n);
 
   scanf("%d", &m);

   int last_ans = 0;

   for(int i = 0; i < m; i++){
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        l = l ^ last_ans;
        r = r ^ last_ans;
        k = k ^ last_ans;

        last_ans = query(1, 1, n, l, r, k);
        printf("%d\n", last_ans);
      }


   
   return 0;

}





