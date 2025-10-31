#include <iostream>
using namespace std;

//Rumah Sakit Hewan


int main(){
    system("cls");
    int jlh;
    string jenis;//var kosong
    cout<<"Masukkan jumlah pasien: "; cin>>jlh;
    string nama[jlh]; //array nama
    int prio[jlh]; //array prioritas
    int umur[jlh]; //array umur
    for (int i=0; i<jlh; i++){ //looping masukkan data
        cout<<"Pasien "<<i+1<<":\n";
        cout<<"Nama hewan: "; cin>>nama[i];
        cout<<"Jenis Hewan: "; cin>>jenis;
        cout<<"Umur: "; cin>>umur[i];
        cout<<"Tingkat darurat: "; cin>>prio[i];
        cout<<"\n";
    }

    for(int i=1; i<jlh; i++){//sorting insertion
        for(int j=i; j>0; j--){
            if(prio[j-1]<prio[j]){
                string name=nama[j];
                nama[j]=nama[j-1];
                nama[j-1]=name;

                int darurat=prio[j];
                prio[j]=prio[j-1];
                prio[j-1]=darurat;

                int age=umur[j];
                umur[j]=umur[j-1];
                umur[j-1]=age;
            }
        }
    }
    int no=1;//angka urutan
    while(jlh>0){
        cout<<no++<<". "<<nama[0]<<"("<<umur[0]<<") - Darurat "<<prio[0]<<"\n";
        for (int i = 0; i < jlh - 1; i++) { //penghapusan data yang sudah di tampilkan
            nama[i]=nama[i+1];
            umur[i]=umur[i+1];
            prio[i]=prio[i+1];
        }
        jlh--;//jumlah dikurangi
    }

}