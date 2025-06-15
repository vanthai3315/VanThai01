#include "Fibonacci_Hash.h"
#include "Traditional_Hash.h"
#include "KeyValueGenerator.h"

/*
 * Chương trình minh họa cách sử dụng bảng băm (hash table) với cách xử lý đụng độ tuyến tính.
 * Sử dụng hai hàm băm truyền thống và fibonacci hashing để cải thiện đụng độ có thể xảy ra.
 * Các phần tử sẽ được chèn vào bảng băm và sau đó thực hiện tìm kiếm, xóa nếu cần.
 */



void veMenu() {
    cout << "-------------------------Menu------------------------" << endl;
	cout << "1. Print hash table" << endl;
	cout << "2. Input size of hash table" << endl;
	cout << "3. Insert key-value pair or get from file" << endl;
	cout << "4. Search key" << endl;
	cout << "5. Remove key" << endl;
	cout << "6. Load factor" << endl;
	cout << "7. Collision count" << endl;
	cout << "8. Count clusters" << endl;
	cout << "9. Average cluster size" << endl;
	cout << "10. Max cluster size" << endl;
	cout << "11. Memory usage" << endl;
	cout << "12. Average search time for inserted keys" << endl;
	cout << "13. Average remove time for inserted keys" << endl;
	cout << "14. Exit" << endl;
	cout << "-----------------------------------------------------" << endl;
}


int main() {
    int option = 0;
	int size = 0;
    Traditional_Hash tradiHash(0);
    Fibonacci_Hash fiboHash(0);
	vector<pair<string, int>> kv, temp;
	while (true) {
		system("cls");
		veMenu();
		cout << "Please enter your option: ";
		cin >> option;
		switch (option) {
		case 1:
		{
			cout << " ------ Table of Traditional Hash ------ " << endl;
			tradiHash.print();
			cout << " ------ Table of Fibonacci Hash ------ " << endl;
			fiboHash.print();
			system("pause");
			break;
		}
		case 2: {
			cout << "Enter the size of the hash table: ";
			cin >> size;
			// Khởi tạo bảng băm với kích thước cho trước
			tradiHash = Traditional_Hash(size);
			fiboHash = Fibonacci_Hash(size);
			cout << "Hash tables created with size " << size << endl;
			system("pause");
			break;
		}
		case 3: {
			cout << " ------------- menu --------------- " << endl;
			cout << "1. Direct data entry" << endl;
			cout << "2. Get data from file" << endl;
			cout << " ---------------------------------- " << endl;
			cout << "Please enter your option: ";
			int choice;
			cin >> choice;
			switch (choice) {
			    case 1: {
				if (size == 0) {
					cout << "Please create a hash table first!" << endl;
					system("pause");
					break;
				}
				
				cout << "1. Random\n";
				cout << "2. Sequential\n";
				cout << "3. Clustered\n";
				cout << "Choose key type: ";

				cin >> choice;

				cout << "How many key-value pairs do you want to insert? ";
				int n;
				cin >> n;

				switch (choice)
				{
				case 1:
				{
					temp = generateRandomKeys(n, randomInt(1, 20));
					kv.insert(kv.end(), temp.begin(), temp.end());
					break;
				}
				case 2:
				{
					temp = generateSequentialKeys(n, "key");
					kv.insert(kv.end(), temp.begin(), temp.end());
					break;
				}
				case 3:
				{
					temp = generateClusteredKeys(n, 20, "key");
					kv.insert(kv.end(), temp.begin(), temp.end());
					break;
				}
				default:
					break;
				}

				double time1 = measureExecutionTime(&Traditional_Hash::insert_n, &tradiHash, n, temp);
				double time2 = measureExecutionTime(&Fibonacci_Hash::insert_n, &fiboHash, n, temp);

				cout << "Traditional_Hash insertion time for " << n << " key-value pairs: " << time1 << " ms" << endl;
				cout << "Fibonacci_Hash insertion time for " << n << " key-value pairs: " << time2 << " ms" << endl;
				cout << "Inserted " << n << " key-value pairs into both hash tables." << endl;
				system("pause");
				break;
			    }
			    case 2: {
					if (size == 0) {
						cout << "Please create a hash table first!" << endl;
						system("pause");
						break;
					}
					ifstream inFile;
					inFile.open("Data.txt");
					if (!inFile.is_open()) {
						cout << "Error!" << endl;
						break;
					}
					int n;
					inFile >> n;
					for (int i = 0; i < n; i++) {
						string line;
						getline(inFile, line);
						if (line.empty()) {
							i--;
							continue;
						}
						stringstream ss(line);
						string word;
						string key;
						string value = "";
						while (ss >> word) {
							key = value;
							value = word;
						}
						tradiHash.insert(key, stoi(value));
						fiboHash.insert(key, stoi(value));
					}
					cout << "Inserted " << n << " key-value pairs into both hash tables." << endl;
					inFile.close();
					system("pause");
					break;
			    }
			}
			break;
		}
		case 4: {
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}
			string key;
			cout << "Enter the key to search: ";
			cin >> key;
			int value;

			bool found1;
			double time1 = measureExecutionTime(
				[&](const string& k, int& v, bool& f) {
					f = tradiHash.search(k, v);
				},
				key, std::ref(value), std::ref(found1)
			);

			if (found1) {
				cout << "Found key " << key << " with value " << value << " in traditional hash table." << endl;
			}
			else {
				cout << "Key " << key << " not found in traditional hash table." << endl;
			}
			cout << "Traditional_Hash search time: " << time1 << " ms" << endl;

			bool found2;
			double time2 = measureExecutionTime(
				[&](const string& k, int& v, bool& f) {
					f = fiboHash.search(k, v);
				},
				key, std::ref(value), std::ref(found2)
			);

			if (found2) {
				cout << "Found key " << key << " with value " << value << " in fibonacci hash table." << endl;
			}
			else {
				cout << "Key " << key << " not found in fibonacci hash table." << endl;
			}
			cout << "Fibonacci_Hash search time: " << time2 << " ms" << endl;

			system("pause");
			break;
		}

		case 5: {
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}
			string key;
			cout << "Enter the key to remove: ";
			cin >> key;

			bool removed1;
			double time1 = measureExecutionTime(
				[&](const string& k, bool& r) {
					r = tradiHash.remove(k);
				},
				key, std::ref(removed1)
			);

			if (removed1) {
				cout << "Key " << key << " removed from traditional hash table." << endl;
			}
			else {
				cout << "Key " << key << " not found in traditional hash table." << endl;
			}
			cout << "Traditional_Hash remove time: " << time1 << " ms" << endl;

			bool removed2;
			double time2 = measureExecutionTime(
				[&](const string& k, bool& r) {
					r = fiboHash.remove(k);
				},
				key, std::ref(removed2)
			);

			if (removed2) {
				cout << "Key " << key << " removed from fibonacci hash table." << endl;
			}
			else {
				cout << "Key " << key << " not found in fibonacci hash table." << endl;
			}
			cout << "Fibonacci_Hash remove time: " << time2 << " ms" << endl;

			if (removed1 || removed2)
			{
				for (int i = 0; i < kv.size(); )
				{
					if (kv[i].first == key)
					{
						kv.erase(kv.begin() + i); // không tăng i vì phần tử tiếp theo đã dồn về
					}
					else
					{
						i++; // chỉ tăng i nếu không xóa
					}
				}
			}


			system("pause");
			break;
		}
		case 6:
		{
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}


			cout << "Load factor of traditional hash is: " << tradiHash.getLoadFactor() << endl;
			cout << "Load factor of fibonacci hash is: " << fiboHash.getLoadFactor() << endl;
			system("pause");

			break;
		}
		case 7:
		{
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}

			cout << "The number of collisions in traditional Hash is: " << tradiHash.getCollisionCount() << endl;
			cout << "The number of collisions in fibonacci Hash is: " << fiboHash.getCollisionCount() << endl;
			system("pause");
			break;
			
		}

		case 8:
		{
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}

			cout << "Number of clusters in traditional hash: " << tradiHash.countClusters() << endl;
			cout << "Number of clusters in fibonacci hash: " << fiboHash.countClusters() << endl;
			system("pause");
			break;
		}
		case 9:
		{
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}

			cout << "Average cluster size in traditional hash: " << tradiHash.averageClusterSize() << endl;
			cout << "Average cluster size in fibonacci hash: " << fiboHash.averageClusterSize() << endl;
			system("pause");
			break;
		}
		case 10:
		{
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}


			cout << "Max cluster size in traditional hash: " << tradiHash.maxClusterSize() << endl;
			cout << "Max cluster size in fibonacci hash: " << fiboHash.maxClusterSize() << endl;
			system("pause");
			break;
		}
		case 11:
		{
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}

			int memory_tradi = tradiHash.memory();
			int memory_fibo = fiboHash.memory();

			cout << "Memory used by Traditional Hash: " << memory_tradi << " bytes" << endl;
			cout << "Memory used by Fibonacci Hash: " << memory_fibo << " bytes" << endl;

			system("pause");
			break;
		}
		case 12: {
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}
			cout << "Average search time in Traditional Hash: " << tradiHash.averageSearchTime(kv) << " ms" << endl;
			cout << "Average search time in Fibonacci Hash: " << fiboHash.averageSearchTime(kv) << " ms" << endl;
			system("pause");
			break;
		}


		case 13: {
			if (size == 0) {
				cout << "Please create a hash table first!" << endl;
				system("pause");
				break;
			}
			cout << "Average remove time in Traditional Hash: " << tradiHash.averageRemoveTime(kv) << " ms" << endl;
			cout << "Average remove time in Fibonacci Hash: " << fiboHash.averageRemoveTime(kv) << " ms" << endl;
			kv.clear();
			system("pause");
			break;
		}



		case 14: {
			cout << "Exiting program..." << endl;
			return 0;
		}
		}
	}
    return 0;
}