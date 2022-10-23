class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BST:
    def __init__(self, data):
        self.root = Node(data)

    def insert(self, data):
        node = self.root
        while True:
            if data < node.data:
                if node.left is None:
                    node.left = Node(data)
                    break
                else:
                    node = node.left
            else:
                if node.right is None:
                    node.right = Node(data)
                    break
                else:
                    node = node.right

    def search(self, data) -> bool:
        node = self.root
        while True:
            if data == node.data:
                return True
            if data < node.data:
                if node.left is None:
                    return False
                node = node.left
            else:
                if node.right is None:
                    return False
                node = node.right

    def remove(self, data):
        node = self.root
        if node.data == data:
            self.root = None
        else:
            while True:
                if data < node.data:
                    if node.left is None:
                        break
                    parent = node
                    node = node.left
                    flag = 1
                elif data > node.data:
                    if node.right is None:
                        break
                    parent = node
                    node = node.right
                    flag = 0
                else:
                    if node.left is None:
                        if node.right is None:
                            if flag:
                                parent.left = None
                            else:
                                parent.right = None
                        else:
                            if flag:
                                parent.left = node.right
                            else:
                                parent.right = node.right
                    else:
                        if node.right is None:
                            if flag:
                                parent.left = node.left
                            else:
                                parent.right = node.left
                        else:
                            if node.left.right is None:
                                if flag:
                                    parent.left.data = node.left.data
                                    parent.left.left = node.left.left
                                else:
                                    parent.right.data = node.left.data
                                    parent.right.left = node.left.left

                            tar = node.left.right
                            tar_parent = node.left
                            while True:
                                if tar.right is None:
                                    break
                                tar_parent = tar
                                tar = tar.right

                            if flag:
                                parent.left.data = tar.data
                            else:
                                parent.right.data = tar.data

                            if tar.left is None:
                                tar_parent.right = None
                            else:
                                tar_parent.right = tar.left
                    break
