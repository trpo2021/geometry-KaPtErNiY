#define CATCH_CONFIG_MAIN
#include "../thirdparty/catch.hpp"
#include <iostream>
#include <libcalc/calc.h>
#include <libin/in.h>
#include <string>
#include <vector>

TEST_CASE("Input functions", "")
{
    SECTION("object name")
    {
        std::string a = "triangle((0 0, 0 5, 5 5, 0 0))";
        std::string b = "circle(0 0, 5)";
        std::string c = "poligon((0 0, 0 5, 5 5, 5 0, 0 0))";
        CHECK(takeObjectName(a) == "triangle");
        CHECK(takeObjectName(b) == "circle");
        CHECK(takeObjectName(c) == "poligon");
    }

    SECTION("points string")
    {
        std::string a = "triangle((0 0, 0 5, 5 5, 0 0))";
        std::string b = "circle(0 0, 5)";
        std::string c = "poligon((0 0, 0 5, 5 5, 5 0, 0 0))";
        CHECK(takePointsString("triangle", a) == "0 0, 0 5, 5 5, 0 0");
        CHECK(takePointsString("circle", b) == "0 0, 5");
        CHECK(takePointsString("poligon", c) == "0 0, 0 5, 5 5, 5 0, 0 0");
    }

    SECTION("points vector")
    {
        std::string a = "0 0, 0 5, 5 5, 0 0";
        std::string b = "0 0, 5";
        std::string c = "0 0, 0 5, 5 5, 5 0, 0 0";
        std::vector<double> ar{0, 0, 0, 5, 5, 5, 0, 0};
        std::vector<double> br{0, 0, 5};
        std::vector<double> cr{0, 0, 0, 5, 5, 5, 5, 0, 0, 0};
        CHECK(takePoints(a) == ar);
        CHECK(takePoints(b) == br);
        CHECK(takePoints(c) == cr);
    }
}

TEST_CASE("Perimetr and square", "")
{
    SECTION("perim")
    {
        std::vector<double> a{0, 0, 3, 4, 6, 0, 0, 0};
        std::vector<double> b{0, 0, 5};
        std::vector<double> c{0, 0, 3, 4, 6, 0, 0, 0, 0, 0};
        CHECK(takePerimetr("triangle", a) == Approx(16));
        CHECK(takePerimetr("circle", b) == Approx(31.4));
        CHECK(takePerimetr("poligon", c) == 16);
    }
    SECTION("square")
    {
        std::vector<double> a{0, 0, 3, 4, 6, 0, 0, 0};
        std::vector<double> b{0, 0, 7};
        std::vector<double> c{0, 0, 3, 4, 6, 0, 0, 0, 0, 0};
        CHECK(takeSquare("triangle", a) == 12);
        CHECK(takeSquare("circle", b) == Approx(153.86));
        CHECK(takeSquare("poligon", c) == 12);
    }
    system("PAUSE");
}

TEST_CASE("Collisions", "")
{
    SECTION("two sections")
    {
        std::vector<double> a{0, 0, 5, 5};
        std::vector<double> b{0, 5, 5, 0};
        std::vector<double> c{3, 0, 7, 4};
        std::vector<double> d{1, 3, 7, 3};
        CHECK(isCollisionSections(
                      a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3])
              == true);
        CHECK(isCollisionSections(
                      a[0], a[1], a[2], a[3], c[0], c[1], c[2], c[3])
              == false);
        CHECK(isCollisionSections(
                      a[0], a[1], a[2], a[3], d[0], d[1], d[2], d[3])
              == true);
        CHECK(isCollisionSections(
                      b[0], b[1], b[2], b[3], b[0], d[1], d[2], d[3])
              == true);
        CHECK(isCollisionSections(
                      c[0], c[1], c[2], c[3], d[0], d[1], d[2], d[3])
              == true);
        CHECK(isCollisionSections(
                      d[0], d[1], d[2], d[3], c[0], c[1], c[2], c[3])
              == true);
    }
    SECTION("two circles")
    {
        std::vector<double> a{0, 0, 3};
        std::vector<double> b{0, 0, 5};
        std::vector<double> c{2, 2, 4};
        CHECK(isCollisionTwoCircles(a, b) == false);
        CHECK(isCollisionTwoCircles(b, c) == true);
        CHECK(isCollisionTwoCircles(a, c) == true);
    }
    SECTION("two poligones (including triangles)")
    {
        std::vector<double> a{0, 0, 0, 5, 5, 5, 5, 0, 0, 0};
        std::vector<double> b{0, 0, 6, 0, 6, 5, 0, 0};
        std::vector<double> c{10, 10, 12, 10, 13, 11, 12, 13, 10, 13, 10, 10};
        CHECK(isCollisionTwoPoligones(a, b) == true);
        CHECK(isCollisionTwoPoligones(b, c) == false);
        CHECK(isCollisionTwoPoligones(a, c) == false);
        CHECK(isCollisionTwoPoligones(c, a) == false);
    }
    SECTION("circle and poligon")
    {
        std::vector<double> ap{0, 0, 0, 5, 5, 5, 5, 0, 0, 0};
        std::vector<double> bp{0, 0, 0, 4, 4, 4, 4, 0, 0, 0};
        std::vector<double> ac{5, 5, 3};
        std::vector<double> bc{2, 2, 1};
        CHECK(isCollisionCirclePoligon(ap, ac) == true);
        CHECK(isCollisionCirclePoligon(bp, bc) == false);
    }

    system("PAUSE");
}
