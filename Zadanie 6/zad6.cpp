#include <iostream>

class ListNode{
public:
    std::string name;
    ListNode* next;

    ListNode(std::string name){
        this->name = name;
        this->next = nullptr;
    }
};

class List{
    ListNode* head;
    ListNode* tail;

public:
    List(){
        head = nullptr;
    }

    void push(std::string name){
        ListNode* newNode = new ListNode(name);
        if(head==nullptr){
            this->head = newNode;
            this->tail = newNode;
        } else {
            this->tail->next = newNode;
            this->tail = newNode;
        }
    }

    void print(){
        ListNode* currNode = this->head;
        while(currNode!=nullptr){
            std::cout << currNode->name << ' ';
            currNode = currNode->next;
        }
    }
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    std::string name;
    int currCrabs, currTraps;

    List** matrix = new List*[100];
    for(int i=0; i<100; i++){
        matrix[i] = new List[9];
    }

    std::cin >> n;
    for(int i=0; i<n; i++){
        std::cin >> name >> currCrabs >> currTraps;
        matrix[currCrabs][currTraps-1].push(name);
    }

    for(int i=99; i>=0; i--){
        for(int j=0; j<9; j++){
            matrix[i][j].print();
        }
    }
}