#include <iostream>
#include <iomanip>
using namespace std;

//Koleksi Film
struct Node { //buat node linked list
    string judul;
    int tahun;
    float rating;
    Node *next;
};

Node *head = NULL; //isi kosong
Node *tail = NULL;

int total;//counter total

void insertFirst(string j, int t, float r){//fungsi insert di depan
    Node *newNode= new Node;
    newNode -> judul=j;
    newNode -> tahun=t;
    newNode -> rating=r;
    newNode -> next=NULL;

    if (head==NULL){
        head=newNode;
        tail=head;
    } else {
        newNode -> next=head;
        head=newNode;
    }
    total++;
}

void insertLast(string j, int t, float r){//fungsi insert di belakang
    Node *newNode= new Node;
    newNode -> judul=j;
    newNode -> tahun=t;
    newNode -> rating=r;
    newNode -> next=NULL;

    if (head==NULL){
        head=newNode;
        tail=head;
    } else{
        tail-> next=newNode;
        tail=newNode;
    }
    total++;
}

void insertAfter(string j, int t, float r, string check){//fungsi insert setelah suatu film
    if (head==NULL){
        cout<<"List Kosong, insert di depan dulu\n";
        return;
    }

    Node *newNode= new Node;
    newNode -> judul=j;
    newNode -> tahun=t;
    newNode -> rating=r;
    newNode -> next=NULL;

    Node *p=head;
    while (p!=NULL && p->judul!=check){//mencari target
        p=p->next;
    }
    
    if (p==NULL){
        cout<<"Film dengan judul "<<check<<"Tidak ditemukan\n";
        delete newNode;
    } else{//hubungkan linked list
        newNode->next=p->next;
        p->next=newNode;
        if(p==tail){ //jika target urutan terakhir, newNode jadi tail
            tail=newNode;
        }
        total++;
    }
}

void deletetitle(string s){//delete berdasarkan judul
    if (head == NULL) {
        cout << "List kosong!\n";
        return;
    }
    if (head->judul == s){// jika target urutan paling awal
        Node *temp = head; //deklarasi temp sebagai pointer head
        head = head->next;
        if (head == NULL) tail = NULL;//
        delete temp;
        total--;
        return;
    }
    Node *p = head;//mulai dari head
    while (p->next != NULL && p->next->judul != s) {//mencari target
        p = p->next;//dari head hingga rear hingga target ditemukan
    }
    if (p->next == NULL) {
        cout << "Film dengan judul " << s << " tidak ditemukan!\n";
    } else { //jika ditemukan, hubungkan linked list target-1 dan target+1
        Node *temp = p->next; //temp sebagai pointer target+1
        p->next = temp->next; //hubungkan linked list target-1 dan target+1
        if (temp == tail) tail = p;//jika urutan terakhir
        delete temp; //delete temp node
        total--;
    }
}

void printList(){//cetak linked list
    cout<<"\n";
    Node *temp=head;
    while(temp!=NULL){
        cout<<temp->judul<<" ("<<temp->tahun<<") - "<<fixed<<setprecision(2)<<temp->rating<<"\n";
        temp=temp->next;
    }
}

int main(){
    system("cls");
    int jlh;
    string jdl;
    int thn;
    float rate; 
    cout<<"Masukkan jumlah film awal: "; cin>>jlh;
    for(int i=0; i<jlh; i++){ //input film awal
        cout<<"Film "<<i+1<<": \n";
        cin.ignore(100, '\n');
        cout<<"Judul: "; getline(cin,jdl);
        cout<<"Tahun: "; cin>>thn;
        cout<<"Rating: "; cin>>rate;
        insertLast(jdl, thn, rate);
        cout<<endl;
    }
    printList();
    char redo;

    do{ //pengulangan update list
        char yn;
        cout<<"Ingin menghapus(1)/memasukkan(2) film?(1/2): "; cin>>yn;
        if (yn=='1'){//delete
        string con;
        cin.ignore(100, '\n');
        cout<<"Masukkan judul film yang sudah ditonton: "; getline(cin,con);
        deletetitle(con);
        printList();
        cout<<"Total film tersisa: "<<total<<endl;
        }
        else if (yn=='2'){//insert
            cout<<"1. Apakah ingin ditonton malam ini?\n";
            cout<<"2. Apakah ingin ditonton setelah film tertentu?\n";
            cout<<"3. Apakah film lama?\n";
            cout<<"Pilih (1/2/3): "; cin>>yn;

            cin.ignore(100, '\n'); //input film
            cout<<"Judul: "; getline(cin,jdl);
            cout<<"Tahun: "; cin>>thn;
            cout<<"Rating: "; cin>>rate;
            cout<<endl<<endl;

            switch (yn){ //switch case untuk menentukan function insert yang dijalankan
                case '1':{
                insertFirst(jdl, thn, rate);
                break;
                }

                case '2': {
                string cek;
                cout<<"Masukkan setelah: "; cin>>cek;
                insertAfter(jdl,thn,rate,cek);
                break;
                }

                case '3':{
                insertLast(jdl,thn,rate);
                break;
                }

                default:
                cout<<"Pilihan tidak valid\n";
                break;
            }
            printList(); //tampilkan
            cout<<"Total film tersisa: "<<total<<endl;
        } else cout<<"Pilihan tidak valid\n";
        cout<<"Ingin lanjut masukkan/menghapus?(y/n): "; cin>>redo; //konfirmasi untuk lanjut/berhenti

    } while(redo!='n' && redo=='y');
}