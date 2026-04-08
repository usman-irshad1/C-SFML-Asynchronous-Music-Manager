// Assignment_1_DSA_ipod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <sstream>
#include <thread>
#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include"DoubleLinkedList.h"
using namespace std;

class MetaData {
    int Track_ID;
    string Title;
    string Artist;
    int seconds;
    string filePath;
    static int id;
public:
    MetaData() {
        Track_ID=id++;
        Title="";
        Artist="";
        seconds=0;
        filePath="";
    };
    int getTrackID() const { return Track_ID; }
    string getTitle() const { return Title; }
    string getArtist() const { return Artist; }
    int getSeconds() const { return seconds; }
    string getPath() const { return filePath; }
    
    void setTitle(string t) {
        for (int i = 0; i < t.length(); i++) {
            t[i] = toupper(t[i]);
        }
        Title = t; }
    void setPath(string t) { filePath = t; }
    void setArtist(string a) { Artist = a; }
    void setSeconds(int s) {
        if (s >= 0) seconds = s; 
    }


    friend ostream& operator<<(ostream& os, MetaData d) {
        os << "ID = " << d.Track_ID << endl << "Title = " << d.Title << endl<<"Artist = "<<d.Artist<<"Length = "<<d.seconds;
        return os;
    }

    
    bool operator==(const MetaData& d) const {
        return (this->Title == d.Title);
    }
    bool operator<(const MetaData& d) {
        if (seconds < d.seconds) {
            return true;
        }
        else { return false; }

    }
    bool operator>(const MetaData& d) {
        if (seconds > d.seconds) {
            return true;
        }
        else { return false; }

    }

};
class IPOD {
    DoublyLinkedList<MetaData> list;
    node<MetaData>* current;
    sf::Music music;
    std::thread autoNextThread;
    std::atomic<bool> stopAutoNext{ false };
public:
    IPOD() {}
    IPOD(const IPOD& d) :list(d.list) { current = nullptr; }
    void addSong(MetaData t ) {
        list.insertAtStart(t);
        if (current == nullptr) {
            current = list.getHead();
        }
        
    }
    void DeleteSong( MetaData t) {
        int x=list.search__b(t);
        if (x == -1) {
            cout << "Cant delete a song that does not exist";
        }
        else {
            list.deleteAtPosition(x);
        }
    }

    void search(string x){
        MetaData a;
        a.setTitle(x);
        cout<<"The song exists in the list or not "<<list.search(a);
    }


    void display() {
        list.displayForward();
    }

    void Metrics() {
        cout << "The size of the playlist is " << list.getSize();
        list.displayForward();
    }


    void play() {
        if (current == nullptr) {
            cout << "Playlist is empty! Add some songs first." << endl;
            return;
        }
       
        if (current != nullptr) {

            if (music.getStatus() == sf::Music::Status::Paused) {
                music.play();
                return;
            }
              
            if (music.openFromFile(current->getData().getPath())) {
                cout << current->getData().getTitle();
                music.play();
            }
            else {

                cout << "Cant load the Path";
            }
            // Start auto-next thread once
            if (!autoNextThread.joinable()) {
                stopAutoNext = false;
                autoNextThread = std::thread(&IPOD::autoNextLoop, this);
            }
        }
        
    }
    void autoNextLoop() {
        while (!stopAutoNext) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (current && music.getStatus() == sf::Music::Status::Stopped) {
                next(); 
            }
        }
    }
    void next() {
        music.stop();
        if (current->getNext() == nullptr) {
            current = list.getHead();
        }
        else {
            current = current->getNext();
        }
        play();
    }
    void previous() {
        music.stop();
        if (current->getPrev() == nullptr) {
            current = list.getTail();
        }
        else {
            current = current->getPrev();
        }

        play();
    }

    void pause() {
        music.pause();
    }
 
    void random() {
        music.stop();

        int n = list.getSize();
        if (n == 0) {
            cout << "Playlist is empty!" << endl;
            return;
        }


        current = list.getHead();
        int random = rand() % list.getSize();
        for (int i = 0; i < random; i++) {
            current = current->getNext();
        }

        play();

    
    }


    void loadFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            string title, artist, secondsStr, path;

            stringstream ss(line);

            getline(ss, title, ',');
            getline(ss, artist, ',');
            getline(ss, secondsStr, ',');
            getline(ss, path);

            MetaData temp;
            temp.setTitle(title);
            temp.setArtist(artist);
            temp.setSeconds(stoi(secondsStr));
            temp.setPath(path);

            addSong(temp);
        }

        file.close();
    }
    void saveToCSV(string filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file for saving!" << endl;
            return;
        }

        node<MetaData>* temp = list.getHead();

        while (temp != nullptr) {
            MetaData data = temp->getData();

            file << data.getTitle() << ","
                << data.getArtist() << ","
                << data.getSeconds() << ","
                << data.getPath() << "\n";

            temp = temp->getNext();
        }

        file.close();
        cout << "Playlist saved successfully!" << endl;
    }


    void stopAutoNextThread() {
        stopAutoNext = true;
        if (autoNextThread.joinable())
            autoNextThread.join();
    } 
    void skipForward() {
        
        music.setPlayingOffset(music.getPlayingOffset() + sf::seconds(10));
        cout << ">>> Skipped 10s forward" << endl;
    }

    void skipBack() {

        music.setPlayingOffset(music.getPlayingOffset() - sf::seconds(10));
        cout << ">>> Skipped 10s backwards" << endl;
    }
   


};


int showMenu() {
    int choice;
    cout << "\n======= IPOD PLAYER =======\n";
    cout << "1. Display Playlist\n";
    cout << "2. Play Current Song\n";
    cout << "3. Next Song\n";
    cout << "4. Previous Song\n";
        cout << "5. Add Song\n";
        cout << "6 for Random\n";
        cout << "7 for Stop\n";
        cout << "8 For skipping 10 seconds\n";
        cout << "9 For GOING BACK 10 seconds\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // clear newline from input
        return choice;
    }

    int MetaData:: id = 0;
    int main() {

        IPOD ipod;
        int choice;

        ipod.loadFromCSV("songs.csv");

        do {
            choice = showMenu();
        
            if (choice == 1) {
                ipod.display();
            }

            else if (choice == 2) {
                ipod.play();
            }

            else if (choice == 3) {
                ipod.next();
            }

            else if (choice == 4) {
                ipod.previous();
            }

            else if (choice == 5) {
                MetaData song;
                string title, artist, path;
                int seconds;

                cout << "Enter Title: ";
                getline(cin, title);

                cout << "Enter Artist: ";
                getline(cin, artist);

                cout << "Enter Duration : ";
                cin >> seconds;
                cin.ignore();

                cout << "Enter Full File Path: ";
                getline(cin, path);

                song.setTitle(title);
                song.setArtist(artist);
                song.setSeconds(seconds);
                song.setPath(path);

                ipod.addSong(song);

                cout << "Song Added Successfully!\n";
            }

            else if (choice == 0) {
                ipod.stopAutoNextThread();
                ipod.saveToCSV("songs.csv");
                cout << "Playlist saved. \n";
            }

            else if (choice == 6) {
                ipod.random();
            }
            else if (choice == 7) {
                ipod.pause();
            }
            else if (choice == 8) {
                ipod.skipForward();
            }
            else if (choice == 9) {
                ipod.skipBack();
            }

            else {
                cout << "Invalid choice!\n";
            }

        } while (choice != 0);

        return 0;
    }
