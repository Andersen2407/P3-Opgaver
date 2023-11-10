def find_missing_element(linked_list):
   for i in range(linked_list[-1] + 1):
      v = i if i in linked_list else 'Missing'
      print(v, end=" -> " if i < linked_list[-1] else '\n')


find_missing_element([0, 1, 3, 4, 5, 8, 12])