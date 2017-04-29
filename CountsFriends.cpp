#include <iostream>

using namespace std;

int siz[100003],arr[100003];

     /*
     int root(int i){
         if(arr[i]==i)return i;
         return arr[i] = root(arr[i]);
       }
     */

    int root(int i){
        while(arr[i]!=i){
          arr[i] = arr[arr[i]];
          i = arr[i];
          }
        return arr[i];
      }

    void union_(int x,int y){

        int rootX = root(x);
        int rootY = root(y);

        if(rootX == rootY) return;
        arr[rootX] = rootY;
        siz[rootY] = siz[rootY] + siz[rootX];
     }

int main()
{
    int n,m;
    cin >> n >> m;

      for(int i=1; i<=n; i++){
          arr[i] = i;
          siz[i] = 1;
      }

      int u,v;
      for(int i=0; i<m; i++){
          cin >> u >> v;
          union_(u,v);
      }

      for(int i=1; i<=n; i++){
          cout << (siz[root(i)]-1) << endl;
      }

    return 0;
}
