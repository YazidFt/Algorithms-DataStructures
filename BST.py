class Node:

    def __init__(self,data):
        self.left = None
        self.right = None
        self.data = data



def insert_node(root, data):
    if(root is None):
        root = Node(data)
        return root
    else:
        if(root.data > data):
            root.left = insert_node(root.left, data) 
        else:
            root.right = insert_node(root.right, data)      
        return root


def preOrder_traversal(root):
    if root:
        print(root.data, end=" ")
        preOrder_traversal(root.left)
        preOrder_traversal(root.right)


#TestInput
n = int(input())
l = list(map(int, input().split()))

root=None

for i in range(n):
    root=insert_node(root, l[i])
    
preOrder_traversal(root)





