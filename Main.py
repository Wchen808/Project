from MyNode import Node
from MyLinkedList import LinkedList
b=LinkedList()
b.add_first(20)
b.add_first(10)
b.add_first(30)
b.add_first(250)
b.add_first(50)
b.add_first(40)
print(b)
b.selectionsort()
print(b)

#40 50 250 30 10 20 before
#10 20 30 40 50 250 after
