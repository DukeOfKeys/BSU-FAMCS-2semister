#include <iostream>

template <class T>
class mStack
{
private:
    class Node
    {
    public:
        Node *next;
        T info;
        Node(Node *_next, T _info) : next(_next), info(_info) {}
    };

    Node *head;

public:
    mStack() : head(nullptr) {}

    mStack(const mStack &other) : head(nullptr)
    {
        if (other.head)
        {
            Node *temp = other.head;
            Node *newNode = new Node(nullptr, temp->info);
            head = newNode;
            Node *current = head;
            temp = temp->next;

            while (temp)
            {
                current->next = new Node(nullptr, temp->info);
                current = current->next;
                temp = temp->next;
            }
        }
    }

    mStack &operator=(const mStack &other)
    {
        if (this == &other)
            return *this;

        clear();

        if (other.head)
        {
            Node *temp = other.head;
            Node *newNode = new Node(nullptr, temp->info);
            head = newNode;
            Node *current = head;
            temp = temp->next;

            while (temp)
            {
                current->next = new Node(nullptr, temp->info);
                current = current->next;
                temp = temp->next;
            }
        }
        return *this;
    }

    mStack(mStack &&other) noexcept : head(other.head)
    {
        other.head = nullptr;
    }

    mStack &operator=(mStack &&other) noexcept
    {
        if (this == &other)
            return *this;

        clear();
        head = other.head;
        other.head = nullptr;

        return *this;
    }

    void push(T el)
    {
        Node *new_el = new Node(head, el);
        head = new_el;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Stack is empty! Cannot pop.");
        }
        Node *temp = head;
        T value = head->info;
        head = head->next;
        delete temp;
        return value;
    }
    T top()
    {
        if (isEmpty())
            throw std::runtime_error("Stack is empty! Cannot give last.");
        return head->info;
    }
    bool isEmpty() const
    {
        return head == nullptr;
    }

    void clear()
    {
        while (!isEmpty())
            pop();
    }

    ~mStack()
    {
        clear();
    }
};
