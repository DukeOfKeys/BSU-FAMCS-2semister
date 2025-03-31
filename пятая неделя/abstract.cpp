#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

class AbstractIterator
{
public:
    virtual ~AbstractIterator() {};
    virtual bool InRange() const = 0;   // индекс в допустимых пределах
    virtual void Reset() = 0;           // сбросить индекс в начало
    virtual int &operator*() const = 0; // разыменование
    virtual void operator++() = 0;      // сдвиг на элемент
};

class AbstractContainer
{
public:
    virtual ~AbstractContainer() {};
    virtual bool IsEmpty() const = 0;    // контейнер пуст
    virtual void push(const int &n) = 0; // втолкнуть
    virtual void pop() = 0;              // вытолкнуть
    virtual int Size() const = 0;        // количество элементов
    virtual void Show() const = 0;
};

class AbstractStack : public AbstractContainer
{
public:
    virtual ~AbstractStack() {};
    virtual int Top() const = 0; // верхний элемент стека
};

class AbstractQueue : public AbstractContainer
{
public:
    virtual ~AbstractQueue() {};
    virtual int Front() const = 0; // первый элемент очереди
    virtual int Back() const = 0;  // последний элемент очереди
};

class ArrayStackIterator; // предваряющее объявление
class ArrayQueueIterator;
class ListStackIterator;
class ListQueueIterator;

/*
РЕАЛИЗАЦИЯ


*/

struct node
{
    int info;
    node *next;
};

class ArrayStack : public AbstractStack
{
protected:
    int size;  // размерность массива
    int *data; // указатель на массив
    int top;   // верхушка стека
public:
    ArrayStack(int _size = 17)
    {
        size = _size;
        data = new int[size];
        top = -1;
    }
    ArrayStack(const ArrayStack &el)
    {
        size = el.size;
        data = new int[size];
        top = el.top;
        for (int i = 0; i <= top; ++i)
        {
            data[i] = el.data[i];
        }
    }
    ArrayStack(ArrayStack &&el)
    {
        data = el.data;
        size = el.size;
        top = el.top;

        el.data = nullptr;
    }
    ~ArrayStack()
    {
        delete[] data;
    }

    void push(const int &n)
    {
        if (IsFull())
        {
            throw "full";
        }
        data[top + 1] = n;
        top = top + 1;
    }
    void pop()
    {
        if (IsEmpty())
        {
            throw "empty";
        }
        top = top - 1;
    }

    bool IsEmpty() const
    {
        return top <= -1;
    }
    bool IsFull() const
    {
        return top >= size - 1;
    }

    int Top() const
    {
        if (IsEmpty())
        {
            throw "empty";
        }
        return data[top];
    }

    int Size() const
    {
        return top + 1;
    }

    ArrayStack operator=(const ArrayStack &el)
    {
        if (this != &el)
        {
            delete[] data;
            size = el.size;
            top = el.top;

            data = new int[size];
            for (int i = 0; i < size; i++)
            {
                data[i] = el.data[i];
            }
        }
        return *this;
    }
    ArrayStack operator=(ArrayStack &&el)
    {
        if (this != &el)
        {
            delete[] data;
            data = el.data;
            size = el.size;
            top = el.top;

            el.data = nullptr;
        }
        return *this;
    }

    void Show() const
    {
        if (IsEmpty())
            throw "stack is empty";

        int i = top;
        while (i != -1)
        {
            cout << data[i] << " ";
            i--;
        }
        cout << endl;
    }
    friend class ArrayStackIterator;
};

class ArrayQueue : public AbstractQueue
{
protected:
    int size;  // размерность массива
    int *data; // указатель на массив
    int head;  // индекс первого занятого элемента
    int tail;  // индекс последнего занятого элемента
    int count; // количество элементов в очереди
public:
    ArrayQueue(int _size = 17)
    {
        size = _size;
        count = 0;
        data = new int[size];
        head = -1;
        tail = 0;
    }
    ArrayQueue(const ArrayQueue &el)
    {
        size = el.size;
        data = new int[size];
        head = el.head;
        count = el.count;
        tail = el.tail;
        for (int i = 0; i < size; ++i)
        {
            data[i] = el.data[i];
        }
    }
    ArrayQueue(ArrayQueue &&el)
    {
        data = el.data;
        head = el.head;
        tail = el.tail;
        size = el.size;
        count = el.count;
        el.data = nullptr;
    }
    ~ArrayQueue()
    {
        delete[] data;
    }

    void push(const int &n)
    {
        if (IsFull())
        {
            throw "full";
        }
        data[tail] = n;
        tail = (tail + 1) % size;
        if (head == -1)
        {
            head = 0;
        }
        count++;
    }
    void pop()
    {
        if (IsEmpty())
        {
            throw "empty";
        }
        head = (head + 1) % size;
        count--;
    }

    bool IsEmpty() const
    {
        return count == 0;
    }
    bool IsFull() const
    {
        return count == size;
    }

    int Size() const
    {
        return count;
    }

    int Front() const
    {
        if (IsEmpty())
        {
            throw "empty";
        }
        return data[head];
    }
    int Back() const
    {
        if (IsEmpty())
        {
            throw "empty";
        }
        return data[(tail - 1 + size) % size];
    }

    ArrayQueue operator=(const ArrayQueue &el)
    {
        if (this != &el)
        {
            delete[] data;
            size = el.size;
            head = el.head;
            tail = el.tail;
            count = el.count;

            data = new int[size];
            for (int i = 0; i < size; i++)
            {
                data[i] = el.data[i];
            }
        }
        return *this;
    }
    ArrayQueue operator=(ArrayQueue &&el)
    {
        if (this != &el)
        {
            delete[] data;
            data = el.data;
            size = el.size;
            head = el.head;
            tail = el.tail;
            count = el.count;

            el.data = nullptr;
        }
        return *this;
    }

    void Show() const
    {
        if (IsEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        int current = head;
        for (int i = 0; i < count; ++i)
        {
            cout << data[current] << " ";
            current = (current + 1) % size;
        }
        cout << endl;
    }
    friend class ArrayQueueIterator;
};

class ListQueue : public AbstractQueue
{
protected:
    node *head;
    node *tail;

public:
    ListQueue() : head(nullptr), tail(nullptr)
    {
    }

    ListQueue(const ListQueue &el)
    {
        head = nullptr;
        tail = nullptr;
        for (auto i = el.head; i != nullptr; i = i->next)
        {
            push(i->info);
        }
    }

    ListQueue(ListQueue &&el)
    {
        head = el.head;
        tail = el.tail;
        el.head = nullptr;
        el.tail = nullptr;
    }

    ~ListQueue()
    {
        while (head != nullptr)
        {
            node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void push(const int &n)
    {
        node *temp = new node;
        temp->info = n;
        temp->next = nullptr;
        if (tail == nullptr)
            head = temp;
        else
            tail->next = temp;
        tail = temp;
    }

    void pop()
    {
        if (head == nullptr)
        {
            throw "Queue is empty";
        }
        node *temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr)
            tail = nullptr;
    }

    int Size() const
    {
        node *temp = head;
        int i = 0;
        while (temp != nullptr)
        {
            i++;
            temp = temp->next;
        }
        return i;
    }

    int Front() const
    {
        if (head == nullptr)
        {
            throw "Queue is empty";
        }
        return head->info;
    }

    int Back() const
    {
        if (tail == nullptr)
        {
            throw "Queue is empty";
        }
        return tail->info;
    }

    bool IsEmpty() const
    {
        return head == nullptr;
    }

    ListQueue &operator=(const ListQueue &el)
    {
        if (this != &el)
        {
            node *temp;
            while (head != nullptr)
            {
                pop();
            }
            tail = nullptr;

            temp = el.head;
            while (temp != nullptr)
            {
                push(temp->info);
                temp = temp->next;
            }
        }
        return *this;
    }

    ListQueue &operator=(ListQueue &&el)
    {
        if (this != &el)
        {
            head = el.head;
            tail = el.tail;
            el.head = nullptr;
            el.tail = nullptr;
        }
        return *this;
    }

    void Show() const
    {
        if (head == nullptr)
        {
            throw "Queue is empty";
        }

        node *current = head;
        while (current != nullptr)
        {
            cout << current->info << " ";
            current = current->next;
        }
        cout << endl;
    }

    friend class ListQueueIterator;
};

class ListStack : public AbstractStack
{
protected:
    node *head;

public:
    ListStack() : head(nullptr) {}

    ListStack(ListStack &&el)
    {
        head = el.head;
        el.head = nullptr;
    }

    ListStack(const ListStack &el)
    {
        head = nullptr;
        node *temp;
        ListStack y;
        temp = el.head;
        while (temp != nullptr)
        {
            y.push(temp->info);
            temp = temp->next;
        }
        temp = y.head;
        while (temp != nullptr)
        {
            push(temp->info);
            temp = temp->next;
        }
    }

    ~ListStack()
    {
        node *temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const int &el)
    {
        node *temp = new node;
        temp->info = el;
        temp->next = head;
        head = temp;
    }

    void pop()
    {
        if (head == nullptr)
        {
            throw "Stack is empty";
        }
        node *temp = head;
        head = head->next;
        delete temp;
    }

    int Size() const
    {
        node *temp = head;
        int i = 0;
        while (temp != nullptr)
        {
            i++;
            temp = temp->next;
        }
        return i;
    }

    int Top() const
    {
        if (head == nullptr)
        {
            throw "Stack is empty";
        }
        return head->info;
    }

    bool IsEmpty() const
    {
        return head == nullptr;
    }

    ListStack &operator=(const ListStack &el)
    {
        if (this != &el)
        {
            node *temp;
            while (head != nullptr)
            {
                pop();
            }

            ListStack y;
            temp = el.head;
            while (temp != nullptr)
            {
                y.push(temp->info);
                temp = temp->next;
            }

            temp = y.head;
            while (temp != nullptr)
            {
                push(temp->info);
                temp = temp->next;
            }
        }
        return *this;
    }

    ListStack &operator=(ListStack &el)
    {
        if (this != &el)
        {
            head = el.head;
            el.head = nullptr;
        }
        return *this;
    }

    void Show() const
    {
        if (head == nullptr)
        {
            throw "Stack is empty";
        }
        node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->info << endl;
            temp = temp->next;
        }
    }

    friend class ListStackIterator;
};

class ArrayStackIterator : public AbstractIterator
{
    ArrayStack &stack_link;
    int pos;
    ArrayStackIterator();

public:
    ArrayStackIterator(ArrayStack &_stack_link) : stack_link(_stack_link), pos(_stack_link.top) {}
    bool InRange() const
    {
        return pos > -1;
    }
    void Reset()
    {
        pos = stack_link.top;
    }
    int &operator*() const
    {
        if (!InRange())
        {
            throw "Iterator out of range";
        }
        return stack_link.data[pos];
    }
    void operator++()
    {
        if (!InRange())
        {
            throw "Iterator out of range";
        }
        --pos;
    }
};

class ArrayQueueIterator : public AbstractIterator
{
    ArrayQueue &a;
    int pos, passed;
    ArrayQueueIterator();

public:
    ArrayQueueIterator(ArrayQueue &_a) : a(_a)
    {
        pos = a.head;
        passed = a.count;
    }
    bool InRange() const
    {
        return passed != 0;
    }
    void Reset()
    {
        pos = a.head;
        passed = a.count;
    }
    int &operator*() const
    {
        if (!InRange())
        {
            throw "Iterator out of range";
        }
        return a.data[pos];
    }
    void operator++()
    {
        pos = (pos + 1) % a.size;
        passed--;
    }
};

class ListStackIterator : public AbstractIterator
{
    ListStack &a;
    node *current;
    ListStackIterator();

public:
    ListStackIterator(ListStack &_a) : a(_a)
    {
        current = a.head;
    }
    bool InRange() const
    {
        return current != nullptr;
    }
    void Reset()
    {
        current = a.head;
    }
    int &operator*() const
    {
        if (!InRange())
        {
            throw "Iterator out of range";
        }
        return current->info;
    }
    void operator++()
    {
        if (!InRange())
        {
            throw "Iterator out of range";
        }
        current = current->next;
    }
};

class ListQueueIterator : public AbstractIterator
{
    ListQueue &a;
    node *current;
    ListQueueIterator();

public:
    ListQueueIterator(ListQueue &_a) : a(_a)
    {
        current = a.head;
    }
    bool InRange() const
    {
        return current != nullptr;
    }
    void Reset()
    {
        current = a.head;
    }
    int &operator*() const
    {
        if (!InRange())
        {
            throw "Iterator out of range";
        }
        return current->info;
    }
    void operator++()
    {
        if (!InRange())
        {
            throw "Iterator out of range";
        }
        current = current->next;
    }
};

int main()
{
    srand(time(NULL));
    ArrayQueue el1;
    AbstractQueue &ref1 = el1;
    for (int index = 0; index < 17; index++)
    {
        ref1.push(rand() % 100);
    }
    ref1.Show();
    ArrayQueueIterator itarator = ArrayQueueIterator(el1);
    AbstractIterator &abstaract_itarator = itarator;
    for (; abstaract_itarator.InRange(); ++abstaract_itarator)
    {
        cout << *abstaract_itarator << " ";
    }
    cout << endl;
    return 0;
}