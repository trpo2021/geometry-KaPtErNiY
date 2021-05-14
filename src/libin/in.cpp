#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define EXPECTEDOBJECTNAME 1
#define EXPECTEDFIRSTBRACKET 2
#define EXPECTEDSECONDBRACKET 3
#define UNEXPECTEDTOKEN 4
#define EXPECTEDCOMMA 5
#define EXPECTEDSPACE 6

vector<string> split(string str, string sep)
{
    vector<string> res;
    string tmp;
    int pos = 0;
    while (pos + 1) {
        pos = str.find(sep);
        if (pos + 1) {
            tmp.append(str, 0, pos);
        } else {
            tmp = str;
        }
        res.push_back(tmp);
        str.erase(0, pos + sep.length());
        tmp = "";
    }
    return res;
}

void error(int code, int column)
{
    for (int i = 0; i < column; i++) {
        cout << " ";
    }
    cout << "^" << endl;
    cout << "Error at column " << column << ": ";
    switch (code) {
    case EXPECTEDOBJECTNAME:
        cout << "expected 'triangle' or 'circle' or 'poligon'";
        break;
    case EXPECTEDFIRSTBRACKET:
        cout << "expected '('";
        break;
    case EXPECTEDSECONDBRACKET:
        cout << "expected ')'";
        break;
    case UNEXPECTEDTOKEN:
        cout << "unexpected token";
        break;
    case EXPECTEDCOMMA:
        cout << "expected ','";
        break;
    case EXPECTEDSPACE:
        cout << "expected ' '";
        break;
    }
    cout << endl << endl;
}

bool isObjectName(string str)
{
    if (!(str == "triangle" || str == "circle" || str == "poligon")) {
        error(EXPECTEDOBJECTNAME, 0);
        return false;
    }
    return true;
}

string takeObjectName(string str)
{
    string ObjectName;
    int pos = str.find('(');
    if (pos + 1) {
        ObjectName.append(str, 0, pos);
        if (isObjectName(ObjectName)) {
            return ObjectName;
        } else {
            return "";
        }
    } else {
        error(EXPECTEDFIRSTBRACKET, str.length());
        return "";
    }
}

bool checkBrackets(string ObjectName, string str)
{
    string bracketFirst = "((", bracketSecond = "))";
    if (ObjectName == "circle") {
        bracketFirst = "(";
        bracketSecond = ")";
    }

    if (str.find(bracketFirst) + 1) {
        if (str.find(bracketSecond) + 1) {
            return 1;
        } else {
            error(EXPECTEDSECONDBRACKET, str.length());
            return 0;
        }
    } else {
        error(EXPECTEDFIRSTBRACKET, ObjectName.length());
        return 0;
    }
}

bool checkExcess(string str)
{
    int pos = str.find(")") + 1;
    int len = str.length();
    while (pos < len) {
        if (str[pos] != ' ' && str[pos] != ')') {
            error(UNEXPECTEDTOKEN, pos);
            return 0;
        }
        pos++;
    }
    return 1;
}

bool checkAlternation(string ObjectName, string str)
{
    int len = str.length();
    bool nowNumber = false;
    bool nowPair = false;
    int brackets;
    if (ObjectName == "circle") {
        brackets = 1;
    } else {
        brackets = 2;
    }

    for (int i = 0; i < len; i++) {
        if (str[i] != ',' && str[i] != ' ' && !nowNumber) {
            nowNumber = true;
        }
        if (str[i] == ' ' && nowNumber) {
            if (!nowPair) {
                nowNumber = false;
                nowPair = true;
            } else {
                error(EXPECTEDCOMMA, ObjectName.length() + brackets + i);
                return 0;
            }
        }
        if (str[i] == ',' && nowNumber) {
            if (nowPair) {
                nowNumber = false;
                nowPair = false;
            } else {
                error(EXPECTEDSPACE, ObjectName.length() + brackets + i);
                return 0;
            }
        }
    }
    return 1;
}

bool checkValid(string ObjectName, string points)
{
    bool valid;
    set<char> validChars{
            '0',
            '1',
            '2',
            '3',
            '4',
            '5',
            '6',
            '7',
            '8',
            '9',
            '(',
            ')',
            ' ',
            ',',
            '.',
            '-'};
    int len = points.length();
    for (int i = 0; i < len; i++) {
        valid = false;
        for (const auto& item : validChars) {
            if (points[i] == item) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            if (ObjectName == "circle") {
                error(UNEXPECTEDTOKEN, ObjectName.length() + i + 1);
            } else {
                error(UNEXPECTEDTOKEN, ObjectName.length() + i + 2);
            }
            return 0;
        }
    }
    return 1;
}

string takePointsString(string ObjectName, string str)
{
    string points;
    if (ObjectName == "circle") {
        points.append(
                str,
                ObjectName.length() + 1,
                str.find(")") - ObjectName.length() - 1);
    } else {
        points.append(
                str,
                ObjectName.length() + 2,
                str.find("))") - ObjectName.length() - 2);
    }

    return points;
}

vector<double> takePoints(string str)
{
    vector<double> points;

    int len = str.length();
    int pos = -1;
    string tmp;

    for (int i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != ',' && pos == -1) {
            pos = i;
        }
        if ((str[i] == ' ' || str[i] == ',') && pos != -1) {
            tmp.append(str, pos, i - pos);
            points.push_back(stod(tmp));
            tmp = "";
            pos = -1;
        }
    }

    tmp.append(str, pos, len);
    points.push_back(stod(tmp));

    return points;
}

bool checkPoints(string ObjectName, string str)
{
    string points = takePointsString(ObjectName, str);

    if (checkValid(ObjectName, points)
        && checkAlternation(ObjectName, points)) {
        return 1;
    }
    return 0;
}

bool checkInput(string str)
{
    int len = str.length();
    for (int i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }

    string ObjectName = takeObjectName(str);

    if (ObjectName != "") {
        if (checkBrackets(ObjectName, str)) {
            if (checkExcess(str)) {
                if (checkPoints(ObjectName, str)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
