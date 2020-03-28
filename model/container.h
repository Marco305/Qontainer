#ifndef CONTAINER_H
#define CONTAINER_H

template <class T>
class Container {
private:
    struct Node {
        T data;
        Node* next;

        Node();

        Node(const T&, Node*);

        Node(T&&, Node*);
    };
    Node* first;

    unsigned int count;

    static Node* copy(Node*);

public:
    class Iterator {
    private:
        Node* ptr;

        friend class Container<T>;
        Iterator(Node*);

    public:
        Iterator();

        bool operator==(const Iterator&) const;

        bool operator!=(const Iterator&) const;

        Iterator& operator++();

        const Iterator operator++(int);

        T* operator->() const;

        T& operator*() const;
    };

    class ConstIterator {
    private:
        Node* ptr;

        friend class Container<T>;
        ConstIterator(Node*);

    public:
        ConstIterator();

        ConstIterator(const Iterator&);

        bool operator==(const ConstIterator&) const;

        bool operator!=(const ConstIterator&) const;

        ConstIterator& operator++();

        const ConstIterator operator++(int);

        T* operator->() const;

        const T& operator*() const;
    };

    Iterator begin();

    Iterator end();

    ConstIterator begin() const;

    ConstIterator cbegin() const;

    ConstIterator end() const;

    ConstIterator cend() const;

    explicit Container();

    Container(const Container&);

    Container& operator=(const Container&);

    ~Container();

    // Insert by copy
    void insert(const T&);

    // Insert by move
    void insert(T&&);

    // Tries to removes the first occurrence and returns whether it has been found or not
    bool remove(const T&);

    // Returns whether there is at least one occurrence
    bool contains(const T&) const;

    void clear();

    bool isEmpty() const;

    unsigned int size() const;
};

/* -------------------- Container::Node -------------------- */

template <class T>
Container<T>::Node::Node() : next(nullptr) {}

template <class T>
Container<T>::Node::Node(const T& data, Container::Node* p) : data(data), next(p) {}

template <class T>
Container<T>::Node::Node(T&& data, Container::Node* p) : data(std::move(data)), next(p) {}

/* ------------------ Container::Iterator ------------------ */

template <class T>
Container<T>::Iterator::Iterator(Container::Node* p) : ptr(p) {}

template <class T>
Container<T>::Iterator::Iterator() : ptr(nullptr) {}

template <class T>
bool Container<T>::Iterator::operator==(const Container::Iterator& it) const {
    return ptr == it.ptr;
}

template <class T>
bool Container<T>::Iterator::operator!=(const Container::Iterator& it) const {
    return ptr != it.ptr;
}

template <class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator++() {
    if (ptr != nullptr) {
        ptr = ptr->next;
    }
    return *this;
}

template <class T>
const typename Container<T>::Iterator Container<T>::Iterator::operator++(int) {
    Iterator tmp(*this);
    if (ptr != nullptr) {
        ptr = ptr->next;
    }
    return tmp;
}

template <class T>
T* Container<T>::Iterator::operator->() const {
    return &(ptr->data);
}

template <class T>
T& Container<T>::Iterator::operator*() const {
    return ptr->data;
}

/* ---------------- Container::ConstIterator ---------------- */

template <class T>
Container<T>::ConstIterator::ConstIterator(Container::Node* p) : ptr(p) {}

template <class T>
Container<T>::ConstIterator::ConstIterator() : ptr(nullptr) {}

template <class T>
Container<T>::ConstIterator::ConstIterator(const Iterator& it) : ptr(it.ptr) {}

template <class T>
bool Container<T>::ConstIterator::operator==(const Container::ConstIterator& it) const {
    return ptr == it.ptr;
}

template <class T>
bool Container<T>::ConstIterator::operator!=(const Container::ConstIterator& it) const {
    return ptr != it.ptr;
}

template <class T>
typename Container<T>::ConstIterator& Container<T>::ConstIterator::operator++() {
    if (ptr != nullptr) {
        ptr = ptr->next;
    }
    return *this;
}

template <class T>
const typename Container<T>::ConstIterator Container<T>::ConstIterator::operator++(int) {
    Iterator tmp(*this);
    if (ptr != nullptr) {
        ptr = ptr->next;
    }
    return tmp;
}

template <class T>
T* Container<T>::ConstIterator::operator->() const {
    return &(ptr->data);
}

template <class T>
const T& Container<T>::ConstIterator::operator*() const {
    return ptr->data;
}

/* ----------------------- Container ----------------------- */

template <class T>
typename Container<T>::Node* Container<T>::copy(Container::Node* p) {
    if (p == nullptr) {
        return nullptr;
    }
    return new Node(p->data, copy(p->next));
}

template <class T>
typename Container<T>::Iterator Container<T>::begin() {
    return Iterator(first);
}

template <class T>
typename Container<T>::Iterator Container<T>::end() {
    return Iterator(nullptr);
}

template <class T>
typename Container<T>::ConstIterator Container<T>::begin() const {
    return ConstIterator(first);
}

template <class T>
typename Container<T>::ConstIterator Container<T>::cbegin() const {
    return ConstIterator(first);
}

template <class T>
typename Container<T>::ConstIterator Container<T>::end() const {
    return ConstIterator(nullptr);
}

template <class T>
typename Container<T>::ConstIterator Container<T>::cend() const {
    return ConstIterator(nullptr);
}

template <class T>
Container<T>::Container() : first(nullptr), count(0) {}

template <class T>
Container<T>::Container(const Container& c) {
    first = copy(c.first);
    count = c.count;
}

template <class T>
Container<T>& Container<T>::operator=(const Container& c) {
    if (this != &c) {
        clear();
        first = copy(c.first);
        count = c.count;
    }
    return *this;
}

template <class T>
Container<T>::~Container() {
    clear();
}

template <class T>
void Container<T>::insert(const T& data) {
    first = new Node(data, first);
    ++count;
}

template <class T>
void Container<T>::insert(T&& data) {
    first = new Node(std::move(data), first);
    ++count;
}

template <class T>
bool Container<T>::remove(const T& data) {
    if (first == nullptr) {
        return false;
    }

    if (first->data == data) {
        Node* p = first;
        first = first->next;
        delete p;
        --count;
        return true;
    }

    Node* p = first->next;
    Node* q = first;
    while (p != nullptr) {
        if (p->data == data) {
            q->next = p->next;
            delete p;
            --count;
            return true;
        }
        q = p;
        p = p->next;
    }

    return false;
}

template <class T>
bool Container<T>::contains(const T& data) const {
    for (Node* p = first; p != nullptr; p = p->next) {
        if (p->data == data) {
            return true;
        }
    }
    return false;
}

template <class T>
void Container<T>::clear() {
    Node* p = first;
    while (p != nullptr) {
        Node* q = p;
        p = p->next;
        delete q;
    }
    first = nullptr;
    count = 0;
}

template <class T>
bool Container<T>::isEmpty() const {
    return first == nullptr;
}

template<class T>
unsigned int Container<T>::size() const {
    return count;
}

#endif // CONTAINER_H