// test_runner.cc

#include <gtest/gtest.h>
#include "library_code.cc"

TEST(findDuplicates, Question5) {
  std::vector<int> nums;
  std::vector<int> rhs;
    
  // Example 1
  nums = std::vector<int>{4,3,2,7,8,2,3,1};
  rhs = std::vector<int>{2,3};
  EXPECT_EQ(findDuplicates(nums), rhs);

  // Example 2
  nums = std::vector<int>{1,1,2};
  rhs = std::vector<int>{1};
  EXPECT_EQ(findDuplicates(nums), rhs);

  // Example 3
  nums = std::vector<int>{1};
  rhs = std::vector<int>{};
  EXPECT_EQ(findDuplicates(nums), rhs);

  // WRITE EXTRA TESTS
  nums = std::vector<int>{2,2,3,3,4,4,5,5,6,6};
  rhs = std::vector<int>{2,3,4,5,6};
  EXPECT_EQ(findDuplicates(nums), rhs);

  nums = std::vector<int>{8,7,6,5,4,3,2,1};
  rhs = std::vector<int>{};
  EXPECT_EQ(findDuplicates(nums), rhs);

  nums = std::vector<int>{1,1,1,1,1};
  rhs = std::vector<int>{1,1,1,1}; 
  EXPECT_EQ(findDuplicates(nums), rhs);

  nums = std::vector<int>{2,4,6,8,2,4,6,8};
  rhs = std::vector<int>{2,4,6,8};
  EXPECT_EQ(findDuplicates(nums), rhs);

  nums = std::vector<int>{1,2,1,4,5,6,7,8};
  rhs = std::vector<int>{1};
  EXPECT_EQ(findDuplicates(nums), rhs);

  nums.clear();
  for (int i = 1; i <= 10000; ++i) nums.push_back(i);
  rhs.clear();
  EXPECT_EQ(findDuplicates(nums), rhs);

  nums.clear();
  for (int i = 1; i <= 5000; ++i) {
    nums.push_back(i);
    nums.push_back(i);
  }
  rhs.clear();
  for (int i = 1; i <= 5000; ++i) {
    rhs.push_back(i);
  }
  EXPECT_EQ(findDuplicates(nums), rhs);
}

TEST(resultsArray, Question6) {
  std::vector<std::vector<int>> queries;
  int k;
  std::vector<int> rhs;

  // Example 1
  queries = std::vector<std::vector<int>>{std::vector<int>{1,2},std::vector<int>{3,4},std::vector<int>{2,3},std::vector<int>{-3,0}};
  k = 2;
  rhs = std::vector<int>{-1,7,5,3};
  EXPECT_EQ(resultsArray(queries, k), rhs);

  // Example 2
  queries = std::vector<std::vector<int>>{std::vector<int>{5,5},std::vector<int>{4,4},std::vector<int>{3,3}};
  k = 1;
  rhs = std::vector<int>{10,8,6};
  EXPECT_EQ(resultsArray(queries, k), rhs);

  // WRITE EXTRA TESTS
  queries = std::vector<std::vector<int>>{ {0, 0}, {1, 1} };
  k = 5;
  rhs = std::vector<int>{-1, -1};
  EXPECT_EQ(resultsArray(queries, k), rhs);

  queries = std::vector<std::vector<int>>{ {1, 1}, {1, 1}, {1, 1} };
  k = 2;
  rhs = std::vector<int>{-1, 2, 2};
  EXPECT_EQ(resultsArray(queries, k), rhs);

  queries = std::vector<std::vector<int>>{ {-1,-2}, {-3,-1}, {-1,-1} };
  k = 2;
  rhs = std::vector<int>{-1, 4, 3};
  EXPECT_EQ(resultsArray(queries, k), rhs);

  queries = std::vector<std::vector<int>>{ {1,5}, {2,2}, {0,3}, {1,1} };
  k = 3;
  rhs = std::vector<int>{-1, -1, 6, 4}; 
  EXPECT_EQ(resultsArray(queries, k), rhs);

  queries.clear();
  for (int i = 999; i >= 0; --i) {
    queries.push_back({i, i});  
  }
  k = 10;
  rhs.clear();
  for (int i = 0; i < 1000; ++i) {
    if (i < 9) rhs.push_back(-1);
    else rhs.push_back(2 * (999 - (i-9)));  
  }
  EXPECT_EQ(resultsArray(queries, k), rhs);
}

TEST(VectorPQueue, Question7) {
  using PQueue = VectorPQueue;

  PQueue* q1 = new PQueue();
  // Insert "ping" and then "pong" in *q1.
  q1->enqueue(std::string("ping"));
  q1->enqueue(std::string("pong"));
  // Extract the minimum of *q1 twice.
  EXPECT_EQ(q1->extractMin(), std::string("ping"));
  EXPECT_EQ(q1->extractMin(), std::string("pong"));
  // Now, *q1 should be empty

  PQueue* q2 = new PQueue();
  // Insert "pong" and then "ping" in *q2.
  q2->enqueue(std::string("pong"));
  q2->enqueue(std::string("ping"));
  // Extract the minimum of *q2 twice.
  EXPECT_EQ(q2->extractMin(), std::string("ping"));
  EXPECT_EQ(q2->extractMin(), std::string("pong"));
  // Now, *q2 should be empty.

  // Test for merge
  q1->enqueue(std::string("ping"));
  q2->enqueue(std::string("pong"));
  PQueue* q3 = PQueue::merge(q1, q2);
  // Do not use q1 and q2 after here.
  EXPECT_EQ(q3->extractMin(), std::string("ping"));
  EXPECT_EQ(q3->extractMin(), std::string("pong"));
  delete q3;
  // Do not use q3 after here.

  // WRITE EXTRA TESTS
  PQueue* escenario1_v = new PQueue();
  escenario1_v->enqueue("c_v");
  escenario1_v->enqueue("a_v");
  escenario1_v->enqueue("b_v");
  EXPECT_EQ(escenario1_v->min(), "a_v");
  EXPECT_EQ(escenario1_v->extractMin(), "a_v");
  EXPECT_EQ(escenario1_v->min(), "b_v");
  EXPECT_EQ(escenario1_v->extractMin(), "b_v");
  EXPECT_EQ(escenario1_v->extractMin(), "c_v");
  delete escenario1_v;

  PQueue* escenario2_v = new PQueue();
  escenario2_v->enqueue("apple");
  escenario2_v->enqueue("banana");
  escenario2_v->enqueue("apple");
  EXPECT_EQ(escenario2_v->extractMin(), "apple");
  EXPECT_EQ(escenario2_v->extractMin(), "apple");
  EXPECT_EQ(escenario2_v->extractMin(), "banana");
  delete escenario2_v;

  PQueue* escenario3_v = new PQueue();
  escenario3_v->enqueue("a_very_long_string_for_vector_test_case_number_three");
  escenario3_v->enqueue("");
  escenario3_v->enqueue("medium_string_v");
  EXPECT_EQ(escenario3_v->extractMin(), "");
  EXPECT_EQ(escenario3_v->extractMin(), "a_very_long_string_for_vector_test_case_number_three");
  EXPECT_EQ(escenario3_v->extractMin(), "medium_string_v");
  delete escenario3_v;

  PQueue* escenario4_merge1_v = new PQueue();
  escenario4_merge1_v->enqueue("z_v_m");
  escenario4_merge1_v->enqueue("x_v_m");
  PQueue* escenario4_merge2_v = new PQueue();
  PQueue* escenario4_merged_v = PQueue::merge(escenario4_merge1_v, escenario4_merge2_v);
  EXPECT_EQ(escenario4_merged_v->extractMin(), "x_v_m");
  EXPECT_EQ(escenario4_merged_v->extractMin(), "z_v_m");
  delete escenario4_merged_v;

  PQueue* escenario5_self_v = new PQueue();
  escenario5_self_v->enqueue("self1_vec");
  escenario5_self_v->enqueue("self0_vec");
  PQueue* escenario5_merged_self_v = PQueue::merge(escenario5_self_v, escenario5_self_v);
  EXPECT_EQ(escenario5_merged_self_v->extractMin(), "self0_vec");
  EXPECT_EQ(escenario5_merged_self_v->extractMin(), "self0_vec");
  EXPECT_EQ(escenario5_merged_self_v->extractMin(), "self1_vec");
  EXPECT_EQ(escenario5_merged_self_v->extractMin(), "self1_vec");
  delete escenario5_merged_self_v;

}

TEST(HeapPQueue, Question7) {
  using PQueue = HeapPQueue;

  PQueue* q1 = new PQueue();
  // Insert "ping" and then "pong" in *q1.
  q1->enqueue(std::string("ping"));
  q1->enqueue(std::string("pong"));
  // Extract the minimum of *q1 twice.
  EXPECT_EQ(q1->extractMin(), std::string("ping"));
  EXPECT_EQ(q1->extractMin(), std::string("pong"));
  // Now, *q1 should be empty

  PQueue* q2 = new PQueue();
  // Insert "pong" and then "ping" in *q2.
  q2->enqueue(std::string("pong"));
  q2->enqueue(std::string("ping"));
  // Extract the minimum of *q2 twice.
  EXPECT_EQ(q2->extractMin(), std::string("ping"));
  EXPECT_EQ(q2->extractMin(), std::string("pong"));
  // Now, *q2 should be empty.

  // Test for merge
  q1->enqueue(std::string("ping"));
  q2->enqueue(std::string("pong"));
  PQueue* q3 = PQueue::merge(q1, q2);
  // Do not use q1 and q2 after here.
  EXPECT_EQ(q3->extractMin(), std::string("ping"));
  EXPECT_EQ(q3->extractMin(), std::string("pong"));
  delete q3;
  // Do not use q3 after here.

  // WRITE EXTRA TESTS
  PQueue* escenario1_h = new PQueue();
  escenario1_h->enqueue("gamma_h");
  escenario1_h->enqueue("alpha_h");
  escenario1_h->enqueue("beta_h");
  EXPECT_EQ(escenario1_h->min(), "alpha_h");
  EXPECT_EQ(escenario1_h->extractMin(), "alpha_h");
  EXPECT_EQ(escenario1_h->min(), "beta_h");
  EXPECT_EQ(escenario1_h->extractMin(), "beta_h");
  EXPECT_EQ(escenario1_h->extractMin(), "gamma_h");
  delete escenario1_h;

  PQueue* escenario2_h = new PQueue();
  escenario2_h->enqueue("frog_h");
  escenario2_h->enqueue("cat_h");
  escenario2_h->enqueue("dog_h");
  escenario2_h->enqueue("cat_h");
  escenario2_h->enqueue("ant_h");
  escenario2_h->enqueue("cat_h");
  EXPECT_EQ(escenario2_h->extractMin(), "ant_h");
  EXPECT_EQ(escenario2_h->extractMin(), "cat_h");
  EXPECT_EQ(escenario2_h->extractMin(), "cat_h");
  EXPECT_EQ(escenario2_h->extractMin(), "cat_h");
  EXPECT_EQ(escenario2_h->extractMin(), "dog_h");
  EXPECT_EQ(escenario2_h->extractMin(), "frog_h");
  delete escenario2_h;

  PQueue* escenario3_h = new PQueue();
  escenario3_h->enqueue("item_h_5");
  escenario3_h->enqueue("item_h_4");
  escenario3_h->enqueue("item_h_3");
  escenario3_h->enqueue("item_h_2");
  escenario3_h->enqueue("item_h_1");
  escenario3_h->enqueue("item_h_0");
  EXPECT_EQ(escenario3_h->extractMin(), "item_h_0");
  EXPECT_EQ(escenario3_h->extractMin(), "item_h_1");
  EXPECT_EQ(escenario3_h->extractMin(), "item_h_2");
  EXPECT_EQ(escenario3_h->extractMin(), "item_h_3");
  EXPECT_EQ(escenario3_h->extractMin(), "item_h_4");
  EXPECT_EQ(escenario3_h->extractMin(), "item_h_5");
  delete escenario3_h;

  PQueue* escenario4_merge1_h = new PQueue();
  escenario4_merge1_h->enqueue("zebra_h_m");
  escenario4_merge1_h->enqueue("apple_h_m");
  escenario4_merge1_h->enqueue("monkey_h_m");
  PQueue* escenario4_merge2_h = new PQueue();
  escenario4_merge2_h->enqueue("banana_h_m");
  escenario4_merge2_h->enqueue("orange_h_m");
  PQueue* escenario4_merged_h = PQueue::merge(escenario4_merge1_h, escenario4_merge2_h);
  EXPECT_EQ(escenario4_merged_h->extractMin(), "apple_h_m");
  EXPECT_EQ(escenario4_merged_h->extractMin(), "banana_h_m");
  EXPECT_EQ(escenario4_merged_h->extractMin(), "monkey_h_m");
  EXPECT_EQ(escenario4_merged_h->extractMin(), "orange_h_m");
  EXPECT_EQ(escenario4_merged_h->extractMin(), "zebra_h_m");
  delete escenario4_merged_h;

  PQueue* escenario5_self_h = new PQueue();
  escenario5_self_h->enqueue("s_heap_c");
  escenario5_self_h->enqueue("s_heap_a");
  escenario5_self_h->enqueue("s_heap_b");
  PQueue* escenario5_merged_self_h = PQueue::merge(escenario5_self_h, escenario5_self_h);
  EXPECT_EQ(escenario5_merged_self_h->extractMin(), "s_heap_a");
  EXPECT_EQ(escenario5_merged_self_h->extractMin(), "s_heap_a");
  EXPECT_EQ(escenario5_merged_self_h->extractMin(), "s_heap_b");
  EXPECT_EQ(escenario5_merged_self_h->extractMin(), "s_heap_b");
  EXPECT_EQ(escenario5_merged_self_h->extractMin(), "s_heap_c");
  EXPECT_EQ(escenario5_merged_self_h->extractMin(), "s_heap_c");
  delete escenario5_merged_self_h;

  PQueue* escenario6_seq_h = new PQueue();
  escenario6_seq_h->enqueue("kilo_h_s");
  escenario6_seq_h->enqueue("lima_h_s");
  EXPECT_EQ(escenario6_seq_h->extractMin(), "kilo_h_s");
  escenario6_seq_h->enqueue("juliett_h_s");
  EXPECT_EQ(escenario6_seq_h->extractMin(), "juliett_h_s");
  escenario6_seq_h->enqueue("india_h_s");
  escenario6_seq_h->enqueue("hotel_h_s");
  EXPECT_EQ(escenario6_seq_h->extractMin(), "hotel_h_s");
  EXPECT_EQ(escenario6_seq_h->extractMin(), "india_h_s");
  EXPECT_EQ(escenario6_seq_h->extractMin(), "lima_h_s");
  delete escenario6_seq_h;

}
// Main entry for GoogleTest
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
