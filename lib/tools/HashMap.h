//
// Created by MY Song on 2021/12/25.
//

#ifndef TEST_COMPILER_HASHMAP_H
#define TEST_COMPILER_HASHMAP_H

#include "string"
#include "iostream"

using namespace std;

class HashMap {
private:
    string values[11];
    int mod = 26;
    int size = 11;
public:
    HashMap();

    int hash(string key);

    int insert(string key);

    int get(string key);

    void print();
};

HashMap::HashMap() {
    for (int i = 0; i < size; i++) {
        values[i] = "NULL";
    }
}

int HashMap::hash(string key) {
    int sum = 0;
    for (char c: key) {
        sum += c;
    }
    return ((sum >> 1) % mod % size);
}

int HashMap::insert(string key) {
    int x = hash(key);
    this->values[x] = key;
    return true;
}

int HashMap::get(string key) {
    int x = hash(key);
    return this->values[x] == key;
}

void HashMap::print() {
    int count = 0;
    cout << "===哈希表===" << endl;
    for (int i = 0; i < 11; i++) {
        cout << i << " " << values[i] << endl;
        if (this->values[i] != "NULL") {
            count++;
        }
    }
    cout << "装填因子: " << count * 1.0 / size << endl;
}

#endif //TEST_COMPILER_HASHMAP_H
