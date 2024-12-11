#include "InMemoryDB.h"
#include <iostream>

using namespace std;

int main() 
{
    InMemoryDB db;

    try 
    {
        cout << "Initial get(\"A\"): " << (db.get("A").has_value() ? to_string(db.get("A").value()) : "null") << '\n';

        db.begin_transaction();
        db.put("A", 5);
        cout << "After put(\"A\", 5), get(\"A\"): " << (db.get("A").has_value() ? to_string(db.get("A").value()) : "null") << '\n';

        db.put("A", 6);
        db.commit();
        cout << "After commit(), get(\"A\"): " << (db.get("A").has_value() ? to_string(db.get("A").value()) : "null") << '\n';

        db.begin_transaction();
        db.put("B", 10);
        db.rollback();
        cout << "After rollback(), get(\"B\"): " << (db.get("B").has_value() ? to_string(db.get("B").value()) : "null") << '\n';

    } 
    catch (const exception& e)
    { cerr << "Exception: " << e.what() << '\n'; }

    return 0;
}
