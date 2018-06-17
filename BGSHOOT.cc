/*
   https://www.spoj.com/problems/BGSHOOT/
   SegTree and coordinate compression 
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

const int MAXN = 200005;
LL seg[4*MAXN];
LL c[MAXN];



    void build(int nd, int l, int r){

          if(l == r){
              seg[nd] = c[l];
              return;
            }
          
           int mid = (l + r)/2;
          
           build(2*nd, l, mid);
           build(2*nd+1, mid+1, r);
          
           seg[nd] = max(seg[2*nd], seg[2*nd+1]);
          
        }




    int query(int nd, int s, int e, int l, int r){

          if(s > r || e < l){
                return -1e9+5;
            }

          if(l <= s && e <= r){
                return seg[nd];
            }
           
           int mid = (s + e)/2;

           return max(query(2*nd, s, mid, l, r), query(2*nd+1, mid+1, e, l, r));
        } 




int main(){

    int n;
    cin >> n;

    vector< pair<LL,LL> > a, b;
    map<LL,LL> p;
    
    set<LL> st;
    int idx = 0;


    for(int i = 0; i < n; i++){
         int x, y;
         cin >> x >> y;
         st.insert(x), st.insert(y);
         a.pb(mp(x,y));
       }


    int q;
    cin >> q;


    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        st.insert(l), st.insert(r);
        b.pb(mp(l,r));
       }
    

    //Compression
    for(set<LL>::iterator it = st.begin(); it != st.end(); it++){
            LL j = *it;
            p[j] = idx;
            idx++;
        }



    for(int i = 0; i < n; i++){
          c[p[a[i].f]] += 1;
          c[p[a[i].s]+1] += -1;   
      }

    for(int i = 0; i < MAXN; i++){
          c[i] += c[i-1];
      }


     build(1, 0, MAXN-1);

   
    for(int i = 0; i < q; i++){
          cout << query(1, 0, MAXN-1, p[b[i].f], p[b[i].s]) << "\n";
         }
    
    

    return 0;
 }

