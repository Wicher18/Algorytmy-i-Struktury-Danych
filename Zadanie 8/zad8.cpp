#include <iostream>
#include <unordered_set>
#include <algorithm>

int min(int x, int y){
    return x < y ? x : y;
}

int max(int x, int y){
    return x > y ? x : y;
}

class Node{
public:
    int value;
    Node* leftSon;
    Node* rightSon;

    Node(int value){
        this->value = value;
        this->leftSon = nullptr;
        this->rightSon = nullptr;
    }
};

class BST{
public:
    Node* root;

    BST(){
        root = nullptr;
    }

    void add_node(Node* newNode){
        if(root = nullptr){
            root = newNode;
            return;
        }

        Node* currNode = root;
        while(currNode != nullptr){
            if(newNode->value < currNode->value){
                if(currNode->leftSon == nullptr){
                    currNode->leftSon = newNode;
                    return;
                } else {
                    currNode = currNode->leftSon;
                }
            } else {
                if(currNode->rightSon == nullptr){
                    currNode->rightSon = newNode;
                    return;
                } else {
                    currNode = currNode->rightSon;
                }
            }
        }
    }
};

void sort(int* array, Node* node, int &i) {
    if(node == nullptr) return;

    sort(array, node->leftSon, i);
    array[i] = node->value;
    i++;
    sort(array, node->rightSon, i);
}

// void find_pair(int* sorted, int size, int target){
//     std::unordered_set<int> set;
//     int remainder;
//     int dif, currLow, currHigh;

//     for(int i=0; i<size; i++){
//         remainder = target - sorted[i];

//         if(set.find(remainder) == set.end()){
//             set.insert(sorted[i]);
//         } else {
//             std::cout << remainder << ' ' << sorted[i];
//             return;
//         }
//     }
// }

void find_pair(int* sorted, int size, int target){
    int currLower = 0, currHigher = 0;
    int i = 0, j = size-1, sum;

    while(i != j){
        sum = sorted[i] + sorted[j];
        if(sum == target){
            currLower = min(sorted[i], sorted[j]);
            currHigher = max(sorted[i], sorted[j]);
            i++;
        } else if(sum > target){
            j--;
        } else {
            i++;
        }
    }

    if(currLower){
        std::cout << currLower << ' ' << currHigher;
    } else {
        std::cout << "NIE ZNALEZIONO";
    }
}

int main(){
    int n, k, floor, ceil;
    std::cin >> n;
    BST* tree = new BST();
    int* array = new int[n];

    for(int i=0; i<n; i++){
        std::cin >> array[i];
    }

    std::sort(array, array+n);

    std::cin >> floor >> ceil;
    int* newFloor, *newCeil;
    for(int i=0; i<n; i++){
        if(array[i] >= floor){
            newFloor = array+i;
            break;
        }
    }
    for(int i=n-1; i>=0; i--){
        if(array[i] <= ceil){
            newCeil = array+i;
            break;
        }
    }

    int counter = 0;
    while(newFloor+counter != newCeil+1){
        tree->add_node(new Node(newFloor[counter]));
        counter++;
    }

    int stage = 0;
    sort(newFloor, tree->root, stage);

    std::cin >> k;
    find_pair(newFloor, counter, k);


}