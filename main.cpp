// main.cpp
#include "music_adt.h"
#include <limits> // Untuk numeric_limits

void displayMenu() {
    cout << "\n=== MANAJEMEN PLAYLIST MUSIK ===" << endl;
    cout << "1. [BST] Tambah Lagu ke Master Library" << endl;
    cout << "2. [BST] Tampilkan Master Library (Sorted)" << endl;
    cout << "3. [BST] Cari Lagu di Library" << endl;
    cout << "4. [BST] Hapus Lagu dari Library" << endl;
    cout << "--------------------------------" << endl;
    cout << "5. [MLL] Buat Playlist Baru" << endl;
    cout << "6. [MLL] Tambah Lagu ke Playlist (Ambil dari Library)" << endl;
    cout << "7. [MLL] Tampilkan Semua Playlist" << endl;
    cout << "8. [MLL] Hapus Lagu dari Playlist" << endl;
    cout << "9. [MLL] Hapus Playlist" << endl;
    cout << "--------------------------------" << endl;
    cout << "10. [PROCESS] Filter Lagu by Artis di Semua Playlist" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
}

int main() {
    // Inisialisasi
    BSTNode* libraryRoot = NULL;
    MLLParent* playlistHead = NULL;
    createList(playlistHead);

    // Dummy Data (Supaya tidak kosong saat run pertama)
    libraryRoot = insertBST(libraryRoot, createBSTNode("Hati-Hati di Jalan", "Tulus", 240));
    libraryRoot = insertBST(libraryRoot, createBSTNode("Yellow", "Coldplay", 260));
    libraryRoot = insertBST(libraryRoot, createBSTNode("Fix You", "Coldplay", 300));
    libraryRoot = insertBST(libraryRoot, createBSTNode("Monokrom", "Tulus", 210));
    
    insertPlaylist(playlistHead, "Galau Indo");
    insertSongToPlaylist(playlistHead, "Galau Indo", {"Hati-Hati di Jalan", "Tulus", 240});
    insertPlaylist(playlistHead, "International Hits");

    int choice;
    string title, artist, playlistName;
    int duration;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

        switch(choice) {
            case 1:
                cout << "Judul: "; getline(cin, title);
                cout << "Artis: "; getline(cin, artist);
                cout << "Durasi (detik): "; cin >> duration;
                libraryRoot = insertBST(libraryRoot, createBSTNode(title, artist, duration));
                cout << "Berhasil ditambahkan ke Library." << endl;
                break;
            case 2:
                cout << "\n--- Master Library (BST Inorder) ---" << endl;
                if (libraryRoot == NULL) cout << "Library Kosong." << endl;
                else inorderTraversal(libraryRoot);
                break;
            case 3: {
                cout << "Cari Judul: "; getline(cin, title);
                BSTNode* res = searchBST(libraryRoot, title);
                if (res) cout << "Ditemukan: " << res->info.title << " oleh " << res->info.artist << endl;
                else cout << "Lagu tidak ditemukan." << endl;
                break;
            }
            case 4:
                cout << "Hapus Judul: "; getline(cin, title);
                libraryRoot = deleteBST(libraryRoot, title);
                cout << "Perintah hapus dijalankan." << endl;
                break;
            case 5:
                cout << "Nama Playlist Baru: "; getline(cin, playlistName);
                insertPlaylist(playlistHead, playlistName);
                break;
            case 6: {
                // Logika: Cari di BST dulu, baru masukkan ke MLL
                cout << "Nama Playlist Tujuan: "; getline(cin, playlistName);
                cout << "Judul Lagu (harus ada di Library): "; getline(cin, title);
                BSTNode* result = searchBST(libraryRoot, title);
                if (result != NULL) {
                    insertSongToPlaylist(playlistHead, playlistName, result->info);
                } else {
                    cout << "Error: Lagu tidak ada di Master Library. Tambahkan dulu ke menu 1." << endl;
                }
                break;
            }
            case 7:
                showAllPlaylists(playlistHead);
                break;
            case 8:
                cout << "Nama Playlist: "; getline(cin, playlistName);
                cout << "Judul Lagu yg dihapus: "; getline(cin, title);
                deleteSongFromPlaylist(playlistHead, playlistName, title);
                break;
            case 9:
                cout << "Nama Playlist yg dihapus: "; getline(cin, playlistName);
                deletePlaylist(playlistHead, playlistName);
                break;
            case 10:
                cout << "Masukkan Nama Artis untuk Filter: "; getline(cin, artist);
                filterSongsByArtist(playlistHead, artist);
                break;
            case 0:
                cout << "Terima kasih." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 0);

    return 0;
}