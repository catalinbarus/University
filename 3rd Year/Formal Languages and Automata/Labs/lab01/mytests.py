import sys
from functools import reduce
from typing import Optional


def max_in_list_simple(l):
    e_max = l[0]
    for elem in l:
        if elem > e_max:
            e_max = elem
    return e_max

def max_in_list_sort(l):
    # aux = l  # aux and l will reference the same object; modify one and you modify both

    # create a new list identical to l
    # aux = l.copy()
    aux = l[:]  # list comprehension; returns the full list

    aux.sort()  # sorts list in place
    return aux[-1]


mylist = [1, 999, 10, 5, 109]

print(max_in_list_simple(mylist))
print(max_in_list_sort(mylist))
print(mylist[:3])
print([*map(lambda x: x * x, mylist)])
print([x * x for x in mylist]) # same sa above ^
