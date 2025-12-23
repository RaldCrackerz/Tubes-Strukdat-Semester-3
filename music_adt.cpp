// music_adt.cpp
#include "music_adt.h"

// ==========================================
// IMPLEMENTASI BST (Master Library)
// ==========================================

BSTNode* createBSTNode(string title, string artist, int duration) {
    BSTNode* newNode = new BSTNode;
    newNode->info.title = title;
    newNode->info.artist = artist;
    newNode->info.duration = duration;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode* insertBST(BSTNode* root, BSTNode* newNode) {
    if (root == NULL) {
        return newNode;
    }
    // Asumsi: Sorting berdasarkan Judul Lagu
    if (newNode->info.title < root->info.title) {
        root->left = insertBST(root->left, newNode);
    } else if (newNode->info.title > root->info.title) {
        root->right = insertBST(root->right, newNode);
    } else {
        cout << "Lagu '" << newNode->info.title << "' sudah ada di Library." << endl;
    }
    return root;
}

BSTNode* searchBST(BSTNode* root, string title) {
    if (root == NULL || root->info.title == title) {
        return root;
    }
    if (title < root->info.title) {
        return searchBST(root->left, title);
    }
    return searchBST(root->right, title);
}

BSTNode* findMin(BSTNode* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

BSTNode* deleteBST(BSTNode* root, string title) {
    if (root == NULL) return root;

    if (title < root->info.title) {
        root->left = deleteBST(root->left, title);
    } else if (title > root->info.title) {
        root->right = deleteBST(root->right, title);
    } else {
        // Node ditemukan
        // Kasus 1: No child atau 1 child
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }
        // Kasus 2: 2 children
        BSTNode* temp = findMin(root->right);
        root->info = temp->info; // Copy data
        root->right = deleteBST(root->right, temp->info.title);
    }
    return root;
}

void inorderTraversal(BSTNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        cout << "- " << root->info.title << " (" << root->info.artist << ") [" << root->info.duration << "s]" << endl;
        inorderTraversal(root->right);
    }
}

// ==========================================
// IMPLEMENTASI MLL (Playlist Management)
// ==========================================

void createList(MLLParent* &first) {
    first = NULL;
}

void insertPlaylist(MLLParent* &first, string name) {
    MLLParent* newP = new MLLParent;
    newP->playlistName = name;
    newP->songs = NULL;
    newP->next = NULL;

    if (first == NULL) {
        first = newP;
    } else {
        // Insert Last
        MLLParent* p = first;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newP;
    }
    cout << "Playlist '" << name << "' berhasil dibuat." << endl;
}

void insertSongToPlaylist(MLLParent* &first, string playlistName, Song newSong) {
    // 1. Cari Parent (Playlist) dulu
    MLLParent* p = first;
    while (p != NULL && p->playlistName != playlistName) {
        p = p->next;
    }

    if (p == NULL) {
        cout << "Playlist '" << playlistName << "' tidak ditemukan." << endl;
        return;
    }

    // 2. Insert Child (Lagu)
    MLLChild* newC = new MLLChild;
    newC->info = newSong;
    newC->next = NULL;

    if (p->songs == NULL) {
        p->songs = newC;
    } else {
        MLLChild* c = p->songs;
        while (c->next != NULL) {
            c = c->next;
        }
        c->next = newC;
    }
    cout << "Lagu '" << newSong.title << "' ditambahkan ke playlist '" << playlistName << "'." << endl;
}

void showAllPlaylists(MLLParent* first) {
    if (first == NULL) {
        cout << "Belum ada playlist." << endl;
        return;
    }
    
    MLLParent* p = first;
    while (p != NULL) {
        cout << "=== Playlist: " << p->playlistName << " ===" << endl;
        MLLChild* c = p->songs;
        if (c == NULL) {
            cout << "  (Kosong)" << endl;
        } else {
            int i = 1;
            while (c != NULL) {
                cout << "  " << i++ << ". " << c->info.title << " - " << c->info.artist << endl;
                c = c->next;
            }
        }
        cout << endl;
        p = p->next;
    }
}

void deleteSongFromPlaylist(MLLParent* &first, string playlistName, string songTitle) {
    MLLParent* p = first;
    while (p != NULL && p->playlistName != playlistName) {
        p = p->next;
    }

    if (p == NULL) {
        cout << "Playlist tidak ditemukan." << endl;
        return;
    }

    MLLChild* c = p->songs;
    MLLChild* prev = NULL;

    while (c != NULL && c->info.title != songTitle) {
        prev = c;
        c = c->next;
    }

    if (c == NULL) {
        cout << "Lagu tidak ditemukan di playlist ini." << endl;
    } else {
        if (prev == NULL) { // Hapus elemen pertama
            p->songs = c->next;
        } else {
            prev->next = c->next;
        }
        delete c;
        cout << "Lagu dihapus dari playlist." << endl;
    }
}

void deletePlaylist(MLLParent* &first, string playlistName) {
    MLLParent* p = first;
    MLLParent* prev = NULL;

    while (p != NULL && p->playlistName != playlistName) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        cout << "Playlist tidak ditemukan." << endl;
        return;
    }

    // Hapus semua child dulu (Memory Management)
    MLLChild* c = p->songs;
    while (c != NULL) {
        MLLChild* tempC = c;
        c = c->next;
        delete tempC;
    }

    // Hapus Parent
    if (prev == NULL) {
        first = p->next;
    } else {
        prev->next = p->next;
    }
    delete p;
    cout << "Playlist '" << playlistName << "' berhasil dihapus." << endl;
}

// ==========================================
// PENGOLAHAN DATA (Processing MLL)
// ==========================================

void filterSongsByArtist(MLLParent* first, string artistName) {
    cout << "\n--- Filter Lagu (MLL): Artist '" << artistName << "' ---" << endl;
    bool found = false;
    MLLParent* p = first;
    
    while (p != NULL) {
        MLLChild* c = p->songs;
        while (c != NULL) {
            if (c->info.artist == artistName) {
                cout << "Playlist [" << p->playlistName << "] -> " << c->info.title << endl;
                found = true;
            }
            c = c->next;
        }
        p = p->next;
    }

    if (!found) cout << "Tidak ada lagu dari artis tersebut di playlist manapun." << endl;
    cout << "-------------------------------------------" << endl;
}