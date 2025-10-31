#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX 5

//Kucing BFS & DFS

class Graph {
private:
    vector<vector<int>> graph = {
        {0,1,1,0,0},
        {1,0,0,1,0},
        {1,0,0,1,0},
        {0,1,1,0,1},
        {0,0,0,1,0}
    };

    vector<vector<int>> weight = {
        {0,5,2,0,0},
        {5,0,0,4,0},
        {2,0,0,1,0},
        {0,4,1,0,3},
        {0,0,0,3,0}
    };
    
    string daftar[MAX]={
        "Ikan Bakar Pak Harry",
        "Gudang Kaleng Bekas",
        "Sushi Kucing Alya",
        "Kedai IKLC",
        "Pasar Ikan Tengah Malam"
    };
    char V[MAX] = {'A','B','C','D','E'};
    int journey=0;

public:
    int charint(char n){//covert data char ke int
        switch(n){
            case 'A': return 0;
            case 'B': return 1;
            case 'C': return 2;
            case 'D': return 3;
            case 'E': return 4;
            default: cout<<"Tidak Valid"; return -1;
        }
    }

    char intchar(int x){//convert data int ke char
        switch(x){
            case 0: return 'A';
            case 1: return 'B';
            case 2: return 'C';
            case 3: return 'D';
            case 4: return 'E';
            default: cout<<"Tidak Valid"; return '?';
        }
    }

    bool adjvalid(int location, int check){//mengecek apakah node graph terhubung
        return graph[location][check] != 0;
    }

    void dfsall(vector<bool>& visited, int vertexnow, int& visitedCount){ //fungsi dfs semua lokasi
        visited[vertexnow] = true;//track lokasi yang dilalui
        visitedCount++;//track berapa yang sudah dilalui
        cout << intchar(vertexnow);
        if (visitedCount < MAX) cout << " -> ";

        if (visitedCount == MAX) return;//jika semua sudah dilalui

        while (true) {
            int minWeight = 9999;//pengganti weight terbesar
            int next = -1;

            for (int i = 0; i < MAX; i++) {
                if (adjvalid(vertexnow, i) && !visited[i]) {//cek apakah valid dan apakah sudah dilalui
                    if (weight[vertexnow][i] > 0 && weight[vertexnow][i] < minWeight){//pengecekan weight terkecil
                        minWeight = weight[vertexnow][i];
                        next = i;//menentukan lokasi yang dilalui selanjutnya
                    }
                }
            }

            if (next == -1) {//jika tidak ada yang bisa dilalui
                break;
            }

            journey += minWeight;//track sejauh apa perjalanan yang ditempuh
            dfsall(visited, next, visitedCount);//rekursif
            if (visitedCount == MAX) return;//jika semua sudah dilalui
        }
    }

    void dfs(char start){ //fungsu start dfs
        vector<bool> visited(MAX, false);//deklarasi vector boolean untuk tracking lokasi yang sudah dilalui
        int visitedCount = 0;//berapa lokasi yang sudah dilalui
        cout << "PENJELAJAHAN PARUL (DFS dari "<<start<<"):\n";
        dfsall(visited, charint(start), visitedCount);//panggil fungsi dfsall
        cout << "\nTotal weight = " << journey <<" meter\n\n";
    }


    void bfs(char startChar, char goalChar){//fungsi bfs
        //konversi char ke int
        int start = charint(startChar);//identifikasi lokasi awal
        int goal = charint(goalChar);//identifikasi lokasi tujuan
        int edge=0;//track total langkah
        vector<bool> visited(MAX, false);//track sudah dilewati
        vector<int> parent(MAX, -1);//
        queue<int> q;//queue int
        visited[start] = true;
        q.push(start);//lokasi awal masuk ke queue

        bool found = false; //boolean jika lokasi tujuan ditemukan

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == goal) {
                found = true;
                break;
            }

            vector<pair<int,int>> neighbors;//track adjacency current
            for (int i=0; i<MAX; i++) {
                if (graph[current][i] == 1 && !visited[i]) {
                    neighbors.push_back({weight[current][i], i});//masukkan ke neighbors
                }
            }

            while (!neighbors.empty()) {//jika current memiliki adjacency yang valid
                int minIndex = 0;
                for (int i=1; i<neighbors.size(); i++) {
                    if (neighbors[i].first < neighbors[minIndex].first) {
                        minIndex = i;//pilih berdasarkan weight terkecil, lalu masukkan lokasi ke minIndex
                    }
                }

                int next = neighbors[minIndex].second;//shift ke index selanjutnya 
                neighbors.erase(neighbors.begin() + minIndex);//hapus yang sudah dilewati

                visited[next] = true; //track sudah dilewati
                parent[next] = current; 
                q.push(next);//next masuk ke queue
            }
        }

        if (!found) {//jika lokasi tujuan ditemukan
            cout << "Goal " << goalChar << " not found from " << startChar << endl;
            return;
        }

        cout << "Jalur Terpendek: \n";//tampilkan perjalanan
        vector<int> path;
        int current = goal;
        while (current != -1) {
            path.insert(path.begin(), current);
            current = parent[current];
        }

        cout <<daftar[start]<<"("<<intchar(path[0])<<")"<< endl;
        for (int i = 0; i < path.size(); i++) {
            if (i > 0) {
            cout<<weight[path[i]][path[i-1]]<<"m"<< endl;
            cout <<daftar[path[i]]<<"("<<intchar(path[i])<<")"<< endl;
            }
        }


        int totalWeight = 0;
        for (int i=0; i<path.size(); i++) {
            cout << intchar(path[i]);
            if (i < path.size()-1) {
                cout << " -> ";
                edge++;
                totalWeight += weight[path[i]][path[i+1]];
            }
        }
        cout<<"\nTotal langkah: "<<edge<<" edge";
        cout << "\nTotal jarak: " << totalWeight <<" meter"<< endl;
    }
    
};
int main() {
    system("cls");
    Graph g;
    g.dfs('A');
    g.bfs('A','E');
}
