import sys
import random
import time

# Set recursiondepth limit
sys.setrecursionlimit(10**8)


class Tree:
    def __init__(self) -> None:
        self.root: Node | None = None


class Node:
    def __init__(self, key, parent=None) -> None:
        self.left_child: Node | None = None
        self.right_child: Node | None = None
        self.parent: Node | None = parent
        self.key: int = key


T = Tree()


def tree_minimum(node: Node):
    while node.left_child != None:
        node = node.left_child
    return node


def inorder_tree_walk(node: Node):
    if node != None:
        inorder_tree_walk(node.left_child)
        print(node.key, end=", ")
        inorder_tree_walk(node.right_child)


def BST_insert(tree: Tree, node: Node):
    x = tree.root       # Comparer node
    y = None               # y is parent of x
    while x != None:
        y = x
        if node.key < x.key:
            x = x.left_child
        else:
            x = x.right_child
    node.parent = y

    if y == None:
        tree.root = node
    elif node.key < y.key:
        y.left_child = node
    else:
        y.right_child = node


def BST_iter_search(node: Node, key):
    while node != None and key != node.key:
        if key < node.key:
            node = node.left_child
        else:
            node = node.right_child
    return node


def BST_transplant(tree: Tree, u: Node, v: Node):
    if u.parent == None:    # If node is root
        tree.root = v
    elif u == u.parent.left_child:  # Is u the left child of its parent?
        u.parent.left_child = v
    else:
        u.parent.right_child = v
    if v != None:
        v.parent = u.parent


def BST_delete(tree: Tree, node: Node):
    if node.left_child == None:
        BST_transplant(tree, node, node.right_child)
    elif node.right_child == None:
        BST_transplant(tree, node, node.left_child)
    else:
        y: Node = tree_minimum(node.right_child)
        if y != node.right_child:
            BST_transplant(tree, y, y.right_child)
            y.right_child = node.right_child
            y.right_child.parent = y
        BST_transplant(tree, node, y)
        y.left_child = node.left_child
        y.left_child.parent = y


n = 5_000_000

# Seed the random function
random.seed(20)

start_time = time.time()

# Generate 20 mil random numbers from 0 to 100.000, and insert them into the BST.
for _ in range(n):
    BST_insert(T, Node(random.randint(0, 100_000)))

# Delete 20% of data
random.seed(20)
for _ in range(n//5):
    a = BST_iter_search(T.root, random.randint(0, 100_000))
    if a != None:
        BST_delete(T, a)

# Add more data
for _ in range(n//2):
    BST_insert(T, Node(random.randint(0, 100_000)))

print(f"Took, {time.time()-start_time} seconds.")
