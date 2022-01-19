#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <unordered_map>

// структуру ListNode модифицировать нельзя
struct ListNode {
     ListNode *prev;
     ListNode *next;
     ListNode *rand; // указатель на произвольный элемент данного списка либо NULL
     std::string data;
};

class List {
public:
    List() = default;
    ~List();
    void Serialize(FILE *file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize(FILE *file);// загрузка из файла (файл открыт с помощью fopen(path, "rb"))

    void addNode(const std::string &data, ListNode *randNode = nullptr);
    void print();
    void clear();

    ListNode* operator[](int index);

    friend std::ostream& operator<<(std::ostream& os, const List& dt);

private:
    void serializeNode(ListNode *node,
                       const std::unordered_map<ListNode*, int> &nodesMap,
                       FILE *file);
    void deserializeNode(ListNode *node,
                       const std::unordered_map<int, ListNode*> &nodesMap,
                       FILE *file);

private:
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int count = 0;
};
