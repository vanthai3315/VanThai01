#pragma once
#include "Standard_Library.h"
#include "measureExecutionTime.h"

using namespace std;

/*
 * Cài đặt bảng băm sử dụng kỹ thuật Linear Probing (thăm dò tuyến tính) để giải quyết xung đột.
 * Sử dụng hàm băng truyền thống để phân bổ các phần tử vào bảng băm.
 */

class Traditional_Hash {
private:
    /*
     * Cấu trúc đại diện cho một entry trong bảng băm.
     * Bao gồm key, value, và trạng thái của ô (đã dùng hay bị xóa hay chưa).
     */
    struct Entry {
        string key;       // Khóa
        int value;        // Giá trị
        bool isOccupied;  // Cờ đánh dấu đã được sử dụng
        bool isDeleted;   // Cờ đánh dấu đã bị xóa (dùng trong xóa mềm)

        Entry();          // Hàm khởi tạo mặc định
    };

    vector<Entry> table;  // Bảng băm chính
    int size;             // Kích thước bảng băm

    int initialSize; // Kích thước ban đầu của bảng băm

    // Hàm băm truyền thống
    int hashFunction(const string& key);

    int collisionCount = 0; // biến đếm va chạm

public:
    // Khởi tạo bảng băm với kích thước cho trước
    Traditional_Hash(int tableSize);

    // Thêm hoặc cập nhật giá trị theo key
    bool insert(const string& key, int value);

    // Tìm kiếm key, lưu kết quả vào biến value nếu tìm thấy
    bool search(const string& key, int& value);

    // Hàm tính trọng tải của bảng băm
    float getLoadFactor();

    // Xóa key khỏi bảng băm
    bool remove(const string& key);

    // Mở rộng bảng băm 
    void rehash_insert();

    // Thu hẹp bảng băm
    void rehash_remove();

    // In toàn bộ nội dung bảng băm
    void print();

    // Hàm chèn n cặp key value vào bảng băm
    void insert_n(int n, vector <pair<string, int>> kv);

    // Số lần va chạm trong bảng băm
    int getCollisionCount();

    // Đếm số cụm trong bảng băm
    int countClusters();

    // Tính kích thước cụm trung bình
    double averageClusterSize();

    // Tìm kích thước cụm lớn nhất
    int maxClusterSize();

    // Tính bộ nhớ đã sử dụng của bảng băm
    int memory();

    // Tính thời gian tìm kiếm trung bình của 1 key
    double averageSearchTime(const vector<pair<string, int>>& kv);

    // Tính thời gian xóa trung bình của 1 key
    double averageRemoveTime(const vector<pair<string, int>>& kv);
};