#pragma once
#include "Standard_Library.h"

using namespace std;

// Hàm sinh số nguyên ngẫu nhiên trong khoảng [minVal, maxVal]
int randomInt(int minVal, int maxVal);

// Sinh key random gồm các ký tự chữ cái và số, độ dài key = length
string randomKey(int length);

// 1. Sinh dữ liệu random keys
vector<pair<string, int>> generateRandomKeys(int n, int keyLength);

// 2. Sinh dữ liệu sequential keys: "key1", "key2", ...
vector<pair<string, int>> generateSequentialKeys(int n);

// 3. Sinh dữ liệu clustered keys: nhiều key cùng prefix, ví dụ prefix + số thứ tự
vector<pair<string, int>> generateClusteredKeys(int n, int clusterSize, const string& prefix);
