/*
  link: https://codeforces.com/contest/620/problem/E
  Approach: Euler walk of the tree + Segment tree (Lazy)

*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cmath>

#define ll long long
#define mp make_pair 
#define pb push_back


using namespace std;

const int MAXN = 500005;


vector<int> v[MAXN];
int st[MAXN], et[MAXN], lazy[4*MAXN];
int c[MAXN], order[MAXN];
ll seg[4*MAXN];
int n, m, cnt = 0;


void DFS(int i, int p){
        order[cnt] = i;
        st[i] = cnt;
        cnt++;
        
        for(int j = 0; j < v[i].size(); j++){
              if(v[i][j] != p){
                   DFS(v[i][j], i);
                }
            }

        et[i] = cnt-1;
      }
  
 
void build(int nd, int l, int r){

        if(l == r){
             seg[nd] = (1ll << c[order[l]]);
             return;
          }
        int mid = (l + r)/2;
        build(2*nd, l, mid);
        build(2*nd+1, mid+1, r);

        seg[nd] = seg[2*nd] | seg[2*nd+1];
     }


void update(int nd, int s, int e, int l, int r, int nc){
         
         if(lazy[nd]){
               seg[nd] = (1ll << lazy[nd]);

               if(s != e){
                   lazy[2*nd] = lazy[nd];
                   lazy[2*nd+1] = lazy[nd];
                 } 
               
               lazy[nd] = 0;
             }

        if(e < l || s > r){
           return;
         }     
        if(s >= l && e <= r){
              seg[nd] = (1ll << nc);
              
              if(s != e){
                 lazy[2*nd] = nc;
                 lazy[2*nd+1] = nc;
                }
              return;
           }
        int mid = (e + s)/2;
        update(2*nd, s, mid, l, r , nc);
        update(2*nd+1, mid+1, e, l, r , nc);

        seg[nd] = seg[2*nd] | seg[2*nd+1];   
      }




ll query(int nd, int s, int e, int l, int r){
        
        if(lazy[nd]){
             seg[nd] = (1ll << lazy[nd]);
            
             if(s != e){
                lazy[2*nd] = lazy[nd];
                lazy[2*nd+1] = lazy[nd];
               } 

             lazy[nd] = 0;
            }
            
        
        if(e < l || s > r){
           return 0;
         }     
        if(s >= l && e <= r){
           return seg[nd];
         }
        int mid = (e + s)/2;
        return query(2*nd, s, mid, l, r) | query(2*nd+1, mid+1, e, l, r);
      }
    

int main(){

    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < n; i++){
        cin >> c[i];
      }

    for(int i = 0; i < n-1; i++){
       int x, y;
       cin >> x >> y;
       x--;y--;
       v[x].pb(y);
       v[y].pb(x);
     }

    DFS(0, -1);

    build(1, 0, n-1);

    
    while(m--){
       
       int idx;
       cin >> idx;

       if(idx == 1){
          int vx, cl;
          cin >> vx >> cl;
          vx--;
          update(1, 0, n-1, st[vx], et[vx], cl);
        } 
       else{
          int vx, tot = 0;
          cin >> vx;
          vx--;
          ll ans = query(1, 0, n-1, st[vx], et[vx]);
        
          for(int i = 0; i < 64; i++){
             if((ans>>i)&1){
               tot++;
              }
          }
          
          cout << tot << "\n";
        }

     }
    



    return 0;
}

