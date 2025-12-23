// music_adt.h
#ifndef MUSIC_ADT_H
#define MUSIC_ADT_H

#include <iostream>
#include <string>
using namespace std;

// --- STRUKTUR DATA ---

// Struktur Data Lagu (Payload)
struct Song {
    string title;
    string artist;
    int duration; // dalam detik
};

// 1. BST Node (Untuk Master Library)
struct BSTNode {
    Song info;
    BSTNode *left;
    BSTNode *right;
};

// 2. MLL Child Node (Lagu di dalam Playlist)
struct MLLChild {
    Song info;
    MLLChild *next;
};

// 2. MLL Parent Node (Playlist itu sendiri)
struct MLLParent {
    string playlistName;
    MLLChild *songs; // Head dari Child List
    MLLParent *next;
};

// --- FUNGSI PRIMITIF ---

// A. Fungsi BST (Master Library)
BSTNode* createBSTNode(string title, string artist, int duration);
BSTNode* insertBST(BSTNode* root, BSTNode* newNode); // Create
BSTNode* searchBST(BSTNode* root, string title);     // Search & Read
BSTNode* deleteBST(BSTNode* root, string title);     // Delete
BSTNode* findMin(BSTNode* root);
void inorderTraversal(BSTNode* root);                // Read (Show All Sorted)

// B. Fungsi MLL (Playlist Management)
void createList(MLLParent* &first);
void insertPlaylist(MLLParent* &first, string name); // Create Playlist
void insertSongToPlaylist(MLLParent* &first, string playlistName, Song newSong); // Create Song in Playlist
void showAllPlaylists(MLLParent* first);             // Read All
void deleteSongFromPlaylist(MLLParent* &first, string playlistName, string songTitle); // Delete Child
void deletePlaylist(MLLParent* &first, string playlistName); // Delete Parent

// C. Pengolahan Data (Processing)
// Fitur: Menampilkan semua lagu dari artis tertentu yang ada di SEMUA playlist
void filterSongsByArtist(MLLParent* first, string artistName); 

#endif