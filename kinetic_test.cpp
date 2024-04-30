#include <iostream>
#include <vector>
#include <algorithm>
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
                heapifyDown(it - heap.begin());
            }
        }
    }

    // Heapify down operation
    void heapifyDown(int idx) {
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        if (left < heap.size() && heap[left]->key > heap[largest]->key)
            largest = left;
        if (right < heap.size() && heap[right]->key > heap[largest]->key)
            largest = right;
    
        if (largest != idx) {
            swap(heap[idx], heap[largest]);
            heapifyDown(largest);
        }
    }

    // Print the kinetic heap
    void printHeap() {
        vector<Node*>::iterator it;
        for (auto it = heap.begin(); it != heap.end(); ++it) {
            std::cout << "Key: " << (*it)->key << ", Data: " << (*it)->data << "\n";
        }
    }

    // Advance time in the kinetic heap
    void advanceTime(int time) {
        for (Node* node : heap) {
            node->certificateTime -= time;
            if (node->certificateTime <= 0) {
                node->certificate = 0;
            }
        }
    }

    // Get the last element of the heap
    Node* getele() {
        if (heap.empty()) return nullptr;
        return heap.back();
    }

    // Destructor to free memory
    ~KineticHeap() {
        for (Node* node : heap) {
            delete node;
        }
    }
};

int main() {
    KineticHeap kheap;

    // Test Case 1: Insert elements into the kinetic heap
    kheap.insert(20, 1);
    kheap.insert(35, 2);
    kheap.insert(13, 3);
    kheap.insert(40, 4);
    kheap.insert(25, 5);

    // Test Case 2: Find the maximum element of the kinetic heap
    Node* maxNode = kheap.findMax();
    if (maxNode)
        cout << "Max Node: Key = " << maxNode->key << ", Data = " << maxNode->data << "\n";

    // Test Case 3: Print the initial heap
    cout << "Initial Heap:\n";
    kheap.printHeap();

    // Test Case 4: Delete a node from the heap
    Node* nodeToDelete = kheap.getele();
    cout << "Node to delete: " << nodeToDelete->key << endl;
    if (nodeToDelete) {
        kheap.deleteElement(nodeToDelete);
        cout << "After deleting node with key " << nodeToDelete->key << ":\n";
        kheap.printHeap();
    } else {
        cout << "Node to delete is null";
    }

    // Test Case 5: Advance time in the kinetic heap
    kheap.advanceTime(10);

    // Test Case 6: Heapify down operation
    kheap.heapifyDown(0);
    cout << "Heap after heapify down operation:\n";
    kheap.printHeap();

    return 0;
}