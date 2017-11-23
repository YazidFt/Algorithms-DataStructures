/*
  Prolem link: http://www.spoj.com/problems/HORRIBLE/
  Segement Tree + Lazy Propagation
*/
#include<iostream>
#include<cstring>
#include<vector>

#define ll long long

using namespace std;

ll ST[4*100007], lazy[4*100007];


 //Add v to all elements between range [a:b]
 void update(int node,int s,int e,int a,int b,int v){
          
          if(lazy[node]!=0){
               ST[node] += (e-s+1)*(1LL)*lazy[node];
               if(s!=e){
                   lazy[2*node]+=lazy[node];
                   lazy[2*node+1]+=lazy[node];
               }
               lazy[node]=0;
            }

          if(s>=a && e<=b){
               ST[node]+=(e-s+1)*(1ll)*v;
               //lazy prop
               //informe the children about the update 
               if(s!=e){
                    lazy[2*node]+=v;
                    lazy[2*node+1]+=v;
                 }
               return;
            }

          if(s>b || e<a){
               return;
           }

          int mid=(s+e)/2;
          
          update(2*node,s,mid,a,b,v);
          update(2*node+1,mid+1,e,a,b,v);

          ST[node] = ST[2*node] + ST[2*node+1];
       }


    
     ll query(int node,int s,int e,int a,int b){
           
           if(lazy[node]!=0){
               ST[node] += (e-s+1)*(1LL)*lazy[node];
               if(s!=e){
                   lazy[2*node]+=lazy[node];
                   lazy[2*node+1]+=lazy[node];
               }
               lazy[node]=0;
            }

            if(s>=a && e<=b){
                 return ST[node];
            }
            if(s>b || e<a){
                return 0;
            }

            int mid=(s+e)/2;

            return (query(2*node,s,mid,a,b) + query(2*node+1,mid+1,e,a,b));
       }


    

int main(){
    
    int t;cin>>t;

    while(t--){
         int n,m;
         cin>>n>>m;

         memset(ST, 0, sizeof(ST));
         memset(lazy, 0, sizeof(lazy));

         while(m--){
             
             int idx;cin>>idx;

             if(idx==0){
                 int a,b,v;cin>>a>>b>>v;
                 update(1,0,n-1,a-1,b-1,v);
             }
             else{
                 int a,b;cin>>a>>b;
                 cout << query(1,0,n-1,a-1,b-1) << endl;
             }
         }
    }


    return 0;
}