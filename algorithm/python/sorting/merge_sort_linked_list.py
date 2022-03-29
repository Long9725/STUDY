# Reference: https://www.geeksforgeeks.org/merge-sort-for-linked-list/
# 시간 복잡도: O(n*log n)

# 공간 복잡도: O(n*log n)

# 접근 방식 2: 이 접근 방식은 더 간단하고 log n 공간을 사용합니다.

# 병합 정렬():

# 연결 목록의 크기가 1이면 헤드를 반환합니다.
# 거북이와 토끼 접근법을 사용하여 중간 찾기
# head2, 즉 오른쪽 하위 연결 목록에 mid의 다음을 저장합니다.
# 이제 다음 중간점을 null로 만듭니다.
# 왼쪽 및 오른쪽 하위 연결 목록에서 mergeSort()를 재귀적으로 호출하고 왼쪽 및 오른쪽 연결 목록의 새 헤드를 저장합니다.
# 왼쪽 및 오른쪽 하위 연결 목록의 새 헤드 인수가 주어지면 merge()를 호출하고 병합 후 반환된 최종 헤드를 저장합니다.
# 병합된 연결 목록의 마지막 헤드를 반환합니다.
# 병합(head1, head2):

# 병합된 목록을 저장하고 더미 노드를 저장하기 위해 포인터를 병합했습니다.
# 포인터 temp를 가져 와서 병합을 할당하십시오.
# head1의 데이터가 head2의 데이터보다 작으면 head1을 temp의 다음으로 저장하고 head1을 head1의 다음으로 이동시킨다.
# 그렇지 않으면 head2를 temp 옆에 저장하고 head2를 head2의 다음으로 이동합니다.
# temp를 다음 temp로 이동합니다.
# head1이 null과 같지 않고 head2가 null과 같지 않을 때까지 3, 4, 5단계를 반복합니다.
# 이제 첫 번째 또는 두 번째 연결 목록의 나머지 노드를 병합된 연결 목록에 추가합니다.
# 병합된 다음 항목을 반환합니다(더미를 무시하고 최종 병합된 연결 목록의 헤드를 반환함).

# Python3 program to merge sort of linked list

# create Node using class Node.
class Node:
	def __init__(self, data):
		self.data = data
		self.next = None

class LinkedList:
	def __init__(self):
		self.head = None
	
	# push new value to linked list
	# using append method
	def append(self, new_value):
		
		# Allocate new node
		new_node = Node(new_value)
		
		# if head is None, initialize it to new node
		if self.head is None:
			self.head = new_node
			return
		curr_node = self.head
		while curr_node.next is not None:
			curr_node = curr_node.next
			
		# Append the new node at the end
		# of the linked list
		curr_node.next = new_node
		
	def sortedMerge(self, a, b):
		result = None
		
		# Base cases
		if a == None:
			return b
		if b == None:
			return a
			
		# pick either a or b and recur..
		if a.data <= b.data:
			result = a
			result.next = self.sortedMerge(a.next, b)
		else:
			result = b
			result.next = self.sortedMerge(a, b.next)
		return result
	
	def mergeSort(self, h):
		
		# Base case if head is None
		if h == None or h.next == None:
			return h

		# get the middle of the list
		middle = self.getMiddle(h)
		nexttomiddle = middle.next

		# set the next of middle node to None
		middle.next = None

		# Apply mergeSort on left list
		left = self.mergeSort(h)
		
		# Apply mergeSort on right list
		right = self.mergeSort(nexttomiddle)

		# Merge the left and right lists
		sortedlist = self.sortedMerge(left, right)
		return sortedlist
	
	# Utility function to get the middle
	# of the linked list
	def getMiddle(self, head):
		if (head == None):
			return head

		slow = head
		fast = head

		while (fast.next != None and
			fast.next.next != None):
			slow = slow.next
			fast = fast.next.next
			
		return slow
		
# Utility function to print the linked list
def printList(head):
	if head is None:
		print(' ')
		return
	curr_node = head
	while curr_node:
		print(curr_node.data, end = " ")
		curr_node = curr_node.next
	print(' ')
	
# Driver Code
if __name__ == '__main__':
	li = LinkedList()
	
	# Let us create a unsorted linked list
	# to test the functions created.
	# The list shall be a: 2->3->20->5->10->15
	li.append(15)
	li.append(10)
	li.append(5)
	li.append(20)
	li.append(3)
	li.append(2)
	
	# Apply merge Sort
	li.head = li.mergeSort(li.head)
	print ("Sorted Linked List is:")
	printList(li.head)

# This code is contributed by Vikas Chitturi
