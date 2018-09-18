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
    int v;
    node *c[26];
 };


 node *get(){

         node* t = new node;
         for(int i = 0; i < 26; i++)
                t->c[i] = NULL;
         t->v = 0;
         return t; 
      }
 

 void insert(node* root, string s){
        node *t;
        t = root;
         
        for(int i = 0; i < s.length(); i++){
            if(t->c[s[i]-'a'] == NULL)
                 t->c[s[i]-'a'] = get();

             t = t->c[s[i]-'a'];
             t->v++;
            } 
       }
 

 int query(node* root, string s){
        
        int ans = 0;
        node *t;
        t = root;
        

        for(int i = 0; i < s.length(); i++){
             if(t->c[s[i]-'a'] != NULL){
                   t = t->c[s[i]-'a'];
                   ans = t->v;
                 }
             else{
                 ans = 0;
                 break;
             }
           }
        
        return ans;
      } 
 


int main(){

    int n, m;
    cin >> n >> m;


    node* root = get();

    for(int i = 0; i < n; i++){
          string s;
          cin >> s;
          insert(root, s);
       }
    

    while(m--){
       string s;
       cin >> s;
       cout << query(root, s) << "\n";
      }
    


    return 0;
}

