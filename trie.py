"""
In computer science, a trie, also called digital tree or prefix tree, is a type of k-ary search tree,
a tree data structure used for locating specific keys from within a set.
These keys are most often strings, with links between nodes defined not by the entire key, but by individual characters.
In order to access a key (to recover its value, change it, or remove it), the trie is traversed depth-first,
following the links between nodes, which represent each character in the key.
"""

class Node:
    def __init__(self, key, data=None):
        self.key = key
        self.data = data
        self.child = {}


class Trie:
    def __init__(self):
        self.head = Node(None)

    def insert(self, string):
        cur_node = self.head
        for char in string:
            if char not in cur_node.child:
                cur_node.child[char] = Node(char)
            cur_node = cur_node.child[char]
        cur_node.data = string

    def search(self, string):
        cur_node = self.head
        for char in string:
            if char not in cur_node.child:
                return False
            cur_node = cur_node.child[char]
        if cur_node.data is not None:
            return True
        return False
