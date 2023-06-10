// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
  // реализация шаблона очереди с приоритетом на связанном списке
 private:
    struct Queue{
      T value;
      Queue* next;
      Queue* prev;
    };
    Queue* head;
    Queue* create(const T& value) {
        Queue* temp = new Queue;
        temp->value = value;
        temp->next = NULL;
        return temp;
    }

 public:
    TPQueue() :head(nullptr) {}
    void push(const T&);
    T pop();
    ~TPQueue() {
        while (head) {
          Queue* tmp = head->next;
          delete head;
          head = tmp;
       }
    }
};
template<typename T>
T TPQueue<T>::pop() {
    if (head == NULL) {
        throw std::string("Empty!");
    } else {
        T i  = head->value;
        Queue* tmp = head->next;
        delete head;
        head = tmp;
        return i;
    }
}
template<typename T>
void TPQueue<T>::push(const T& i) {
    if (head == NULL) {
        head = create(i);
    } else {
        Queue* cur = head;
        int l = 0;
        while (cur) {
            if (cur->value.prior < i.prior) {
                break;
            }
            cur = cur->next;
            l++;
        }
        if (l == 0) {
            Queue* tmp = new Queue;
            tmp->next = head;
            tmp->value = i;
            head = tmp;
        } else {
            cur = head;
            for (int k = 1; k < l; k++) {
                cur = cur->next;
            }
            Queue* tmp = new Queue;
            tmp->next = cur->next;
            tmp->value = i;
            cur->next = tmp;
        }
    }
}

struct SYM {
  char ch;
  int prior;
};


#endif  // INCLUDE_TPQUEUE_H_
