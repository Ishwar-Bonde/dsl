class Data:
    def __init__(self, key="", value=0):
        self.key = key
        self.value = value

    def set(self):
        self.key = input("Key: ")
        self.value = int(input("Value: "))


class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * size
        self.chain = [-1] * size

    def hash(self, val):
        return val % self.size

    def insert(self, d):
        i = self.hash(d.value)
        if self.find(d, True) != -1:
            print("Duplicate!")
            return
        if self.table[i] is None:
            self.table[i] = d
            print(f"Inserted at {i}")
        else:
            j = i
            while self.chain[j] != -1:
                j = self.chain[j]
            k = (j + 1) % self.size
            while self.table[k] is not None:
                if k == i:
                    print("Full!")
                    return
                k = (k + 1) % self.size
            self.table[k] = d
            self.chain[j] = k
            print(f"Inserted at {k}, chained from {j}")

    def find(self, d, silent=False):
        i = self.hash(d.value)
        while i != -1:
            if self.table[i] and self.table[i].value == d.value and self.table[i].key == d.key:
                if not silent:
                    print(f"Found at {i}")
                return i
            i = self.chain[i]
        if not silent:
            print("Not found")
        return -1

    def delete(self, d):
        i = self.find(d, True)
        if i == -1:
            print("Not found")
            return
        self.table[i] = None
        for x in range(self.size):
            if self.chain[x] == i:
                self.chain[x] = self.chain[i]
                break
        self.chain[i] = -1
        print(f"Deleted from {i}")

    def show(self):
        for i in range(self.size):
            if self.table[i]:
                print(f"{i}: {self.table[i].key}, {self.table[i].value} -> {self.chain[i]}")
            else:
                print(f"{i}: Empty -> {self.chain[i]}")


# Main Loop
ht = HashTable()
while True:
    print("\n1.Insert 2.Search 3.Delete 4.Display 5.Exit")
    ch = input("Choice: ")
    if ch == '1':
        d = Data()
        d.set()
        ht.insert(d)
    elif ch == '2':
        d = Data()
        d.set()
        ht.find(d)
    elif ch == '3':
        d = Data()
        d.set()
        ht.delete(d)
    elif ch == '4':
        ht.show()
    elif ch == '5':
        break
    else:
        print("Invalid")