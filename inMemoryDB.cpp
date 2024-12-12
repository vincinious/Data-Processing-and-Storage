#include "inMemoryDB.h"

using namespace std;

int inMemoryDB::get(const string& key) 
{
    /* Check if the key exists in the transaction data */
    if (transactionActive && transactionData.find(key) != transactionData.end())
       { return transactionData[key]; }
  
    /* Check the main database if not in the transaction data */
    if (database.find(key) != database.end()) 
       { return database[key]; }

    /* If key is not found */
    throw runtime_error("Key does not exist in the Database");
}

void inMemoryDB::put(const string& key, int val) 
{
    /* Check if transaction is active. If not throw error */
    if (!transactionActive) 
       { throw runtime_error("No currently active transaction."); }

    /* Insert a key and value or update the existing */
    transactionData[key] = val;
}

void inMemoryDB::begin_transaction()
{
    /* Check if transaction is active. If yes, throw error */
    if (transactionActive)
    { throw runtime_error("A transaction is already in progress."); }

    /* Add current transaction to the stack */
    transactionStack.push(transactionData); 

    /* Change active status of transaction */
    transactionActive = true;
}

void inMemoryDB::commit()
{
    /* Check if transaction is active. If not throw error */
    if (!transactionActive)
    { throw runtime_error("No active transaction."); }

    /* Update the keys and values to the main database */ 
    for (const auto& [key, val] : transactionData) 
       { database[key] = val; }

    /* Clear and remove the transaction data */
    transactionData.clear(); 
    transactionStack.pop();
    transactionActive = false;
}

void inMemoryDB::rollback() 
{
    /* Check if transaction is active. If not throw error */
    if (!transactionActive)
       { throw runtime_error("No active transaction to rollback."); }

    /* Restore the transaction state from the stack and remove it */
    transactionData = transactionStack.top(); 
    transactionStack.pop();
    transactionActive = false;
}
