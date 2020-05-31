#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "recording.h"
using namespace std;


class Repository {
    protected:
        vector<Recording> watch_list;
        unsigned int selected_recording;

    public:
        virtual void add(Recording r) = 0;
        virtual void remove(string title) = 0;
        virtual vector<Recording> get_watchlist() = 0;
        virtual string next() = 0;
        virtual void save(string title) = 0;
        virtual ~Repository() {}
        virtual void set_current_recording(int position) {selected_recording = position;}
        virtual void remove_from_watchlist(int element_index) = 0;
        virtual int get_selected_recording_index() {
            return selected_recording;
        }
        virtual void set_selected_recording_index(int new_index) {
            selected_recording = new_index;
        }
};


class MemoryRepository: public Repository {
	private:
		vector<Recording> container;

	public:
		MemoryRepository();
		void add(Recording r);
		vector<Recording> get_container();
		void remove(string title);
		string next();
        void save(string title);
		vector<Recording> get_watchlist();
		bool search(string title);
        void remove_from_watchlist(int element_index);
        ~MemoryRepository();
};


class FileRepository: public Repository {
    private:
        string filename, watchlist_filename;
        unsigned int number_of_elements;

    public:
        FileRepository(string filename);
        void add(Recording r);
        void remove(string title);
        string next();
        void save(string title);
        vector<Recording> get_watchlist();
        bool search(string title);
        string get_filename();
        void set_filename(string new_filename);
        string get_watchlist_filename();
        void set_watchlist_filename(string new_filename);
        vector<string> tokenize(string line, char delimiter);
        std::string strip(std::string str);
        int get_number_of_elements();
        void update_watchlist_html_file();
        void update_watchlist_csv_file(); 
        vector<Recording> get_container();
        friend ostream& operator<<(ostream& out, Recording& recording); 
        void remove_from_watchlist(int element_index);

        ~FileRepository();
};
