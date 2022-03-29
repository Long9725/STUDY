// Reference: https://www.geeksforgeeks.org/merge-sort-for-linked-list/
// 시간 복잡도: O(n*log n)

// 공간 복잡도: O(n*log n)

// 접근 방식 2: 이 접근 방식은 더 간단하고 log n 공간을 사용합니다.

// 병합 정렬():

// 연결 목록의 크기가 1이면 헤드를 반환합니다.
// 거북이와 토끼 접근법을 사용하여 중간 찾기
// head2, 즉 오른쪽 하위 연결 목록에 mid의 다음을 저장합니다.
// 이제 다음 중간점을 null로 만듭니다.
// 왼쪽 및 오른쪽 하위 연결 목록에서 mergeSort()를 재귀적으로 호출하고 왼쪽 및 오른쪽 연결 목록의 새 헤드를 저장합니다.
// 왼쪽 및 오른쪽 하위 연결 목록의 새 헤드 인수가 주어지면 merge()를 호출하고 병합 후 반환된 최종 헤드를 저장합니다.
// 병합된 연결 목록의 마지막 헤드를 반환합니다.
// 병합(head1, head2):

// 병합된 목록을 저장하고 더미 노드를 저장하기 위해 포인터를 병합했습니다.
// 포인터 temp를 가져 와서 병합을 할당하십시오.
// head1의 데이터가 head2의 데이터보다 작으면 head1을 temp의 다음으로 저장하고 head1을 head1의 다음으로 이동시킨다.
// 그렇지 않으면 head2를 temp 옆에 저장하고 head2를 head2의 다음으로 이동합니다.
// temp를 다음 temp로 이동합니다.
// head1이 null과 같지 않고 head2가 null과 같지 않을 때까지 3, 4, 5단계를 반복합니다.
// 이제 첫 번째 또는 두 번째 연결 목록의 나머지 노드를 병합된 연결 목록에 추가합니다.
// 병합된 다음 항목을 반환합니다(더미를 무시하고 최종 병합된 연결 목록의 헤드를 반환함).

#include<stdio.h>
#include<stdlib.h>
  
/* Link list node */
struct node
{
    int data;
    struct node* next;
};
 
/* function prototypes */
struct node* SortedMerge(struct node* a, struct node* b);
void FrontBackSplit(struct node* source,
          struct node** frontRef, struct node** backRef);
 
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct node** headRef)
{
  struct node* head = *headRef;
  struct node* a;
  struct node* b;
 
  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b);
 
  /* Recursively sort the sublists */
  MergeSort(&a);
  MergeSort(&b);
 
  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b);
}
 
/* See http://geeksforgeeks.org/?p=3622 for details of this
   function */
struct node* SortedMerge(struct node* a, struct node* b)
{
  struct node* result = NULL;
 
  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
 
  /* Pick either a or b, and recur */
  if (a->data <= b->data)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra node should go in the front list.
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct node* source,
          struct node** frontRef, struct node** backRef)
{
  struct node* fast;
  struct node* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}
 
/* Function to print nodes in a given linked list */
void printList(struct node *node)
{
  while(node!=NULL)
  {
   printf("%d ", node->data);
   node = node->next;
  }
}
 
/* Function to insert a node at the beginging of the linked list */
void push(struct node** head_ref, int new_data)
{
  /* allocate node */
  struct node* new_node =
            (struct node*) malloc(sizeof(struct node));
  
  /* put in the data  */
  new_node->data  = new_data;
  
  /* link the old list off the new node */
  new_node->next = (*head_ref);   
  
  /* move the head to point to the new node */
  (*head_ref)    = new_node;
}
  
/* Drier program to test above functions*/
int main()
{
  /* Start with the empty list */
  struct node* res = NULL;
  struct node* a = NULL;
  
  /* Let us create a unsorted linked lists to test the functions
   Created lists shall be a: 2->3->20->5->10->15 */
  push(&a, 15);
  push(&a, 10);
  push(&a, 5);
  push(&a, 20);
  push(&a, 3);
  push(&a, 2);
  
  /* Sort the above created Linked List */
  MergeSort(&a);
  
  printf("\n Sorted Linked List is: \n");
  printList(a);          
  
  getchar();
  return 0;
}