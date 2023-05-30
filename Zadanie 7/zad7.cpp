#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>

#define INTMAX 2147483647;

int min(int x, int y){
    return x < y ? x : y;
}

class Edge{
public:
    int target;
    int weight;

    Edge(int target, int weight){
        this->target = target;
        this->weight = weight;
    }

    Edge(){}
};

class Compare{
public:
    bool operator()(Edge* a, Edge* b){
        return a->weight > b->weight;
    }
};

class ListNode{
public:
    ListNode* next;
    Edge* edge;

    ListNode(Edge* edge){
        next = nullptr;
        this->edge = edge;
    }
};

class List{ 
public:

    ListNode* head;

    List(){
        head = nullptr;
    }

    void push(ListNode* newNode){
        if(head == nullptr){
            head = newNode;
            return;
        }

        ListNode* currNode = this->head;
        while(currNode != nullptr){
            if(currNode->edge->target == newNode->edge->target){
                currNode->edge->weight = min(currNode->edge->weight, newNode->edge->weight);
                return;
            }
            if(currNode->next == nullptr){
                currNode->next = newNode;
                return;
            }
            currNode = currNode->next;
        }
    }

};

class Node{
public:
    int x;
    int y;
    List neighbours;
};

void add_neighbours(Node* graph, Edge* sorted, int size){
    Edge* newNeighbour = new Edge(sorted[1].target, std::abs(sorted[0].weight - sorted[1].weight));
    graph[sorted[0].target].neighbours.push(new ListNode(newNeighbour));
    Edge currNode, left, right;

    for(int i=1; i< size-1; i++){
        currNode = sorted[i];
        left = sorted[i-1];
        right = sorted[i+1];
        newNeighbour = new Edge(left.target, std::abs(currNode.weight - left.weight));
        graph[currNode.target].neighbours.push(new ListNode(newNeighbour));
        newNeighbour = new Edge(right.target, std::abs(currNode.weight - right.weight));
        graph[currNode.target].neighbours.push(new ListNode(newNeighbour));
    }

    newNeighbour = new Edge(sorted[size-2].target, std::abs(sorted[size-1].weight - sorted[size-2].weight));
    graph[sorted[size-1].target].neighbours.push(new ListNode(newNeighbour));
}

int dijkstra(Node* graph, int start, int finish, int size){
    int weights[size];
    Edge* currEdge;
    ListNode* currNeighbour;
    int currNeighbourId, currEdgeId;
    for(int i=0; i<size; i++){
        weights[i] = INTMAX;
    }
    weights[start] = 0;
    std::priority_queue<Edge*,std::vector<Edge*>, Compare> pQueue;

    pQueue.push(new Edge(start, 0));
    while(!pQueue.empty()){
        currEdge = pQueue.top();
        pQueue.pop();
        currEdgeId = currEdge->target;

        currNeighbour = graph[currEdgeId].neighbours.head;
        while(currNeighbour != nullptr){
            currNeighbourId = currNeighbour->edge->target;
            if(weights[currNeighbourId] > weights[currEdgeId] + currNeighbour->edge->weight){
                weights[currNeighbourId] = weights[currEdgeId] + currNeighbour->edge->weight;
                pQueue.push(currNeighbour->edge);
            }
            currNeighbour = currNeighbour->next;
        }
    }

    return weights[finish];
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n, start, finish;
    std::cin >> n;
    Node* graph = new Node[n];
    Edge* sorted = new Edge[n];
    int x, y;
    for(int i=0; i<n; i++){
        std::cin >> x >> y;
        graph[i].x = x;
        graph[i].y = y;
        sorted[i].target = i;
        sorted[i].weight = x;
    }
    std::cin >> start >> finish;

    std::sort(sorted, sorted+n, [](Edge a, Edge b){return a.weight > b.weight;});
    add_neighbours(graph, sorted, n);

    for(int i=0; i<n; i++){
        sorted[i].target = i;
        sorted[i].weight = graph[i].y;
    }
    std::sort(sorted, sorted+n, [](Edge a, Edge b){return a.weight > b.weight;});
    add_neighbours(graph, sorted, n);

    std::cout << dijkstra(graph, start, finish, n);
    return 0;
}