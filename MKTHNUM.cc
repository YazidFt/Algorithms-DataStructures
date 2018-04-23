/*
  Spoj K-th Number: http://www.spoj.com/problems/MKTHNUM/
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

int n, m;
int a[100004];
vector<int> seg[4*100004];



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


int query(int nd, int s, int e, int l, int r, int x){

        if(e < l || s > r){
              return 0;
           }

        if(s >= l && e <= r){
             return lower_bound(all(seg[nd]), x) - seg[nd].begin();
           }
       
        int mid = (s + e)/2;
        return query(2*nd, s, mid, l, r, x) + query(2*nd+1, mid+1, e, l, r, x);

    }


int SearchBin(int l, int r, int k){
      
      int lo, ro, mid, res;
      lo = 1; ro = n;

      while(lo <= ro){

           int mid = (lo + ro)/2;
           int v = a[mid];

           if(query(1, 1, n, l, r, v) >= k){
                ro = mid - 1;
             }
           else{
                res = v;
                lo = mid + 1;
            }
         }
       return res;  
     }



int main(){

   
   scanf("%d%d", &n, &m);

   for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
     }

   build(1, 1, n);

   sort(a+1, a+n+1);


   for(int i = 0; i < m; i++){
         int l, r, k;
         scanf("%d%d%d", &l, &r, &k);
         cout << SearchBin(l, r, k) << endl;
       }

 
   return 0;

}





