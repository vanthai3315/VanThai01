#include "Traditional_Hash.h"
#include <cmath>  // Để dùng log2

// Hàm tạo: khởi tạo bảng băm với kích thước cho trước
Traditional_Hash::Traditional_Hash(int tableSize) : size(tableSize), initialSize(tableSize) {
    table.resize(size);  // Cấp phát bảng với số ô bằng size
}

// Constructor mặc định của Entry
Traditional_Hash::Entry::Entry() : key(""), value(0), isOccupied(false), isDeleted(false) {}

// Hàm băm đơn giản: tính tổng ASCII các ký tự trong chuỗi rồi mod với kích thước bảng
int Traditional_Hash::hashFunction(const string& key) {
    int sum = 0;
    for (char c : key) {
        sum += static_cast<int>(c);
    }
    if ((size & (size - 1)) == 0) return sum & (size - 1);
    else return sum % size;
}

// Hàm chèn phần tử vào bảng băm
bool Traditional_Hash::insert(const string& key, int value) {
    if (getLoadFactor() >= 0.7) // Nếu vượt qua ngưỡng cho phép thì phải tăng kích thước của bảng băm
    {
        rehash_insert(); // Tăng kích thước của bảng băm
    }

    int baseIndex = hashFunction(key);
    int i = 0;

    // Tìm vị trí trống (linear probing)
    while (i < size) {
        int index = (baseIndex + i) % size;
        if (!table[index].isOccupied) {
            // Ghi đè vào vị trí trống
            table[index].key = key;
            table[index].value = value;
            table[index].isOccupied = true;
            table[index].isDeleted = false;
            return true;
        }
        else if (table[index].key == key) {
            // Nếu khóa đã tồn tại, cập nhật giá trị
            table[index].value = value;
            return true;
        }
        // Bị va chạm, phải dò tiếp
        collisionCount++;

        i++;
    }

    return false; // Bảng đầy
}

// Tìm kiếm một khóa và gán giá trị nếu tìm thấy
bool Traditional_Hash::search(const string& key, int& value) {
    int baseIndex = hashFunction(key);
    int i = 0;

    while (i < size) {
        int index = (baseIndex + i) % size;

        if (table[index].isOccupied && table[index].key == key) {
            value = table[index].value;
            return true;
        }
        else if (!table[index].isOccupied && !table[index].isDeleted) {
            // Nếu gặp vị trí chưa từng được ghi, dừng tìm kiếm
            return false;
        }
        i++;
    }

    return false;
}

float Traditional_Hash::getLoadFactor() {
    int occupiedCount = 0;
    for (const auto& entry : table) {
        if (entry.isOccupied) {
            occupiedCount++;

        }
    }
    return static_cast <float>(occupiedCount) / size;
}

// Xóa phần tử khỏi bảng băm
bool Traditional_Hash::remove(const string& key) {
    int baseIndex = hashFunction(key);
    int i = 0;

    while (i < size) {
        int index = (baseIndex + i) % size;

        if (table[index].isOccupied && table[index].key == key) {
            // Đánh dấu là đã xóa nhưng không giải phóng để tránh phá vỡ chuỗi probing
            table[index].isOccupied = false;
            table[index].isDeleted = true;
            return true;
        }
        else if (!table[index].isOccupied && !table[index].isDeleted) {
            // Nếu gặp ô chưa từng được ghi, dừng
            return false;
        }

        i++;
    }
    if (getLoadFactor() <= 0.3 && size > initialSize) {
        rehash_remove();
    }
    return false;
}

// Mở rộng bảng băm khi bảng đầy
void Traditional_Hash::rehash_insert()
{
    int oldSize = size; // Lưu kích thước bảng băm cũ
    size *= 2;          // Tăng gấp đôi kích thước bảng băm
    vector<Entry> oldTable = table; // Sao chép bảng băm cũ

    table.clear();      // Xóa nội dung bảng hiện tại
    table.resize(size); // Tạo bảng mới với kích thước mới

    for (Entry entry : oldTable) {
        if (entry.isOccupied) {
            insert(entry.key, entry.value); // Thêm lại các phần tử vào bảng mới
        }
    }
}


void Traditional_Hash::rehash_remove() {
    int oldSize = size; // Lưu kích thước bảng băm cũ
    size /= 2;          // Giảm một nửa kích thước bảng băm
    vector<Entry> oldTable = table; // Sao chép bảng băm cũ

    table.clear();      // Xóa nội dung bảng hiện tại
    table.resize(size); // Tạo bảng mới với kích thước mới

    for (Entry entry : oldTable) {
        if (entry.isOccupied) {
            insert(entry.key, entry.value); // Thêm lại các phần tử vào bảng mới
        }
    }
}

// In nội dung bảng băm ra màn hình
void Traditional_Hash::print() {
    if (table.size() == 0) {
		std::cout << "Hash table is empty." << std::endl;
		return;
	}
    for (int i = 0; i < size; i++) {
        if (table[i].isOccupied) {
            std::cout << i << ": " << table[i].key << " -> " << table[i].value << std::endl;
        }
        else {
            std::cout << i << ": Empty" << std::endl;
        }
    }
}

// Hàm chèn n cặp key value vào bảng băm
void Traditional_Hash::insert_n(int n, vector <pair<string, int>> kv)
{
    for (int i = 0; i < n; i++)
    {
        // Chèn vào bảng băm
        insert(kv[i].first, kv[i].second);
    }
}

// Hàm đếm số lần va chạm
int Traditional_Hash::getCollisionCount()
{
    return collisionCount;
}


// Đếm số cụm trong bảng băm
int Traditional_Hash::countClusters()
{
    int count = 0;
    bool inCluster = false;

    for (int i = 0; i < size; i++)
    {
        if (table[i].isOccupied)
        {
            if (!inCluster)
            {
                count++;
                inCluster = true;
            }
        }
        else
        {
            inCluster = false;
        }
    }

    return count;
}

// Tính kích thước cụm trung bình
double Traditional_Hash::averageClusterSize()
{
    int clusterCount = 0, clusterSum = 0, current = 0;
    bool inCluster = false;

    for (int i = 0; i < size; i++)
    {
        if (table[i].isOccupied)
        {
            if (!inCluster)
            {
                inCluster = true;
                current = 1;
                clusterCount++;
            }
            else
            {
                current++;
            }
        }
        else if (inCluster)
        {
            clusterSum += current;
            inCluster = false;
        }
    }

    // Trường hợp kết thúc bảng mà vẫn còn cluster chưa tính
    if (inCluster)
    {
        clusterSum += current;
    }

    if (clusterCount == 0) return 0.0;

    return static_cast<double>(clusterSum) / clusterCount;
}

// Tìm kích thước cụm lớn nhất
int Traditional_Hash::maxClusterSize()
{
    int maxSize = 0, current = 0;

    for (int i = 0; i < size; i++)
    {
        if (table[i].isOccupied)
        {
            current++;
            if (current > maxSize)
                maxSize = current;
        }
        else
        {
            current = 0;
        }
    }

    return maxSize;
}

// Tính bộ nhớ đã sử dụng của bảng băm
int Traditional_Hash::memory()
{
    return size * sizeof Entry;
}

double Traditional_Hash::averageSearchTime(const std::vector<std::pair<std::string, int>>& kv)
{
    int value;
    bool found;
    double totalTime = 0.0;

    for (const auto& pair : kv)
    {
        const std::string& key = pair.first;

        totalTime += measureExecutionTime([&](const std::string& k, int& v, bool& f)
            {
                f = this->search(k, v);
            }, key, std::ref(value), std::ref(found));
    }
    return totalTime / kv.size();
}

double Traditional_Hash::averageRemoveTime(const std::vector<std::pair<std::string, int>>& kv)
{
    bool removed;
    double totalTime = 0.0;

    for (const auto& pair : kv)
    {
        const std::string& key = pair.first;

        totalTime += measureExecutionTime([&](const std::string& k, bool& r)
            {
                r = this->remove(k);
            }, key, std::ref(removed));
    }
    return totalTime / kv.size();
}
