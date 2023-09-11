#pragma once
#include <atomic>


template <typename T> 
class nomutexqueue
{
public:

    struct nomutexqueueNode
    {
    /* data */
        T val_;
        std::atomic<nomutexqueueNode*> next;
        nomutexqueueNode(const T& val) : val_(val), next(nullptr){} 
        nomutexqueueNode() = default;
    };
    std::atomic<nomutexqueueNode*> head_;
    std::atomic<nomutexqueueNode*> tail_;
    /* data */
    
public:
    nomutexqueue(/* args */) {
        head_ = new nomutexqueueNode();
        tail_ = head_.load();
    }

    nomutexqueue(const nomutexqueue<T>&) = delete;

    void Enqueue(const T & val) {
        auto p = new nomutexqueueNode(val);
        nomutexqueueNode* old_tail = tail_.exchange(p);
        old_tail-> next = p; 
    }

    T Dequeue() {
        nomutexqueueNode* data_node;
        T ret;
        nomutexqueueNode* old_head = head_;
        do {
            data_node = old_head -> next;
            ret = data_node -> val_;
        }
        while(head_.compare_exchange_weak(old_head, data_node) != true);
        delete old_head;
        return ret;
    }

};


