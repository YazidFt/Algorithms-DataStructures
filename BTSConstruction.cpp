#include <iostream>

using namespace std;

 struct node{
     int data;
     node *left;
     node *right;
     node(int x) : data(x), left(NULL), right(NULL) {}

 };

node * insert_node(node *root, int v){

     if(root == NULL){
        root = new node(v);
        return  root;
       }
     else{
          if(v > root->data){
               root->right =  insert_node(root->right,v);
            }
          else if(v < root->data){
               root->left =  insert_node(root->left,v);
             }

          return root;
        }

     }

void  preOrder_traversal(node *root){
          if(root){
               cout << root->data << " ";
               preOrder_traversal(root->left);
               preOrder_traversal(root->right);
             }
         }


int main()
{
   int n;
   cin >> n;

   node *root=NULL;

   int val;
   for(int i=0; i<n; i++){
     cin >> val;
     root = insert_node(root, val);
    }

   preOrder_traversal(root);

   return 0;
}
