/**
  * https://www.spoj.com/problems/SUBXOR/
  * Solution using Trie data structure
**/
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
#define f first
#define s second

using namespace std;


struct node{

    ll lc, rc;
    node *l;
    node *r;

    node(){
        lc = 0, rc = 0;
        l = r = NULL;
     }
 };



node* insert(node* root, ll x, int i){

       if(i == -1){
            return root;
         }
       
       int d = (x&(1<<i)) != 0;

       if(d){
           root->rc++;
           if(root->r == NULL){
                root->r = new node();
             }
           root->r = insert(root->r, x, i-1);
        }
       else{
           root->lc++;
           if(root->l == NULL){
                root->l = new node();
             }
           root->l =  insert(root->l, x, i-1);
        }
      
      return root;
   }

 

 ll query(node* root, ll x, int i, int k){
        
        if(root == NULL || i == -1){
             return 0;
          }
        
        int d1 = (x >> i) & 1;
        int d2 = (k >> i) & 1;


        if(d2){
            if(!d1)
               return root->lc + query(root->r, x, i - 1, k);
            else
               return root->rc + query(root->l, x, i - 1, k);
        }
        else{
            if(!d1)
               return query(root->l, x, i - 1, k);
            else
               return query(root->r, x, i - 1, k);
            
        }
       
     }





int main(){


    int t;
    cin >> t;


    while(t--){

        int n, k;
        cin >> n >> k;

        ll res = 0;
        ll  s = 0, a;

        node* root = new node();
        root = insert(root, 0, 31);

        for(int i = 1; i <= n; i++){
              cin >> a;
              s = s ^ a;  
              res = res + query(root, s, 31, k);
              root = insert(root, s, 31);
            }

        cout << res  << "\n";
    
       }
    


    return 0;
  }

