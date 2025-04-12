#include <gtest/gtest.h>
#include "library_code.cc"

// Question 7 Tests
TEST(MyLinkedListTest, BasicOperations) {
    MyLinkedList list;
    list.addAtHead(1);
    list.addAtTail(3);
    list.addAtIndex(1, 2);  // List: 1->2->3
    EXPECT_EQ(list.get(1), 2);
    list.deleteAtIndex(1);  // List: 1->3
    EXPECT_EQ(list.get(1), 3);
    
    // TODO: Implement tests
    list.deleteAtIndex(0);
    list.deleteAtIndex(0);
    EXPECT_EQ(list.get(0),-1);

    for (int i = 0; i < 1000; i++) {
        MyLinkedList* tempList = new MyLinkedList();
        tempList->addAtHead(i);
        tempList->addAtTail(i + 1000);
        tempList->deleteAtIndex(0);
        delete tempList;  
    }

    list.addAtHead(10);
    list.addAtTail(20);
    EXPECT_EQ(list.get(2),-1);
    list.deleteAtIndex(5);

    list.addAtIndex(5,99);
    EXPECT_EQ(list.get(5),-1);
    list.addAtIndex(1,15);
    EXPECT_EQ(list.get(1),15);

    MyLinkedList* infiniteLoopTest = new MyLinkedList();
    infiniteLoopTest->addAtHead(1);
    infiniteLoopTest->addAtIndex(1, 2);
    infiniteLoopTest->deleteAtIndex(5);  
    delete infiniteLoopTest; 
}

// Question 8 Tests
TEST(KthCharacterTest, BasicExamples) {
    std::vector<int> ops1 = {0, 0, 0};
    EXPECT_EQ(kthCharacter(5, ops1), 'a');

    std::vector<int> ops2 = {0, 1, 0, 1};
    EXPECT_EQ(kthCharacter(10, ops2), 'b');

    // TODO: Implement tests
    std::vector<int> ops3(100, 0);
    EXPECT_EQ(kthCharacter(1e14, ops3), 'a');

    std::vector<int> ops4 = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}; 
    EXPECT_EQ(kthCharacter(1024, ops4), 'f'); 

    std::vector<int> ops5(10, 1);
    EXPECT_EQ(kthCharacter(1023, ops5), 'j');
 
}

// Question 9 Tests
TEST(MedianSortedArraysTest, BasicExamples) {
    std::vector<int> nums1 = {1, 3};
    std::vector<int> nums2 = {2};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 2.0);

    nums1 = {1, 2};
    nums2 = {3, 4};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 2.5);

    // TODO: Implement tests
    nums1 = {};
    nums2 = {1,3,5};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 3);

    nums1 = {10, 20, 30, 40, 50};
    nums2 = {};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 30.0);

    nums1 = {10, 20, 30, 40, 50};
    nums2 = {5, 15, 25, 35, 45, 55};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 30);

    nums1 = {1, 1, 1, 1};
    nums2 = {1, 1, 1, 1};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 1.0);

    nums1 = {-10, -5, 0, 5, 10};
    nums2 = {-8, -3, 2, 7};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 0.0);

    nums1 = {100, 200, 300};
    nums2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_FLOAT_EQ(findMedianSortedArrays(nums1, nums2), 7);
}

// Question 10 Tests
TEST(ReverseKGroupTest, BasicExamples) {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int k = 2;
    ListNode* result = reverseKGroup(head, k);
    std::vector<int> expected_vals = {2, 1, 4, 3, 5};
    for (int val : expected_vals) {
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->val, val);
        result = result->next;
    }
    // TODO: Implement tests

    ListNode* head2 = new ListNode(2);
    head2->next = new ListNode(1);
    head2->next->next = new ListNode(4);
    head2->next->next->next = new ListNode(3);
    head2->next->next->next->next = new ListNode(5);

    int k4 = 1;
    ListNode* result4 = reverseKGroup(head2, k4);
    std::vector<int> expected_vals4 = {2,1,4,3,5};
    for (int val : expected_vals4) {
        ASSERT_NE(result4, nullptr);
        EXPECT_EQ(result4->val, val);
        result4 = result4->next;
    }

    int k2 = 3;
    ListNode* result2 = reverseKGroup(head2, k2);
    std::vector<int> expected_vals2 = {4,1,2,3,5};
    for (int val : expected_vals2) {
        ASSERT_NE(result2, nullptr);
        EXPECT_EQ(result2->val, val);
        result2 = result2->next;
    }

    

    int k3 = 2;
    ListNode* head3 = new ListNode(1);
    ListNode* result3 = reverseKGroup(head3, k3);
    std::vector<int> expected_vals3 = {1};
    for (int val : expected_vals3) {
        ASSERT_NE(result3, nullptr);
        EXPECT_EQ(result3->val, val);
        result3 = result3->next;
    }
}

// Main entry for GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
