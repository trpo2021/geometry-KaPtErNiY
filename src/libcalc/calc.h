#pragma once
#pragma once

#include <geometry/struct.h>
#include <string>
#include <vector>

double takePerimetr(std::string ObjectName, std::vector<double> points);
double takeSquare(std::string ObjectName, std::vector<double> points);
void calcCollision(std::vector<object>& objects);
bool isCollisionSections(
        double start1x,
        double start1y,
        double end1x,
        double end1y,
        double start2x,
        double start2y,
        double end2x,
        double end2y);
bool isCollisionTwoCircles(
        std::vector<double> circle1, std::vector<double> circle2);
bool isCollisionCirclePoligon(
        std::vector<double> poligon, std::vector<double> circle);
bool isCollisionTwoPoligones(
        std::vector<double> poligon1, std::vector<double> poligon2);
