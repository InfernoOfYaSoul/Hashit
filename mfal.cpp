#include <iostream>

using namespace std;
struct Node
{
    Point key;
    Node *next = nullptr;
};

// сортируемый объект
struct Point
{
    unsigned x, y;
};

// равенство объектов
bool equal_point(Point const &first, Point const &second)
{
    return first.x == second.x and first.y == second.y;
}

// хэш-функция
// пример
unsigned hash_point(Point const &p)
{
    return p.x << 10;
}

// деление
unsigned del_hash_point(Point const &p, size_t size)
{
    return p.x % size;
}

// структура таблицы
struct HTable
{
    Node **table;
    float load_factor;
    std::size_t size_t;
};

// ну типо инициализация таблицы?
HTable first_one(std::size_t size)
{
    Node **table = new Node *[size];
    for (std::size_t i = 0; i != size; ++i)
    {
        table[i] = nullptr;
    }
    return HTable{table, 0.f, size};
}

// удаление таблицы и списка
void destroy_list(Node *&head_ref)
{
    if (head_ref == nullptr)
    {
        return;
    }
    while (head_ref->next != nullptr)
    {
        Node *el = head_ref->next->next;
        delete head_ref->next;
        head_ref->next = el;
    }
    delete head_ref->next;
    head_ref = nullptr;
    return;
}

void erase_table(HTable &tablet)
{
    for (std::size_t i = 0; i != tablet.size_t; ++i)
    {
        destroy_list(tablet.table[i]);
    }
    delete[] tablet.table;
}

// добавление эл-та
void push_front(Node *&head_ref, Point new_key)
{
    if (head_ref == nullptr)
    {
        head_ref = new Node;
        head_ref->key = new_key;
    }
    Node *new_node = new Node;
    new_node->key = new_key;
    new_node->next = head_ref;
    head_ref = new_node;
}

void add_el(HTable &tablet, Point const &new_key)
{
    unsigned ind = hash_point(new_key) % tablet.size_t;
    Node *head = tablet.table[ind];
    bool found = false;
    while (nullptr != head && !found)
    {
        found = equal_point(head->key, new_key);
        head = head->next;
    }
    if (!found)
    {
        push_front(tablet.table[ind], new_key);
        // tablet.table[ind] = push_front(tablet.table[ind], new_key);
        tablet.load_factor += 1.f / tablet.size_t;
    }
}

// поиск элемента
Node *find_el(HTable &tablet, Point const &need_key)
{
    unsigned ind = hash_point(need_key) % tablet.size_t;
    Node *head = tablet.table[ind];
    bool found = false;
    while (nullptr != head && !found)
    {
        found = equal_point(head->key, need_key);
        if (found)
        {
            return head;
        }
        head = head->next;
    }
    if (!found)
    {
        return nullptr;
    }
}

// удаление элемента (не работает не написано не фурычит)
void delete_el(HTable &tablet, Point const &need_key)
{
    unsigned ind = hash_point(need_key) % tablet.size_t;
    Node *head = tablet.table[ind];
    bool found = false;
    while (nullptr != head && !found)
    {
        found = equal_point(head->next->key, need_key);
        if (found)
        {
            Node *el = head->next->next;
            delete head->next;
            head->next = el;
        }
        head = head->next;
    }
}

// расширение таблицы
void rehash(HTable &tablet, std::size_t new_size)
{
    HTable tt = first_one(new_size);
    for (std::size_t i = 0; i != tablet.size_t; ++i)
    {
        Node *head = tablet.table[i];
        while (nullptr != head)
        {
            add_el(tt, head->key);
            head = head->next;
        }
    }
    erase_table(tablet);
    tablet = tt;
}

int main()
{
    int size = 701;
    HTable t = first_one(size);

    Point a;
    a.x = 5;
    a.y = 8;
    add_el(t, a);
    erase_table(t);
    return 0;
}