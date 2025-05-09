// library_code.cc

#include <iostream>
#include <vector>

// Question 7: Linked List Implementation
class MyLinkedList {
private:
    struct Node{
        int val;
        Node* next;
        Node(int x) : val(x), next(nullptr) {}
    };

    Node* head;
    int size;
    
public:
    MyLinkedList() {
        head = nullptr;
        size = 0;
    }
    
    int get(int index) {
        if(index < 0 || index >= size || !head){
            return -1;
        }
        Node* curr = head;
        for(int i = 0; i < index; ++i){
            curr = curr->next;
        }
        return curr->val;
    }
    
    void addAtHead(int val) {
        Node* newNode = new Node(val); 
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    void addAtTail(int val) {
        Node* newNode = new Node(val);
        if(!head){
            head = newNode;
        }
        else{
          Node* curr = head;
          while(curr->next){
            curr = curr->next;
          }  
          curr->next = newNode;
        }
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if(index < 0 || index > size){
            return;
        }
        if(index == 0){
            addAtHead(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* curr = head;
        for(int i = 0; i < index -1; ++i){
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if(index < 0 || index >= size || !head){
            return;
        }
        Node* temp;
        if(index == 0){
            temp = head;
            head = head->next;
        }
        else{
            Node* curr = head;
            for(int i = 0; i < index - 1; ++i){
                curr = curr->next;
            }
            temp = curr->next;
            curr->next = temp->next;
        }
        delete temp;
        size--;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */



// Question 8: kth character after operations
char kthCharacter(long long k, std::vector<int>& operations) {
    char word = 'a';
    int size = operations.size();

    while((1LL << (size - 1)) >= k){
        size--;
    }

    while(size > 0){
        if(k > (1LL << (size - 1)) && operations[size - 1] == 1){
            word++;
            k -= (1LL << (size - 1));
        }
        size--;
    }
    return word;
}

// Question 9: Median of two sorted arrays
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    if (nums1.size() > nums2.size())
    {
        nums1.swap(nums2);
    }
    int n = nums1.size();
    int m = nums2.size();

    int start = 0;
    int end = n;

    while(start <= end){
        int i = (start + end)/2;
        int j = (m+n+1)/2 - i;

        int num1_1 = i > 0 ? nums1[i - 1] : -2147483647;
        int num1_2 = i < n ? nums1[i] : 2147483647;
        int num2_1 = j > 0 ? nums2[j - 1] : -2147483647;
        int num2_2 = j < m ? nums2[j] : 2147483647;

        if(num1_1 > num2_2){
            end = i-1;                                                                                                            
        }
        else if(num1_2 < num2_1){
            start = i+1;
        }
        else{
            int leftmax = std::max(num1_1, num2_1);
            int rightmin = std::min(num1_2, num2_2);
            if((m+n)%2 == 1){
                return leftmax;
            }
            else{
                return (leftmax+rightmin)/2.0;
            }
        }
    }
    return 0.0;
}

// Question 10: Reverse linked list k nodes
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
    
ListNode* reverseKGroup(ListNode* head, int k) {
    if(!head || k == 1) return head;
    // TODO: Implement  
    int length = 0;
    ListNode *listlength = head;
    while(listlength){
        length++;
        listlength = listlength->next;
    }

    ListNode dummy(0,head);
    ListNode *prevGroupEnd = &dummy;

    while(length >= k){
        ListNode* cur = prevGroupEnd->next;
        ListNode* nextGroupStart = cur;
        ListNode* prev = nullptr;

        for(int i = 0; i<k; i++){
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        prevGroupEnd->next->next = cur;
        prevGroupEnd->next = prev;

        prevGroupEnd = nextGroupStart;
        length -= k;
    }

    return dummy.next;
}


