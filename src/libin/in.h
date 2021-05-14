#pragma once

#include <string>
#include <vector>

bool checkInput(std::string str);
std::string takeObjectName(std::string str);
std::string takePointsString(std::string figureName, std::string str);
std::vector<double> takePoints(std::string str);
