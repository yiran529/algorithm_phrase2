red=True
black=False
#########################################################
#                        API
#put 
#get
#delete
#
class RBBST:#一个RBBST实例表示一棵红黑树
    
    class NODE:
        def __init__(self,key,val,color):
            self.key=key
            self.val=val
            self.color=color
            self.N=1
            self.left=None
            self.right=None
    def __init__(self,key,val=None):
        self.root=self.NODE(key,val,black)
    def __FlipColor(self,node):
        if node.color==black:
            node.color=red
            node.right.color=node.left.color=black
        else:
            node.color=black
            node.right.color=node.left.color=red
    def __rotateLeft(self,node):
        save=node.right
        node.right=save.left
        save.left=node
        save.color=node.color
        node.color=red
        return save
    def __rotateRight(self,node):
        save=node.left
        node.left=save.right
        save.right=node
        save.color=node.color
        node.color=red
        return save
    def __isEmpty(self,root):
        return root==None
    def __isRed(self,root):
        return not self.__isEmpty(root) and root.color
    def __cmp(self,a,b):
        if isinstance(a,str) and isinstance(b,str):
            return int(ord(a)-ord(b))
        
    def put(self,key,val=None):
        self.root=self.__put(self.root,key,val)
        self.root.color=black

    def __put(self,h,key,val):
        if self.__isEmpty(h):return self.NODE(key,val,red)
        cmp=self.__cmp(key,h.key)
        if cmp>0:h.right=self.__put(h.right,key,val)
        elif cmp<0:h.left=self.__put(h.left,key,val)
        else:h.val=val
        
        return self.__balance(h)
    
    def get(self,key):
        target=self.__get(self.root,key)
        if target:return "{0}:{1}".format(target.key,target.val)
        else:return "NOT FOUND"
    def __get(self,h,key):
        if self.__isEmpty(h):return None
        cmp=self.__cmp(key,h.key)
        if cmp==0:return h
        elif cmp>0:return self.__get(h.right,key)
        else:return self.__get(h.left,key)

    def __MoveLeft(self,h):
        self.__FlipColor(h)
        if self.__isRed(h.right.left):
            h.right=self.__rotateRight(h.right)
            h=self.__rotateLeft(h)
            self.__FlipColor(h)
        return h
    def __MoveRight(self,h):
        self.__FlipColor(h)
        if self.__isRed(h.left.left):
            h=self.__rotateRight(h)
            self.__FlipColor(h)
        return h
    
    def __balance(self,h):
        if self.__isRed(h.right) and not self.__isRed(h.left):
            h=self.__rotateLeft(h)
        if self.__isRed(h.left) and self.__isRed(h.left.left):
            h=self.__rotateRight(h)
        if self.__isRed(h.left) and self.__isRed(h.right):
            self.__FlipColor(h)
        return h
    
    def __min(self,h):
        if self.__isEmpty(h):return None
        elif self.__isEmpty(h.left):return h
        else:return self.__min(h.left)

    def delete(self,key):
        if not self.__isRed(self.root.left):self.root.color=red
        self.root=self.__delete(self.root,key)
        if not self.__isEmpty(self.root):self.root.color=black

    def __delete(self,h,key):
        if h==None:return 
        if self.__cmp(key,h.key)<0:
            if not self.__isRed(h.left) and not self.__isRed(h.left.left):
                h=self.__MoveLeft(h)
            h.left=self.__delete(h.left,key)
        else:
            if self.__isRed(h.left):h=self.__rotateRight(h)
            if self.__cmp(key,h.key)==0 and self.__isEmpty(h.right):
                del h
                return None
            if not self.__isEmpty(h.right) and not self.__isEmpty(h.right.left):
                h=self.__MoveRight(h)
            if self.__cmp(key,h.key)==0:
                min=self.__min(h.right)
                h.key=min.key
                h.val=min.val
                h.right=self.__delete(h.right,min.key)
            else:
                h.right=self.__delete(h.right,key)

        return self.__balance(h)



    def __str_helper(self,root,depth):
        if self.__isEmpty(root):return ""
        indent=depth*2
        color="RED" if root.color==red else "BLACK"
        node_info=str(root.key)+"|"+str(root.val)+"|"+color
        return " "*indent+node_info+"\n"+self.__str_helper(root.left,depth+1)\
            +self.__str_helper(root.right,depth+1)
    def __str__(self):
        return self.__str_helper(self.root,0)
    def debug(self):
        print(self.root.key)
        print(self.root.left)
        print(self.root.right)
        
tree=RBBST('A',1)
tree.put('B')
tree.put('C')
tree.put('D')
tree.put('E')
tree.put('F')
tree.put('G')
tree.put('H')
tree.put('I')
tree.put('J')
tree.put('K')
tree.put('L')
tree.put('M')
tree.put('N')
print(tree)
tree.delete('H')
print(tree)
print(tree.get('A'))
