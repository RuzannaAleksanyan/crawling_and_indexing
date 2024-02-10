// // 1
// #include <iostream>
// #include <vector>

// int binary_search(std::vector<int>& vec, int key, int start, int end) {
//     if (start <= end) {
//         int mid = start + (end - start) / 2;  // Corrected calculation
//         if (vec[mid] == key) {
//             return mid;
//         } else if (vec[mid] > key) {
//             return binary_search(vec, key, start, mid - 1);
//         } else if (vec[mid] < key) {
//             return binary_search(vec, key, mid + 1, end);
//         }
//     }

//     return -1;
// }

// int main() {
//     int key = 89;
//     std::vector<int> vec = {1, 2, 3, 4, 5};
//     std::cout << binary_search(vec, key, 0, vec.size() - 1) << std::endl;

//     return 0;
// }


// // 5
// #include <iostream>

// int foo(char c1, char c2, short sh) {
//     int target = 0;
//     target = c1;
//     target = (target << sizeof(char) * 8) + c2;
//     target = (target << sizeof(short) * 8) + sh;
//     return target;
// }

// int main() {
//     std::cout << foo(1, 1, 1) << std::endl;
// }

// // 7
// #include <iostream>
// bool exp(int val) {
//     if(val % 2 == 1) {
//         return false;
//     }

//     if(!(val & (val - 1))) {
//         return true;
//     }
//     return false;
// }

// int main() {
//     std::cout << exp(8) << std::endl;
// }


// // 9
// #include <iostream>
// #include <fstream>


// int main() {
//     int x = 3;
//     int y = 1;
//     int res = 0;

//     while(x != 0 && y != 0) {
//         if(x % 2 != y % 2) {
//             ++res;
//         } 
//         x /= 2;
//         y /= 2;
//     }

//     if(x == 0) {
//         while(y != 0) {
//             if(y % 2 == 1) {
//                 ++res;
//             }
//             y /= 2;
//         }
//     } else {
//         while(x != 0) {
//             if(x % 2 == 1) {
//                 ++res;
//             }
//             x /= 2;
//         }
//     }

//     std::cout << res << std::endl;
// }


// // 2
// #include <iostream>
// #include <vector>

// void binary(int k) {
//     std::vector<int> vec;

//     if (k == 0) {
//         vec.push_back(0);
//     } else {
//         while (k > 0) {
//             vec.push_back(k % 2);
//             k /= 2;
//         }
//     }

//     for (int i = vec.size() - 1; i >= 0; --i) {
//         std::cout << vec[i];
//     }
//     std::cout << std::endl;
// }

// int main() {
//     binary(5);
//     return 0;
// }


// // 4
// #include <iostream>

// char substr(const std::string& str, const std::string& sub_str) {
//     int i = 0;
//     while(str[i] != '\0') {
//         if(str[i] != sub_str[0]) {
//             ++i;
//         } else {
//             int j = 0;
//             int k = i;
//             while(str[k] != '\0' && sub_str[j] != '\0' && str[k] == sub_str[j]) {
//                 ++k;
//                 ++j;
//             }

//             if(sub_str[j] == '\0') {
//                 return str[i];
//             } else {
//                 ++i;
//             }
//         }
//     }
//     return ' ';
// }

// int main() {
//     std::string str = "Hello, World!";
//     std::string sub_str = "World";

//     char result = substr(str, sub_str);

//     if (result != ' ') {
//         std::cout << "Substring found: " << result << std::endl;
//     } else {
//         std::cout << "Substring not found." << std::endl;
//     }

// }

// // 6
// #include <iostream>

// int main() {
//     int a = 3;
//     int b = a;
//     int X = 4;
//     int res = 0;

//     while(b <= X) {
//         b *= a;
//         ++res;
//     }

//     std::cout << res << std::endl;
// }

// // 17
// #include <iostream>

// struct ListNode {
//     int val;
//     ListNode* next;
//     ListNode(int x) : val(x), next(nullptr) {}
// };

// int hasCycle(ListNode* head) {
//     if(!head || !head->next) {
//         return 0;
//     }

//     ListNode* cur1 = head;
//     ListNode* cur2 = head;

//     while(cur2 && cur2->next) {
//         cur1 = cur1->next;
//         cur2 = cur2->next->next;

//         if(cur1 == cur2) {
//             return 1;
//         }
//     }

//     return 0;
// }

// int main() {
//     // Example usage
//     ListNode* head = new ListNode(1);
//     head->next = new ListNode(2);
//     head->next->next = new ListNode(3);
//     head->next->next->next = new ListNode(4);
    
//     // Uncomment the line below to create a cycle in the linked list
//     // head->next->next->next->next = head;

//     int result = hasCycle(head);
//     if (result) {
//         std::cout << "The linked list contains a cycle.\n";
//     } else {
//         std::cout << "The linked list does not contain a cycle.\n";
//     }

//     // Clean up memory
//     while (head) {
//         ListNode* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }

// // 20
// #include <iostream>

// struct ListNode {
//     int val;
//     ListNode* next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode* next) : val(x), next(next) {}
// };

// void removeNodesWithValue(ListNode*& head, int val) {
//     while(head != nullptr && head->val == val) {
//         ListNode* tmp = head;
//         head = head->next;
//         delete tmp;
//     }

//     ListNode* cur = head;
//     while(cur->next != nullptr) {
//         if(cur->next->val  == val) {
//             ListNode* tmp = cur->next;
//             cur->next = cur->next->next;
//             delete tmp;
//         } else {
//             cur = cur->next;
//         }
//     }
// }

// // Function to print the linked list for verification
// void printList(ListNode* head) {
//     while (head != nullptr) {
//         std::cout << head->val << " ";
//         head = head->next;
//     }
//     std::cout << std::endl;
// }

// int main() {
//     // Example usage
//     ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(2, new ListNode(4, nullptr)))));
    
//     std::cout << "Original List: ";
//     printList(head);

//     int valueToRemove = 2;
//     removeNodesWithValue(head, valueToRemove);

//     std::cout << "List after removing nodes with value " << valueToRemove << ": ";
//     printList(head);

//     // Free memory
//     while (head != nullptr) {
//         ListNode* temp = head;
//         head = head->next;
//         delete temp;
//     }

//     return 0;
// }


// // 3
// #include <iostream>
// #include <vector>

// using namespace std;

// vector<vector<int>> rotate_180_degrees(const vector<vector<int>>& matrix) {
//     int n = matrix.size();
//     vector<vector<int>> rotated_matrix(n, vector<int>(n));

//     for (int i = n - 1; i >= 0; --i) {
//         for (int j = n - 1; j >= 0; --j) {
//             rotated_matrix[n - 1 - i][n - 1 - j] = matrix[i][j];
//         }
//     }

//     return rotated_matrix;
// }

// int main() {
//     try {
//         int n;
//         cout << "Enter the size of the square matrix (N): ";
//         cin >> n;

//         vector<int> numbers(n);
//         for (int i = 0; i < n; ++i) {
//             cout << "Enter number " << i + 1 << ": ";
//             cin >> numbers[i];
//         }

//         vector<vector<int>> matrix(n, vector<int>(n));
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 cout << "Enter element at position (" << i + 1 << "," << j + 1 << "): ";
//                 cin >> matrix[i][j];
//             }
//         }

//         vector<vector<int>> rotated_matrix = rotate_180_degrees(matrix);

//         cout << "\nOriginal Matrix:\n";
//         for (const auto& row : matrix) {
//             for (int element : row) {
//                 cout << element << " ";
//             }
//             cout << endl;
//         }

//         cout << "\nRotated Matrix (180 degrees):\n";
//         for (const auto& row : rotated_matrix) {
//             for (int element : row) {
//                 cout << element << " ";
//             }
//             cout << endl;
//         }
//     } catch (const exception& e) {
//         cout << "Error: " << e.what() << endl;
//     }

//     return 0;
// }



