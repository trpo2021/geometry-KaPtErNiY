#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <geometry/struct.h>
#include <geometry/structFunctions.h>
#include <libcalc/calc.h>
#include <libin/in.h>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Russian");
    vector<object> objects;
    string str;

    cout << "Enter tokens" << endl;

    while (getline(cin, str)) {
        if (str == "") {
            break;
        }

        if (checkInput(str)) {
            addNewObject(objects, str);
        }
    }

    calcCollision(objects);
    printObjects(objects);

    system("PAUSE");

    return 1;
}
