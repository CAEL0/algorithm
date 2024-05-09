class Node:
    def __init__(self, data=None, next=None):
        self.data = data
        self.next = next


class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0
    
    def is_empty(self):
        return self.size == 0
    
    def appendleft(self, value):
        node = Node(value, self.head)
        if not self.size:
            self.tail = node
        self.head = node
        self.size += 1
    
    def append(self, value):
        node = Node(value, None)
        if not self.size:
            self.head = node
        else:
            temp = self.head
            while temp.next:
                temp = temp.next
            temp.next = node
        self.tail = node
        self.size += 1
    
    def popleft(self):
        if self.size:
            self.head = self.head.next
            self.size -= 1
    
    def pop(self):
        if self.size:
            temp = self.head
            while temp.next:
                temp = temp.next
            temp.next = None
            self.tail = temp
            self.size -= 1
    
    def insert_after(self, node_data, value):
        temp = self.head
        while temp:
            if temp.data == node_data:
                temp.next = Node(value, temp.next)
                if temp.next.next is None:
                    self.tail = temp.next
                self.size += 1
                break
            temp = temp.next
    
    def delete_after(self, node_data):
        temp = self.head
        while temp:
            if temp.data == node_data:
                if temp.next:
                    temp.next = temp.next.next
                    if temp.next is None:
                        self.tail = temp
                    self.size -= 1
                break
            temp = temp.next
