#include <iostream>

#define INTMAX 2147483647

bool inBounds(int row, int size){
    if((row>=0) && (row<size)) return true;
    return false;
}

int hetman(int** weights, int** constraints, bool** board, int size, int* weight, int* tempWeight, int* columns, int* tempCols, int row){

    //po ustawieniu hetmana w ostatnim rzędzie podmień najmniejszą wagę i pozycje hetmanów
    if(row == size){
        *weight = *tempWeight;
        for(int i=0;i<size;i++){
            columns[i] = tempCols[i];
        }
        return 1;
    }

    for(int i=0;i<size;i++){

        if(!constraints[row][i]){
            board[row][i] = true;
            tempCols[row] = i;

            //aktualna waga rozwiązania
            *tempWeight += weights[row][i];

            if(*tempWeight >= *weight){
                *tempWeight -= weights[row][i];
                continue;
            }

            //constraint dla kolumny
            for(int j=row;j<size;j++){
                constraints[j][i]++;
            }

            //constraint dla przekątnych
            int deviation = i, tempCol = 0;
            while(tempCol<size){
                if(inBounds(row-deviation, size)){
                    constraints[row-deviation][tempCol]++;
                }
                if(inBounds(row+deviation, size)){
                    constraints[row+deviation][tempCol]++;
                }
                
                tempCol++;
                deviation--;
            }

            hetman(weights, constraints, board, size, weight, tempWeight, columns, tempCols, row+1);
                board[row][i] = false;
                *tempWeight -= weights[row][i];

                //usunięcie constraint'a dla kolumny i wiersza
                for(int j=row;j<size;j++){
                    constraints[j][i]--;
                }

                //usunięcie constraint'a dla przekątnych
                deviation = i, tempCol = 0;
                while(tempCol<size){
                    if(inBounds(row-deviation, size)){
                        constraints[row-deviation][tempCol]--;
                    }
                    if(inBounds(row+deviation, size)){
                        constraints[row+deviation][tempCol]--;
                    }
                
                    tempCol++;
                    deviation--;
                }
            
        }
    }

    return 0;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;

    int** weights = new int*[size];
    int** constraints = new int*[size];
    bool** board = new bool*[size];

    //wprowadzenie początkowego stanu planszy
    for(int i=0;i<size;i++){
        weights[i] = new int[size];
        constraints[i] = new int[size];
        board[i] = new bool[size];
        for(int j=0;j<size;j++){
            std::cin >> weights[i][j];
            constraints[i][j]=0;
            board[i][j]=false;
        }
    }

    int* weight = new int;
    int* columns = new int[size];
    int* tempCols = new int[size];
    *weight = INTMAX;
    int* tempWeight = new int;
    *tempWeight = 0;

    hetman(weights, constraints, board, size, weight, tempWeight, columns, tempCols, 0);

    for(int i=0;i<size;i++){
        std::cout << columns[i] << ' ';
    }

    return 0;
}