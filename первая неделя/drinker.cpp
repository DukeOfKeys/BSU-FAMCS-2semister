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
        int data = head->info;
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


#include <iostream>
//#include "mqueue.hpp"
int main(){
    mqueue<int> player1;
    mqueue<int> player2;
    int input;
    for (int counter = 0; counter < 5; counter++){
        cin >> input;
        player1.push(input);
    }
    for (int counter = 0; counter < 5; counter++){
        cin >> input;
        player2.push(input);
    }
    int operations = 0;
    while (player1.head != NULL && player2.head != NULL)
    {
        if(operations > 1000000)
            break;
        else
            operations++;
        //player1.display();
        int i1, i2;
        i1 = player1.pop();
        i2 = player2.pop();
        if(i1 == 0 && i2 == 9){
            player1.push(i1);
            player1.push(i2);
            continue;
        }
        if(i2 == 0 && i1 == 9){
            player2.push(i1);
            player2.push(i2);
            continue;
        }
        if(i1>i2){
            player1.push(i1);
            player1.push(i2);
        }
        else{
            player2.push(i1);
            player2.push(i2);
        }
    }
    if(operations > 1000000)
        cout << "botva";
    else{
        if(player1.head == NULL){
            cout << "second ";
           // player2.display();
        }
        else{
            cout << "first ";
            //player1.display();
        }
    cout << operations<<endl;
}
}