#include <iostream>
#include <string>
#include <vector>

#include <geometry/struct.h>
#include <libcalc/calc.h>
#include <libin/in.h>

using namespace std;

void addNewObject(vector<object>& objects, string str)
{
    object tmp;

    tmp.id = objects.size() + 1;
    tmp.name = takeObjectName(str);

    string points = takePointsString(tmp.name, str);
    tmp.points = takePoints(points);

    tmp.perimetr = takePerimetr(tmp.name, tmp.points);
    tmp.square = takeSquare(tmp.name, tmp.points);

    objects.push_back(tmp);
}

void printObjects(vector<object> objects)
{
    for (int i = 0; i < (int)objects.size(); i++) {
        cout << objects[i].id << ". " << objects[i].name << ": ";
        for (int j = 0; j < (int)objects[i].points.size(); j++) {
            cout << objects[i].points[j] << " ";
        }
        cout << endl;
        cout << "perimetr = " << objects[i].perimetr << endl;
        cout << "square = " << objects[i].square << endl;
        for (int j = 0; j < (int)objects[i].collision.size(); j++) {
            cout << "\t" << objects[i].collision[j]->id << ". "
                 << objects[i].collision[j]->name << endl;
        }
        cout << endl;
    }
}
