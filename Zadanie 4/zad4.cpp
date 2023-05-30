#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>



class Node{
    public:
    int id;
       
    Node(int id){
        this->id = id;
    }

    class ListNode{
    public:
    Node* node;
    ListNode* next;

        ListNode(Node* node){
            this->next = nullptr;
            this->node = node;
        }

    };

    class List{
        public:
        ListNode* head = nullptr;

        void push(Node* node){
            ListNode* newNode = new ListNode(node);

            if(head==nullptr){
                head = newNode;
                return;
            }

            ListNode* currNode = head;
            while(currNode->next != nullptr) currNode = currNode->next;

            currNode->next = newNode;
        }
    };

    List neighbours;
};

void BFS(int startId, int* targetIds, int targetSize, Node** graph, int size){
    int* d = new int[size];
    int currId;
    int currNodeId;
    Node::ListNode* currNode = nullptr;
    //uzupełnienie tabeli d wartością maksymalną+1
    for(int i=0; i<size; i++){
        d[i] = size;
    }
    d[startId] = 0; //ustawienie dystansu startowego miasta na 0
    std::queue<int> q;
    q.push(startId); //dodanie startowego miasta do kolejki
    while(!q.empty()){
        currId = q.front();
        currNode = graph[currId]->neighbours.head; //pobranie pierwszego sąsiada dla danego miasta
        while(currNode != nullptr){
            currNodeId = currNode->node->id; //przypisanie pod currNodeId id aktualnego sąsiada
            if(d[currNodeId] == size){
                d[currNodeId] = d[currId] + 1;
                q.push(currNodeId);
            }
            currNode = currNode->next;
        }
        q.pop(); 
    }

    for(int i=0; i<targetSize; i++){ //wpisanie w tabelę z id miast docelowych długość ścieżek do tych miast
        targetIds[i] = d[targetIds[i]];
    }
}



int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    //pobranie ilości miast i miast docelowych
    int n, target;
    Node* startingPoint;
    std::cin >> n >> target;

    //utworzenie tabeli dla id miast docelowych oraz tabeli dla wszystkich miast
    int* targetIds = new int[target];
    Node** cities = new Node*[n];

    std::unordered_map<std::string, int> map;

    std::string name;
    for(int i=0; i<n; i++){
        std::cin >> name; //pobranie nazwy miasta
        map[name] = i; //przypisanie id dla tej nazwy
        cities[i] = new Node(i); //dodanie miasta o id "i" do tabeli wszystkich miast
    }

    Node* node = nullptr;
    for(int i=0; i<n; i++){
        std::cin >> name;
        while(name != "X"){
            cities[i]->neighbours.push(cities[map[name]]);
            std::cin >> name;
        }
    }

    std::cin >> name;
    startingPoint = cities[map[name]];

    for(int i=0; i<target; i++){
        std::cin >> name;
        targetIds[i] = cities[map[name]]->id; //przypisanie id miasta docelowego do tabeli
    }
    
    BFS(startingPoint->id, targetIds, target, cities, n);

    int longest = 0;
    for(int i=0; i<target; i++){ //sprawdzenie najdłuższej ścieżki do miast docelowych
        if(longest < targetIds[i]) longest = targetIds[i];
    }

    std::cout << longest;

    return 0;
}