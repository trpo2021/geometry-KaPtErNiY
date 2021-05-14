#include <cmath>
#include <geometry/struct.h>
#include <string>
#include <vector>

using namespace std;

const double PI = 3.14;

double takePerimetr(string objectName, vector<double> points)
{
    double perim = 0;
    if (objectName == "circle") {
        perim = 2 * PI * points[2];
    } else {
        for (int i = 0; i < (int)points.size() - 2; i += 2) {
            perim
                    += sqrt(pow(points[i + 2] - points[i], 2)
                            + pow(points[i + 1] - points[i + 3], 2));
        }
    }
    return perim;
}

double takeSquare(string ObjectName, vector<double> points)
{
    double square = 0;
    if (ObjectName == "circle") {
        square = PI * pow(points[2], 2);
    } else {
        for (int i = 0; i < (int)points.size() - 2; i += 2) {
            square += points[i] * points[i + 3];
        }
        for (int i = 0; i < (int)points.size() - 2; i += 2) {
            square -= points[i + 1] * points[i + 2];
        }
        square = abs(square) / 2;
    }
    return square;
}

bool isCollisionSections(
        double start1x,
        double start1y,
        double end1x,
        double end1y,
        double start2x,
        double start2y,
        double end2x,
        double end2y)
{
    double dir1x = end1x - start1x;
    double dir1y = end1y - start1y;
    double dir2x = end2x - start2x;
    double dir2y = end2y - start2y;

    
    float a1 = -dir1y;
    float b1 = +dir1x;
    float d1 = -(a1 * start1x + b1 * start1y);

    float a2 = -dir2y;
    float b2 = +dir2x;
    float d2 = -(a2 * start2x + b2 * start2y);

    
    float seg1_line2_start = a2 * start1x + b2 * start1y + d2;
    float seg1_line2_end = a2 * end1x + b2 * end1y + d2;

    float seg2_line1_start = a1 * start2x + b1 * start2y + d1;
    float seg2_line1_end = a1 * end2x + b1 * end2y + d1;

   
    if (seg1_line2_start * seg1_line2_end >= 0
        || seg2_line1_start * seg2_line1_end >= 0)
        return false;

    return true;
}

bool isCollisionTwoCircles(vector<double> circle1, vector<double> circle2)
{
    double radius1 = circle1[2];
    double radius2 = circle2[2];

    double distanse
            = sqrt(pow((circle1[0] - circle2[0]), 2)
                   + pow((circle1[1] - circle2[1]), 2));

    if ((radius1 + radius2) < distanse) {
        return false;
    }
    if (abs(radius1 - radius2)
        > distanse) { 
        return false;
    }
    return true;
}

bool isCollisionCirclePoligon(vector<double> poligon, vector<double> circle)
{
    bool isPointInside;
    double distance
            = sqrt(pow((poligon[0] - circle[0]), 2)
                   + pow((poligon[1] - circle[1]), 2));
    if (distance < circle[2]) {
        isPointInside = true;
    } else {
        isPointInside = false;
    }
    for (int i = 2; i < (int)poligon.size(); i += 2) {
        distance
                = sqrt(pow((poligon[i] - circle[0]), 2)
                       + pow((poligon[i + 1] - circle[1]), 2));
        if ((distance < circle[2]) != isPointInside) {
            return true;
        }
    }
    return false;
}

bool isCollisionTwoPoligones(
        vector<double> poligon1, vector<double> poligon2)
{
    for (int i = 0; i < (int)poligon1.size() - 3; i += 2) {
        for (int j = 0; j < (int)poligon2.size() - 3; j += 2) {
            if (isCollisionSections(
                        poligon1[i],
                        poligon1[i + 1],
                        poligon1[i + 2],
                        poligon1[i + 3],
                        poligon2[j],
                        poligon2[j + 1],
                        poligon2[j + 2],
                        poligon2[j + 3])) {
                return true;
            }
        }
    }
    return false;
}

void calcCollision(vector<object>& objects)
{
    for (int i = 0; i < (int)objects.size(); i++) {
        for (int j = i + 1; j < (int)objects.size(); j++) {
            if (objects[i].name == "circle") {
                if (objects[j].name == "circle") {
                    if (isCollisionTwoCircles(
                                objects[j].points, objects[i].points)) {
                        objects[j].collision.push_back(&objects[i]);
                        objects[i].collision.push_back(&objects[j]);
                    }
                } else {
                    if (isCollisionCirclePoligon(
                                objects[j].points, objects[i].points)) {
                        objects[j].collision.push_back(&objects[i]);
                        objects[i].collision.push_back(&objects[j]);
                    }
                }
            } else {
                if (objects[j].name == "circle") {
                    if (isCollisionCirclePoligon(
                                objects[i].points, objects[j].points)) {
                        objects[j].collision.push_back(&objects[i]);
                        objects[i].collision.push_back(&objects[j]);
                    }
                } else {
                    if (isCollisionTwoPoligones(
                                objects[j].points, objects[i].points)) {
                        objects[j].collision.push_back(&objects[i]);
                        objects[i].collision.push_back(&objects[j]);
                    }
                }
            }
        }
    }
}
