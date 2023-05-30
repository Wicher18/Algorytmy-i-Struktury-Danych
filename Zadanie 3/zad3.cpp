#include <iostream>

int compareStrings(std::string s1, std::string s2){
    if(s1 == s2){
        return 0;
    } else if(s1 < s2){
        return -1;
    } else {
        return 1;
    }
}

//struktura pojedynczego węzła
class Node{
public:
    std::string key;
    int copies;
    Node* parent;
    Node* leftSon;
    Node* rightSon;

    Node(){
        copies=1;
        leftSon=nullptr;
        rightSon=nullptr;
    }

    Node(Node* p, std::string currKey){
        copies=1;
        leftSon=nullptr;
        rightSon=nullptr;
        key=currKey;
        parent=p;
    }

};

//funkcja do wyświetlenia drzewa in order
void inOrder(Node* node){
    if(node->leftSon!=nullptr) inOrder(node->leftSon);
    for(int i=0;i<node->copies;i++) std::cout << node->key + "\n";
    if(node->rightSon!=nullptr) inOrder(node->rightSon);
}

//funkcja do usunięcia drzewa
void deleteTree(Node* node){
    if(node == nullptr) return;
    deleteTree(node->leftSon);
    deleteTree(node->rightSon);
    delete node;
    
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    
    int n;
    std::cin >> n;
    Node* root = new Node();
    std::cin >> root->key;
    root->parent = nullptr;


    int result;
    Node* currentNode;
    std::string currentKey;
    for(int i=1;i<n;i++){
        std::cin >> currentKey;
        currentNode = root;
        while(currentNode != nullptr){
            result = compareStrings(currentNode->key, currentKey);

            if(result==0){ //klucze są takie same, zwiększa ilość kopii danego węzła
                currentNode->copies++;
                currentNode = nullptr;
            
            } else if(result>=1){ //nowy klucz jest mniejszy od aktualnego węzła
                if(currentNode->leftSon == nullptr){
                    currentNode->leftSon = new Node(currentNode, currentKey);
                    currentNode = nullptr;
                } else {
                    currentNode = currentNode->leftSon;
                }
            
            } else { //nowy klucz jest większy od aktualnego węzła
                if(currentNode->rightSon == nullptr){
                    currentNode->rightSon = new Node(currentNode, currentKey);
                    currentNode = nullptr;
                } else {
                    currentNode = currentNode->rightSon;
                }
            }
        }
    }
    
    inOrder(root);
    deleteTree(root);

    return 0;
}