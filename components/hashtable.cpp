#include "headers/hashtable.h"

HashTable::HashTable(int size) : tableSize(size)
{
    table.resize(tableSize);
}

HashTable::~HashTable() {}

int HashTable::hashFunction(const std::string &word) const
{
    unsigned long hash = 5381;
    for (char c : word)
    {
        hash = ((hash << 5) + hash) + static_cast<unsigned long>(c);
    }
    return hash % tableSize;
}

void HashTable::addText(const std::string &text)
{
    std::stringstream ss(text);
    std::string word;
    while (ss >> word)
    {
        int index = hashFunction(word);
        bool found = false;
        for (auto &pair : table[index])
        {
            if (pair.first == word)
            {
                pair.second++;
                found = true;
                break;
            }
        }
        if (!found)
        {
            table[index].emplace_back(word, 1);
        }
    }
    std::cout << "Texto adicionado. Contagem de palavras atualizada." << std::endl;
}

int HashTable::countWord(const std::string &word)
{
    int index = hashFunction(word);
    for (const auto &pair : table[index])
    {
        if (pair.first == word)
        {
            return pair.second;
        }
    }
    std::cout << "A palavra \"" << word << "\" não foi encontrada." << std::endl;
    return 0;
}

void HashTable::updateWord(const std::string &word, int newCount)
{
    int index = hashFunction(word);
    for (auto &pair : table[index])
    {
        if (pair.first == word)
        {
            pair.second = newCount;
            std::cout << "Contagem da palavra \"" << word << "\" atualizada para " << newCount << "." << std::endl;
            return;
        }
    }
    std::cout << "A palavra \"" << word << "\" não foi encontrada." << std::endl;
}

void HashTable::removeWord(const std::string &word)
{
    int index = hashFunction(word);
    for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
        if (it->first == word)
        {
            table[index].erase(it);
            // std::cout << "Palavra \"" << word << "\" removida." << std::endl;
            return;
        }
    }
    // std::cout << "A palavra \"" << word << "\" não foi encontrada." << std::endl;
}

bool HashTable::containsWord(const std::string &word)
{
    int index = hashFunction(word);
    for (const auto &pair : table[index])
    {
        if (pair.first == word)
        {
            // std::cout << "A palavra \"" << word << "\" está presente e ocorre " << pair.second << " vez(es)." << std::endl;
            return true;
        }
    }
    // std::cout << "A palavra \"" << word << "\" não foi encontrada." << std::endl;
    return false;
}

void HashTable::printTable() const
{
    for (int i = 0; i < tableSize; ++i)
    {
        if (!table[i].empty())
        {
            std::cout << "Índice " << i << ": ";
            for (const auto &pair : table[i])
            {
                std::cout << "(\"" << pair.first << "\", " << pair.second << ") -> ";
            }
            std::cout << "NULL" << std::endl;
        }
    }
}
