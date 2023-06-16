#include "Queue.h"

Node::Node(byte *data, size_t length) : length(length), next(nullptr)
{
    this->data = new byte[length];
    memcpy(this->data, data, length);
}

Node::~Node()
{
    delete[] data;
}

ByteQueue::ByteQueue() : front(nullptr), rear(nullptr) {}

ByteQueue::~ByteQueue()
{
    Node *temp = front;
    while (temp != nullptr)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
}

bool ByteQueue::enqueue(byte *data, size_t length)
{
    Node *newNode = new Node(data, length);

    if (isEmpty())
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    Serial.println("Enqueued");
    return true;
}

QueueNodeData ByteQueue::dequeue()
{
    QueueNodeData data;
    if (isEmpty())
    {
        data.data = nullptr;
        data.length = 0;
        return data;
    }

    Node *temp = front;
    data.data = new byte[front->length];

    memcpy(data.data, temp->data, temp->length);
    data.length = temp->length;

    front = front->next;
    delete temp;
    return data;
}

bool ByteQueue::isEmpty() const
{
    return front == nullptr;
}
