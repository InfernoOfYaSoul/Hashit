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
unsigned hash_point(Point const &p)
{
    return p.x;
}

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
