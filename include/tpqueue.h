// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
using namespace std;

struct SYM {
    char ch;
    int prior;
};

class TPQueue {
private:
    struct ITEM {
        SYM data;
        ITEM* next;
    };

    ITEM* head;
    ITEM* tail;
    ITEM* create(const SYM& data, ITEM* next);
    ITEM* findIns(const SYM& data);
public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const SYM& data);
    SYM pop();
    void remove(const SYM& data);
    void append(const SYM& data);
    void print();
};

TPQueue::ITEM* TPQueue::create(const SYM& data, ITEM* next) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = next;

    return item;
}

TPQueue::ITEM* TPQueue::findIns(const SYM& data) {
    ITEM* prev = nullptr;
    ITEM* curr = head;
    while (curr != nullptr && data.prior <= curr->data.prior) {
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

TPQueue::~TPQueue() {
    while (head)
        pop();
}

void TPQueue::push(const SYM& data) {
    ITEM* newItem = create(data, nullptr);

    if (head == nullptr) {
        // Если очередь пуста, новый элемент становится первым
        head = newItem;
        tail = newItem;
    }
    else if (data.prior > head->data.prior) {
        // Если приоритет нового элемента больше приоритета головы, новый элемент становится новой головой
        newItem->next = head;
        head = newItem;
    }
    else {
        ITEM* current = head;
        while (current->next && data.prior <= current->next->data.prior) {
            // Проходим по очереди, пока не найдем элемент, у которого приоритет меньше нового элемента
            current = current->next;
        }
        newItem->next = current->next;
        current->next = newItem;
        if (current == tail) {
            // Если текущий элемент - это хвост, обновляем хвост
            tail = newItem;
        }
    }
}

SYM TPQueue::pop() {
    if (head) {
        ITEM* temp = head->next;
        SYM data = head->data;
        delete head;
        head = temp;
        return data;
    }
    else {
        cout << "Очередь пуста!" << endl;
        return SYM{ '\0', 0 };
    }
}

void TPQueue::remove(const SYM& data) {
    ITEM* prev = nullptr;
    ITEM* curr = head;
    while (curr != nullptr) {
        if (curr->data.ch == data.ch && curr->data.prior == data.prior) {
            if (prev == nullptr) {
                head = curr->next;
                delete curr;
                curr = head;
            }
            else {
                prev->next = curr->next;
                if (curr == tail)
                    tail = prev;
                delete curr;
                curr = prev->next;
            }
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void TPQueue::append(const SYM& data) {
    ITEM* newItem = create(data, nullptr);

    if (tail) {
        tail->next = newItem;
        tail = newItem;
    }
    else {
        head = tail = newItem;
    }
}

void TPQueue::print() {
    ITEM* current = head;
    while (current) {
        cout << current->data.ch << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    TPQueue queue;

    cout << "Введите полный список символов и их приоритетов через пробел, для завершения введите '0 0':\n";

    vector<SYM> inputList;
    while (true) {
        SYM data;
        cin >> data.ch >> data.prior;
        if (data.ch == '0' && data.prior == 0)
            break;
        inputList.push_back(data);
    }

    for (const auto& data : inputList) {
        queue.push(data);
    }

    while (true) {
        cout << "Выберите действие:\n";
        cout << "1. Удалить элемент\n";
        cout << "2. Добавить элемент\n";
        cout << "3. Завершить работу\n";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Введите символ и его приоритет, которые необходимо удалить из очереди: ";
            SYM data;
            cin >> data.ch >> data.prior;
            queue.remove(data);
            cout << "Очередь после удаления элемента: ";
            queue.print();
        }
        else if (choice == 2) {
            cout << "Введите символ и его приоритет для добавления в очередь: ";
            SYM data;
            cin >> data.ch >> data.prior;
            queue.push(data);
            cout << "Очередь после добавления нового элемента: ";
            queue.print();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    }

    cout << "Извлечение символов из очереди:" << endl;
    while (true) {
        SYM data = queue.pop();
        if (data.ch == '\0')
            break;
        cout << "Извлечен символ: " << data.ch << ", Приоритет: " << data.prior << endl;
    }

    cout << "Очередь пуста!" << endl;

    return 0;
}
