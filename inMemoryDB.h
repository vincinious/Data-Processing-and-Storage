#include <string>
#include <unordered_map>
#include <stack>
#include <stdexcept>

using namespace std;

class inMemoryDB 
{
private:
    unordered_map<string, int> database;
    unordered_map<string, int> transactionData;
    stack<unordered_map<string, int>> transactionStack;
    bool transactionActive = false;

public:
    int get(const string& key);              /* return value associated with the key or null if doesnt exist */
    void put(const string& key, int val);    /* create a new key if it doesnt exist, or update the existing key value */
    void begin_transaction();                /* start a new transaction */
    void commit();                           /* applies changes within the transaction to the main state */
    void rollback();                         /* abort all changes within the transaction and reset */
};


