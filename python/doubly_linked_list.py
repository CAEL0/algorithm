class Node:
    def __init__(self, data=None, next=None, prev=None):
        self.data = data
        self.next = next
        self.prev = prev


class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0
    
    def is_empty(self):
        return self.size == 0
    
    def appendleft(self, value):
        node = Node(value, self.head, None)
        if not self.size:
            self.tail = node
        else:
            self.head.prev = node
        self.head = node
        self.size += 1
    
    def append(self, value):
        node = Node(value, None, self.tail)
        if not self.size:
            self.head = node
        else:
            self.tail.next = node
        self.tail = node
        self.size += 1
    
    def popleft(self):
        if self.size:
            self.head = self.head.next
            self.head.prev = None
            self.size -= 1
    
    def pop(self):
        if self.size:
            self.tail = self.tail.prev
            self.tail.next = None
            self.size -= 1
    
    def insert_after(self, node_data, value):
        temp = self.head
        while temp:
            if temp.data == node_data:
                temp.next = Node(value, temp.next, temp)
                if temp.next.next is None:
                    self.tail = temp.next
                else:
                    temp.next.next.prev = temp.next
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
                    else:
                        temp.next.prev = temp
                    self.size -= 1
                break
            temp = temp.next
