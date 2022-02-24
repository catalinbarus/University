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


def max_in_list_and_sort(l):
    l.sort()  # l will be changed
    return l[-1]


def max_in_range(l, start, stop):
    e_max = l[start]
    # range(x, y) = all ints in [x, y)
    for i in range(start, stop):
        if l[i] > e_max:
            e_max = l[i]
    return e_max


def max_in_range_slicing(l, start, stop):
    # l[x:y] = all elements with indexes in [x, y)
    return max(l[start:stop])


def longest_positive(l):
    sequence = []
    for e in l:
        if e < 0:
            i = l.index(e)  # i = index of the first appearance of e in list
            if i >= len(sequence):
                sequence = l[:i]  # exclude negative element
            l = l[i+1:]  # remove current sequence from l, negative element included

        elif e == l[-1]:  # last element is > 0
            i = l.index(e)
            if i >= len(sequence):
                sequence = l[:i+1]  # include the last element
            # we finished analysing the list
    return sequence


def list_of_unique_chars(s: str):
    return set(list(s))  # can't make a set directly from a str buy we can make a list out of str


def palindrome(l):
    fst_half = snd_half = []  # we can assign a val to multiple vars at once

    if len(l) % 2 == 0:  # even length list
        mid = int(len(l) / 2)  # / results in a float result; must explicitly convert to int to use as index
        fst_half = l[:mid]
        snd_half = l[mid:][::-1]  # get the second half and reverse it
        # [::-1] returns the reversed list; we can chain slicing operations

    else:  # odd length list
        # avoid middle element
        mid = int((len(l) + 1) / 2)
        fst_half = l[:mid - 1]
        snd_half = l[mid:][::-1]

    return fst_half == snd_half  # compares lists elem by elem


def allplus1(l):  # adds 1 to each element of a list
    return map(lambda x: x + 1, l)


def sum_l(l):  # computes the sum of elements of a list
    # no code written here can access plus() because it wasn't defined yet

    # inner functions are very useful for defining local, reusable functionality
    def plus(x, y):
        return x + y

    # plus() can only be used in sum_l(l)

    return reduce(plus, l)  # reduce is a little different from Haskell folds: it does not use an initial value


def short_sum(l):
    # lambda list_of_args: funct_body
    return reduce(lambda x, y: x + y, l)


def get_youth(l: list) -> list:
    # this function computes the age of a given CNP
    def age(cnp: str):
        # conversion to integer of the two-character year code
        if int(cnp[5:8]) <= 21:
            return 2021 - int("20" + cnp[5:7])
        else:
            return 2021 - int("19" + cnp[5:7])

    # computing the average ages (a map could have also been used)
    # age(x[-1]) == last element in each tuple == cnp
    avg = reduce(lambda a, b: a + b, [age(x[-1]) for x in l]) / len(l)

    # we return the last name and the age of the filtered list l
    return [(ln, age(cnp)) for (fn, ln, cnp) in l if cnp[0] == '2' and age(cnp) <= avg]


if __name__ == '__main__':
    l_int = [1, -7, 9, 1, 2, -4, 5, 8, 9, 3]
    l_str = ['10', '-7', '19', '1', '2', '42', '5', '8', '9', '3']

    print(f"Max in {l_int} is {max_in_list_simple(l_int)}")
    print(f"Max in {l_str} is {max_in_list_simple(l_str)}")

    print(f"Max in {l_int} is {max_in_list_sort(l_int)}. List is still {l_int}")
    print(f"Max in {l_str} is {max_in_list_sort(l_str)}. List is still {l_str}")

    print(f"Max in {l_int} is {max_in_list_and_sort(l_int)}. List is now {l_int}")
    print(f"Max in {l_str} is {max_in_list_and_sort(l_str)}. List is now {l_str}")

    print(f"Max in range is {max_in_range(l_int, 3, 7)}")
    print(f"Max in range is {max_in_range_slicing(l_int, 3, 7)}")

    # examples of list operation
    list1 = ['a', 2, 'v']
    print(list1)
    list1.append(3)
    print(list1)
    list1.insert(2, 'b')
    print(list1)
    list1.extend([4, 5])  # add elems of another list at the end of list1
    print(list1)

    # sorted returns a new sorted list; all list elements must be of the same type to be compared
    print(f"{sorted([str(x) for x in list1])} {list1}")

    # examples with dictionaries
    dict1 = {}
    if not dict1:
        # an empty dict == False
        print('empty')

    dict2 = {'key1': [1, 2, 3],
             1: 'qw'}
    print(dict2)
    for key in dict2:
        # access element
        print(f'{dict2[key]} {dict2.get(key)} {dict2.get(key, None)}')
    for key, e in dict2.items():
        print(e)

    dict2['newKey'] = 2  # add a key and value
    print(dict2)

    dic_test = {}
    # lists can't be keys, tuples can
    l = [1, 2]
    # dic_test[l] = 3  # will give an error
    # print(dic_test)
    dic_test[tuple(l)] = 3
    print(dic_test)

    d = {"ana": 1, "are": 2, "mere": 3}
    s = ""
    for key, elem in d.items():  # access both key and elements at once
        s += key + ' ' + str(elem) + ' '
    print(s)

    # examples with set
    set1 = set()
    if not set1:
        # an empty set == False
        print('empty set')

    l = [1, 2, '4', 4, 2]
    set2 = set(l)  # make set from list; list object remains unchanged

    set3 = {1, 2, '4', 4, 2}  # init set with values; duplicates will be lost
    print(f'{set2} {set3} {l}')

    set2.add(3)
    print(set2)
    set2.add(3)  # adding a val that already exists has no effect
    print(set2)

    # longest sequence of positive numbers
    l_int1 = [1, -7, 9, 1, 2, -4, 5, 8, 9, 3]
    l_int2 = [1, 7, 9, 1, 2, -4, 5, 8, 9, 3]
    l_int3 = [1, -7, -9, 1, 2, 4, 5, -8, 9, 3]
    print(f"Longest positive sequence is {longest_positive(l_int1)}")
    print(f"Longest positive sequence is {longest_positive(l_int2)}")
    print(f"Longest positive sequence is {longest_positive(l_int3)}")

    # if we want to use str inside f-strings we can't use "" for both or '' for both
    # f-string has "" => str must have ''
    # f-string has '' => str must have ""
    print(f"Unique chars: {list_of_unique_chars('qwwmmmfijsiejiwa')}")
    print(f'Unique chars: {sorted(list(list_of_unique_chars("qwwmmmfijsiejiwa")))}')

    # .sort() sorts in place and modifies list, sorted() returns the sorted list and leaves the original unaltered
    # map doesn't return a list but the obj it returns can be casted to list

    list_tup = [(1, 2, 3), (4, 5, 6), ('a', 'b', 'c'), ('d', 'e', 6)]
    for (x, y, z) in list_tup:  # this works because all list_tup elements are tuples with 3 vals
        print(f'{x} {y} {z}')

    # sort by last element in tuple; convert to str to make them comparable (can only compare elems of the same type)
    # key = optional argument for controlling what we sort
    # sort() has a key argument too
    print(sorted(list_tup, key=lambda tup: str(tup[-1])))

    # check if list is palindrome
    l1 = ['a', 1, 'b', 2, 'b', 1, 'a']
    l2 = ['a', 1, 'b', 'b', 1, 'a']
    l3 = ['a', 1, 'b', 2, 'b', 1, 'a', 3]
    l4 = ['a', 1, 'b', 'b', 1, 'a', 3]
    print(f'{palindrome(l1)} {palindrome(l2)} {palindrome(l3)} {palindrome(l4)}')

    l = [1, -7, 9, 1, 2, -4, 5, 8, 9, 3]
    print(f'{allplus1(l)}')
    print(f'{list(allplus1(l))}, initial {l}')
    print(sum_l(l))
    print(short_sum(l))

    # str can be used like lists; example of list comprehension with conditions (filter)
    list_str = ['qwer', 'wq', 'dfgyhub']
    print([x for x in list_str if len(x) > 3 and x[1] == 'w'])

    print(get_youth([("Mary", "Smith", "2030602123456"), ("Anne", "Doe", "2121092123456"),
                     ("Matei", "Dan", "1121202123456"), ("Maggie", "Byrne", "2121078123456")]))

    # get cli args with sys.argv; it's a list
    print(sys.argv[1:])
    filename = sys.argv[1]

    # use classic open() => must call close()
    f = open(filename, 'r')
    print(f.read())  # will print the whole file
    f.close()

    with open(filename, 'r') as f:  # use with open() => no need for close()
        # everything we do with f we do in this block
        content = f.read()  # the contents of f are now a string
        lines = content.split('\n')

        # create dict from list of keys; each key now has associated the value None
        graph = dict.fromkeys(range(0, int(lines[0])))

        open_streets = [x for x in lines[1:] if ' O ' in x]  # filter list of strings
        # useful checks:
        # if substring in string
        # if element in list/set/tuple
        # if key in dict

        print(open_streets)
        for x in open_streets:
            # create undirected graph as adjacency list kept as dict

            # x is of type '1 O 2'; we extract the nodes as int
            node1 = int(x[0])
            node2 = int(x[-1])

            # x is None evaluates to True even if the value of x is None
            # x is not None doesn't necessarily evaluate to True even if the value of x is None
            # None evaluates to False

            if graph[node1]:  # graph[node1] is not None
                graph[node1].add(node2)  # add to set

            else:  # graph[node1] is None
                graph[node1] = {node2}  # we use sets to avoid duplicates

            if graph[node2]:
                graph[node2].add(node1)
            else:
                graph[node2] = {node1}

            # set.add() returns None => if we do s1 = s1.add() s1 will become None

        print(f'Our graph of open roads is: {graph}')

        # typing hints help the programmer
        def dfs(visited: set, state: int):  # example of depth first search implemented in python
            if state not in visited:
                visited.add(state)

                if graph.get(state, False):
                    # state has children in graph
                    for next_state in graph[state]:
                        # dfs for neighbors
                        dfs(visited, next_state)

        # Optional[] typing means it can be any of the types between [] or it can be None
        def find_dests(start: int) -> Optional[set]:  # find accessible nodes from given node
            accessible = set()
            dfs(accessible, start)  # inner fct can call other inner fct provided that they were defined before them
            accessible.remove(start)  # we won't consider the start node as reachable destination => remove from set

            if accessible:
                return accessible
            return None

        for node in graph:
            print(f'From {node} we can go to: {find_dests(node)}')
