#include "task2.h"

List::~List() {
    clear();
}

void List::clear() {
    ListNode *tmp = head;
    while (tmp) {
        auto prev = tmp;
        tmp = tmp->next;
        delete prev;
    }

    count = 0;
    head = nullptr;
    tail = nullptr;
}

void List::addNode(const std::string &data, ListNode *randNode) {
    ListNode *node = new ListNode({nullptr, nullptr, randNode, data});
    if (count == 0) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++count;
}

ListNode* List::operator[](int index) {
    if (index >= count || index < 0) return nullptr;
    if (index == 0) return head;
    if (index == count - 1) return tail;

    ListNode *tmp = head;
    int curIndex = 0;
    while (tmp) {
        if (curIndex == index) {
            return tmp;
        }
        tmp = tmp->next;
        ++curIndex;
    }

    return nullptr;
}

void List::Serialize(FILE *file) {
    if (!file) return;
    fwrite(&count, sizeof(int), 1, file);

    if (count != 0) {
        ListNode *tmp = head;
        std::unordered_map<ListNode*, int> nodesMap;
        int index = 0;
        while (tmp) {
            nodesMap[tmp] = index;
            ++index;
            tmp = tmp->next;
        }

        tmp = head;
        while (tmp) {
            serializeNode(tmp, nodesMap, file);
            tmp = tmp->next;
        }
    }
}

void List::serializeNode(ListNode *node,
                         const std::unordered_map<ListNode*, int> &nodesMap,
                         FILE *file) {
    std::string serializeNodeString;

    auto writeIndex = [&nodesMap, &file](ListNode* node) {
        int index = -1;
        if (node) {
            auto it = nodesMap.find(node);
            if (it != nodesMap.end()) {
                index = it->second;
            }
        }
        fwrite(&index, sizeof(int), 1, file);
    };

    writeIndex(node->prev);
    writeIndex(node->next);
    writeIndex(node->rand);

    auto str = node->data;
    auto dataSize = str.length();
    fwrite(&dataSize, sizeof(size_t), 1, file);
    fwrite(str.c_str(), str.length(), 1, file);
}

void List::Deserialize(FILE *file) {
    if (!file) return;

    clear();

    fread(&count, sizeof(int), 1, file);

    if (count != 0) {
        std::unordered_map<int, ListNode*> nodesMap;
        int index = 0;
        while (index != count) {
            nodesMap[index] = new ListNode();
            ++index;
        }

        index = 0;
        while (index != count) {
            auto node = nodesMap[index];
            deserializeNode(node, nodesMap, file);
            ++index;
        }

        head = nodesMap[0];
        tail = nodesMap[count - 1];
    }
}

void List::deserializeNode(ListNode *node,
                           const std::unordered_map<int, ListNode*> &nodesMap,
                           FILE *file) {
    auto parseNode = [&nodesMap, &file]() {
        int index;
        fread(&index, sizeof(int), 1, file);

        ListNode *node = nullptr;
        auto it = nodesMap.find(index);
        if (it != nodesMap.end()) {
            node = it->second;
        }

        return node;
    };

    node->prev = parseNode();
    node->next = parseNode();
    node->rand = parseNode();

    size_t dataSize;
    fread(&dataSize, sizeof(size_t), 1, file);

    char str[dataSize];
    fread(str, dataSize, 1, file);
    node->data = std::move(std::string(str));
}

std::ostream& operator<<(std::ostream& os, const List& dt) {
    ListNode *tmp = dt.head;
    while (tmp) {
        os << tmp->data;
        if (tmp->rand) {
            os << '(' << tmp->rand->data << ')';
        }
        tmp = tmp->next;
        if (tmp) {
            os << ',';
        }
    }
    os << '\n';
    return os;
}

int main() {
    List myList;

    myList.addNode("Test1");
    myList.addNode("Test2", myList[0]);
    myList.addNode("Test3", myList[1]);
    myList.addNode("Test4");
    myList.addNode("Test5", myList[3]);
    myList.addNode("Test6");
    std::cout << "1) Initial state:\t" << myList;

    // Saving to file
    FILE *file = fopen("./out", "wb");

    if (file) {
        myList.Serialize(file);
        fclose(file);
    }

    // Clearing list
    myList.clear();
    std::cout << "2) List has been cleared:\t" << myList;

    file = fopen("./out", "rb");

    // Loading list data from file
    if (file) {
        myList.Deserialize(file);
        fclose(file);
    }

    std::cout << "3) Deserialized list:\t" << myList;

    // Trying to add some nodes
    myList.addNode("Seventh", myList[0]);
    myList.addNode("Eight", myList[6]);

    std::cout << "4) Added two nodes:\t"<< myList;

    return 0;
}
