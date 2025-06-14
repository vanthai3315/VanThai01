#include "KeyValueGenerator.h"

using namespace std;

// Hàm sinh số nguyên ngẫu nhiên trong khoảng [minVal, maxVal]
int randomInt(int minVal, int maxVal)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);
    return dist(gen);
}

// Sinh key random gồm các ký tự chữ cái và số, độ dài key = length
string randomKey(int length)
{
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string key;
    for (int i = 0; i < length; i++)
    {
        key += chars[rand() % chars.size()];
    }
    return key;
}

// 1. Sinh dữ liệu random keys
vector<pair<string, int>> generateRandomKeys(int n, int keyLength)
{
    vector<pair<string, int>> data;
    for (int i = 0; i < n; i++)
    {
        string key = randomKey(keyLength);
        int value = randomInt(0, 1000);
        data.push_back({ key, value });
    }
    return data;
}


// 2. Sinh dữ liệu sequential keys: "key1", "key2", ...
vector<pair<string, int>> generateSequentialKeys(int n)
{
    vector<pair<string, int>> data;
    for (int i = 1; i <= n; i++)
    {
        string key = "key" + to_string(i);
        int value = randomInt(0, 1000);
        data.push_back({ key, value });
    }
    return data;
}

// 3. Sinh dữ liệu clustered keys: nhiều key cùng prefix, ví dụ prefix + số thứ tự
vector<pair<string, int>> generateClusteredKeys(int n, int clusterSize, const string& prefix)
{
    vector<pair<string, int>> data;
    int clusters = n / clusterSize;
    if (n % clusterSize != 0) clusters++;

    for (int c = 0; c < clusters; c++)
    {
        for (int i = 0; i < clusterSize && (c * clusterSize + i) < n; i++)
        {
            // key dạng: prefix + cluster number + "_" + index in cluster
            string key = prefix + to_string(c) + "_" + to_string(i);
            int value = randomInt(0, 1000);
            data.push_back({ key, value });
        }
    }
    return data;
}