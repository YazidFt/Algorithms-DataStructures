/*
   link: https://www.spoj.com/problems/QTREE/
    Algorithm: Heavy Light Decomposition
*/

#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
 
#define LL long long
#define mp make_pair 
#define pb push_back
#define f first
#define s second
 
using namespace std;
 
const int MAXN = 10005;
const int M = 19;
int MAX_L;
vector<pair<int, int> > vec[MAXN];
vector<int> idx[MAXN];
int tab[19][MAXN];
int dpt[MAXN];
int siz[MAXN];
int at[MAXN];
int End_edg[MAXN];
int chainN[MAXN];
int chainH[MAXN];
int PosA[MAXN];
int chainPtr;
 
int ST[4*MAXN];
 
          
 
       int  DFS(int i, int p, int d=0){ 
               tab[0][i] = p;
               dpt[i] = d;
               int sz = 1;
 
               for(int j = 0; j < vec[i].size(); j++){
                    if(vec[i][j].f != p){
                        End_edg[idx[i][j]] = vec[i][j].f;
                        sz += DFS(vec[i][j].f, i, d+1);               
                       }
                   }
 
               siz[i] = sz;
               return sz;
             }


 
 
        void  HLD(int nd, int w, int p){
                 
                if(chainH[chainPtr] == -1){
                       chainH[chainPtr] = nd;
                    }
                
                //chain number of nd
                chainN[nd] = chainPtr;
                PosA[nd] = MAX_L;
                at[MAX_L++] = w;
 
                
                int mx_sz=-1, nw;
                int nd2 = -1;
                
                // Next chainPtr child
                for(int i = 0; i < vec[nd].size(); i++){
                      if(vec[nd][i].f != p){
                             if(nd2 == -1 || siz[vec[nd][i].f] > mx_sz){
                                    mx_sz = siz[vec[nd][i].f];
                                    nw    = vec[nd][i].s;
                                    nd2   =  vec[nd][i].f;
                                 }
                              }
                       }
                
 
                if(nd2 != -1){
                      HLD(nd2, nw, nd); 
                   }
                
 
                for(int i = 0; i < vec[nd].size(); i++){
                        if(vec[nd][i].f != p && vec[nd][i].f != nd2){
                                chainPtr++;
                                HLD(vec[nd][i].f, vec[nd][i].s , nd);
                            }
                     }
              
                }
 
        
 
 
    int getLCA(int u, int v) {
          
        if(dpt[u] < dpt[v]) swap(u,v);
               
        int d = dpt[u] - dpt[v];
        
        for(int i = 0; i < 19; i++){
            if((d>>i)&1) u = tab[i][u]; 
          }
 
      if(u == v) return u;
      
        for(int i = 18; i >= 0; i--){
            if(tab[i][u] != tab[i][v]) {
            u = tab[i][u]; v = tab[i][v];
            }
           }
 
      return tab[0][u];
      }
 
 
      
      void build(int nd, int l, int r){
              
             if(l == r-1){
                  ST[nd] = at[l]; 
                  return;
                }
     
             int mid = (l + r)/2;
             build(2*nd, l, mid);
             build(2*nd+1, mid, r);
             
             ST[nd] = max(ST[2*nd], ST[2*nd+1]);
           }
         
        
 
        void update(int nd, int s, int e, int pos, int val){
                if(pos >= e || pos < s){
                     return;
                  }     
                if((s == (e-1)) && (pos == s)){
                      at[s] = val;
                      ST[nd] = val;
                      return;
                  }
                int mid = (s + e)/2;
 
                update(2*nd, s, mid, pos, val);
                update(2*nd+1, mid, e, pos, val);
 
                ST[nd] = max(ST[2*nd], ST[2*nd+1]);
              }
             
 
 
        int query_chain (int nd, int s, int e, int l, int r) {
               if(s >= r || e <= l) {
                   return -1;
                 }
               if(s >= l && e <= r) {
                   return ST[nd];
                 }
              
                int mid = (s + e)/2;
              return max(query_chain(2*nd, s, mid, l, r), query_chain(2*nd+1, mid, e, l, r));
            }
        
         
 
        int crawlTree(int a, int b){
                  if(a == b) return 0;
                  //b is the a ancestor
                  int res = -1;
                  int b_chain = chainN[b];
                  int a_chain;
 
                  while(true){
                      a_chain = chainN[a];
                      
                      if(a_chain == b_chain){
                          
                          if(a == b) break;
                          
                          int tmp = query_chain(1, 0, MAX_L, PosA[b]+1, PosA[a]+1);
                          res = max(res, tmp);
                          break;
                        }
                      
                      int tmp2 = query_chain(1, 0, MAX_L, PosA[chainH[a_chain]], PosA[a]+1);
                      res = max(res, tmp2);
 
                      a = chainH[a_chain];
                      a = tab[0][a];
                    }
 
                return res;
             }
        
         
 
        int query(int a, int b){
               int lca = getLCA(a,b);
               int q1 = crawlTree(a, lca);
               int q2 = crawlTree(b, lca);
               return max(q1, q2);
             }
 
 
 
int main(){
    
    
    
    int t;
    scanf("%d", &t);
 
 
    for(int k = 0; k < t; k++){
 
        int n;
        scanf("%d", &n);
 
        MAX_L = 0;
        chainPtr = 0;
 
        for(int i = 0; i <= n; i++){
              vec[i].clear();
              idx[i].clear();
              chainH[i] = -1;
        for(int j=0; j< M; j++) tab[j][i] = -1;
            }
 
        for(int i = 1; i <= n-1; i++){
             int l, r, c;
             scanf("%d%d%d", &l, &r, &c);
             l--; r--;
             vec[l].pb(mp(r,c));
             vec[r].pb(mp(l,c));
             idx[l].pb(i-1);
             idx[r].pb(i-1);
            }
 
        
        DFS(0, -1);
        HLD(0, -1, -1);
        build(1, 0, MAX_L);
 
 
        for(int i = 1; i < M; i++){
            for(int j = 1; j <= n; j++){
                   if(tab[i-1][j] != -1)
                        tab[i][j] = tab[i-1][tab[i-1][j]];
                  }
               }
        
 
        while(true){
 
 
            char s[6];
            scanf("%c", &s[0]);
 
            if(s[0] == 'D'){
                  scanf("%c%c%c", &s[1], &s[2], &s[3]);
                  break;
               }
            if(s[0] == 'C'){
                 
                 scanf("%c%c%c%c%c", &s[1], &s[2], &s[3], &s[4], &s[5]);
                 int i, w;
                 scanf("%d%d", &i, &w);
                 i--;
                 int e = End_edg[i];
                 int pos = PosA[e];
                 update(1, 0, MAX_L, pos, w);
 
             }
            if(s[0] == 'Q'){
 
                scanf("%c%c%c%c", &s[1], &s[2], &s[3], &s[4]);
                int l, r;
                scanf("%d%d", &l, &r);
                l--; r--;
                printf("%d\n", query(l,r));
 
              }
            
            }
        
        
        }
    
 
    return 0;
 }