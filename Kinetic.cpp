#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int certificate;
    int certificateTime;

    Node(int k, int d) : key(k), data(d), left(nullptr), right(nullptr), parent(nullptr), certificate(0), certificateTime(INT_MAX) {}
};

// Certificate event
struct CertificateEvent {
    Node* node;
    int time;

    CertificateEvent(Node* n, int t) : node(n), time(t) {}

    bool operator<(const CertificateEvent& other) const {
        return time > other.time;
    }
};

class KineticHeap {
private:
    vector<Node*> heap;

public:
     // Insert an element into the kinetic heap
    void insert(int key, int data) {
        Node* newNode = new Node(key, data);
        heap.push_back(newNode);
        heapifyUp(heap.size() - 1);
    }

    // Find the maximum element of the kinetic heap
    Node* findMax() {
        if (heap.empty()){
            return nullptr;            
        } 
        return heap.front();
    }
  // Delete the maximum element from the kinetic heap
    void deleteMax() {
        if (heap.empty()) return;

        delete heap.front();
        heap.front() = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
    // Delete element using key
    void deleteElement(Node* nd) {
      if (nd == nullptr) 
          return;

      auto it = find(heap.begin(), heap.end(), nd);
      if (it != heap.end()) {
          swap(*it, heap.back());
          heap.pop_back();
          if (it != heap.end()) {
            heapifyDown(it - heap.begin()); \\to be defined
          }
      }
    }

    // Print the kinetic heap
    void printHeap() {
        vector<Node*>::iterator it;
        for (auto it = heap.begin(); it != heap.end(); ++it) {
        std::cout << "Key: " << (*it)->key << ", Data: " << (*it)->data << "\n";
        }
    }

    //to fetch given node(for delete function)
   Node* getele() {
    if (heap.empty()) return nullptr;
        return heap.back();
   }

   //destructor
   ~KineticHeap() {
        for (Node* node : heap) {
            delete node;
        }
    }


};

int main() {
    KineticHeap kheap;

    // Insert elements....
    kheap.insert(20, 1);
    kheap.insert(35, 2);
    kheap.insert(13, 3);
    kheap.insert(40, 4);
    kheap.insert(25, 5);

    //Find max
    Node* maxNode = kheap.findMax();
    if (maxNode)
        cout << "Max Node: Key = " << maxNode->key << ", Data = " << maxNode->data << "\n";
    //traverse heap
    std::cout << "Initial Heap:\n";
    kheap.printHeap();
 
    // Delete a specific element
    Node* nodeToDelete = kheap.getele();
    
    cout<<nodeToDelete->key<<endl;
    if (nodeToDelete) {
        kheap.deleteElement(nodeToDelete);
        std::cout << "After deleting node with key " << nodeToDelete->key << ":\n";
        kheap.printHeap();
    }
    else{
      cout<<"Node to delete is null";
    }


    return 0;
}
