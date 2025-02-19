#include <iostream>
using namespace std;
template <class T>
class mqueue {
    class Node {
    public:
        T info;
        Node* next;
        Node() : next(NULL) {}
    };

public:
    Node* head;
    Node* tail;

    mqueue() : head(NULL), tail(NULL) {}

    void push(T _info) {
        Node* temp = new Node;
        temp->info = _info;
        if (head == NULL || tail == NULL)
            head = temp;
        else
            tail->next = temp;
        tail = temp;
        tail->next = NULL;
    }
    bool empty() {
        return head == NULL;
    }
    mqueue(const mqueue& el) : head(NULL), tail(NULL) { 
        for (auto i = el.head; i != NULL; i = i->next) {
            push(i->info);
        }
    }

    void display() const {
        for (auto i = head; i != NULL; i = i->next)
            cout << i->info << " ";
        cout << endl;
    }

    T pop() {
        if (head == NULL) {
            throw runtime_error("Queue is empty");
        }
        auto temp = head->next;
        T data = head->info;
        delete head;
        head = temp;
        if (head == NULL) {
            tail = NULL;
        }
        return data;
    }

    ~mqueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

