#include <iostream>
#include <string>

using namespace std;

class Peak{
    public:
    string name;
    unsigned int height;
    int id;
};

void insertion_sort(Peak arr[], int n){
    Peak curr;
    int j;

    for(int i=1;i<n;i++){
        if(arr[i].height<arr[i-1].height){
            curr=arr[i];
            for(j=i-1;(j>=0) && (arr[j].height>curr.height);j--){
                arr[j+1]=arr[j];
            }
            arr[j+1]=curr;
        }
    }
}

void stability_check(Peak arr[], int n){
    bool flag = true;
    Peak temp;
    while(flag){
        flag = false;
        for(int i=0;i<n-1;i++){
            if((arr[i].height == arr[i+1].height) && (arr[i].id > arr[i+1].id)){
                flag = true;
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int t, n;
    cin >> t;

    for(int i=0;i<t;i++){
        cin >> n;
        Peak* peaks = new Peak[n];
        for(int j=0;j<n;j++){ // Zapisanie n danych wejściowych do tablicy
            cin >> peaks[j].name >> peaks[j].height;
            peaks[j].id = j;
        }

        int currPower=0;
        Peak temp;
        for(int j=0;j<n;j++){ // Podzielenie danych wejściowych na dwie grupy - potęgi 2 i resztę
            if((peaks[j].height & (peaks[j].height-1)) == 0){ // Sprawdzenie czy wysokość jest potęgą 2
                temp=peaks[j];
                peaks[j]=peaks[currPower];
                peaks[currPower]=temp;
                currPower++;
            }
        }

        insertion_sort(peaks, currPower); // Posortowanie danych z potęgą 2
        insertion_sort(peaks+currPower, n-currPower); // Posortowanie reszty danych
        stability_check(peaks,n); // Sprawdzenie czy szczyty o tej samej wysokości nie zamieniły się miejscami

        for(int j=0;j<n;j++){
                cout << peaks[j].name + '-'; 
                cout << peaks[j].height;
                cout << ' ';
        }

        cout << '\n';

        delete[] peaks;
    }
    
}