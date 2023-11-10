class HashTable:
   def __init__(self, size=10):
       self.m = size
       # Contains a (key, value) pair for each entry
       self.table = [None] * size


   def _hashByDivision(self, key):
       # h(k) = k mod m =          # Use hash() to convert any object to int
       return hash(key) % self.m


   def _probe_linear(self, key, i):
       return (self._hashByDivision(key) + i) % self.m


   def hash_insert(self, key, value):  # Done
       for i in range(self.m):  # i: [0... (m-1)]
           index = self._probe_linear(key, i)
           if self.table[index] is None:
               self.table[index] = (key, value)
               return
       raise Exception("Hash table is full")


   def hash_delete(self, key):  # If the same key is used it will delete the first one in the list
       for i in range(self.m):
           index = self._probe_linear(key, i)
           if self.table[index] != None:
               if self.table[index][0] == key:
                   self.table[index] = None
                   return
       raise Exception("Key not found")


   def hash_search(self, key):
       for i in range(self.m):
           index = self._probe_linear(key, i)
           if self.table[index] != None:
               if self.table[index][0] == key:
                   return self.table[index][1]
       raise KeyError("Key not found")


   def __str__(self):
       return str(self.table)




hash_table = HashTable(11)


hash_table.hash_insert("a", 6)
hash_table.hash_insert("b", 7)
hash_table.hash_insert("c", 8)
hash_table.hash_insert("d", 123)
print(hash_table)
# --> [None, ('c', 8), ('a', 6), ('d', 123), None, None, None, None, None, None, ('b', 7)]
hash_table.hash_delete("b")
print(hash_table)
# --> [None, ('c', 8), ('a', 6), ('d', 123), None, None, None, None, None, None, None]
hash_table.hash_insert("k", 3456789)
print(hash_table)
# --> [None, ('c', 8), ('a', 6), ('d', 123), ('k', 3456789), None, None, None, None, None, None]
print(hash_table.hash_search("d"))
# --> 123
