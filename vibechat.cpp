#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

//! Global Variabel ===>
string nama_login;     // Pengguna yang sedang login
string nomor_login;    // Nomor pengguna yang sedang login
//! <=== Global Variabel

//! <=== Prototype Function
void garis();
void sign_up();
bool login();
void display_menu(string nama);
void fitur_profile();
void fitur_chat();
void tampilkan_chat(string nomor_tujuan);
void fitur_kontak();
void pesan_favorite(string nomor_tujuan);
void favorit();
void tampilkan_menu_horizontal(string menu_items[], int jumlah_menu, int selected);
//! Prototype Function ===>

//! <=== Struct
struct User{
    string no_hp;
    string nama;
    string pin;
    string tentang;
};
User users[100]; // Array untuk menyimpan data pengguna
int jumlah_user = 4;   // Jumlah pengguna saat ini

struct Message{
    string pengirim;  // Nomor pengirim
    string penerima;  // Nomor penerima
    string isi_pesan; // Isi pesan
    time_t waktu;     // Waktu kirim
};
Message messagess[1000]; // Array untuk menyimpan semua pesan
int jumlah_pesan = 0;  // Jumlah pesan saat ini

struct Contact{
    string nomor;       // Nomor yang disimpan
    string nama_kontak; // Nama kontak yang disimpan
    string pemilik;     // Nomor pemilik kontak
};
Contact contacts[100]; // Array untuk menyimpan kontak
int jumlah_kontak = 0; // Jumlah kontak tersimpan

struct Favorite {
    string nomor_pengirim;  // Nomor pengirim pesan favorit
    string isi_pesan;       // Isi pesan favorit
    time_t waktu;           // Waktu pesan dikirim
    string pemilik;         // Nomor pemilik favorit (user yang menyimpan)
};
Favorite favorites[1000];   // Array untuk menyimpan pesan favorit
int jumlah_favorite = 0;    // Jumlah pesan favorit saat ini

//! Struct ===>


//! <=== Function
void tampilan_header(){
    garis();
    cout << "| \033[1;36m____    ____  __  .______    _______      ______  __    __       ___   .___________.\033[0m |" << endl;
    cout << "| \033[1;36m\\   \\  /   / |  | |   _  \\  |   ____|    /      ||  |  |  |     /   \\  |           |\033[0m |" << endl;
    cout << "|  \033[1;36m\\   \\/   /  |  | |  |_)  | |  |__      |  ,----'|  |__|  |    /  ^  \\ `---|  |----`\033[0m |" << endl;
    cout << "|   \033[1;36m\\      /   |  | |   _  <  |   __|     |  |     |   __   |   /  /_\\  \\    |  |\033[0m      |" << endl;
    cout << "|    \033[1;36m\\    /    |  | |  |_)  | |  |____    |  `----.|  |  |  |  /  _____  \\   |  |\033[0m      |" << endl;
    cout << "|     \033[1;36m\\__/     |__| |______/  |_______|    \\______||__|  |__| /__/     \\__\\  |__|\033[0m      |" << endl;
    cout << "|                                                                                      |" << endl;
    garis();
}

void garis(){
    for (int i = 0; i <= 86; i++)
    {
        cout << ((i == 0) ? " " : "=");
    }
    cout << endl;
}

// Fungsi untuk menghitung panjang string tanpa kode warna ANSI
int panjang_tanpa_warna(string teks){
    int panjang = 0;
    for (int i = 0; i < teks.length(); ++i){
        if (teks[i] == '\x1b' && i + 1 < teks.length() && teks[i + 1] == '['){
            i += 2;
            while (i < teks.length() && teks[i] != 'm')
                i++;
        }
        else{
            panjang++;
        }
    }
    return panjang;
}

// Fungsi untuk menampilkan teks dengan spasi di kiri dan kanan
void spasi(string teks, int lebar, bool selected, bool newline){
    int panjang_teks = panjang_tanpa_warna(teks); // Gunakan panjang tanpa kode warna
    int sisa = lebar - panjang_teks;
    int spasi_kiri = sisa / 2;
    int spasi_kanan = sisa - spasi_kiri;

    cout << "|";
    if (selected){
        cout << "\033[1;36m"; // Warna magenta terang untuk opsi yang dipilih
    }
    for (int i = 0; i < spasi_kiri; i++){
        cout << " ";
    }
    cout << teks;
    for (int i = 0; i < spasi_kanan; i++){
        cout << " ";
    }
    if (selected){
        cout << "\033[0m"; // Reset warna
    }
    cout << "|";
    if (newline){
        cout << endl;
    }
}

// Fungsi untuk menampilkan teks dengan spasi di kiri dan kanan
void rata_kiri(string teks, int lebar){
    int panjang_teks = panjang_tanpa_warna(teks); // Gunakan panjang tanpa kode warna
    int spasi_kanan = lebar - panjang_teks - 2;   // -2 untuk "| " di awal
    cout << "| " << teks;
    for (int i = 0; i < spasi_kanan; i++){
        cout << " ";
    }
    cout << " |";
    cout << endl;
}

void rata_kanan(string teks, int lebar){
    int panjang_teks = panjang_tanpa_warna(teks); // Gunakan panjang tanpa kode warna
    int spasi_kiri = lebar - panjang_teks - 2;    // -2 untuk " |" di akhir
    cout << "|";
    for (int i = 0; i < spasi_kiri; i++){
        cout << " ";
    }
    cout << " " << teks << " |";
    cout << endl;
}

// Fungsi untuk memecah teks menjadi beberapa baris dengan batas karakter
// Mengembalikan jumlah baris yang dihasilkan
int pecah_teks(string teks, string hasil_baris[], int batas_karakter = 40) {
    int jumlah_baris = 0;
    string baris_sekarang = "";
    string kata = "";
    
    for (int i = 0; i <= teks.length(); i++) {
        // Jika menemui spasi atau akhir string
        if (i == teks.length() || teks[i] == ' ') {
            // Jika ini bukan akhir string dan bukan spasi, tambahkan karakter ke kata
            if (i < teks.length() && teks[i] != ' ') {
                kata += teks[i];
            }
            
            // Cek apakah kata bisa ditambahkan ke baris sekarang
            if (baris_sekarang.length() == 0) {
                baris_sekarang = kata;
            } else if (baris_sekarang.length() + 1 + kata.length() <= batas_karakter) {
                baris_sekarang += " " + kata;
            } else {
                // Simpan baris sekarang dan mulai baris baru
                hasil_baris[jumlah_baris] = baris_sekarang;
                jumlah_baris++;
                baris_sekarang = kata;
            }
            kata = "";
        } else {
            kata += teks[i];
        }
    }
    
    // Tambahkan baris terakhir jika tidak kosong
    if (baris_sekarang.length() > 0) {
        hasil_baris[jumlah_baris] = baris_sekarang;
        jumlah_baris++;
    }
    
    return jumlah_baris;
}

// Fungsi rata kiri dengan word wrap
void rata_kiri_wrap(string teks, int lebar, int batas_karakter = 40) {
    string baris_teks[50]; // Array untuk menyimpan baris-baris hasil pemecahan
    int jumlah_baris = pecah_teks(teks, baris_teks, batas_karakter);
    
    for (int i = 0; i < jumlah_baris; i++) {
        int panjang_teks = panjang_tanpa_warna(baris_teks[i]);
        int spasi_kanan = lebar - panjang_teks - 2;
        cout << "| \033[34m" << baris_teks[i] << "\033[0m";
        for (int j = 0; j < spasi_kanan; j++) {
            cout << " ";
        }
        cout << " |" << endl;
    }
}

// Fungsi rata kanan dengan word wrap
void rata_kanan_wrap(string teks, int lebar, int batas_karakter = 40) {
    string baris_teks[50]; // Array untuk menyimpan baris-baris hasil pemecahan
    int jumlah_baris = pecah_teks(teks, baris_teks, batas_karakter);
    
    for (int i = 0; i < jumlah_baris; i++) {
        int panjang_teks = panjang_tanpa_warna(baris_teks[i]);
        int spasi_kiri = lebar - panjang_teks - 2;
        cout << "|";
        for (int j = 0; j < spasi_kiri; j++) {
            cout << " ";
        }
        cout << " \033[32m" << baris_teks[i] << "\033[0m |" << endl;
    }
}

// Menu awal
void menu_awal(){
    string daftar[] = {"Sign Up", "Login", "Exit"};
    int jumlah = 3;
    int option = 1;
    char key;

    while (true){
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        for (int i = 0; i < jumlah; i++){
            spasi("========================", 86, false, true);
            bool aktif = (option == i + 1);
            spasi(daftar[i], 86, aktif, true);
            spasi("========================", 86, false, true);
        }
        garis();

        key = getch();
        bool enter = false;
        switch (key){
        case 'w':
            option = (option > 1) ? option - 1 : jumlah;
            break;
        case 's':
            option = (option < jumlah) ? option + 1 : 1;
            break;
        case 13:
            enter = true;
            break;
        }

        if (enter){
            if (daftar[option - 1] == "Exit"){
                cout << "Exiting...\n";
                exit(0);
            }
            else if (daftar[option - 1] == "Sign Up"){
                sign_up();
            }
            else if (daftar[option - 1] == "Login"){
                login();
            }
        }
    }
}

// SIGN UP
void sign_up(){
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    spasi("SIGN UP", 86, false, true);
    garis();
    if (jumlah_user >= 100){
        cout << "Maaf, jumlah pengguna sudah mencapai batas maksimum.\n";
        system("pause");
        return;
    }
    string no_hp, pin, nama, tentang;
    bool no_hp_valid;
    bool pin_valid;

    do{
        no_hp_valid = true;
        cout << "Masukkan Nomor HP : ";
        getline(cin, no_hp);

        if (no_hp.substr(0, 2) != "08") {
            cout << "Nomor HP harus diawali dengan 08\n";
            no_hp_valid = false;
            continue;
        }
        for (int i = 0; i < jumlah_user; i++){
            if (users[i].no_hp == no_hp){
                no_hp_valid = false;
                cout << "Nomor HP sudah terdaftar\n";
                break;
            }
        }
    } while (!no_hp_valid);

    do{
        pin_valid = true;
	    cout << "Masukkan PIN (4 digit): ";
    	getline(cin, pin);
    	
    	if (pin.length() < 4){
    		cout << "PIN terlalu pendek\n";
    		pin_valid = false;
    		continue;
		}
    } while (!pin_valid);
    
    cout << "Masukkan Nama: ";
    getline(cin, nama);
    cout << "Masukkan Tentang Anda: ";
    getline(cin, tentang);

    User *ptr_user = &users[jumlah_user];
    ptr_user->no_hp = no_hp;
    ptr_user->pin = pin;
    ptr_user->nama = nama;
    ptr_user->tentang = tentang;
    jumlah_user++;
    cout << "\nSign Up Berhasil!\n";
    system("pause");
}

// LOGIN
bool login(){
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    spasi("LOGIN", 86, false, true);
    garis();
    string no_hp;
    string pin;
    cout << "Masukkan Nomor HP: ";
    getline(cin, no_hp);
    cout << "Masukkan PIN: ";
    getline(cin, pin);
    for (int i = 0; i < jumlah_user; i++){
        if (users[i].no_hp == no_hp && users[i].pin == pin){
            nama_login = users[i].nama;
            nomor_login = users[i].no_hp;
            cout << "\nLogin Berhasil!\n";
            system("pause");
            display_menu(nama_login);
            return true;
        }
    }
    cout << "\nNomor HP atau PIN salah!\n";
    system("pause");
    return false;
}

// MENU LOGIN
void display_menu(string nama){
    string daftar[] = {"PROFILE", "ROOM CHAT", "KONTAK", "FAVORIT", "LOGOUT"};
    int jumlah = 5;
    int option = 1;
    char key;

    while (true){
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        spasi("WELCOME " + nama, 86, false, true);
        garis();
        for (int i = 0; i < jumlah; i++){
            spasi("========================", 86, false, true);
            bool aktif = (option == i + 1);
            spasi(daftar[i], 86, aktif, true);
        }
        spasi("========================", 86, false, true);
        garis();

        key = getch();
        bool enter = false;
        switch (key){
        case 'w':
            option = (option > 1) ? option - 1 : jumlah;
            break;
        case 's':
            option = (option < jumlah) ? option + 1 : 1;
            break;
        case 13:
            enter = true;
            break;
        }

        if (enter){
            if (daftar[option - 1] == "LOGOUT"){
                nama_login = "";
                nomor_login = "";
                return;
            }
            else if (daftar[option - 1] == "PROFILE"){
                fitur_profile();
            }
            else if (daftar[option - 1] == "ROOM CHAT"){
                fitur_chat();
            }
            else if (daftar[option - 1] == "KONTAK"){
                fitur_kontak();
            }
            else if (daftar[option - 1] == "FAVORIT"){
                favorit();
                system("pause");
            }
        }
    }
}

void fitur_profile(){
    system("cls");
    tampilan_header();
    garis();
    spasi("PROFILE", 86, false, true);
    garis();
    
    int index = -1;
    for(int i = 0; i < jumlah_user; i++){
        if (users[i].nama == nama_login){
            index = i;
            break;
        }
    }
    if(index == -1){
        cout << "Pengguna tidak ditemukan!\n";
        system("pause");
        return;
    }
    User *user = &users[index];
    rata_kiri("No HP   : " + user->no_hp, 86);
    rata_kiri("Nama    : " + user->nama, 86);
    rata_kiri("PIN     : " + user->pin, 86);
    rata_kiri("Tentang : " + user->tentang, 86);
    garis();
    rata_kiri("1. Edit Profile", 86);
    rata_kiri("0. Kembali", 86);
    cout << "Masukkan pilihan (1 atau 0): ";
    int pilih;
    cin >> pilih;
    cin.ignore();
    
    if (pilih == 0){
        return;
    } else if(pilih == 1){
        system("cls");
        tampilan_header();
        garis();
        rata_kiri("1. Nomor HP : " + user->no_hp, 86);
        rata_kiri("2. Nama     : " + user->nama, 86);
        rata_kiri("3. PIN      : " + user->pin, 86);
        rata_kiri("4. Tentang  : " + user->tentang, 86);
        rata_kiri("0. Kembali", 86);
        garis();
        rata_kiri("Pilih data yang ingin diubah (0-4): ", 86);
        int pilihan;
        cin >> pilihan;
        cin.ignore();
        if (pilihan == 0){
            return;
        } else if (pilihan == 1){
            string no_baru;
            bool valid = true;
            do{
                valid = true;
                cout << "Masukkan Nomor HP Baru: ";
                getline(cin, no_baru);
                for (int i = 0; i < jumlah_user; i++){
                    if(i != index && users[i].no_hp == no_baru){
                        valid = false;
                        cout << "Nomor HP sudah terdaftar!\n";
                        break;
                    }
                }
            } while(!valid);
            user->no_hp = no_baru;
            cout << "Nomor HP berhasil diperbarui!\n";
        } else if (pilihan == 2){
            cout << "Masukkan Nama Baru: ";
            getline(cin, user->nama);
            nama_login = user->nama;
            cout << "Nama berhasil diperbarui!\n";
        } else if (pilihan == 3){
            bool pin_valid;
            do{
                pin_valid = true;
	            cout << "Masukkan PIN Baru (4 digit): ";
                getline(cin, user->pin);
                
                if (user->pin.length() < 4){
                    cout << "PIN terlalu pendek\n";
                    pin_valid = false;
                    continue;
                }
            } while (!pin_valid);
            cout << "PIN berhasil diperbarui!\n";
        } else if (pilihan == 4){
            cout << "Masukkan Tentang Baru: ";
            getline(cin, user->tentang);
            cout << "Tentang berhasil diperbarui!\n";
            return;
        } else {
            cout << "Pilihan tidak valid!\n";
            system("pause");  
        }  
    }else{
        cout << "Pilihan tidak valid!\n";
        system("pause");
    }       
}

// Fungsi untuk mencari user berdasarkan nomor
bool cari_user_by_nomor(string nomor){
    for (int i = 0; i < jumlah_user; i++){
        if (users[i].no_hp == nomor){
            return true;
        }
    }
    return false;
}

// Fungsi untuk mendapatkan nama kontak berdasarkan nomor
string get_nama_kontak(string nomor){
    for (int i = 0; i < jumlah_kontak; i++){
        if (contacts[i].nomor == nomor && contacts[i].pemilik == nomor_login){
            return contacts[i].nama_kontak;
        }
    }
    return nomor;
}

// Fungsi untuk menyimpan kontak
void simpan_kontak(string nomor, string nama_kontak){
    if (jumlah_kontak < 100){
        Contact *ptr_contact = &contacts[jumlah_kontak];
        ptr_contact->nomor = nomor;
        ptr_contact->nama_kontak = nama_kontak;
        ptr_contact->pemilik = nomor_login;
        jumlah_kontak++;
    }
}

// Fungsi untuk menampilkan profile
void tampilkan_profile(string nomor){
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    spasi("Profile (" + nomor + ")", 86, false, true);
    garis();

    for (int i = 0; i < jumlah_user; i++){
        if (users[i].no_hp == nomor){
            rata_kiri("No      : " + users[i].no_hp, 86);
            rata_kiri("Nama    : " + users[i].nama, 86);
            rata_kiri("Tentang : " + users[i].tentang, 86);
            break;
        }
    }
    garis();
    rata_kiri("1. Save Kontak", 86);
    rata_kiri("0. Kembali", 86);
    garis();

    char pilihan;
    cout << ">> ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == '1'){
        string nama_kontak;
        cout << "Save dengan: ";
        getline(cin, nama_kontak);
        simpan_kontak(nomor, nama_kontak);
        cout << "Kontak berhasil disimpan!\n";
        system("pause");
    }
}

// Fungsi untuk mengirim pesan
void kirim_pesan(string pengirim, string penerima, string pesan){
    if (jumlah_pesan < 1000){
        Message *ptr_message = &messagess[jumlah_pesan];
        ptr_message->pengirim = pengirim;
        ptr_message->penerima = penerima;
        ptr_message->isi_pesan = pesan;
        ptr_message->waktu = time(0);
        jumlah_pesan++;
    }
}

// Fungsi untuk menampilkan chat
void tampilkan_chat(string nomor_tujuan){
    string daftar[] = {"PROFILE", "CHAT/BALAS", "FAVORIT", "KEMBALI"};
    int jumlah = 4;
    int option = 1;
    while (true){
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        string nama_display = get_nama_kontak(nomor_tujuan);
        spasi(nama_display, 86, false, true);
        garis();
        
        bool ada_chat = false;
        for (int i = 0; i < jumlah_pesan; i++){
            Message *ptr_msg = &messagess[i];
            if ((ptr_msg->pengirim == nomor_login && ptr_msg->penerima == nomor_tujuan) ||
                (ptr_msg->pengirim == nomor_tujuan && ptr_msg->penerima == nomor_login)){
                ada_chat = true;
                string waktu_str = ctime(&ptr_msg->waktu);
                waktu_str.erase(waktu_str.length() - 1); // Remove newline
                if (ptr_msg->pengirim == nomor_login){
                    rata_kanan("----------------------------------------", 86);
                    rata_kanan("\033[2m" + waktu_str + "\033[0m", 86);
                    rata_kanan_wrap(ptr_msg->isi_pesan, 86, 40); //  fungsi wrap
                    rata_kanan("----------------------------------------", 86);
                }
                else{
                    rata_kiri("----------------------------------------", 86);
                    rata_kiri("\033[2m" + waktu_str + "\033[0m", 86);
                    rata_kiri_wrap(ptr_msg->isi_pesan, 86, 40); //  fungsi wrap
                    rata_kiri("----------------------------------------", 86);
                }
            }
        }

        if (!ada_chat){
            spasi("Belum ada pesan", 86, false, true);
        }
        tampilkan_menu_horizontal(daftar, jumlah, option);
        char key = getch();
        bool enter = false;
        switch (key){
        case 'a':
            option = (option > 1) ? option - 1 : jumlah;
            break;
        case 'd':
            option = (option < jumlah) ? option + 1 : 1;
            break;
        case 13:
            enter = true;
            break;
        }

        if (enter){
            if (daftar[option - 1] == "KEMBALI"){
                break;
            }
            else if (daftar[option - 1] == "PROFILE"){
                tampilkan_profile(nomor_tujuan);
            }
            else if (daftar[option - 1] == "CHAT/BALAS"){
                system("cls");
                cout << "\033[36m" << tanggal << "\033[0m" << endl;
                tampilan_header();
                garis();
                spasi(nama_display, 86, false, true);
                garis();
                string pesan;
                if(!ada_chat){
                    cout << "Chat dengan: ";
                }else{
                    cout << "Balas dengan: ";
                }
                getline(cin, pesan);
                kirim_pesan(nomor_login, nomor_tujuan, pesan);
                cout << "Pesan terkirim!\n";
                system("pause");
            }
            else if(daftar[option - 1] == "FAVORIT"){
                pesan_favorite(nomor_tujuan);
            }
        }
    }
}

// FITUR CHAT
void fitur_chat(){
    while(true){
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        spasi("CHAT", 86, false, true);
        garis();

        string nomor_chat[100];
        int jumlah_chat = 0;
        
        for (int i = 0; i < jumlah_pesan; i++){
            Message *ptr_msg = &messagess[i];
            if (ptr_msg->pengirim == nomor_login || ptr_msg->penerima == nomor_login){
                string nomor_tujuan = (ptr_msg->pengirim == nomor_login) ? ptr_msg->penerima : ptr_msg->pengirim;
                
                bool sudah_ada = false;
                for(int j = 0; j < jumlah_chat; j++){
                    if(nomor_chat[j] == nomor_tujuan){
                        sudah_ada = true;
                        break;
                    }
                }
                
                if(!sudah_ada && jumlah_chat < 100){
                    nomor_chat[jumlah_chat] = nomor_tujuan;
                    jumlah_chat++;
                }
            }
        }

        string daftar_menu[102];
        int total_menu = 0;
        
        for(int i = 0; i < jumlah_chat; i++){
            string nama_kontak = get_nama_kontak(nomor_chat[i]);
            if(nama_kontak == nomor_chat[i]){
                daftar_menu[total_menu] = nomor_chat[i];
            } else {
                daftar_menu[total_menu] = nama_kontak;
            }
            total_menu++;
        }
        
        daftar_menu[total_menu] = "Chat Nomor Baru";
        total_menu++;
        daftar_menu[total_menu] = "Kembali";
        total_menu++;

        int option = 1;
        char key;
        
        while(true){
            system("cls");
            time_t now = time(0);
            string tanggal = string(ctime(&now));
            cout << "\033[36m" << tanggal << "\033[0m" << endl;
            tampilan_header();
            garis();
            spasi("CHAT", 86, false, true);
            garis();
            
            if(jumlah_chat == 0){
                spasi("Belum ada chat sebelumnya", 86, false, true);
            } else {
                for(int i = 0; i < jumlah_chat; i++){
                    spasi("========================", 86, false, true);
                    bool aktif = (option == i + 1);
                    spasi("( " + daftar_menu[i] + " )", 86, aktif, true);
                    spasi("========================", 86, false, true);
                }
            }
            garis();
            spasi("========================", 86, false, true);
            bool aktif_baru = (option == jumlah_chat + 1);
            spasi("Chat Nomor Baru", 86, aktif_baru, true);
            spasi("========================", 86, false, true);
            
            spasi("========================", 86, false, true);
            bool aktif_kembali = (option == jumlah_chat + 2);
            spasi("Kembali", 86, aktif_kembali, true);
            spasi("========================", 86, false, true);
            
            garis();

            key = getch();
            bool enter = false;
            switch (key){
            case 'w':
                option = (option > 1) ? option - 1 : total_menu;
                break;
            case 's':
                option = (option < total_menu) ? option + 1 : 1;
                break;
            case 13:
                enter = true;
                break;
            }

            if (enter){
                if (option == total_menu){
                    return;
                }
                else if (option == total_menu - 1){
                    system("cls");
                    time_t now = time(0);
                    string tanggal = string(ctime(&now));
                    cout << "\033[36m" << tanggal << "\033[0m" << endl;
                    tampilan_header();
                    garis();
                    spasi("CHAT NOMOR BARU", 86, false, true);
                    garis();
                    
                    string nomor_tujuan;
                    cout << "Masukkan nomor yang ingin di chat: ";
                    getline(cin, nomor_tujuan);

                    if (!cari_user_by_nomor(nomor_tujuan)){
                        cout << "Nomor tidak terdaftar di vibe chat\n";
                        system("pause");
                        continue;
                    }

                    if (nomor_tujuan == nomor_login){
                        cout << "Tidak bisa chat dengan diri sendiri\n";
                        system("pause");
                        continue;
                    }
                    
                    tampilkan_chat(nomor_tujuan);
                    break;
                }
                else {
                    string nomor_terpilih = nomor_chat[option - 1];
                    tampilkan_chat(nomor_terpilih);
                    break;
                }
            }
        }
    }
}

// Fungsi untuk menghapus kontak
void hapus_kontak(string nama_kontak){
    bool ada = false;
    for (int i = 0; i < jumlah_kontak; i++){
        if (contacts[i].nama_kontak == nama_kontak && contacts[i].pemilik == nomor_login){
            ada = true;
            for (int j = i; j < jumlah_kontak - 1; j++){
                Contact *ptr_current = &contacts[j];
                Contact *ptr_next = &contacts[j + 1];
                ptr_current->nomor = ptr_next->nomor;
                ptr_current->nama_kontak = ptr_next->nama_kontak;
                ptr_current->pemilik = ptr_next->pemilik;
            }
            jumlah_kontak--;
            cout << "Kontak '" << nama_kontak << "' berhasil dihapus!\n";
            break;
        }
    }
    if (!ada){
        cout << "Kontak '" << nama_kontak << "' tidak ditemukan!\n";
    }
    system("pause");
}

// FITUR KONTAK
void fitur_kontak(){
    while (true){
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        spasi("DAFTAR KONTAK", 86, false, true);
        garis();

        bool ada_kontak = false;
        for (int i = 0; i < jumlah_kontak; i++){
            if (contacts[i].pemilik == nomor_login){
                ada_kontak = true;
                string tampilan = contacts[i].nama_kontak + " (" + contacts[i].nomor + ")";
                rata_kiri(tampilan, 86);
            }
        }

        if (!ada_kontak){
            spasi("Belum ada kontak tersimpan", 86, false, true);
        }

        garis();
        rata_kiri("1. Hapus kontak", 86);
        rata_kiri("0. Kembali", 86);
        garis();

        char pilihan;
        cout << ">> ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == '1'){
            if (!ada_kontak){
                cout << "Tidak ada kontak untuk dihapus!\n";
                system("pause");
                continue;
            }

            string nama_kontak;
            cout << "Masukkan nama kontak yang ingin dihapus: ";
            getline(cin, nama_kontak);
            hapus_kontak(nama_kontak);
        }
        else if (pilihan == '0'){
            break;
        }
    }
}

void pesan_favorite(string nomor_tujuan) {
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    
    bool ada_pesan = false;
    int counter = 1;
    int indeks_pesan[1000];
    
    spasi("PILIH PESAN UNTUK DISIMPAN KE FAVORIT", 86, false, true);
    garis();
    
    for (int i = 0; i < jumlah_pesan; i++) {
        if ((messagess[i].pengirim == nomor_tujuan && messagess[i].penerima == nomor_login) ||
            (messagess[i].pengirim == nomor_login && messagess[i].penerima == nomor_tujuan)) {
            ada_pesan = true;
            indeks_pesan[counter] = i;
            
            string waktu_str = ctime(&messagess[i].waktu);
            waktu_str.erase(waktu_str.length() - 1); // Remove newline
            
            
            cout << counter << ". ";
            if (messagess[i].pengirim == nomor_login) {
                cout << "Anda: ";
            } else {
                cout << get_nama_kontak(nomor_tujuan) << ": ";
            }
            cout << "[" << waktu_str << "] ";
            cout << messagess[i].isi_pesan << endl;
            
            counter++;
        }
    }
    
    if (!ada_pesan) {
        cout << "Tidak ada pesan dengan kontak ini.\n";
        system("pause");
        return;
    }
    
    garis();
    cout << "Masukkan nomor pesan yang ingin difavoritkan (0 untuk batal): ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    if (pilihan > 0 && pilihan < counter) {
        int idx_pesan = indeks_pesan[pilihan];
        
        bool sudah_ada = false;
        for (int i = 0; i < jumlah_favorite; i++) {
            if (favorites[i].nomor_pengirim == messagess[idx_pesan].pengirim &&
                favorites[i].isi_pesan == messagess[idx_pesan].isi_pesan &&
                favorites[i].pemilik == nomor_login) {
                sudah_ada = true;
                break;
            }
        }
        
        if (!sudah_ada) {
            if (jumlah_favorite < 1000) {
                favorites[jumlah_favorite].nomor_pengirim = messagess[idx_pesan].pengirim;
                favorites[jumlah_favorite].isi_pesan = messagess[idx_pesan].isi_pesan;
                favorites[jumlah_favorite].waktu = messagess[idx_pesan].waktu;
                favorites[jumlah_favorite].pemilik = nomor_login;
                jumlah_favorite++;
                cout << "Pesan berhasil disimpan ke favorit!\n";
            } else {
                cout << "Maaf, kapasitas favorit penuh.\n";
            }
        } else {
            cout << "Pesan ini sudah ada di favorit.\n";
        }
        system("pause");
    }
}

void favorit() {
    while (true) {
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        spasi("PESAN FAVORIT", 86, false, true);
        garis();
        
        bool ada_favorite = false;
        for (int i = 0; i < jumlah_favorite; i++) {
            if (favorites[i].pemilik == nomor_login) {
                ada_favorite = true;
                
                string waktu_str = ctime(&favorites[i].waktu);
                waktu_str.erase(waktu_str.length() - 1); // Remove newline
                
                string show_name;
                if (favorites[i].nomor_pengirim == nomor_login) {
                    show_name = "Anda";
                } else {
                    show_name = get_nama_kontak(favorites[i].nomor_pengirim);
                }
                
                cout << "[" << waktu_str << "] ";
                cout << show_name << " (" << favorites[i].nomor_pengirim << "):\n";
                cout << "  " << favorites[i].isi_pesan << "\n";
                garis();
            }
        }
        
        if (!ada_favorite) {
            spasi("Belum ada pesan favorit", 86, false, true);
            garis();
        }
        
        rata_kiri("0. Kembali", 86);
        garis();
        char pilihan;
        cout << ">> ";
        cin >> pilihan;
        cin.ignore();
        
        if (pilihan == '0') {
            break;
        }
    }
}

// Fungsi untuk menampilkan menu horizontal
void tampilkan_menu_horizontal(string menu_items[], int jumlah_menu, int selected){
    garis();
    cout << "|";
    
    int lebar_total = 83;
    int lebar_per_item = lebar_total / jumlah_menu;
    int sisa_lebar = lebar_total % jumlah_menu;
    
    for(int i = 0; i < jumlah_menu; i++){
        int lebar_item = lebar_per_item;
        if(i < sisa_lebar) lebar_item++;
        
        int panjang_teks = menu_items[i].length();
        int spasi_kiri = (lebar_item - panjang_teks) / 2;
        int spasi_kanan = lebar_item - panjang_teks - spasi_kiri;
        
        if(selected == i + 1){
            cout << "\033[1;36m";
        }
        
        for(int j = 0; j < spasi_kiri; j++){
            cout << " ";
        }
        
        cout << menu_items[i];
        
        for(int j = 0; j < spasi_kanan; j++){
            cout << " ";
        }
        
        if(selected == i + 1){
            cout << "\033[0m";
        }
        
        if(i < jumlah_menu - 1){
            cout << "|";
        }
    }
    cout << "|" << endl;
    garis();
}
//! Function ===>

int main(){
    users[0].no_hp = "081938668095";
    users[0].nama = "Chiz";
    users[0].pin = "chiz123";
    users[0].tentang = "Christian Hadi Candra";
    users[1].no_hp = "085337848171";
    users[1].nama = "Liya";
    users[1].pin = "liya123";
    users[1].tentang = ".";
    users[2].no_hp = "085180687523";
    users[2].nama = "Jeje";
    users[2].pin = "jeje123";
    users[2].tentang = "Tidak dapat bicara, VibeChat saja";
    users[3].no_hp = "082293100170";
    users[3].nama = "Fatio";
    users[3].pin = "tio123";
    users[3].tentang = "@mfs.fito";
    menu_awal();
    return 0;
}