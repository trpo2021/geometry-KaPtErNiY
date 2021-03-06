#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void error();



vector<float> createTriangle(string& str)
{
    string s = str;

    vector<float> data;
    vector<float> empty;

    int begin = s.find("((");
    int end = s.find("))");

    if (end == -1) {
        error();
        return empty;
    }

    string dataString = "";
    dataString.append(s, begin, s.length()-begin);

    if ((dataString[0] == '(') && (dataString[1] == '(')) {
        dataString.erase(0, 2);
    } else {
        error();
        return data;
    }
    int count = 0, column = 10;
    for (int i = 0; i < (int)dataString.length(); i++) {
        string elem = "";
        if (count < 7) {
            if (((dataString[i] < 48) || (dataString[i] > 57))
                && (dataString[i] != 32) && (dataString[i] != 44)
                && (dataString[i] != 46)) {
                error();
                return empty;
            }
            if (dataString[i] == ' ') {
                elem.append(dataString, 0, i);
                data.push_back(stof(elem));
                dataString.erase(0, i + 1);
                i = 0;
                count++;
                column++;
            }
            if (dataString[i] == ',') {
                elem.append(dataString, 0, i);
                data.push_back(stof(elem));
                dataString.erase(0, i + 2);
                i = 0;
                count++;
                column += 2;
            }
        } else if (count == 7) {
            int end = dataString.find("))");
            if (end != -1) {
                elem.append(dataString, 0, end);
                data.push_back(stof(elem));

                dataString.erase(0, end + 2);
                i = 0;
                count += 2;
            } else {
                error();
                return empty;
            }
        } else {
            error();
            return empty;
        }
        column++;
    }

    return data;
}

void error()
{
    cout << "error" << endl;
}


int main()
{
    
    vector<pair<string, vector<float>>> figures;
    string s;
    int count = 1;

    cout << "choose figures" << endl;

    while (getline(cin, s)) {
        if (s == "") {
            break;
        }

        int begin = s.find("(");

        for (int i = 0; i < (int)s.length(); i++) {
            s[i] = tolower(s[i]);
        }

        string figureName = "";
        figureName.append(s, 0, begin);
        
      

        vector<float> figurePoints;

        if (figureName == "triangle") {
            figurePoints = createTriangle(s);
        } else {
            error();
        }

        pair<string, vector<float>> figure;

        if (figurePoints.size() > 0) {
            figure.first = figureName;
            figure.second = figurePoints;
            figures.push_back(figure);
            count++;
        }
    }

    for (int i = 0; i < (int)figures.size(); i++) {
        cout << i + 1 << ". " << figures[i].first << ": ";
        for (int j = 0; j < (int)figures[i].second.size(); j++) {
            cout << figures[i].second[j] << " ";
        }
        cout << endl;
    }
    system("PAUSE");
}
