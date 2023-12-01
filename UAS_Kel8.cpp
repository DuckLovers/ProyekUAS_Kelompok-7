// Program Spotify Sederhana

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Variabel Untuk Estetika Aplikasi
int tableLength = 73;

// Struktur untuk merepresentasikan simpul dalam pohon n-ary
struct SongNode {
    string songName;
    string artistName;
    SongNode* next;

    // Konstruktor untuk inisialisasi simpul lagu
    SongNode(const string& song, const string& artist) : songName(song), artistName(artist), next(nullptr) {}
};

// Struktur untuk merepresentasikan simpul dalam pohon n-ary
struct PlaylistNode {
    string playlistName;
    SongNode* songList;
    PlaylistNode* next;

    // Konstruktor untuk inisialisasi simpul playlist
    PlaylistNode(const string& playlist) : playlistName(playlist), songList(nullptr), next(nullptr) {}

    // Fungsi untuk menambahkan lagu ke playlist
    void addSong(const string& song, const string& artist) {
        SongNode* newSong = new SongNode(song, artist);
        newSong->next = songList;
        songList = newSong;
    }

    // Fungsi untuk menampilkan lagu dalam playlist
    void viewSongs() const {
        SongNode* currentSong = songList;
        string output;
        while (currentSong != nullptr) {
            output = "= " + currentSong->songName + " by " + currentSong->artistName;
            cout << setfill(' ') << setw(tableLength - 1) << left << output << "=" << endl;
            currentSong = currentSong->next;
        }
    }

    // Fungsi untuk mengedit lagu dalam playlist
    void editSong(const string& oldSong, const string& newSong, const string& newArtist) {
        SongNode* currentSong = songList;
        while (currentSong != nullptr) {
            if (currentSong->songName == oldSong) {
                // Jika lagu ditemukan, edit informasinya
                currentSong->songName = newSong;
                currentSong->artistName = newArtist;
                cout << "Lagu berhasil diedit." << endl;
                return;
            }
            currentSong = currentSong->next;
        }
        cout << "Lagu tidak ditemukan." << endl;
    }

    // Fungsi untuk menghapus lagu dari playlist
    void removeSong(const string& song) {
        SongNode* currentSong = songList;
        SongNode* prevSong = nullptr;

        while (currentSong != nullptr) {
            if (currentSong->songName == song) {
                // Jika lagu ditemukan, hapus dari playlist
                if (prevSong != nullptr) {
                    prevSong->next = currentSong->next;
                } else {
                    // Jika lagu adalah yang pertama, atur songList
                    songList = currentSong->next;
                }

                delete currentSong;
                cout << "Lagu berhasil dihapus." << endl;
                return;
            }

            prevSong = currentSong;
            currentSong = currentSong->next;
        }

        cout << "Lagu tidak ditemukan." << endl;
    }

    // Fungsi untuk mencari lagu dalam playlist berdasarkan nama
    SongNode* findSong(const string& songName) const {
        SongNode* currentSong = songList;
        while (currentSong != nullptr) {
            if (currentSong->songName == songName) {
                // Jika lagu ditemukan, kembalikan pointer ke node lagu tersebut
                return currentSong;
            }
            currentSong = currentSong->next;
        }
        // Jika lagu tidak ditemukan, kembalikan nullptr
        return nullptr;
    }
};

// Struktur untuk merepresentasikan simpul dalam pohon n-ary
struct AccountNode {
    string accountName;
    string password;
    PlaylistNode* playlistInfo;  // Menyimpan informasi tentang playlist
    AccountNode* nextSibling; // Pointer ke saudara setelahnya
    AccountNode* firstChild; // Pointer ke anak pertama

    // Konstruktor untuk inisialisasi simpul akun
    AccountNode(const string& name, const string& pass) : accountName(name), password(pass), playlistInfo(nullptr), nextSibling(nullptr), firstChild(nullptr) {}

    // Fungsi untuk menambahkan anak ke simpul ini
    void addChild(AccountNode* child) {
        if (firstChild == nullptr) {
            // Jika tidak ada anak, atur sebagai anak pertama
            firstChild = child;
        } else {
            // Jika sudah ada anak, tambahkan sebagai saudara setelahnya
            AccountNode* temp = firstChild;
            while (temp->nextSibling != nullptr) {
                temp = temp->nextSibling;
            }
            temp->nextSibling = child;
        }
    }

    // Fungsi untuk menambahkan playlist ke akun ini
    void addPlaylist(PlaylistNode* playlist) {
        if (playlistInfo == nullptr) {
            // Jika tidak ada playlistInfo, atur sebagai playlistInfo pertama
            playlistInfo = playlist;
        } else {
            // Jika sudah ada playlistInfo, tambahkan sebagai saudara setelahnya
            PlaylistNode* temp = playlistInfo;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = playlist;
        }
    }

    // Fungsi untuk melihat playlist dalam akun
    void viewPlaylists() const {
        PlaylistNode* currentPlaylist = playlistInfo;
        string output;
        while (currentPlaylist != nullptr) {
            output = "= " + currentPlaylist->playlistName;
            cout << setfill(' ') << setw(tableLength - 1) << left << output << "=" << endl;
            currentPlaylist = currentPlaylist->next;
        }
    }

    // Fungsi untuk mengedit playlist dalam akun
    void editPlaylist(const string& oldPlaylist, const string& newPlaylist) {
        PlaylistNode* currentPlaylist = playlistInfo;
        while (currentPlaylist != nullptr) {
            if (currentPlaylist->playlistName == oldPlaylist) {
                // Jika playlist ditemukan, edit informasinya
                currentPlaylist->playlistName = newPlaylist;
                cout << "Playlist berhasil diedit." << endl;
                return;
            }
            currentPlaylist = currentPlaylist->next;
        }
        cout << "Playlist tidak ditemukan." << endl;
    }

    // Fungsi untuk menghapus playlist dari akun
    void removePlaylist(const string& playlist) {
        PlaylistNode* currentPlaylist = playlistInfo;
        PlaylistNode* prevPlaylist = nullptr;
        SongNode *currentSong, *tempSong;

        while (currentPlaylist != nullptr) {
            if (currentPlaylist->playlistName == playlist) {
                // Jika playlist ditemukan, hapus dari akun
                if (prevPlaylist != nullptr) {
                    prevPlaylist->next = currentPlaylist->next;
                } else {
                    // Jika playlist adalah yang pertama, atur playlistInfo
                    playlistInfo = currentPlaylist->next;
                }

                // Hapus semua lagu dalam playlist
                currentSong = currentPlaylist->songList;
                while (currentSong != nullptr) {
                    tempSong = currentSong;
                    currentSong = currentSong->next;
                    delete tempSong;
                }

                delete currentPlaylist;
                cout << "Playlist berhasil dihapus." << endl;
                return;
            }

            prevPlaylist = currentPlaylist;
            currentPlaylist = currentPlaylist->next;
        }

        cout << "Playlist tidak ditemukan." << endl;
    }

    // Fungsi untuk mencari playlist dalam akun berdasarkan nama
    PlaylistNode* findPlaylist(const string& playlistName) const {
        PlaylistNode* currentPlaylist = playlistInfo;
        while (currentPlaylist != nullptr) {
            if (currentPlaylist->playlistName == playlistName) {
                // Jika playlist ditemukan, kembalikan pointer ke node playlist tersebut
                return currentPlaylist;
            }
            currentPlaylist = currentPlaylist->next;
        }
        // Jika playlist tidak ditemukan, kembalikan nullptr
        return nullptr;
    }
};

// Struktur untuk merepresentasikan simpul dalam pohon n-ary
struct ApplicationNode {
    string appName;
    AccountNode* accountInfo;  // Menyimpan informasi tentang akun
    ApplicationNode* nextSibling; // Pointer ke saudara setelahnya
    ApplicationNode* firstChild; // Pointer ke anak pertama

    // Konstruktor untuk inisialisasi simpul aplikasi
    ApplicationNode(const string& app) : appName(app), accountInfo(nullptr), nextSibling(nullptr), firstChild(nullptr) {}

    // Fungsi untuk menambahkan akun pada Applikasi ini
    void addAccount(AccountNode* child) {
        if (accountInfo == nullptr) {
            // Jika tidak ada accountInfo, atur sebagai accountInfo pertama
            accountInfo = child;
        } else {
            // Jika sudah ada accountInfo, tambahkan sebagai saudara setelahnya
            AccountNode* temp = accountInfo;
            while (temp->nextSibling != nullptr) {
                temp = temp->nextSibling;
            }
            temp->nextSibling = child;
        }
    }
    // Fungsi untuk melihat akun dalam aplikasi
    void viewAccounts() const {
        AccountNode* currentAccount = accountInfo;
        string output;
        while (currentAccount != nullptr) {
            output = "= " + currentAccount->accountName;
            cout << setfill(' ') << setw(tableLength - 1) << left << output << "=" << endl;
            currentAccount = currentAccount->nextSibling;
        }
    }

    // Fungsi untuk mengedit akun dalam aplikasi
    void editAccount(const string& oldAccount, const string& newAccount, const string& newPassword) {
        AccountNode* currentAccount = accountInfo;
        while (currentAccount != nullptr) {
            if (currentAccount->accountName == oldAccount) {
                // Jika akun ditemukan, edit informasinya
                currentAccount->accountName = newAccount;
                currentAccount->password = newPassword;
                cout << "Akun berhasil diedit." << endl;
                return;
            }
            currentAccount = currentAccount->nextSibling;
        }
        cout << "Akun tidak ditemukan." << endl;
    }

    void removeAccount(const string& account) {
        AccountNode* currentAccount = accountInfo;
        AccountNode* prevAccount = nullptr;
        SongNode *currentSong, *tempSong;
        PlaylistNode *currentPlaylist, *tempPlaylist;
        while (currentAccount != nullptr) {
            if (currentAccount->accountName == account) {
                // Jika akun ditemukan, hapus dari aplikasi
                if (prevAccount != nullptr) {
                    prevAccount->nextSibling = currentAccount->nextSibling;
                } else {
                    // Jika akun adalah yang pertama, atur accountInfo
                    accountInfo = currentAccount->nextSibling;
                }

                // Hapus semua playlist yang terkait dengan akun ini
                PlaylistNode* currentPlaylist = currentAccount->playlistInfo;
                while (currentPlaylist != nullptr) {
                    PlaylistNode* tempPlaylist = currentPlaylist;
                    currentPlaylist = currentPlaylist->next;

                    // Hapus semua lagu dalam playlist
                    currentSong = tempPlaylist->songList;
                    while (currentSong != nullptr) {
                        tempSong = currentSong;
                        currentSong = currentSong->next;
                        delete tempSong;
                    }

                    delete tempPlaylist;
                }

                // Atur playlistInfo menjadi nullptr setelah menghapus semua playlist
                currentAccount->playlistInfo = nullptr;

                delete currentAccount;
                cout << "Akun berhasil dihapus." << endl;
                return;
            }

            prevAccount = currentAccount;
            currentAccount = currentAccount->nextSibling;
        }

        cout << "Akun tidak ditemukan." << endl;
    }

    // Fungsi untuk mencari akun dalam aplikasi berdasarkan nama akun
    AccountNode* findAccount(const string& accountName) const {
        AccountNode* currentAccount = accountInfo;
        while (currentAccount != nullptr) {
            if (currentAccount->accountName == accountName) {
                // Jika akun ditemukan, kembalikan pointer ke node akun tersebut
                return currentAccount;
            }
            currentAccount = currentAccount->nextSibling;
        }
        // Jika akun tidak ditemukan, kembalikan nullptr
        return nullptr;
    }
};

//Fungsi Membuat Menu Aplikasi
// Function declarations
void showAccountMenu(AccountNode* currentAccount, ApplicationNode* root);
void showPlaylistMenu(PlaylistNode* currentPlaylist, AccountNode* currentAccount, ApplicationNode* root);
void showSongMenu(SongNode* currentSong, PlaylistNode* currentPlaylist, AccountNode* currentAccount, ApplicationNode* root);

// Main menu
void showMainMenu(ApplicationNode* root) {
    int input;
    do {
        cout << setfill('=') << setw(tableLength) << "=" << endl;
        cout << setfill('=') << setw((tableLength - 11)/2) << "" << " Main Menu " << setw((tableLength - 11)/2) << "" << endl;
        cout << setfill('=') << setw(tableLength) << "=" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= List Akun :" << "=" << endl;
        root->viewAccounts();
        cout << setfill('=') << setw((tableLength - 39)/2) << "" << " Silahkan Memilih Aksi Yang Diinginkan " << setw((tableLength - 39)/2) << "" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= 1. Tambah Akun" << "=" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= 2. Edit Akun" << "=" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= 3. Hapus Akun" << "=" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= 4. Buka Akun" << "=" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= 5. Exit" << "=" << endl;
        cout << setfill('=') << setw(tableLength) << "=" << endl;
        cout << endl;
        cout << "Pilihan: ";
        cin >> input;
        cin.ignore();

        switch (input) {
            case 1: {
                // Implementasi tambah akun
                string username, password;
                cout << "Masukkan nama akun baru: ";
                getline(cin, username);
                cout << "Masukkan password untuk akun baru: ";
                getline(cin, password);

                // Membuat objek akun baru dan menambahkannya ke dalam aplikasi
                AccountNode* newAccount = new AccountNode(username, password);
                root->addAccount(newAccount);
                cout << "Akun berhasil ditambahkan." << endl;
                break;
            }

            case 2: {
                // Implementasi edit akun
                string oldUsername, newUsername, newPassword;
                cout << "Masukkan nama akun yang ingin diedit: ";
                getline(cin, oldUsername);

                // Mencari akun yang ingin diedit dan mengubah informasinya
                AccountNode* accountToEdit = root->findAccount(oldUsername);
                if (accountToEdit != nullptr) {
                    cout << "Masukkan nama akun baru: ";
                    getline(cin, newUsername);
                    cout << "Masukkan password baru untuk akun: ";
                    getline(cin, newPassword);
                    accountToEdit->accountName = newUsername;
                    accountToEdit->password = newPassword;
                    cout << "Akun berhasil diubah." << endl;
                } else {
                    cout << "Akun tidak ditemukan." << endl;
                }
                break;
            }

            case 3: {
                // Implementasi hapus akun
                string usernameToDelete;
                cout << "Masukkan nama akun yang ingin dihapus: ";
                getline(cin, usernameToDelete);

                // Mencari dan menghapus akun dari aplikasi
                AccountNode* accountToDelete = root->findAccount(usernameToDelete);
                if (accountToDelete != nullptr) {
                    root->removeAccount(usernameToDelete);
                } else {
                    cout << "Akun tidak ditemukan." << endl;
                }
                break;
            }

            case 4: {
                // Implementasi buka akun
                string accountName, accountPassword;
                cout << "Masukkan nama akun: ";
                getline(cin, accountName);
                AccountNode* currentAccount = root->findAccount(accountName);
                if (currentAccount != nullptr) {
                    cout << "Masukkan password akun: ";
                    getline(cin, accountPassword);
                    if(accountPassword == currentAccount->password){
                        cout << endl;
                        showAccountMenu(currentAccount, root);
                    } else {
                        cout << "Password salah" << endl;
                    }
                } else {
                    cout << "Akun tidak ditemukan." << endl;
                }
                break;
            }
            case 5: {
            // Keluar dari aplikasi
            cout << "Terima kasih telah menggunakan aplikasi." << endl;
            // Dealokasi memori setelah selesai digunakan
        }

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << endl;
    } while (input != 5);
}

// Akun menu
void showAccountMenu(AccountNode* currentAccount, ApplicationNode* root) {
    string judulMenu = "= Menu Akun (" + currentAccount->accountName + ") =";
    int padding = (tableLength - judulMenu.length()) / 2;
    int input;
    do {
        cout << setfill('=') << setw(tableLength) << "" << endl;
        cout << setw(padding) << "" << judulMenu << setw(padding + (tableLength - judulMenu.length()) % 2) << "" << endl;
        cout << setfill('=') << setw(tableLength) << "" << setfill(' ') << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= List Playlist :" << "=" << endl;
        currentAccount->viewPlaylists();
        cout << setfill('=') << setw((tableLength - 39)/2) << "" << " Silahkan Memilih Aksi Yang Diinginkan " << setw((tableLength - 39)/2) << "" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= 1. Tambah Playlist" << "=" << endl;
        cout << setw(tableLength - 1) << left << "= 2. Edit Playlist" << "=" << endl;
        cout << setw(tableLength - 1) << left << "= 3. Hapus Playlist" << "=" << endl;
        cout << setw(tableLength - 1) << left << "= 4. Buka Playlist" << "=" << endl;
        cout << setw(tableLength - 1) << left << "= 5. Kembali ke Menu Utama" << "=" << endl;
        cout << setfill('=') << setw(tableLength) << "=" << endl;
        cout << endl;
        cout << "Pilihan: ";
        cin >> input;
        cin.ignore();

        switch (input) {
            case 1: {
                // Implementasi tambah playlist
                string playlistName;
                cout << "Masukkan nama playlist baru: ";
                getline(cin, playlistName);
                cout << endl;

                // Membuat objek playlist baru dan menambahkannya ke akun saat ini
                PlaylistNode* newPlaylist = new PlaylistNode(playlistName);
                currentAccount->addPlaylist(newPlaylist);
                cout << "Playlist berhasil ditambahkan." << endl;
                break;
            }

           case 2: {
                // Implementasi edit playlist
                string oldPlaylistName, newPlaylistName;
                cout << "Masukkan nama playlist yang ingin diedit: ";
                getline(cin, oldPlaylistName);
                cout << "Masukkan nama playlist baru: ";
                getline(cin, newPlaylistName);

                // Mencari playlist yang ingin diedit dan mengubah namanya
                currentAccount->editPlaylist(oldPlaylistName, newPlaylistName);
                break;
            }

            case 3: {
                // Implementasi hapus playlist
                string playlistNameToDelete;
                cout << "Masukkan nama playlist yang ingin dihapus: ";
                getline(cin, playlistNameToDelete);
                cout << endl;

                // Mencari dan menghapus playlist dari akun saat ini
                currentAccount->removePlaylist(playlistNameToDelete);
                break;
            }

            case 4: {
                // Implementasi buka playlist
                string playlistName;
                cout << "Masukkan nama playlist: ";
                getline(cin, playlistName);
                cout << endl;

                PlaylistNode* currentPlaylist = currentAccount->findPlaylist(playlistName);
                if (currentPlaylist != nullptr) {
                    cout << endl;
                    showPlaylistMenu(currentPlaylist, currentAccount, root);
                } else {
                    cout << "Playlist tidak ditemukan." << endl;
                }
                break;
            }
            case 5: {
                // Kembali ke menu utama
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << endl;
    } while (input != 5);
}



// Playlist menu
void showPlaylistMenu(PlaylistNode* currentPlaylist, AccountNode* currentAccount, ApplicationNode* root) {
    string judulMenu = "= Menu Playlist (" + currentPlaylist->playlistName + ") =";
    int padding = (tableLength - judulMenu.length()) / 2;
    int input;
    do {
        cout << setfill('=') << setw(tableLength) << "" << endl;
        cout << setw(padding) << "" << judulMenu << setw(padding + (tableLength - judulMenu.length()) % 2) << "" << endl;
        cout << setfill('=') << setw(tableLength) << "" << setfill(' ') << endl;
        cout << setw(tableLength - 1) << left << "= List Lagu :" << "=" << endl;
        currentPlaylist->viewSongs();
        cout << setfill('=') << setw((tableLength - 39)/2) << "" << " Silahkan Memilih Aksi Yang Diinginkan " << setw((tableLength - 39)/2) << "" << endl;
        cout << setfill(' ') << setw(tableLength - 1) << left << "= 1. Tambah Lagu" << "=" << endl;
        cout << setw(tableLength - 1) << left << "= 2. Edit Lagu" << "=" << endl;
        cout << setw(tableLength - 1) << left << "= 3. Hapus Lagu" << "=" << endl;
        cout << setw(tableLength - 1) << left << "= 4. Kembali ke Menu Akun" << "=" << endl;
        cout << setfill('=') << setw(tableLength) << "=" << setfill(' ') << endl;
        cout << endl;
        cout << "Pilihan: ";
        cin >> input;
        cin.ignore();

        switch (input) {
            case 1: {
                // Implementasi tambah lagu
                string songName, artistName;
                cout << "Masukkan nama lagu: ";
                getline(cin, songName);
                cout << "Masukkan nama artis: ";
                getline(cin, artistName);

                // Menambah lagu ke dalam playlist
                currentPlaylist->addSong(songName, artistName);
                cout << "Lagu berhasil ditambahkan ke playlist." << endl;
                break;
            }
            case 2: {
                // Implementasi edit lagu
                string oldSongName, newSongName, newArtistName;
                cout << "Masukkan nama lagu yang ingin diedit: ";
                getline(cin, oldSongName);
                cout << "Masukkan nama lagu baru: ";
                getline(cin, newSongName);
                cout << "Masukkan nama artis baru: ";
                getline(cin, newArtistName);

                // Mengedit lagu dalam playlist
                currentPlaylist->editSong(oldSongName, newSongName, newArtistName);
                break;
            }
            case 3: {
                // Implementasi hapus lagu
                string songNameToDelete;
                cout << "Masukkan nama lagu yang ingin dihapus: ";
                getline(cin, songNameToDelete);

                // Menghapus lagu dari playlist
                currentPlaylist->removeSong(songNameToDelete);
                break;
            }
            case 4: {
                // Kembali ke menu akun
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << endl;
    } while (input != 4);
}

// Fungsi untuk mencetak pohon secara preorder (akar-anak)
void printTree(ApplicationNode* root, int depth = 0) {
    if (root != nullptr) {
        // Menambahkan indentasi sesuai dengan kedalaman simpul
        for (int i = 0; i < depth; ++i) {
            cout << "| ";
        }

        // Mencetak data simpul
        cout << "Aplikasi: " << root->appName << endl;

        // Mencetak informasi akun (jika ada)
        if (root->accountInfo != nullptr) {
            AccountNode* account = root->accountInfo;
            while (account != nullptr) {
                cout << "| | Akun: " << account->accountName << ", Password: " << account->password << endl;

                // Mencetak informasi playlist (jika ada)
                if (account->playlistInfo != nullptr) {
                    PlaylistNode* playlist = account->playlistInfo;
                    while (playlist != nullptr) {
                        cout << "| | | Playlist: " << playlist->playlistName << endl;

                        // Mencetak lagu dalam playlist
                        SongNode* song = playlist->songList;
                        while (song != nullptr) {
                            cout << "| | | | Lagu: " << song->songName << " by " << song->artistName << endl;
                            song = song->next;
                        }

                        playlist = playlist->next;
                    }
                }

                account = account->nextSibling;
            }
        }

        // Mencetak anak-anak simpul
        ApplicationNode* child = root->firstChild;
        while (child != nullptr) {
            printTree(child, depth + 1);
            child = child->nextSibling;
        }
    }
}

// Fungsi Pembersihan Memori
    // Fungsi untuk menghapus daftar lagu dalam playlist secara rekursif
        void deleteSongList(SongNode* song) {
            while (song != nullptr) {
                SongNode* temp = song;
                song = song->next;
                delete temp;
            }
        }

    // Fungsi untuk menghapus pohon playlist secara rekursif
    void deletePlaylistTree(PlaylistNode* playlist) {
        if (playlist != nullptr) {
            // Hapus semua lagu dalam playlist
            deleteSongList(playlist->songList);

            // Hapus saudara setelahnya (playlist lain dalam akun)
            deletePlaylistTree(playlist->next);
            // Hapus simpul playlist
            delete playlist;
        }
    }

    // Fungsi untuk menghapus pohon akun secara rekursif
    void deleteAccountTree(AccountNode* account) {
        if (account != nullptr) {
            // Hapus semua playlist dalam akun
            deletePlaylistTree(account->playlistInfo);

            // Hapus semua saudara setelahnya (akun lain dalam aplikasi)
            deleteAccountTree(account->nextSibling);
            // Hapus anak pertama (jika ada)
            deleteAccountTree(account->firstChild);
            // Hapus simpul akun
            delete account;
        }
    }

    // Fungsi untuk menghapus pohon n-ary secara rekursif
    void deleteTree(ApplicationNode* root) {
        if (root != nullptr) {
            // Hapus semua akun dalam aplikasi
            deleteAccountTree(root->accountInfo);

            // Hapus semua anak pertama
            deleteTree(root->firstChild);
            // Hapus semua saudara setelahnya
            deleteTree(root->nextSibling);
            // Hapus simpul akar
            delete root;
        }
    }

int main() {
    ApplicationNode* root = new ApplicationNode("Spotify Sederhana");
    AccountNode* currentAccount;
    PlaylistNode* currentPlaylist;

    // Data Default
    // Menambahkan akun pertama
    currentAccount = new AccountNode("Aidhil", "2004");

    currentPlaylist = new PlaylistNode("Jepang");
    currentPlaylist->addSong("Eine Kleine", "Kenshi Yonezu");
    currentPlaylist->addSong("Yoru Ni Kakeru", "Yoasobi");
    currentAccount->addPlaylist(currentPlaylist);

    currentPlaylist = new PlaylistNode("Inggris");
    currentPlaylist->addSong("Bad Liar", "Imagine Dragon");
    currentPlaylist->addSong("My Love", "Westlife");
    currentPlaylist->addSong("Coco", "Pewdiepie");
    currentPlaylist->addSong("2004 Breakup", "The Gentle Men");
    currentAccount->addPlaylist(currentPlaylist);

    root->addAccount(currentAccount);

    // Menambahkan akun kedua
    currentAccount = new AccountNode("Syafaat", "202020");

    currentPlaylist = new PlaylistNode("Olahraga");
    currentPlaylist->addSong("Imagine Dragons", "Believer");
    currentPlaylist->addSong("Eminem", "Lose Yourself");
    currentPlaylist->addSong("Eye of the Tiger", "Survivor");
    currentPlaylist->addSong("We Will Rock You", "Queen");
    currentAccount->addPlaylist(currentPlaylist);

    currentPlaylist = new PlaylistNode("Galau");
    currentPlaylist->addSong("Andmesh", "Hanya Rindu");
    currentPlaylist->addSong("Armada", "Harusnya Aku");
    currentPlaylist->addSong("Someone You Loved", "Lewis Capaldi");
    currentPlaylist->addSong("All of Me", "John Legend");
    currentAccount->addPlaylist(currentPlaylist);

    root->addAccount(currentAccount);

    // Menambahkan akun ketiga
    currentAccount = new AccountNode("Husni", "1465");

    currentPlaylist = new PlaylistNode("Inggris");
    currentPlaylist->addSong("Control", "Zoe Wees");
    currentPlaylist->addSong("Somebody To You", "The Vamps");
    currentAccount->addPlaylist(currentPlaylist);

    currentPlaylist = new PlaylistNode("Galau");
    currentPlaylist->addSong("Sial", "Mahalini");
    currentPlaylist->addSong("Usai", "Tiara Andini");
    currentPlaylist->addSong("Kuira Kau Rumah", "Amigdala");
    currentPlaylist->addSong("Muak", "Aruma");
    currentAccount->addPlaylist(currentPlaylist);

    root->addAccount(currentAccount);

    // Menambahkan akun keempat
    currentAccount = new AccountNode("Fida", "1111");
    currentPlaylist = new PlaylistNode("Kpop");
    currentPlaylist->addSong("Nct Dream", "Candy");
    currentPlaylist->addSong("Nct 127", "Pilot");
    currentPlaylist->addSong("WayV", "Love Talk");
    currentAccount->addPlaylist(currentPlaylist);
    root->addAccount(currentAccount);


    cout << "Gambar Tree Secara Keseluruhan" << endl;
    printTree(root);
    cout<<endl;

    // Menampilkan menu utama
    showMainMenu(root);


    // Dealokasi memori setelah selesai digunakan
    deleteTree(root);

    return 0;
}
