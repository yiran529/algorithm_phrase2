class AVL:
    class NODE:
        def __init__(self,key,val):
            self.key=key
            self.val=val
            self.height=1
            self.left=None
            self.right=None
    def __init__(self):
        self.root=None
    def __isEmpty(self,h):
        return h==None
    def __rotateLeft(self,node):
        save=node.right
        node.right=save.left
        save.left=node
        self.__updateHeight(save)
        self.__updateHeight(node)
        if node==self.root:self.root=save
        return save
    def __rotateRight(self,node):
        save=node.left
        node.left=save.right
        save.right=node
        self.__updateHeight(save)
        self.__updateHeight(node)
        if node==self.root:self.root=save
        return save
    def __getHeight(self,node):
        if self.__isEmpty(node):return 0
        else:return node.height
    def __updateHeight(self,node):
        if not self.__isEmpty(node):
            node.height=1+max(self.__getHeight(node.left),self.__getHeight(node.right))
            return node.height
    def insert(self,key,val):
        newNode=self.__insert(self.root,key,val)
        if self.root==None:self.root=newNode
    def __insert(self,h,key,val):
        ##Normal BST insertio
        if self.__isEmpty(h):
            newNode=self.NODE(key,val)##Do not forget 'self.'
            return newNode
        elif h.key==key:h.val=val
        elif key>h.key:h.right=self.__insert(h.right,key,val)
        elif key<h.key:h.left=self.__insert(h.left,key,val)
        ##AVL fixing balance
        if self.__getHeight(h.left)-self.__getHeight(h.right)==2:
            if key<h.left.key:
                h=self.__rotateRight(h)
            elif key>h.left.key:
                h.left=self.__rotateLeft(h.left)
                h=self.__rotateRight(h)
        if self.__getHeight(h.right)-self.__getHeight(h.left)==2:
            if key>h.right.key:
                h=self.__rotateLeft(h)
            elif key<h.right.key:
                h.right=self.__rotateRight(h.right)
                h=self.__rotateLeft(h)
        self.__updateHeight(h)##This sentence is necessary!
        return h
    def __str_helper(self,root,depth):
        if self.__isEmpty(root):return ""
        indent=depth*2
        node_info=str(root.key)+"|"+str(root.val)
        return " "*indent+node_info+"\n"+self.__str_helper(root.left,depth+1)\
            +self.__str_helper(root.right,depth+1)
    def __str__(self):
        print("We're gonna display the tree structure with the node displayed\
        in the form of 'key|val'")
        return self.__str_helper(self.root,0)
    def __getMin(self,h):
        if h.left!=None:return self.__getMin(h.left)
        elif h.left==None:return h
    def delete(self,key):
        self.__delete(self.root,key)
    def __delete(self,h,key):
        if self.__isEmpty(h):return None
        elif key>h.key:h.right=self.__delete(h.right,key)
        elif key<h.key:h.left=self.__delete(h.left,key)
        elif key==h.key:
            if self.__isEmpty(h.left) and self.__isEmpty(h.right):
                if h==self.root:self.root=None
                del(h)
                return None
            elif self.__isEmpty(h.left):
                save=h.right
                if h==self.root:self.root=save
                del(h)
                return save
            elif self.__isEmpty(h.right):
                save=h.left
                if h==self.root:self.root=save
                del(h)
                return save
            else:
                min=self.__getMin(h.right)
                h.key=min.key
                h.val=min.val
                h.right=self.__delete(h.right,min.key)
        if self.__getHeight(h.left)-self.__getHeight(h.right)==2:
            if self.__getHeight(h.left.left)>=self.__getHeight(h.left.right):
                h=self.__rotateRight(h)
            else:
                h.left=self.__rotateLeft(h.left)
                h=self.__rotateRight(h)
        if self.__getHeight(h.right)-self.__getHeight(h.left)==2:
            if self.__getHeight(h.right.right)>=self.__getHeight(h.right.right):
                h=self.__rotateLeft(h)
            else:
                h.right=self.__rotateRight(h.right)
                h=self.__rotateLeft(h)
        self.__updateHeight(h)
        return h
################################################################################
#   We use AVL tree to implement the container Map of C++, which has functions #                         
# including insertion,deletion and finding.                                    #       #
################################################################################

class map(AVL):
   def __find(self,h,key):
       if self.__isEmpty(h):return 'Not Found!'
       elif key==h.key:return h.val
       elif key>h.key:return self.__find(h.right,key)
       else:return self.__find(h.left,key) 
   def find(self,key):
       return self.__find(self.root,key)
BBST=AVL()
BBST.insert(1,1)
BBST.insert(2,3)
BBST.insert(3,3)
BBST.insert(4,3)
BBST.insert(5,2)   
BBST.insert(-1,1)
BBST.insert(9,-2)
BBST.insert(8,7)
BBST.delete(3)
BBST.delete(2)
BBST.delete(-1)
BBST.delete(1)
print(BBST)






