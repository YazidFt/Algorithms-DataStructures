/*
  Problem link: http://www.spoj.com/problems/GSS3/
*/


#include<iostream>
#include<cstdio>
#include<set>
#include<cstring>


using namespace std;

int a[50005];
const int maxN = 50005;
int ans;


struct node {
       int st; //segment sum
       int bs; //best sum
       int bl; //best left
       int br; //best right
       
       node() {
           st = 0;
           bs = 0;
           bl = 0;
           br = 0;
       };
       
       node merge(node& l, node& r){
            st =  l.st + r.st;
            bl =  max(l.st + r.bl, l.bl);
            br =  max(r.st + l.br, r.br);
            bs =  max(l.bs, max(r.bs, l.br + r.bl));
          }

}sg[4*maxN];



void build(int nd, int l, int r){

        if(l == r){
             sg[nd].st = a[l];
             sg[nd].bs = a[l];
             sg[nd].bl = a[l];
             sg[nd].br = a[l];
             return;
           }
        
        int mid = (l + r)/2;
        build(2*nd, l, mid);
        build(2*nd+1, mid+1, r);

        sg[nd].merge(sg[2*nd], sg[2*nd+1]);
     }


void update(int nd, int l, int r, int i,int v){
       
       if(i < l || i > r){
             return;
         }  
       
       if(l==r){
             a[l] = v;
             sg[nd].st = a[l];
             sg[nd].bs = a[l];
             sg[nd].bl = a[l];
             sg[nd].br = a[l];
             return;
         }

    
       int mid = (l + r)/2;

       if(i <= mid){
            update(2*nd, l, mid, i, v);
        }
       else{
            update(2*nd+1, mid+1, r, i, v);
        }

       sg[nd].merge(sg[2*nd], sg[2*nd+1]);
  }



node query(int nd, int s, int e, int l, int r){
   
         if(e < l || s > r){
             node no = node();
             return no;
           }
         
        
         if(l <= s && r >= e){
              return sg[nd];
           }

         int mid = (s + e)/2;

         if(r <= mid){
               return query(2*nd, s, mid, l, r);
         }
         else if(l > mid){
               return query(2*nd+1, mid+1, e, l, r);
         }
         else{
            node ns, nl, nr;
            nl = query(2*nd, s, mid, l, r);
            nr = query(2*nd+1, mid+1, e, l, r);
            ns.merge(nl, nr);

            return ns;
          }
         
         
      }






int main(){
   
   int n;
   cin >> n;

   for(int i = 0; i < n; i++){
        cin >> a[i];
    }
   
   build(1, 0, n-1);

   int q;
   cin >> q;

   while(q--){
        int d, l, r;
        cin >> d >> l >> r;

        if(d==0){
            l--;
            update(1, 0, n-1, l, r);
         }
        else{
            l--;r--;
            cout << query(1, 0, n-1, l, r).bs << endl;
        }
     }
  
   
   return 0;
}





