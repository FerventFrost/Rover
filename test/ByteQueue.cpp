#include "Queue.h"

ByteQueue::ByteQueue(size_t size) : maxSize(size), frontIndex(0), rearIndex(0), currentSize(0) {
    queueArray = new byte[size];
}

ByteQueue::~ByteQueue() {
    delete[] queueArray;
}

bool ByteQueue::enqueue(const char* data, size_t length) {
    if (isFull()) {
        return false;  // Queue is full, unable to enqueue
    }

    for (size_t i = 0; i < length; ++i) {
        queueArray[rearIndex] = data[i];
        rearIndex = (rearIndex + 1) % maxSize;
        ++currentSize;
    }

    return true;
}

bool ByteQueue::dequeue(char* data, size_t length) {
    if (isEmpty() || length > currentSize) {
        return false;  // Queue is empty or insufficient data to dequeue
    }

    for (size_t i = 0; i < length; ++i) {
        data[i] = queueArray[frontIndex];
        frontIndex = (frontIndex + 1) % maxSize;
        --currentSize;
        std::cout<<data[i];
    }
    std::cout<<'\n';
    return true;
}

bool ByteQueue::isEmpty() const {
    return currentSize == 0;
}

bool ByteQueue::isFull() const {
    return currentSize == maxSize;
}

size_t ByteQueue::size() const {
    return currentSize;
}
