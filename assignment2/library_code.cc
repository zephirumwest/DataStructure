  // library_code.cc

  #include <iostream>
  #include <vector>
  #include <string>
  #include <utility>

  // Question 5: Find all duplicates in an array
  std::vector<int> findDuplicates(std::vector<int>& nums) {
    std::vector<int> answer;
    for(int i = 0; i < nums.size(); i++){
      int k = nums[i] < 0 ? -nums[i] : nums[i];
      if (nums[k - 1] < 0) {
        answer.push_back(k);
      } else {
        nums[k - 1] *= -1;
      }
    }
    return answer;
  }

  // Question 6: k-th nearest obstacle queries
  std::vector<int> resultsArray(std::vector<std::vector<int>>& queries, int k) {
    std::vector<int> heap; 
    std::vector<int> results;

    for (const auto& query : queries) {
        int x = query[0] < 0 ? -query[0] : query[0];
        int y = query[1] < 0 ? -query[1] : query[1];
        int distance = x + y;

        if (heap.size() < k) {
            heap.push_back(distance);
            int idx = heap.size() - 1;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (heap[idx] <= heap[parent]) break;
                int temp = heap[parent];
                heap[parent] = heap[idx];
                heap[idx] = temp;
                idx = parent;
            }
        } else if (distance < heap[0]) {
            heap[0] = distance;
            int idx = 0;
            while (true) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int largest = idx;

                if (left < heap.size() && heap[left] > heap[largest]) 
                    largest = left;
                if (right < heap.size() && heap[right] > heap[largest])
                    largest = right;

                if (largest == idx) break;
                int temp = heap[idx];
                heap[idx] = heap[largest];
                heap[largest] = temp;
                idx = largest;
            }
        }

        results.push_back(heap.size() >= k ? heap[0] : -1);
    }

    return results;
  }

  // Question 7: Priority queue implementation
  class PQueue {
    public:
      virtual void enqueue(const std::string& elem) = 0;
      virtual std::string extractMin() = 0;
      virtual const std::string& min() const = 0;
      virtual ~PQueue() = default;
  };

  // Question 7: Implementation 1: Unsorted Vector - VectorPQueue class
  class VectorPQueue : public PQueue {
    public:
      VectorPQueue();
      ~VectorPQueue();
      void enqueue(const std::string& elem) override;
      std::string extractMin() override;
      const std::string& min() const override;
      static VectorPQueue* merge(VectorPQueue* one, VectorPQueue* two);
    private:
      std::vector<std::string> data;
    public:
      // update this section with the list of
      // data members and helper methods needed to implement
      // the vector-backed version of the PQueue.
  };

  VectorPQueue::VectorPQueue() : PQueue() /* WRITE YOUR CODE (if necessary) */ {
    // WRITE YOUR CODE
  }

  VectorPQueue::~VectorPQueue() {
    // WRITE YOUR CODE
  }

  void VectorPQueue::enqueue(const std::string& elem) {
    data.push_back(elem);
  }

  std::string VectorPQueue::extractMin() {
    if (data.empty()) std::exit(1);
    int minIndex = 0;
    for (size_t i = 1; i < data.size(); ++i) {
      if (data[i] < data[minIndex]) minIndex = static_cast<int>(i);
    }

    std::string result = data[minIndex];
    data.erase(data.begin() + minIndex);
    return result;
  }

  const std::string& VectorPQueue::min() const {
    if (data.empty()) std::exit(1); 

    int minIndex = 0;
    for (size_t i = 1; i < data.size(); ++i) {
      if (data[i] < data[minIndex]) minIndex = static_cast<int>(i);
    }
    return data[minIndex];
  }

  VectorPQueue* VectorPQueue::merge(VectorPQueue* one, VectorPQueue* two) {
    VectorPQueue* result = new VectorPQueue();
  
    if (one == two) {
      if (one != nullptr) { 
          result->data.reserve(one->data.size() * 2); 
          result->data.insert(result->data.end(), one->data.begin(), one->data.end());
          result->data.insert(result->data.end(), one->data.begin(), one->data.end());
          delete one; 
      }
    } else {
      if (one != nullptr) {
          result->data.insert(result->data.end(), one->data.begin(), one->data.end());
          delete one;
      }
      if (two != nullptr) {
          result->data.insert(result->data.end(), two->data.begin(), two->data.end());
          delete two;
      }
    }
    return result;
  }

// Question 7: Implementation 2: Binary Heap - HeapPQueue class
class HeapPQueue : public PQueue {
  public:
      HeapPQueue();
      ~HeapPQueue() override; 
      void enqueue(const std::string& elem) override;
      std::string extractMin() override;
      const std::string& min() const override;
      static HeapPQueue* merge(HeapPQueue* one, HeapPQueue* two);
  
  private:
      std::string* heap;  
      int size;           
      int capacity;      
  
      void bubbleUp(int idx);
      void bubbleDown(int idx);
      void resize(int newCapacity); 

      static void heapify(std::string* arr, int n, int idx);
  };
  

  HeapPQueue::HeapPQueue() : PQueue(), size(0), capacity(4) { 
      // Initially, the length of the internal array should be
      // 4 + 1 if you employ 1-based indexing, or
      // 4 + 0 if you employ 0-based indexing.
      // WRITE YOUR CODE
      heap = new std::string[capacity]; 
  }
  
  HeapPQueue::~HeapPQueue() {
      // WRITE YOUR CODE
      delete[] heap; 
      heap = nullptr; 
      size = 0;
      capacity = 0;
  }
  

  void HeapPQueue::resize(int newCapacity) {
      if (newCapacity <= capacity) return; 
  
      std::string* newHeap = new std::string[newCapacity];
      for (int i = 0; i < size; ++i) {
          newHeap[i] = heap[i];
      }
  
      delete[] heap;
      heap = newHeap;
      capacity = newCapacity;
  }
  
  void HeapPQueue::bubbleUp(int idx) {
      while (idx > 0) {
          int parent = (idx - 1) / 2;
          if (heap[idx] < heap[parent]) {
              std::string temp = heap[idx];
              heap[idx] = heap[parent];
              heap[parent] = temp;
              idx = parent;
          } else {
              break;
          }
      }
  }
  
  void HeapPQueue::bubbleDown(int idx) {
      while (true) {
          int left_child = 2 * idx + 1;
          int right_child = 2 * idx + 2;
          int smallest_idx = idx; 
  
          if (left_child < size && heap[left_child] < heap[smallest_idx]) {
              smallest_idx = left_child;
          }
          if (right_child < size && heap[right_child] < heap[smallest_idx]) {
              smallest_idx = right_child;
          }
  
          if (smallest_idx != idx) {
              std::string temp = heap[idx];
              heap[idx] = heap[smallest_idx];
              heap[smallest_idx] = temp;
              idx = smallest_idx;
          } else {
              break;
          }
      }
  }
  
  void HeapPQueue::enqueue(const std::string& elem) {
      if (size == capacity) {
          resize(capacity == 0 ? 4 : capacity * 2); 
      }
  
      heap[size] = elem; 
      bubbleUp(size);    
      size++;            
  }
  
  std::string HeapPQueue::extractMin() {
      if (size == 0) {
          std::exit(1); 
      }
  
      std::string minVal = heap[0]; 
      heap[0] = heap[size - 1];   
      size--;                     
  
      if (size > 0) {
          bubbleDown(0); 
      }
  
      return minVal;
  }
  
  const std::string& HeapPQueue::min() const {
      if (size == 0) {
          std::exit(1);
      }
      return heap[0];
  }
  
  void HeapPQueue::heapify(std::string* arr, int n, int idx) {
      while (true) {
          int left_child = 2 * idx + 1;
          int right_child = 2 * idx + 2;
          int smallest_idx = idx;
  
          if (left_child < n && arr[left_child] < arr[smallest_idx]) {
              smallest_idx = left_child;
          }
          if (right_child < n && arr[right_child] < arr[smallest_idx]) {
              smallest_idx = right_child;
          }
  
          if (smallest_idx != idx) {
              std::string temp = arr[idx];
              arr[idx] = arr[smallest_idx];
              arr[smallest_idx] = temp;
              idx = smallest_idx;
          } else {
              break;
          }
      }
  }
  
  HeapPQueue* HeapPQueue::merge(HeapPQueue* one, HeapPQueue* two) {
    HeapPQueue* result = new HeapPQueue(); 

    if (one == two) {
        if (one != nullptr) { 
            int originalSize = one->size;
            int newTotalSize = originalSize * 2;

            delete[] result->heap; 
            result->size = newTotalSize;
            result->capacity = (newTotalSize > 0) ? newTotalSize : 4;
            result->heap = new std::string[result->capacity];

            for (int i = 0; i < originalSize; ++i) {
                result->heap[i] = one->heap[i];
                result->heap[originalSize + i] = one->heap[i]; 
            }

            for (int i = (result->size / 2) - 1; i >= 0; --i) {
                HeapPQueue::heapify(result->heap, result->size, i);
            }
            delete one; 
        }


    } else {
        int sizeOne = (one != nullptr) ? one->size : 0;
        int sizeTwo = (two != nullptr) ? two->size : 0;
        int totalSize = sizeOne + sizeTwo;

        delete[] result->heap; 
        result->size = totalSize;
        result->capacity = (totalSize > 0) ? totalSize : 4;
        result->heap = new std::string[result->capacity];

        int currentIndex = 0;
        if (one != nullptr) {
            for (int i = 0; i < one->size; ++i) {
                result->heap[currentIndex++] = one->heap[i];
            }
            delete one;
        }
        if (two != nullptr) {
            for (int i = 0; i < two->size; ++i) {
                result->heap[currentIndex++] = two->heap[i];
            }
            delete two;
        }

        for (int i = (result->size / 2) - 1; i >= 0; --i) {
            HeapPQueue::heapify(result->heap, result->size, i);
        }
    }
    return result;
}
