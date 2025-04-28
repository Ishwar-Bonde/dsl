class Person:
    def __init__(self, name="", tel=0):
        self.name = name
        self.telephone = tel

    def set_data(self):
        self.name = input("Enter name: ")
        while True:
            tel = input("Enter telephone number: ")
            if tel.isdigit():
                self.telephone = int(tel)
                break
            print("Invalid number. Try again.")


class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.table = [None] * size

    def hash(self, key): return key % self.size

    def insert(self, person): pass
    def search(self, tel): pass
    def delete(self, tel): pass

    def display(self):
        print("\nHash Table:")
        for i, p in enumerate(self.table):
            if p:
                print(f"{i}: {p.name} - {p.telephone}")
            else:
                print(f"{i}: Empty")


class LinearProbing(HashTable):
    def insert(self, person):
        index = self.hash(person.telephone)
        for i in range(self.size):
            idx = (index + i) % self.size
            if self.table[idx] is None or self.table[idx].telephone == person.telephone:
                self.table[idx] = person
                print("Inserted at index", idx)
                return
        print("Table Full")

    def search(self, tel):
        index = self.hash(tel)
        for i in range(self.size):
            idx = (index + i) % self.size
            if self.table[idx] is None: break
            if self.table[idx].telephone == tel:
                print(f"Found at index {idx}: {self.table[idx].name}")
                return
        print("Not found")

    def delete(self, tel):
        index = self.hash(tel)
        for i in range(self.size):
            idx = (index + i) % self.size
            if self.table[idx] is None: break
            if self.table[idx].telephone == tel:
                self.table[idx] = None
                print("Deleted", tel)
                return
        print("Not found")


class QuadraticProbing(HashTable):
    def insert(self, person):
        index = self.hash(person.telephone)
        for i in range(self.size):
            idx = (index + i * i) % self.size
            if self.table[idx] is None or self.table[idx].telephone == person.telephone:
                self.table[idx] = person
                print("Inserted at index", idx)
                return
        print("Table Full")

    def search(self, tel):
        index = self.hash(tel)
        for i in range(self.size):
            idx = (index + i * i) % self.size
            if self.table[idx] is None: break
            if self.table[idx].telephone == tel:
                print(f"Found at index {idx}: {self.table[idx].name}")
                return
        print("Not found")

    def delete(self, tel):
        index = self.hash(tel)
        for i in range(self.size):
            idx = (index + i * i) % self.size
            if self.table[idx] is None: break
            if self.table[idx].telephone == tel:
                self.table[idx] = None
                print("Deleted", tel)
                return
        print("Not found")


def menu(ht):
    while True:
        print("\n--- MENU ---")
        ch = input("1.Insert 2.Search 3.Delete 4.Display 5.Back\nChoose: ")
        if ch == '1':
            p = Person()
            p.set_data()
            ht.insert(p)
        elif ch == '2':
            ht.search(int(input("Enter number to search: ")))
        elif ch == '3':
            ht.delete(int(input("Enter number to delete: ")))
        elif ch == '4':
            ht.display()
        elif ch == '5':
            break
        else:
            print("Invalid choice")


def main():
    while True:
        print("\n=== Hash Table Menu ===")
        ch = input("1.Linear Probing 2.Quadratic Probing 3.Exit\nChoose: ")
        if ch == '1':
            menu(LinearProbing())
        elif ch == '2':
            menu(QuadraticProbing())
        elif ch == '3':
            print("Goodbye!")
            break
        else:
            print("Invalid choice")


if __name__ == "__main__":
    main()