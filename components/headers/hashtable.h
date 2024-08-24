#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

class HashTable
{
public:
    HashTable(int size = 100);
    ~HashTable();

    void addText(const std::string &text);
    int countWord(const std::string &word);
    void updateWord(const std::string &word, int newCount);
    void removeWord(const std::string &word);
    bool containsWord(const std::string &word);
    void printTable() const;

private:
    int hashFunction(const std::string &word) const;
    std::vector<std::list<std::pair<std::string, int>>> table;
    int tableSize;
};

#endif // HASHTABLE_H