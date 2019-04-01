#include "trie.h"
#include "dict.h"

#include <iostream>

enum Type
{
    TRIE,
    DICT
};

Type parseType(std::string str)
{
    if (str == "TRIE")
        return TRIE;
    if (str == "DICT")
        return DICT;
    return Type();
}

enum Operation
{
    INSERT,
    SEARCH
};

Operation parseOperation(std::string str)
{
    if (str == "INSERT")
        return INSERT;
    if (str == "SEARCH")
        return SEARCH;
    return Operation();
}

int main()
{
    std::string type;
    std::cin >> type;

    Trie *trie = new Trie();
    Dictionary *dict = new Dictionary();

    while (std::cin)
    {
        std::string operation, value;
        std::cin >> operation >> value;

        switch (parseType(type))
        {
        case TRIE:
            switch (parseOperation(operation))
            {
            case INSERT:
                trie->insert(value);
                break;
            case SEARCH:
                std::cout << trie->search(value) << std::endl;
                break;
            }
            break;
        case DICT:
            switch (parseOperation(operation))
            {
            case INSERT:
                dict->insert(value);
                break;
            case SEARCH:
                std::cout << dict->search(value) << std::endl;
                break;
            }
            break;
        }
    }

    free(trie);
    free(dict);

    return 0;
}
