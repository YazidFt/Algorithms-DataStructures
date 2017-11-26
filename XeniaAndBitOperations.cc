/*
  ST Problem link: http://codeforces.com/contest/339/problem/D
*/

#include<iostream>
#include<vector>

using namespace std;

int a[1<<18];
long long n,m;


struct node{
     int v, l;  
 } ST[4*(1<<18)];


      void build(int node,int s,int e){
             
             if(s==e){
                 ST[node].v = a[s];
                 ST[node].l = 0;
                 return;
               }

                 int mid=(e+s)/2;

                 build(2*node,s,mid);
                 build(2*node+1,mid+1,e);

                 ST[node].l = ST[2*node].l + 1;
             
                 if(ST[node].l & 1)
                    ST[node].v = ST[2*node].v | ST[2*node+1].v;
                 else
                    ST[node].v = ST[2*node].v ^ ST[2*node+1].v;
             }


     void update(int node,int s,int e,int p,int b){
               if(s==e){
                   ST[node].v = b;
                   return;
               }
               int mid=(s+e)/2;

               if(p<=mid){
                    update(2*node,s,mid,p,b);
               }
               else{
                    update(2*node+1,mid+1,e,p,b);
               }

                if(ST[node].l & 1)
                    ST[node].v = ST[2*node].v | ST[2*node+1].v;
                 else
                    ST[node].v = ST[2*node].v ^ ST[2*node+1].v; 
          }


int main(){

   cin>>n>>m;

   for(int i=0;i<(1<<n);i++){
           cin>>a[i];
     }

   build(1,0,((1<<n)-1));

   while(m--){
       int p,b;cin>>p>>b;
       update(1,0,((1<<n)-1),p-1,b);
       cout << ST[1].v << endl;
       
     }
  
    return 0;
}