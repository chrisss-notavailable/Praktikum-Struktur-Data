#include<iostream>
#include<fstream>
#include<sstream>
#include <algorithm>
#include <cctype>
using namespace std ;

string toLowerCase(string str){
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// STRUCT PROGRAM

struct servis {
    string masuk;
    string model;
    string merek;
    string kendala;
    string montir;
    string namac;
    long long noc;
    servis* next;
};

struct cust{
    string nama;
    int umur;
    string gender;
    long long no;
    string alamat;
    cust* next;
    cust* prev ;
};


// PROTOTYPE FUNGSI

void simpanCustomer();
void simpanServis();
void simpanHistory(servis* simpan);
void loadCustomer();
void loadAntrian();
void loadHistory();
void dataCust();
void semuaDataCust();
void tambahSS();
void dataSS();
void servisSelesai();
void riwayatServis();
void montir();
void menuServis();
void menuAdmin();

// VAR GLOBAL

cust* headCust = NULL;
// servis* semuaServis = NULL ;
servis* frontServis = NULL ;
servis* rearServis = NULL;
servis* selesaiServis = NULL;

// FUNNGSI DASAR 

cust* cariCust (string nama) {

    if(headCust == NULL)
        return NULL;

    cust* bantu = headCust;

    do {
        if (bantu->nama == nama)
            return bantu;

        bantu = bantu->next;

    } while(bantu != headCust);

    return NULL;
}

void masukServis (servis* baru){
    if(frontServis == NULL){
        frontServis = baru ;
        rearServis = baru;
    }

    else{
        rearServis -> next = baru;
        rearServis = baru ;
    }
}

servis* keluarServis (){
    
    if(frontServis == NULL ){
        return NULL;
    }
    servis* keluar = frontServis ;
    frontServis = frontServis -> next ;

    if(frontServis == NULL){
        rearServis = NULL;
    }
    keluar -> next = NULL;
    return keluar;
} 

void tambahServisFile(string masuk,string model, string merek,string kendala, string montir,string namac, long long noc)
{
    servis* baru = new servis;
    baru->masuk = masuk;
    baru->model = model;
    baru->merek = merek;
    baru->kendala = kendala;
    baru->montir = montir;
    baru->namac = namac;
    baru->noc = noc;
    baru->next = NULL;

    masukServis(baru);
}


// OPERASI PROGRAM

void tambahCust (string nama, int umur, string gender,long long no,string alamat){
    cust* baru = new cust;
    baru -> nama = nama ;
    baru -> umur = umur ;
    baru -> gender = gender ;
    baru -> no = no ;
    baru -> alamat = alamat ;
    baru -> next = NULL;
    baru -> prev = NULL;

    // if (headCust == NULL ){
    //     headCust = baru ;
    // }
    // else {
    //     cust* bantu = headCust;
    //     while (bantu -> next != NULL)
    //         bantu = bantu -> next;
    //     bantu -> next = baru;
    //     baru -> prev = bantu;
    // }
    if (headCust == NULL ){  // doubly circular
    headCust = baru;
    baru->next = baru;
    baru->prev = baru;
}
else {
    cust* tail = headCust->prev;

    tail->next = baru;
    baru->prev = tail;

    baru->next = headCust;
    headCust->prev = baru;
}
}


void tambahSS() {
    cin.ignore();
    string model,merek,kendala,montir,nama,masuk;

    cout << "Tamggal Masuk : ";
    getline(cin,masuk);
    cout << "Model mobil :";
    getline(cin,model);
    cout << "Merek mobil :";
    getline(cin,merek);
    cout << "Kendala :";
    getline(cin,kendala);
    cout << "Montir :";
    getline (cin,montir);
    cout << "Nama Pelanggan :";
    getline (cin,nama);

    cust* pelanggan = cariCust(nama);

    if (pelanggan == NULL){
        long long no;
        int umur;
        string alamat, gender;

        cout <<"No HP :" ;
        cin >> no;
        cin.ignore();
        cout <<"Alamat :" ;
        getline(cin,alamat);
        cout <<"Umur :" ;
        cin >> umur;
        cin.ignore();
        cout <<"Gender : " ;
        getline(cin,gender);

        tambahCust (nama,umur,gender,no,alamat);
        pelanggan = cariCust(nama);
        
        cout << "Pelanggan baru berhasil terdaftar\n";
    }
    else{
        cout << "pelanggan sudah terdaftar\n";
    }

    servis* baru = new servis ;
    baru -> masuk = masuk;
    baru -> model = model;
    baru -> merek = merek;
    baru -> kendala = kendala;
    baru -> montir = montir;
    baru -> namac = pelanggan -> nama ;
    baru -> noc = pelanggan -> no ;
    baru -> next = NULL;

    masukServis(baru);

simpanCustomer();
simpanServis();

system("pause");
}

void dataSS(){

    if (frontServis == NULL) {
        cout << " Tidak ada servis ";
        system ("pause");
        return ;
    }

    cout <<"\n======== Data Service ========\n";

    servis* bantu = frontServis;
    int antri = 1;

    while(bantu != NULL){
        cout << "==============================================\n";
        cout << " Antrian ke : " << antri << endl;
        cout << " Tanggal Masuk Service :" << bantu -> masuk << endl;
        cout << " Model Mobil :" << bantu -> model << endl;
        cout << " Merek Mobil :" << bantu -> merek << endl;
        cout << " kendala : " << bantu -> kendala << endl;
        cout << " Montir : " << bantu -> montir << endl;
        cout << " Nama Pelanggan :" << bantu -> namac << endl;
        cout << " No Telp Pelanggan :" << bantu -> noc << endl;
        cout << "==============================================\n";
        bantu = bantu -> next ;
        antri ++;
    }

system("pause");
}

void dataCust () {
    if(headCust==NULL)
    return;
    
    cust* current = headCust;
    char menu;

    while (true) {
        cout << "\n========= Data Pelanggan =========\n";
        cout << "Nama : " << current -> nama << endl;
        cout << "Nomer Telepon : " << current -> no << endl;
        cout << "umur: " << current->umur << endl;
        cout << "Gender: " << current -> gender << endl;
        cout << "Alamat: " << current -> alamat << endl;

        cout <<"\n[N]EXT    [P]REVIOUS [E]EXIT\nPilihan :";
        cin >> menu;

        if (menu == 'N' || menu == 'n'){
            current = current-> next;
        }
        else if (menu == 'P' || menu == 'p'){
            current = current-> prev;
        }
        else if (menu == 'E' || menu == 'e'){
            break;
        }
    }
}


void semuaDataCust() {

    if(headCust == NULL){
        cout << "Belum ada data pelanggan.\n";
        system("pause");
        return;
    }

    cout << "\n====== SEMUA PELANGGAN ======\n";

    cust* current = headCust;

    do {
        cout << "-----------------------\n";
        cout << "Nama: " << current->nama << endl;
        cout << "Nomor Telepon: " << current->no << endl;
        cout << "Alamat: " << current->alamat << endl;

        servis* bantuServis = frontServis;
        servis* servisTerakhir = NULL;

        while(bantuServis != NULL){
            if(toLowerCase(bantuServis->namac) == toLowerCase(current->nama)){
                servisTerakhir = bantuServis;
            }
            bantuServis = bantuServis->next;
        }

        if(servisTerakhir != NULL){
            cout << "___Servis Terakhir___\n";
            cout << "Mobil: " << servisTerakhir->model << endl;
            cout << "Kendala: " << servisTerakhir->kendala << endl;
            cout << "Montir: " << servisTerakhir->montir << endl;
        }
        else{
            cout << "Belum pernah melakukan servis.\n";
        }

        cout << "-----------------------\n";

        current = current->next;

    } while(current != headCust);

    system("pause");
}

void servisSelesai(){

    if(frontServis == NULL){
        cout << "Tidak ada servis di antrian\n";
        system("pause");
        return;
    }

    string daftarMontir[5];
    int jumlahMontir = 0;

    servis* cari = frontServis;

    while(cari != NULL){

        bool montir = false;

        for(int i=0;i<jumlahMontir;i++){
            if(toLowerCase(daftarMontir[i]) == toLowerCase(cari->montir)){
            montir = true;
                break;
            }
        }

        if(!montir){
            daftarMontir[jumlahMontir] = cari->montir;
            jumlahMontir++;
        }

        cari = cari ->next;
    }

    cout << "\nPilih Montir!\n";

    for(int i=0;i<jumlahMontir;i++){
        cout << i+1 << ". " << daftarMontir[i] << endl;
    }

    int pilih;
    cout << "Pilihan: ";
    cin >> pilih;

    if(pilih < 1 || pilih > jumlahMontir){
        cout << "Pilihan tidak valid\n";
        system("pause");
        return;
    }

    string montir = daftarMontir[pilih-1];

    servis* prev = NULL;
    cari = frontServis;
    servis* target = NULL;
    servis* prevTarget = NULL;

    while(cari != NULL){

        if(toLowerCase(cari->montir) == toLowerCase(montir)){
            target = cari;
            prevTarget = prev;
            break;
        }

        prev = cari;
        cari = cari->next;
    }

    if(target == NULL){
        cout << "Tidak ada servis untuk montir tersebut\n";
        system("pause");
        return;
    }

    if(prevTarget == NULL){
        frontServis = target->next;
    }
    else{
        prevTarget->next = target->next;
    }

    if(target == rearServis){
        rearServis = prevTarget;
    }

    cout << "\n======== SERVIS ========\n";
    cout << "Tanggal Masuk :" << target->masuk << endl;
    cout << "Model Mobil :" << target->model << endl;
    cout << "Merek Mobil :" << target->merek << endl;
    cout << "Kendala :" << target->kendala << endl;
    cout << "Montir :" << target->montir << endl;
    cout << "Nama Pelanggan :" << target->namac << endl;
    cout << "Telp Pelanggan :" << target->noc << endl;

    char status;

    cout << "\nApakah servis ini sudah selesai? (Y/N): ";
    cin >> status;

    status = tolower(status);

    if(status == 'y'){

        target->next = selesaiServis;
        selesaiServis = target;

        simpanHistory(target);

        cout << "Servis sudah dinyatakan selesai\n";
    }
    else if(status == 'n'){

        masukServis(target);

        cout << "Servis dikembalikan ke antrian\n";
    }
    else{

        cout << "Input tidak valid\n";
        masukServis(target);
    }

    simpanServis();

    system("pause");
}

void riwayatServis (){
    cin.ignore();
    string nama;

    cout << "masukkan nama pelanggan: ";
    getline (cin,nama);

    servis* bantu = selesaiServis;

    bool ada = false;

    cout << "\n------------- Riwayat Servis -------------\n";
    cout << "SUDAH SELESAI DIKERJAKAN : \n";

    while (bantu != NULL){
        if(toLowerCase(bantu->namac) == toLowerCase(nama)){
            
            ada = true;
            cout << "\n========== SUDAH SELESAI ==========\n";
            cout << "tanggal masuk :" << bantu -> masuk << endl;
            cout << "Model mobil :" << bantu -> model << endl;
            cout << "Merek mobil :" << bantu -> merek << endl;
            cout << "Kendala :" << bantu -> kendala << endl;
            cout << "Montir :" << bantu -> montir << endl;
            cout << "No telp :" << bantu -> noc << endl;
            cout << "===================================\n";
        }
        bantu = bantu-> next;
    }
    if(!ada){
        cout <<"\nbelum ada servis yang sudah selesai \n" ;
    }

    cout << "---------------------------------------------";
    servis* cari = frontServis;
    bool antrian = false ;

    cout << "\nSEDANG DALAM PROSES PENGERJAAN : \n";
    
    while (cari != NULL){
        if(toLowerCase(cari->namac) == toLowerCase(nama)){

            antrian = true ;
            cout << "\n========== DALAM PROSES ==========\n";
            cout << "tanggal masuk :" << cari -> masuk << endl;
            cout << "Model mobil :" << cari -> model << endl;
            cout << "Merek mobil :" << cari -> merek << endl;
            cout << "Kendala :" << cari -> kendala << endl;
            cout << "Montir :" << cari -> montir << endl;
            cout << "No telp :" << cari -> noc << endl;
            cout << "===================================\n";
        }
        cari = cari-> next ;
    }
    if(!antrian){
        cout << "tidak ada servis yang sedang di kerjakan\n";
    }
system ("pause");
}

void montir() {
int pilih;
    string namaMontir;

    cout << "\n====== RIWAYAT MONTIR ======\n";
    cout << "Pilih montir?\n";
    cout << "1. Suby\n";
    cout << "2. Farhan\n";
    cout << "3. Dimas\n";
    cout << "4. Aldo\n";
    cout << "Pilihan: ";
    cin >> pilih;

    switch(pilih){
        case 1: 
            namaMontir = "Suby"; 
            break;

        case 2: 
            namaMontir = "Farhan"; 
            break;

        case 3: 
            namaMontir = "Dimas"; 
            break;

        case 4: 
            namaMontir = "Aldo";
            break;
            
        default:
            cout << "Pilihan tidak valid!\n";
            system("pause");
            return;
    }

    string inputLower = toLowerCase(namaMontir);

    cout << "\n====== Riwayat Kerja Montir: " << namaMontir << " ======\n";



    ifstream antrian("Antrian.txt");

    if(!antrian.is_open()){
        return;
    }

    string line;
    bool adaAntrian = false;

    cout << "\n--- Servis yg Sedang Dikerjakan ---\n";

    while(getline(antrian, line)){

        stringstream ss(line);

        string masuk, model, merek, kendala, montir, namac, noStr;

        getline(ss, masuk, '|');
        getline(ss, model, '|');
        getline(ss, merek, '|');
        getline(ss, kendala, '|');
        getline(ss, montir, '|');
        getline(ss, namac, '|');
        getline(ss, noStr, '|');

        if(toLowerCase(montir) == inputLower){

            adaAntrian = true;

            cout << "-----------------------------\n";
            cout << "Tanggal Masuk : " << masuk << endl;
            cout << "Model Mobil   : " << model << endl;
            cout << "Merek Mobil   : " << merek << endl;
            cout << "Kendala       : " << kendala << endl;
            cout << "Pelanggan     : " << namac << endl;
            cout << "No Telp       : " << noStr << endl;
        }
    }

    if(!adaAntrian){
        cout << "Tidak ada antrian untuk montir\n";
    }

    antrian.close();


    ifstream history("HistoryServis.txt");

    if(!history.is_open()){
        return;
    }

    bool adaHistory = false;

    cout << "\n--- Servis Yang Selesai ---\n";

    while(getline(history, line)){

        stringstream ss(line);

        string masuk, model, merek, kendala, montir, namac, noStr;

        getline(ss, masuk, '|');
        getline(ss, model, '|');
        getline(ss, merek, '|');
        getline(ss, kendala, '|');
        getline(ss, montir, '|');
        getline(ss, namac, '|');
        getline(ss, noStr, '|');

        if(toLowerCase(montir) == inputLower){

            adaHistory = true;

            cout << "-----------------------------\n";
            cout << "Tanggal Servis: " << masuk << endl;
            cout << "Model Mobil   : " << model << endl;
            cout << "Merek Mobil   : " << merek << endl;
            cout << "Kendala       : " << kendala << endl;
            cout << "Pelanggan     : " << namac << endl;
            cout << "No Telp       : " << noStr << endl;
        }
    }

    if(!adaHistory){
        cout << "belum ada pekerjaaan yang selesai\n";
    }

    history.close();

    system("pause");
}

// FILE HANDLING

void simpanCustomer(){
    if(headCust == NULL) 
    return;

    ofstream file("Customer.txt");
    cust* bantu = headCust;

    do{
        file << bantu->nama << "|"
            << bantu->umur << "|"
            << bantu->gender << "|"
            << bantu->no << "|"
            << bantu->alamat << endl;

        bantu = bantu->next;

    } while(bantu != headCust);

    file.close();
}

void simpanServis(){
    ofstream file("Antrian.txt");
    servis* bantu = frontServis;

    while(bantu != NULL){
        file<< bantu->masuk << "|"  
            << bantu->model << "|"
            << bantu->merek << "|"
            << bantu->kendala << "|"
            << bantu->montir << "|"
            << bantu->namac << "|"
            << bantu->noc << endl;

        bantu = bantu->next;
    }
    file.close();
}

void simpanHistory(servis* simpan){

    ofstream file ("HistoryServis.txt", ios::app);

    file    << simpan->masuk << "|"
            << simpan->model << "|"
            << simpan->merek << "|"
            << simpan->kendala << "|"
            << simpan->montir << "|"
            << simpan->namac << "|"
            << simpan->noc << endl;

    file.close();
}

void loadCustomer(){
    ifstream file("Customer.txt");
    if(!file.is_open())
    return;

    string line;

    while(getline(file, line)){
        stringstream ss(line);
        string nama, umurStr, gender, noStr, alamat;

        getline(ss, nama, '|');
        getline(ss, umurStr, '|');
        getline(ss, gender, '|');
        getline(ss, noStr, '|');
        getline(ss, alamat, '|');

        tambahCust(nama, stoi(umurStr), gender, stoll(noStr), alamat);
    }

    file.close();
}

void loadAntrian() {

    ifstream file("Antrian.txt");

    if(!file.is_open())
    return;

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string masuk, model, merek, kendala, montir, namac, noStr;

        getline(ss, masuk, '|');
        getline(ss, model, '|');
        getline(ss, merek, '|');
        getline(ss, kendala, '|');
        getline(ss, montir, '|');
        getline(ss, namac, '|');
        getline(ss, noStr, '|');

        tambahServisFile(masuk, model, merek, kendala, montir, namac, stoll(noStr));
    }

    file.close();
}

void loadHistory(){
    ifstream file ("HistoryServis.txt");

    if(!file.is_open())
        return;
    
        string line;

        while(getline(file,line)){

        stringstream ss(line);

        string masuk, model, merek, kendala, montir, namac, noStr;

        getline(ss, masuk, '|');
        getline(ss, model, '|');
        getline(ss, merek, '|');
        getline(ss, kendala, '|');
        getline(ss, montir, '|');
        getline(ss, namac, '|');
        getline(ss, noStr, '|');

        servis* baru = new servis;

        baru->masuk = masuk;
        baru->model = model;
        baru->merek = merek;
        baru->kendala = kendala;
        baru->montir = montir;
        baru->namac = namac;
        baru->noc = stoll(noStr);

        baru->next = selesaiServis;
        selesaiServis = baru;
        }
    file.close();
}

// MENU

void menuServis() {
    int pilih;

    do {
        cout << "\n====== Services ======\n";
        cout << "1. Semua Servis Singkat\n";
        cout << "2. Servis Baru\n";
        cout << "3. Selesaikan Pekerjaan\n";
        cout << "4. Riwayat Kerja Montir\n";
        cout << "5. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilih;

        switch(pilih) {
            case 1:
                dataSS(); 
                break;
            case 2:
                tambahSS(); 
                break;
            case 3:
                servisSelesai();
                break;
            case 4:
                montir();
                break;
        }

    } while(pilih != 5);
}

void menuAdmin() {
    int pilih ;

    do{

        cout << "\n======= Menu Admin =======\n";
        cout << "1. Servis\n";
        cout << "2. Pelanggan Baru\n";
        cout << "3. Data Pelanggan\n";
        cout << "4. Semua Data Pelanggan\n";
        cout << "5. Kembali\n";
        cout << "Pilihan :" ;
        cin >> pilih;

        switch (pilih){
            case 1 :
                menuServis();
                break;

            case 2 : {
                cin.ignore();
                string nama, gender, alamat;
                long long no ;
                int umur;

                cout << "Nama : ";
                getline (cin, nama);

                cout << "No HP : ";
                cin >> no ;
                cin.ignore();

                cout << "Alamat : ";
                getline (cin, alamat);

                cout << "Umur : ";
                cin >>  umur;
                cin.ignore();

                cout << "gender : ";
                getline (cin, gender);

                tambahCust(nama,umur,gender,no,alamat);
                simpanCustomer();

                cout << "Pelanggan berhasil didaftarkan\n" ;
                system("pause");
                break;
            }

            case 3 :
                dataCust();
                break;

            case 4 :
                semuaDataCust();
                break;
            
            default :
                cout << "pilihan tidak valid\n";
        }
    }
    while (pilih !=5);
}

// PROGRAM UTAMA

int main() {

    loadCustomer();
    loadAntrian();
    loadHistory();

    string menu;

    do {
        cout << "\n====== Welcome To Lognuts ======\n";
        cout << "1. Antrian Servis\n";
        cout << "2. Riwayat Servis anda\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";
        cin >> menu;

        if(menu == "adminacces8008"){
            menuAdmin();
            continue;
        }

        else if (menu == "1"){
            dataSS();
        }

        else if (menu == "2"){
            riwayatServis();
        }

        else if (menu == "3"){
            break ;
        }
        
        else{
            cout << "pilihan tidak valid \n";
        }

    } while(true);

    return 0;
}