#program to construct binary tree using inorder and postorder traversals

class newNode:
	def __init__(self, data):
		self.data = data
		self.left = None
		self.right = None

def construct(In, post, inStrt, inEnd, pIndex):	
	if (inStrt > inEnd):
		return None

	node = newNode(post[pIndex[0]])
	pIndex[0] -= 1

	if (inStrt == inEnd):
		return node

	iIndex = search(In, inStrt, inEnd, node.data)

	node.right = construct(In, post, iIndex + 1, inEnd, pIndex)
	node.left = construct(In, post, inStrt, iIndex - 1, pIndex)

	return node

def constructTree(In, post, n):
	pIndex = [n - 1]
	return construct(In, post, 0, n - 1, pIndex)

def search(arr, strt, end, value):
	i = 0
	for i in range(strt, end + 1):
		if (arr[i] == value):
			break
	return i

def maxDepth(node):
    if node is None:
        return 0 
 
    else :
        lDepth = maxDepth(node.left)
        rDepth = maxDepth(node.right)

        if (lDepth > rDepth):
            return lDepth+1
        else:
            return rDepth+1

if __name__ == '__main__':
	In = [8,6,9,4,7,2,5,1,3]
	post = [8,9,6,7,4,5,2,3,1]
	n = len(In)

	root = constructTree(In, post, n)

	ht = maxDepth(root) - 1
	print("Height of Binary Tree: ", ht)