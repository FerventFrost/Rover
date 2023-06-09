#include "Queue.h"

Node::Node(byte* data, size_t length) : length(length), next(nullptr) {
    this->data = new byte[length];
    memcpy(this->data, data, length);
}

Node::~Node() {
    delete[] data;
}

ByteQueue::ByteQueue() : front(nullptr), rear(nullptr) {}

ByteQueue::~ByteQueue() {
    Node* temp = front;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

bool ByteQueue::enqueue(byte* data, size_t length) {
    Node* newNode = new Node(data, length);

    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    return true;
}

bool ByteQueue::dequeue(byte* data, size_t length) {
    if (isEmpty()) {
        return false;
    }

    Node* temp = front;
    front = front->next;
    memcpy(data, temp->data, length);
    delete temp;

    return true;
}

bool ByteQueue::isEmpty() const {
    return front == nullptr;
}
// ByteQueue::ByteQueue(size_t size) : maxSize(size), frontIndex(0), rearIndex(0), currentSize(0) {
//     queueArray = new byte[size];
// }

// ByteQueue::~ByteQueue() {
//     delete[] queueArray;
// }

// bool ByteQueue::enqueue(const byte* data, size_t length) {
//     if (isFull()) {
//         return false;  // Queue is full, unable to enqueue
//     }

//     for (size_t i = 0; i < length; ++i) {
//         queueArray[rearIndex] = data[i];
//         rearIndex = (rearIndex + 1) % maxSize;
//         ++currentSize;
//     }

//     return true;
// }

// bool ByteQueue::dequeue(byte* data, size_t length) {
//     if (isEmpty() || length > currentSize) {
//         return false;  // Queue is empty or insufficient data to dequeue
//     }

//     for (size_t i = 0; i < length; ++i) {
//         data[i] = queueArray[frontIndex];
//         frontIndex = (frontIndex + 1) % maxSize;
//         --currentSize;
//     }

//     return true;
// }

// bool ByteQueue::isEmpty() const {
//     return currentSize == 0;
// }

// bool ByteQueue::isFull() const {
//     return currentSize == maxSize;
// }

// size_t ByteQueue::size() const {
//     return currentSize;
// }
