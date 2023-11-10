import random
import time

# Define Node
class Node():
    def __init__(self, val):
        self.val = val       # Value of Node
        self.parent = None   # Parent of Node
        self.left = None     # Left Child of Node
        self.right = None    # Right Child of Node
        # Red Node as new node is always inserted as Red Node
        self.color = 1

# Define R-B Tree
class RBTree():
    def __init__(self):
        self.NULL = Node(0)
        self.NULL.color = 0
        self.NULL.left = None
        self.NULL.right = None
        self.root = self.NULL

    # Insert New Node
    def insertNode(self, key):
        node = Node(key)
        node.parent = None
        node.val = key
        node.left = self.NULL
        node.right = self.NULL
        node.color = 1         # Set root colour as Red

        y = None
        x = self.root

        while x != self.NULL:  # Find position for new node
            y = x
            if node.val < x.val:
                x = x.left
            else:
                x = x.right

        node.parent = y        # Set parent of Node as y
        if y == None:    # If parent i.e, is none then it is root node
            self.root = node
        elif node.val < y.val: # Check if it is right Node or Left Node by checking the value
            y.left = node
        else:
            y.right = node

        if node.parent == None:       # Root node is always Black
            node.color = 0
            return
        
        if node.parent.parent == None:# If parent of node is Root Node
            return
        self.fixInsert(node)          # Else call for Fix Up

    def minimum(self, node):
        while node.left != self.NULL:
            node = node.left
        return node

    # Code for left rotate
    def LR(self, x):
        y = x.right                    # Y = Right child of x
        # Change right child of x to left child of y
        x.right = y.left
        if y.left != self.NULL:
            y.left.parent = x

        # Change parent of y as parent of x
        y.parent = x.parent
        if x.parent == None:   # If parent of x == None ie. root node
            self.root = y      # Set y as root
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y

    # Code for right rotate
    def RR(self, x):
        y = x.left  # Y = Left child of x
        # Change left child of x to right child of y
        x.left = y.right
        if y.right != self.NULL:
            y.right.parent = x

        # Change parent of y as parent of x
        y.parent = x.parent
        if x.parent == None:       # If x is root node
            self.root = y          # Set y as root
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x
        x.parent = y

    # Fix Up Insertion
    def fixInsert(self, k):
        while k.parent.color == 1:        # While parent is red
            if k.parent == k.parent.parent.right: # if parent is right child of its parent
                u = k.parent.parent.left # Left child of grandparent
                if u.color == 1:         # if color of left child of grandparent i.e, uncle node is red
                    u.color = 0          # Set both children of grandparent node as black
                    k.parent.color = 0
                    k.parent.parent.color = 1 # Set grandparent node as Red
                    # Repeat the algo with Parent node to check conflicts
                    k = k.parent.parent
                else:
                    if k == k.parent.left:                # If k is left child of it's parent
                        k = k.parent
                        # Call for right rotation
                        self.RR(k)
                    k.parent.color = 0
                    k.parent.parent.color = 1
                    self.LR(k.parent.parent)
            else:                                         # if parent is left child of its parent
                u = k.parent.parent.right                 # Right child of grandparent
                if u.color == 1:                          # if color of right child of grandparent i.e, uncle node is red
                    u.color = 0                           # Set color of childs as black
                    k.parent.color = 0
                    k.parent.parent.color = 1             # set color of grandparent as Red
                    k = k.parent.parent                   # Repeat algo on grandparent to remove conflicts
                else:
                    if k == k.parent.right:               # if k is right child of its parent
                        k = k.parent
                        # Call left rotate on parent of k
                        self.LR(k)
                    k.parent.color = 0
                    k.parent.parent.color = 1
                    # Call right rotate on grandparent
                    self.RR(k.parent.parent)
            if k == self.root:                            # If k reaches root then break
                break
        self.root.color = 0                               # Set color of root as black

    # Function to fix issues after deletion
    def fixDelete(self, x):
        while x != self.root and x.color == 0:           # Repeat until x reaches nodes and color of x is black
            if x == x.parent.left:                       # If x is left child of its parent
                s = x.parent.right                        # Sibling of x
                if s.color == 1:                         # if sibling is red
                    s.color = 0                           # Set its color to black
                    x.parent.color = 1                    # Make its parent red
                    # Call for left rotate on parent of x
                    self.LR(x.parent)
                    s = x.parent.right
                # If both the child are black
                if s.left.color == 0 and s.right.color == 0:
                    s.color = 1                           # Set color of s as red
                    x = x.parent
                else:
                    if s.right.color == 0:               # If right child of s is black
                        s.left.color = 0                  # set left child of s as black
                        s.color = 1                       # set color of s as red
                        # call right rotation on x
                        self.RR(s)
                        s = x.parent.right

                    s.color = x.parent.color
                    x.parent.color = 0                    # Set parent of x as black
                    s.right.color = 0
                    # call left rotation on parent of x
                    self.LR(x.parent)
                    x = self.root
            else:                                        # If x is right child of its parent
                s = x.parent.left                         # Sibling of x
                if s.color == 1:                         # if sibling is red
                    s.color = 0                           # Set its color to black
                    x.parent.color = 1                    # Make its parent red
                    # Call for right rotate on parent of x
                    self.RR(x.parent)
                    s = x.parent.left

                if s.right.color == 0 and s.right.color == 0:
                    s.color = 1
                    x = x.parent
                else:
                    if s.left.color == 0:                # If left child of s is black
                        s.right.color = 0                 # set right child of s as black
                        s.color = 1
                        # call left rotation on x
                        self.LR(s)
                        s = x.parent.left

                    s.color = x.parent.color
                    x.parent.color = 0
                    s.left.color = 0
                    self.RR(x.parent)
                    x = self.root
        x.color = 0

    # Function to transplant nodes
    def __rb_transplant(self, u, v):
        if u.parent == None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent

    # Function to handle deletion
    def delete_node_helper(self, node, key):
        z = self.NULL
        while node != self.NULL:                          # Search for the node having that value/ key and store it in 'z'
            if node.val == key:
                z = node

            if node.val <= key:
                node = node.right
            else:
                node = node.left

        if z == self.NULL:                                # If Kwy is not present then deletion not possible so return
            print("Value not present in Tree !!")
            return

        y = z
        # Store the color of z- node
        y_original_color = y.color
        if z.left == self.NULL:                            # If left child of z is NULL
            x = z.right                                     # Assign right child of z to x
            # Transplant Node to be deleted with x
            self.__rb_transplant(z, z.right)
        elif (z.right == self.NULL):                       # If right child of z is NULL
            x = z.left                                      # Assign left child of z to x
            # Transplant Node to be deleted with x
            self.__rb_transplant(z, z.left)
        else:                                              # If z has both the child nodes
            # Find minimum of the right sub tree
            y = self.minimum(z.right)
            y_original_color = y.color                      # Store color of y
            x = y.right
            if y.parent == z:                              # If y is child of z
                x.parent = y                                # Set parent of x as y
            else:
                self.__rb_transplant(y, y.right)
                y.right = z.right
                y.right.parent = y

            self.__rb_transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color
        if y_original_color == 0:                          # If color is black then fixing is needed
            self.fixDelete(x)

    # Deletion of node
    def delete_node(self, val):
        self.delete_node_helper(self.root, val)         # Call for deletion

    # Function to print
    def __printCall(self, node, indent, last):
        if node != self.NULL:
            print(indent, end=' ')
            if last:
                print("R----", end=' ')
                indent += "     "
            else:
                print("L----", end=' ')
                indent += "|    "

            s_color = "RED" if node.color == 1 else "BLACK"
            print(str(node.val) + "(" + s_color + ")")
            self.__printCall(node.left, indent, False)
            self.__printCall(node.right, indent, True)

    # Function to call print
    def print_tree(self):
        self.__printCall(self.root, "", True)

# Function to generate random data
def generate_random_data(num_data_points):
    data = list(range(1, num_data_points + 1))
    random.shuffle(data)
    return data

# Function to insert random data points into the Red-Black Tree
def insert_random_data(rb_tree, data):
    for item in data:
        rb_tree.insertNode(item)

# Function to delete a random percentage of data from the Red-Black Tree
def delete_random_percentage(rb_tree, data, percentage):
    num_to_delete = int(len(data) * percentage)
    items_to_delete = random.sample(data, num_to_delete)
    for item in items_to_delete:
        rb_tree.delete_node(item)
        data.remove(item)

if __name__ == "__main__":
    num_data_points = 1000000  # Change this to the desired number of data points
    percentage_to_delete = 0.20  # Change this to the desired deletion percentage

    data = generate_random_data(num_data_points)
    bst = RBTree()

    print("Inserting random data into the Red-Black Tree...")
    start_time = time.time()
    insert_random_data(bst, data)
    end_time = time.time()
    insertion_time = end_time - start_time
    print("Red-Black Tree after inserting random data:")
    bst.print_tree()

    print("\nDeleting a random percentage of data...")
    start_time = time.time()
    delete_random_percentage(bst, data, percentage_to_delete)
    end_time = time.time()
    deletion_time = end_time - start_time
    print("Red-Black Tree after deleting a random percentage of data:")
    bst.print_tree()

    total_execution_time = insertion_time + deletion_time
    print(f"Total execution time: {total_execution_time:.4f} seconds")