#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

//! <=== Global Variabel
string nama_login;     // Pengguna yang sedang login
string nomor_login;    // Nomor pengguna yang sedang login
//! Global Variabel ===>

//! <=== Struct
struct User {
    string no_hp;
    string nama;
    string pin;
    string tentang;
};
User users[100]; // Array untuk menyimpan data pengguna
int jumlah_user = 4;   // Jumlah pengguna saat ini

struct Message {
    string pengirim;  // Nomor pengirim
    string penerima;  // Nomor penerima
    string isi_pesan; // Isi pesan
    time_t waktu;     // Waktu kirim
};
Message messagess[1000]; // Array untuk menyimpan semua pesan
int jumlah_pesan = 0;  // Jumlah pesan saat ini

struct Contact {
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

//! <=== Prototype Function
void garis();
void sign_up();
bool login();
void display_menu(string &nama);
void fitur_profile();
void edit_user_profile(User* user);
void tampilkan_chat(string &nomor_tujuan);
void fitur_chat();
void fitur_kontak();
void edit_kontak(Contact* contact);
void pesan_favorite(string &nomor_tujuan);
void favorit();
void hapus_favorite(Favorite* fav, int* index);
void tampilkan_menu_horizontal(string* menu_items, int jumlah_menu, int selected);
//! Prototype Function ===>

//! <=== Function
void tampilan_header() {
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

void garis() {
    for (int i = 0; i <= 86; i++) {
        cout << ((i == 0) ? " " : "=");
    }
    cout << endl;
}

int panjang_tanpa_warna(string &teks) {
    int panjang = 0;
    for (int i = 0; i < teks.length(); ++i) {
        if (teks[i] == '\x1b' && i + 1 < teks.length() && teks[i + 1] == '[') {
            i += 2;
            while (i < teks.length() && teks[i] != 'm')
                i++;
        } else {
            panjang++;
        }
    }
    return panjang;
}

void spasi(string &teks, int lebar, bool selected, bool newline) {
    int panjang_teks = panjang_tanpa_warna(teks);
    int sisa = lebar - panjang_teks;
    int spasi_kiri = sisa / 2;
    int spasi_kanan = sisa - spasi_kiri;

    cout << "|";
    if (selected) {
        cout << "\033[1;36m";
    }
    for (int i = 0; i < spasi_kiri; i++) {
        cout << " ";
    }
    cout << teks;
    for (int i = 0; i < spasi_kanan; i++) {
        cout << " ";
    }
    if (selected) {
        cout << "\033[0m";
    }
    cout << "|";
    if (newline) {
        cout << endl;
    }
}

void rata_kiri(string &teks, int lebar) {
    int panjang_teks = panjang_tanpa_warna(teks);
    int spasi_kanan = lebar - panjang_teks - 2;
    cout << "| " << teks;
    for (int i = 0; i < spasi_kanan; i++) {
        cout << " ";
    }
    cout << " |" << endl;
}

void rata_kanan(string &teks, int lebar) {
    int panjang_teks = panjang_tanpa_warna(teks);
    int spasi_kiri = lebar - panjang_teks - 2;
    cout << "|";
    for (int i = 0; i < spasi_kiri; i++) {
        cout << " ";
    }
    cout << " " << teks << " |" << endl;
}

int pecah_teks(string &teks, string* hasil_baris, int batas_karakter = 40) {
    int jumlah_baris = 0;
    string baris_sekarang = "";
    string kata = "";
    
    for (int i = 0; i <= teks.length(); i++) {
        if (i == teks.length() || teks[i] == ' ') {
            if (i < teks.length() && teks[i] != ' ') {
                kata += teks[i];
            }
            if (baris_sekarang.length() == 0) {
                baris_sekarang = kata;
            } else if (baris_sekarang.length() + 1 + kata.length() <= batas_karakter) {
                baris_sekarang += " " + kata;
            } else {
                hasil_baris[jumlah_baris] = baris_sekarang;
                jumlah_baris++;
                baris_sekarang = kata;
            }
            kata = "";
        } else {
            kata += teks[i];
        }
    }
    
    if (baris_sekarang.length() > 0) {
        hasil_baris[jumlah_baris] = baris_sekarang;
        jumlah_baris++;
    }
    
    return jumlah_baris;
}

void rata_kiri_wrap(string &teks, int lebar, int batas_karakter = 40) {
    string baris_teks[50];
    int jumlah_baris = pecah_teks(teks, baris_teks, batas_karakter);
    
    for (int i = 0; i < jumlah_baris; i++) {
        string &ptr_baris = baris_teks[i];
        int panjang_teks = panjang_tanpa_warna(ptr_baris);
        int spasi_kanan = lebar - panjang_teks - 2;
        cout << "| \033[34m" << ptr_baris << "\033[0m";
        for (int j = 0; j < spasi_kanan; j++) {
            cout << " ";
        }
        cout << " |" << endl;
    }
}

void rata_kanan_wrap(string &teks, int lebar, int batas_karakter = 40) {
    string baris_teks[50];
    int jumlah_baris = pecah_teks(teks, baris_teks, batas_karakter);
    
    for (int i = 0; i < jumlah_baris; i++) {
        string &ptr_baris = baris_teks[i];
        int panjang_teks = panjang_tanpa_warna(ptr_baris);
        int spasi_kiri = lebar - panjang_teks - 2;
        cout << "|";
        for (int j = 0; j < spasi_kiri; j++) {
            cout << " ";
        }
        cout << " \033[32m" << ptr_baris << "\033[0m |" << endl;
    }
}

void menu_awal() {
    string daftar[] = {"Sign Up", "Login", "Exit"};
    int jumlah = 3;
    int option = 1;
    char key;

    while (true) {
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        for (int i = 0; i < jumlah; i++) {
            string separator = "========================";
            spasi(separator, 86, false, true);
            bool aktif = (option == i + 1);
            spasi(daftar[i], 86, aktif, true);
            spasi(separator, 86, false, true);
        }
        garis();

        key = getch();
        bool enter = false;
        switch (key) {
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

        if (enter) {
            if (daftar[option - 1] == "Exit") {
                cout << "Exiting...\n";
                exit(0);
            } else if (daftar[option - 1] == "Sign Up") {
                sign_up();
            } else if (daftar[option - 1] == "Login") {
                login();
            }
        }
    }
}

void sign_up() {
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    string signup_title = "SIGN UP";
    spasi(signup_title, 86, false, true);
    garis();
    if (jumlah_user >= 100) {
        cout << "Maaf, jumlah pengguna sudah mencapai batas maksimum.\n";
        system("pause");
        return;
    }
    string no_hp, pin, nama, tentang;
    bool no_hp_valid;
    bool pin_valid;

    do {
        no_hp_valid = true;
        cout << "Masukkan Nomor HP : ";
        getline(cin, no_hp);
        if (no_hp.substr(0, 2) != "08") {
            cout << "Nomor HP harus diawali dengan 08\n";
            no_hp_valid = false;
            continue;
        }
        for (int i = 0; i < jumlah_user; i++) {
            User *ptr_check = &users[i];
            if (ptr_check->no_hp == no_hp) {
                no_hp_valid = false;
                cout << "Nomor HP sudah terdaftar\n";
                break;
            }
        }
    } while (!no_hp_valid);

    do {
        pin_valid = true;
        cout << "Masukkan PIN (4 digit): ";
        getline(cin, pin);
        if (pin.length() < 4) {
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
    *(&ptr_user->no_hp) = no_hp;
    *(&ptr_user->pin) = pin;
    *(&ptr_user->nama) = nama;
    *(&ptr_user->tentang) = tentang;
    jumlah_user++;
    cout << "\nSign Up Berhasil!\n";
    system("pause");
}

bool login() {
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    string login_title = "LOGIN";
    spasi(login_title, 86, false, true);
    garis();
    string no_hp;
    string pin;
    cout << "Masukkan Nomor HP: ";
    getline(cin, no_hp);
    cout << "Masukkan PIN: ";
    getline(cin, pin);
    for (int i = 0; i < jumlah_user; i++) {
        User *ptr_user = &users[i];
        if (ptr_user->no_hp == no_hp && ptr_user->pin == pin) {
            *(&nama_login) = ptr_user->nama;
            *(&nomor_login) = ptr_user->no_hp;
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

void display_menu(string &nama) {
    string daftar[] = {"PROFILE", "ROOM CHAT", "KONTAK", "FAVORIT", "LOGOUT"};
    int jumlah = 5;
    int option = 1;
    char key;

    while (true) {
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        string welcome = "WELCOME " + nama;
        spasi(welcome, 86, false, true);
        garis();
        for (int i = 0; i < jumlah; i++) {
            string separator = "========================";
            spasi(separator, 86, false, true);
            bool aktif = (option == i + 1);
            spasi(daftar[i], 86, aktif, true);
        }
        string separator = "========================";
        spasi(separator, 86, false, true);
        garis();

        key = getch();
        bool enter = false;
        switch (key) {
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

        if (enter) {
            if (daftar[option - 1] == "LOGOUT") {
                *(&nama_login) = "";
                *(&nomor_login) = "";
                return;
            } else if (daftar[option - 1] == "PROFILE") {
                fitur_profile();
            } else if (daftar[option - 1] == "ROOM CHAT") {
                fitur_chat();
            } else if (daftar[option - 1] == "KONTAK") {
                fitur_kontak();
            } else if (daftar[option - 1] == "FAVORIT") {
                favorit();
                system("pause");
            }
        }
    }
}

void edit_user_profile(User* user) {
    system("cls");
    tampilan_header();
    garis();
    string opt1 = "1. Nomor HP : " + user->no_hp;
    string opt2 = "2. Nama     : " + user->nama;
    string opt3 = "3. PIN      : " + user->pin;
    string opt4 = "4. Tentang  : " + user->tentang;
    string opt0 = "0. Kembali";
    rata_kiri(opt1, 86);
    rata_kiri(opt2, 86);
    rata_kiri(opt3, 86);
    rata_kiri(opt4, 86);
    rata_kiri(opt0, 86);
    garis();
    string prompt = "Pilih data yang ingin diubah (0-4): ";
    rata_kiri(prompt, 86);
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    if (pilihan == 0) {
        return;
    } else if (pilihan == 1) {
        string no_baru;
        bool valid = true;
        do {
            valid = true;
            cout << "Masukkan Nomor HP Baru: ";
            getline(cin, no_baru);
            for (int i = 0; i < jumlah_user; i++) {
                if (users[i].no_hp == no_baru && &users[i] != user) {
                    valid = false;
                    cout << "Nomor HP sudah terdaftar!\n";
                    break;
                }
            }
        } while (!valid);
        *(&user->no_hp) = no_baru;
        *(&nomor_login) = no_baru; // Sinkronkan global
        cout << "Nomor HP berhasil diperbarui!\n";
    } else if (pilihan == 2) {
        cout << "Masukkan Nama Baru: ";
        getline(cin, *(&user->nama));
        *(&nama_login) = user->nama; // Sinkronkan global
        cout << "Nama berhasil diperbarui!\n";
    } else if (pilihan == 3) {
        bool pin_valid;
        do {
            pin_valid = true;
            cout << "Masukkan PIN Baru (4 digit): ";
            getline(cin, *(&user->pin));
            if (user->pin.length() < 4) {
                cout << "PIN terlalu pendek\n";
                pin_valid = false;
            }
        } while (!pin_valid);
        cout << "PIN berhasil diperbarui!\n";
    } else if (pilihan == 4) {
        cout << "Masukkan Tentang Baru: ";
        getline(cin, *(&user->tentang));
        cout << "Tentang berhasil diperbarui!\n";
    } else {
        cout << "Pilihan tidak valid!\n";
    }
    system("pause");
}

void fitur_profile() {
    system("cls");
    tampilan_header();
    garis();
    string profile_title = "PROFILE";
    spasi(profile_title, 86, false, true);
    garis();
    
    int index = -1;
    for (int i = 0; i < jumlah_user; i++) {
        if (users[i].nama == nama_login) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Pengguna tidak ditemukan!\n";
        system("pause");
        return;
    }
    User* user = &users[index];
    string no_hp_info = "No HP   : " + user->no_hp;
    string nama_info = "Nama    : " + user->nama;
    string pin_info = "PIN     : " + user->pin;
    string tentang_info = "Tentang : " + user->tentang;
    rata_kiri(no_hp_info, 86);
    rata_kiri(nama_info, 86);
    rata_kiri(pin_info, 86);
    rata_kiri(tentang_info, 86);
    garis();
    string edit_menu = "1. Edit Profile";
    string back_menu = "0. Kembali";
    rata_kiri(edit_menu, 86);
    rata_kiri(back_menu, 86);
    cout << "Masukkan pilihan (1 atau 0): ";
    int pilih;
    cin >> pilih;
    cin.ignore();
    
    if (pilih == 0) {
        return;
    } else if (pilih == 1) {
        edit_user_profile(user);
    } else {
        cout << "Pilihan tidak valid!\n";
        system("pause");
    }
}

bool cari_user_by_nomor(string &nomor) {
    for (int i = 0; i < jumlah_user; i++) {
        User *ptr_user = &users[i];
        if (ptr_user->no_hp == nomor) {
            return true;
        }
    }
    return false;
}

string get_nama_kontak(string &nomor) {
    for (int i = 0; i < jumlah_kontak; i++) {
        Contact *ptr_contact = &contacts[i];
        if (ptr_contact->nomor == nomor && ptr_contact->pemilik == nomor_login) {
            return ptr_contact->nama_kontak;
        }
    }
    return nomor;
}

void simpan_kontak(string &nomor, string &nama_kontak) {
    if (jumlah_kontak < 100) {
        Contact *ptr_contact = &contacts[jumlah_kontak];
        *(&ptr_contact->nomor) = nomor;
        *(&ptr_contact->nama_kontak) = nama_kontak;
        *(&ptr_contact->pemilik) = nomor_login;
        jumlah_kontak++;
    }
}

void tampilkan_profile(string &nomor) {
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    string profile_title = "Profile (" + nomor + ")";
    spasi(profile_title, 86, false, true);
    garis();

    for (int i = 0; i < jumlah_user; i++) {
        User *ptr_user = &users[i];
        if (ptr_user->no_hp == nomor) {
            string no_info = "No      : " + ptr_user->no_hp;
            string nama_info = "Nama    : " + ptr_user->nama;
            string tentang_info = "Tentang : " + ptr_user->tentang;
            rata_kiri(no_info, 86);
            rata_kiri(nama_info, 86);
            rata_kiri(tentang_info, 86);
            break;
        }
    }
    garis();
    string save_menu = "1. Save Kontak";
    string back_menu = "0. Kembali";
    rata_kiri(save_menu, 86);
    rata_kiri(back_menu, 86);
    garis();

    char pilihan;
    cout << ">> ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == '1') {
        string nama_kontak;
        cout << "Save dengan: ";
        getline(cin, nama_kontak);
        simpan_kontak(nomor, nama_kontak);
        cout << "Kontak berhasil disimpan!\n";
        system("pause");
    }
}

void kirim_pesan(string &pengirim, string &penerima, string &pesan) {
    if (jumlah_pesan < 1000) {
        Message *ptr_message = &messagess[jumlah_pesan];
        *(&ptr_message->pengirim) = pengirim;
        *(&ptr_message->penerima) = penerima;
        *(&ptr_message->isi_pesan) = pesan;
        *(&ptr_message->waktu) = time(0);
        jumlah_pesan++;
    }
}

void tampilkan_chat(string &nomor_tujuan) {
    string daftar[] = {"PROFILE", "CHAT/BALAS", "FAVORIT", "KEMBALI"};
    int jumlah = 4;
    int option = 1;
    while (true) {
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
        for (int i = 0; i < jumlah_pesan; i++) {
            Message *ptr_msg = &messagess[i];
            if ((ptr_msg->pengirim == nomor_login && ptr_msg->penerima == nomor_tujuan) ||
                (ptr_msg->pengirim == nomor_tujuan && ptr_msg->penerima == nomor_login)) {
                ada_chat = true;
                string waktu_str = ctime(&ptr_msg->waktu);
                waktu_str.erase(waktu_str.length() - 1);
                if (ptr_msg->pengirim == nomor_login) {
                    string separator = "----------------------------------------";
                    rata_kanan(separator, 86);
                    string waktu_info = "\033[2m" + waktu_str + "\033[0m";
                    rata_kanan(waktu_info, 86);
                    rata_kanan_wrap(ptr_msg->isi_pesan, 86, 40);
                    rata_kanan(separator, 86);
                } else {
                    string separator = "----------------------------------------";
                    rata_kiri(separator, 86);
                    string waktu_info = "\033[2m" + waktu_str + "\033[0m";
                    rata_kiri(waktu_info, 86);
                    rata_kiri_wrap(ptr_msg->isi_pesan, 86, 40);
                    rata_kiri(separator, 86);
                }
            }
        }

        if (!ada_chat) {
            string no_message = "Belum ada pesan";
            spasi(no_message, 86, false, true);
        }
        tampilkan_menu_horizontal(daftar, jumlah, option);
        char key = getch();
        bool enter = false;
        switch (key) {
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

        if (enter) {
            if (daftar[option - 1] == "KEMBALI") {
                break;
            } else if (daftar[option - 1] == "PROFILE") {
                tampilkan_profile(nomor_tujuan);
            } else if (daftar[option - 1] == "CHAT/BALAS") {
                system("cls");
                cout << "\033[36m" << tanggal << "\033[0m" << endl;
                tampilan_header();
                garis();
                spasi(nama_display, 86, false, true);
                garis();
                string pesan;
                if (!ada_chat) {
                    cout << "Chat dengan: ";
                } else {
                    cout << "Balas dengan: ";
                }
                getline(cin, pesan);
                kirim_pesan(nomor_login, nomor_tujuan, pesan);
                cout << "Pesan terkirim!\n";
                system("pause");
            } else if (daftar[option - 1] == "FAVORIT") {
                pesan_favorite(nomor_tujuan);
            }
        }
    }
}

void fitur_chat() {
    while (true) {
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        string chat_title = "CHAT";
        spasi(chat_title, 86, false, true);
        garis();

        string nomor_chat[100];
        int jumlah_chat = 0;
        
        for (int i = 0; i < jumlah_pesan; i++) {
            Message *ptr_msg = &messagess[i];
            if (ptr_msg->pengirim == nomor_login || ptr_msg->penerima == nomor_login) {
                string nomor_tujuan = (ptr_msg->pengirim == nomor_login) ? ptr_msg->penerima : ptr_msg->pengirim;
                
                bool sudah_ada = false;
                for (int j = 0; j < jumlah_chat; j++) {
                    if (nomor_chat[j] == nomor_tujuan) {
                        sudah_ada = true;
                        break;
                    }
                }
                
                if (!sudah_ada && jumlah_chat < 100) {
                    nomor_chat[jumlah_chat] = nomor_tujuan;
                    jumlah_chat++;
                }
            }
        }

        string daftar_menu[102];
        int total_menu = 0;
        
        for (int i = 0; i < jumlah_chat; i++) {
            string nama_kontak = get_nama_kontak(nomor_chat[i]);
            if (nama_kontak == nomor_chat[i]) {
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
        
        while (true) {
            system("cls");
            time_t now = time(0);
            string tanggal = string(ctime(&now));
            cout << "\033[36m" << tanggal << "\033[0m" << endl;
            tampilan_header();
            garis();
            spasi(chat_title, 86, false, true);
            garis();
            
            if (jumlah_chat == 0) {
                string no_chat = "Belum ada chat sebelumnya";
                spasi(no_chat, 86, false, true);
            } else {
                for (int i = 0; i < jumlah_chat; i++) {
                    string separator = "========================";
                    spasi(separator, 86, false, true);
                    bool aktif = (option == i + 1);
                    string menu_item = "( " + daftar_menu[i] + " )";
                    spasi(menu_item, 86, aktif, true);
                    spasi(separator, 86, false, true);
                }
            }
            garis();
            string separator = "========================";
            spasi(separator, 86, false, true);
            bool aktif_baru = (option == jumlah_chat + 1);
            string chat_baru = "Chat Nomor Baru";
            spasi(chat_baru, 86, aktif_baru, true);
            spasi(separator, 86, false, true);
            
            spasi(separator, 86, false, true);
            bool aktif_kembali = (option == jumlah_chat + 2);
            string kembali = "Kembali";
            spasi(kembali, 86, aktif_kembali, true);
            spasi(separator, 86, false, true);
            
            garis();

            key = getch();
            bool enter = false;
            switch (key) {
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

            if (enter) {
                if (option == total_menu) {
                    return;
                } else if (option == total_menu - 1) {
                    system("cls");
                    time_t now = time(0);
                    string tanggal = string(ctime(&now));
                    cout << "\033[36m" << tanggal << "\033[0m" << endl;
                    tampilan_header();
                    garis();
                    string chat_baru_title = "CHAT NOMOR BARU";
                    spasi(chat_baru_title, 86, false, true);
                    garis();
                    
                    string nomor_tujuan;
                    cout << "Masukkan nomor yang ingin di chat: ";
                    getline(cin, nomor_tujuan);

                    if (!cari_user_by_nomor(nomor_tujuan)) {
                        cout << "Nomor tidak terdaftar di vibe chat\n";
                        system("pause");
                        continue;
                    }

                    if (nomor_tujuan == nomor_login) {
                        cout << "Tidak bisa chat dengan diri sendiri\n";
                        system("pause");
                        continue;
                    }
                    
                    tampilkan_chat(nomor_tujuan);
                    break;
                } else {
                    string nomor_terpilih = nomor_chat[option - 1];
                    tampilkan_chat(nomor_terpilih);
                    break;
                }
            }
        }
    }
}

void hapus_kontak(string &nama_kontak) {
    bool ada = false;
    for (int i = 0; i < jumlah_kontak; i++) {
        Contact *ptr_contact = &contacts[i];
        if (ptr_contact->nama_kontak == nama_kontak && ptr_contact->pemilik == nomor_login) {
            ada = true;
            for (int j = i; j < jumlah_kontak - 1; j++) {
                Contact *ptr_current = &contacts[j];
                Contact *ptr_next = &contacts[j + 1];
                *(&ptr_current->nomor) = ptr_next->nomor;
                *(&ptr_current->nama_kontak) = ptr_next->nama_kontak;
                *(&ptr_current->pemilik) = ptr_next->pemilik;
            }
            jumlah_kontak--;
            cout << "Kontak '" << nama_kontak << "' berhasil dihapus!\n";
            break;
        }
    }
    if (!ada) {
        cout << "Kontak '" << nama_kontak << "' tidak ditemukan!\n";
    }
    system("pause");
}

void edit_kontak(Contact* contact) {
    system("cls");
    tampilan_header();
    garis();
    string title = "EDIT KONTAK";
    spasi(title, 86, false, true);
    garis();
    string opt1 = "1. Nama Kontak: " + contact->nama_kontak;
    string opt2 = "2. Nomor: " + contact->nomor;
    string opt0 = "0. Kembali";
    rata_kiri(opt1, 86);
    rata_kiri(opt2, 86);
    rata_kiri(opt0, 86);
    garis();
    cout << "Pilih data yang ingin diubah (0-2): ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    if (pilihan == 0) {
        return;
    } else if (pilihan == 1) {
        cout << "Masukkan Nama Kontak Baru: ";
        getline(cin, *(&contact->nama_kontak));
        cout << "Nama kontak berhasil diperbarui!\n";
    } else if (pilihan == 2) {
        string no_baru;
        bool valid = true;
        do {
            valid = true;
            cout << "Masukkan Nomor Baru: ";
            getline(cin, no_baru);
            if (!cari_user_by_nomor(no_baru)) {
                cout << "Nomor tidak terdaftar di vibe chat\n";
                valid = false;
            }
        } while (!valid);
        *(&contact->nomor) = no_baru;
        cout << "Nomor kontak berhasil diperbarui!\n";
    } else {
        cout << "Pilihan tidak valid!\n";
    }
    system("pause");
}

void fitur_kontak() {
    while (true) {
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        string kontak_title = "DAFTAR KONTAK";
        spasi(kontak_title, 86, false, true);
        garis();

        bool ada_kontak = false;
        for (int i = 0; i < jumlah_kontak; i++) {
            Contact *ptr_contact = &contacts[i];
            if (ptr_contact->pemilik == nomor_login) {
                ada_kontak = true;
                string tampilan = ptr_contact->nama_kontak + " (" + ptr_contact->nomor + ")";
                rata_kiri(tampilan, 86);
            }
        }

        if (!ada_kontak) {
            string no_kontak = "Belum ada kontak tersimpan";
            spasi(no_kontak, 86, false, true);
        }

        garis();
        string hapus_menu = "1. Hapus kontak";
        string edit_menu = "2. Edit kontak";
        string back_menu = "0. Kembali";
        rata_kiri(hapus_menu, 86);
        rata_kiri(edit_menu, 86);
        rata_kiri(back_menu, 86);
        garis();

        char pilihan;
        cout << ">> ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == '1') {
            if (!ada_kontak) {
                cout << "Tidak ada kontak untuk dihapus!\n";
                system("pause");
                continue;
            }
            string nama_kontak;
            cout << "Masukkan nama kontak yang ingin dihapus: ";
            getline(cin, nama_kontak);
            hapus_kontak(nama_kontak);
        } else if (pilihan == '2') {
            if (!ada_kontak) {
                cout << "Tidak ada kontak untuk diedit!\n";
                system("pause");
                continue;
            }
            string nama_kontak;
            cout << "Masukkan nama kontak yang ingin diedit: ";
            getline(cin, nama_kontak);
            bool found = false;
            for (int i = 0; i < jumlah_kontak; i++) {
                Contact* ptr_contact = &contacts[i];
                if (ptr_contact->nama_kontak == nama_kontak && ptr_contact->pemilik == nomor_login) {
                    edit_kontak(ptr_contact);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Kontak '" << nama_kontak << "' tidak ditemukan!\n";
                system("pause");
            }
        } else if (pilihan == '0') {
            break;
        }
    }
}

void pesan_favorite(string &nomor_tujuan) {
    system("cls");
    time_t now = time(0);
    string tanggal = string(ctime(&now));
    cout << "\033[36m" << tanggal << "\033[0m" << endl;
    tampilan_header();
    garis();
    
    bool ada_pesan = false;
    int counter = 1;
    int indeks_pesan[1000];
    
    string favorite_title = "PILIH PESAN UNTUK DISIMPAN KE FAVORIT";
    spasi(favorite_title, 86, false, true);
    garis();
    
    for (int i = 0; i < jumlah_pesan; i++) {
        Message *ptr_msg = &messagess[i];
        if ((ptr_msg->pengirim == nomor_tujuan && ptr_msg->penerima == nomor_login) ||
            (ptr_msg->pengirim == nomor_login && ptr_msg->penerima == nomor_tujuan)) {
            ada_pesan = true;
            indeks_pesan[counter] = i;
            
            string waktu_str = ctime(&ptr_msg->waktu);
            waktu_str.erase(waktu_str.length() - 1);
            
            cout << counter << ". ";
            if (ptr_msg->pengirim == nomor_login) {
                cout << "Anda: ";
            } else {
                string nama_kontak = get_nama_kontak(nomor_tujuan);
                cout << nama_kontak << ": ";
            }
            cout << "[" << waktu_str << "] ";
            cout << ptr_msg->isi_pesan << endl;
            
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
            Favorite *ptr_fav = &favorites[i];
            if (ptr_fav->nomor_pengirim == messagess[idx_pesan].pengirim &&
                ptr_fav->isi_pesan == messagess[idx_pesan].isi_pesan &&
                ptr_fav->pemilik == nomor_login) {
                sudah_ada = true;
                break;
            }
        }
        
        if (!sudah_ada) {
            if (jumlah_favorite < 1000) {
                Favorite *ptr_favorite = &favorites[jumlah_favorite];
                *(&ptr_favorite->nomor_pengirim) = messagess[idx_pesan].pengirim;
                *(&ptr_favorite->isi_pesan) = messagess[idx_pesan].isi_pesan;
                *(&ptr_favorite->waktu) = messagess[idx_pesan].waktu;
                *(&ptr_favorite->pemilik) = nomor_login;
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

void hapus_favorite(Favorite* fav, int* index) {
    for (int i = *index; i < jumlah_favorite - 1; i++) {
        Favorite *ptr_current = &favorites[i];
        Favorite *ptr_next = &favorites[i + 1];
        *(&ptr_current->nomor_pengirim) = ptr_next->nomor_pengirim;
        *(&ptr_current->isi_pesan) = ptr_next->isi_pesan;
        *(&ptr_current->waktu) = ptr_next->waktu;
        *(&ptr_current->pemilik) = ptr_next->pemilik;
    }
    jumlah_favorite--;
    cout << "Pesan favorit berhasil dihapus!\n";
    system("pause");
}

void favorit() {
    while (true) {
        system("cls");
        time_t now = time(0);
        string tanggal = string(ctime(&now));
        cout << "\033[36m" << tanggal << "\033[0m" << endl;
        tampilan_header();
        garis();
        string favorit_title = "PESAN FAVORIT";
        spasi(favorit_title, 86, false, true);
        garis();
        
        bool ada_favorite = false;
        int counter = 1;
        int indeks_favorite[1000];
        
        for (int i = 0; i < jumlah_favorite; i++) {
            Favorite *ptr_fav = &favorites[i];
            if (ptr_fav->pemilik == nomor_login) {
                ada_favorite = true;
                indeks_favorite[counter] = i;
                
                string waktu_str = ctime(&ptr_fav->waktu);
                waktu_str.erase(waktu_str.length() - 1);
                
                string show_name;
                if (ptr_fav->nomor_pengirim == nomor_login) {
                    show_name = "Anda";
                } else {
                    show_name = get_nama_kontak(ptr_fav->nomor_pengirim);
                }
                
                string waktu_info = "[" + waktu_str + "] ";
                string pesan_info = "";
                pesan_info += counter; 
                pesan_info += ". " + show_name + " (" + ptr_fav->nomor_pengirim + "):";
                cout << waktu_info << pesan_info << "\n";
                string isi_pesan = "  " + ptr_fav->isi_pesan;
                cout << isi_pesan << "\n";
                garis();
                counter++;
            }
        }
        
        if (!ada_favorite) {
            string no_favorite = "Belum ada pesan favorit";
            spasi(no_favorite, 86, false, true);
            garis();
        }
        
        string hapus_menu = "1. Hapus pesan favorit";
        string back_menu = "0. Kembali";
        rata_kiri(hapus_menu, 86);
        rata_kiri(back_menu, 86);
        garis();
        cout << ">> ";
        char pilihan;
        cin >> pilihan;
        cin.ignore();
        
        if (pilihan == '0') {
            break;
        } else if (pilihan == '1') {
            if (!ada_favorite) {
                cout << "Tidak ada pesan favorit untuk dihapus!\n";
                system("pause");
                continue;
            }
            cout << "Masukkan nomor pesan favorit yang ingin dihapus: ";
            int nomor;
            cin >> nomor;
            cin.ignore();
            if (nomor > 0 && nomor < counter) {
                int idx = indeks_favorite[nomor];
                hapus_favorite(&favorites[idx], &idx);
            } else {
                cout << "Nomor tidak valid!\n";
                system("pause");
            }
        }
    }
}

void tampilkan_menu_horizontal(string* menu_items, int jumlah_menu, int selected) {
    garis();
    cout << "|";
    
    int lebar_total = 83;
    int lebar_per_item = lebar_total / jumlah_menu;
    int sisa_lebar = lebar_total % jumlah_menu;
    
    for (int i = 0; i < jumlah_menu; i++) {
        int lebar_item = lebar_per_item;
        if (i < sisa_lebar) lebar_item++;
        
        int panjang_teks = menu_items[i].length();
        int spasi_kiri = (lebar_item - panjang_teks) / 2;
        int spasi_kanan = lebar_item - panjang_teks - spasi_kiri;
        
        if (selected == i + 1) {
            cout << "\033[1;36m";
        }
        
        for (int j = 0; j < spasi_kiri; j++) {
            cout << " ";
        }
        
        cout << menu_items[i];
        
        for (int j = 0; j < spasi_kanan; j++) {
            cout << " ";
        }
        
        if (selected == i + 1) {
            cout << "\033[0m";
        }
        
        if (i < jumlah_menu - 1) {
            cout << "|";
        }
    }
    cout << "|" << endl;
    garis();
}

int main() {
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