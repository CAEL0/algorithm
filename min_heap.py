"""
In computer science, a heap is a specialized tree-based data structure which is essentially an almost complete 
tree that satisfies the heap property: in a max heap, for any given node C, if P is a parent node of C, then the key 
(the value) of P is greater than or equal to the key of C.
In a min heap, the key of P is less than or equal to the key of C.
The node at the "top" of the heap (with no parents) is called the root node.
"""


class MinHeap:
    def __init__(self):
        self.array = [0]
    
    def push(self, n):
        i = len(self.array)
        self.array.append(n)
        while i > 1:
            if self.array[i] < self.array[i // 2]:
                self.array[i], self.array[i // 2] = self.array[i // 2], self.array[i]
                i //= 2
            else:
                break
    
    def pop(self):
        if len(self.array) == 1:
            return 0
        
        if len(self.array) == 2:
            return self.array.pop()
        
        res = self.array[1]
        
        self.array[1] = self.array.pop()
        i = 1
        while True:
            if len(self.array) <= 2 * i:
                break
            
            if len(self.array) == 2 * i + 1:
                if self.array[i] > self.array[2 * i]:
                    self.array[i], self.array[2 * i] = self.array[2 * i], self.array[i]
                break
            
            if (self.array[i] <= self.array[2 * i]) and (self.array[i] <= self.array[2 * i + 1]):
                break
            
            if self.array[i] > self.array[2 * i]:
                if self.array[2 * i] > self.array[2 * i + 1]:
                    self.array[i], self.array[2 * i + 1] = self.array[2 * i + 1], self.array[i]
                    i = 2 * i + 1
                else:
                    self.array[i], self.array[2 * i] = self.array[2 * i], self.array[i]
                    i *= 2
            else:
                self.array[i], self.array[2 * i + 1] = self.array[2 * i + 1], self.array[i]
                i = 2 * i + 1
        
        return res
