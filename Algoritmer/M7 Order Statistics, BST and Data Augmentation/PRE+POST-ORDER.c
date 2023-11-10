PREORDER(T, x)	// Initial call has x=root node
	if x == NIL:
		return
	print(x)
	PREORDER(T, x.left_child)
	PREORDER(T, x.right_child)

PREORDER(T, rootNode)

POSTORDER(T, x)
	if x == NIL:
		return
	PREORDER(T, x.left_child)
	PREORDER(T, x.right_child)
	print(x)

POSTORDER(T, rootNode)