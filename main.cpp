#include "inMemoryDB.h"
#include <iostream>

using namespace std;

int main() 
{
    InMemoryDB db;

    try 
    {
        /* Try to get value of key A from the main db */
        cout << "Initial get(\"A\"): " << (db.get("A").has_value() ? to_string(db.get("A").value()) : "null") << '\n';

        /* Start a new transaction, add A, 5 as key and value, and attempt to get the value in the transaction */
        db.begin_transaction();
        db.put("A", 5);
        cout << "After put(\"A\", 5), get(\"A\"): " << (db.get("A").has_value() ? to_string(db.get("A").value()) : "null") << '\n';

        /* Update the key to A, 6 within the transaction*/ 
        db.put("A", 6);
        db.commit();
        cout << "After commit(), get(\"A\"): " << (db.get("A").has_value() ? to_string(db.get("A").value()) : "null") << '\n';

        /* Start a new transaction, add A, 6 as key and value, and attempt to get the value in the transaction */
        db.begin_transaction();
        db.put("B", 10);
        db.rollback();
        cout << "After rollback(), get(\"B\"): " << (db.get("B").has_value() ? to_string(db.get("B").value()) : "null") << '\n';

    } 
    catch (const exception& e)
    /* Display any errors */
    { cerr << "Exception: " << e.what() << '\n'; }

    return 0;
}
