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
