#include "repository.h"
#include "myexceptions.h"
#include "string_functions.h"
#include <QDebug>
#include <string>

MemoryRepository::MemoryRepository() {
	selected_recording = 0;
}


void MemoryRepository::add(Recording r) {
	for (Recording& recording: container){
		if (recording.get_title() == r.get_title()) {
			RepositoryException re("Can't add duplicate elements!\n");
			throw re;
		}
	}

	container.push_back(r);
}


vector<Recording> MemoryRepository::get_container() {
	return container;
}


void MemoryRepository::remove(string title) {
	for (auto it = container.begin(); it != container.end(); it++) {
		if (it->get_title() == title) {
			container.erase(it);
			return;
		}
	}
}


MemoryRepository::~MemoryRepository() {
}


void MemoryRepository::remove_from_watchlist(int element_index) {
    watch_list.erase(watch_list.begin()+element_index);
}


bool MemoryRepository::search(string title) {
	for (Recording& recording: container) {
		if (recording.get_title() == title) {
			return true;
		}
	}

	return false;
}


string MemoryRepository::next() {
	if (selected_recording + 1 < container.size()) {
		selected_recording++;
	} else {
		selected_recording = 0;
	}

	return container[selected_recording].get_as_string();	
}


void MemoryRepository::save(string title) {
    for (auto item: container) {
        if (item.get_title() == title) {
            watch_list.push_back(item);
            break;
        }
    }
}


vector<Recording> MemoryRepository::get_watchlist() {
	return watch_list;
}



FileRepository::FileRepository(string filename) {
    this->filename = filename;
    ofstream file_creator(filename);
    selected_recording = 0;
    number_of_elements = 0;
}


vector<string> FileRepository::tokenize(std::string line, char delimiter) {
    /**
     *
     * Splits a string into tokens by using a delimiter and returns them in a std::vector
     *
     * Input:
     * 		- line: string
     * 		- delimiter: character
     *
     * Output:
     * 		- tokens: std::vector
     **/
    vector<string> tokens;

    stringstream stream(line);
    string token;

    while(getline(stream, token, delimiter)) {
        token = strip(token);
        tokens.push_back(token);
    }

    return tokens;
}


void FileRepository::remove_from_watchlist(int element_index) {
    watch_list.erase(watch_list.begin() + element_index);

    for (auto element: watch_list) {
        qDebug() << QString::fromStdString(element.get_as_string());
    }

    if (watchlist_filename.find(".html") != std::string::npos) {
        update_watchlist_html_file();
    } else {
        update_watchlist_csv_file();
    }
}


std::string FileRepository::strip(std::string str) {
    /**
     *
     * Removes all trailing whitespaces and newline characters.
     *
     * Input:
     * 		- str: the string
     *
     * Output:
     * 		- str: the string after its trailing whitespaces and \n characters have been removed.
     * **/
    while (str[0] == ' ' || str[0] == '\n')
        str.erase(0,1);

    while (str[str.size()-1] == ' ' || str[str.size()-1] == '\n')
        str.erase(str.size()-1,1);

    return str;
}


ostream& operator<<(ostream& out, Recording& recording) {
    out << recording.get_as_string() << "\n";
    return out;
}


void FileRepository::add(Recording recording) {
    ifstream in(filename);
    string element;

    while (getline(in, element)){
        vector<string> tokens = tokenize(element, ',');
        if (recording.get_title() == tokens[0]) {
            RepositoryException re("Can't add duplicate elements!\n");
            throw re;
        }
    }

    ofstream append_stream(filename, std::ios::app);
    append_stream << recording;
    append_stream.close();
    in.close();
    number_of_elements++;
}


string FileRepository::get_filename() {
    return filename;
}


void FileRepository::remove(string title) {
    string element;
    bool element_found = false;
    ifstream in(filename);
    ofstream temp("tempfile.out");

    while (getline(in, element)) {
        vector<string> tokens = tokenize(element, ',');

        if (title != tokens[0]) {
            temp << element << "\n";
        } else {
            element_found = true;
        }
    }

    if (!element_found)
        return;

    temp.close();

    ifstream temp_in("tempfile.out");
    ofstream new_out(filename);
    while (getline(temp_in, element)) {
        new_out << element << "\n";
    }

    number_of_elements--;
}


bool FileRepository::search(string title) {
    string element;
    ifstream in(filename);

    while (getline(in, element)) {
        vector<string> tokens = StringFunctions::tokenize(element, ',');
        if (tokens[0] == title) {
            return true;
        }
    }

    return false;
}


int FileRepository::get_number_of_elements() {
    return number_of_elements;
}


string FileRepository::next() {
    selected_recording++;
    if (selected_recording >= number_of_elements) {
        selected_recording = 0;
    }

    unsigned int counter = 0;
    string element;
    ifstream in(filename);

    while (getline(in, element)) {
        if (counter == selected_recording)
            return element;

        counter++;
    }

    return "Element not found!";
}




void FileRepository::save(string title) {
    string element;
    ifstream in(filename);
    unsigned int counter = 0;

    while (getline(in, element)) {
        vector<string> tokens = StringFunctions::tokenize(element, ',');

        int times_accessed = stoi(tokens[3]);
        Recording recording(tokens[0], tokens[1], tokens[2], times_accessed, tokens[4]);

        if (recording.get_title() == title) {
            watch_list.push_back(recording);

            if (watchlist_filename.find(".html") != std::string::npos) {
                update_watchlist_html_file();
            } else {
                update_watchlist_csv_file();
            }

            counter++;
        }
    }
}


vector<Recording> FileRepository::get_container() {
    vector<Recording> container;
    string element;
    ifstream in(filename);

    while (getline(in, element)) {
        vector<string> tokens = StringFunctions::tokenize(element, ',');

        int times_accessed = stoi(tokens[3]);
        Recording recording(tokens[0], tokens[1], tokens[2], times_accessed, tokens[4]);
        container.push_back(recording);
    }

    return container;
}


vector<Recording> FileRepository::get_watchlist() {
    return watch_list;
}


FileRepository::~FileRepository() {
}


void FileRepository::set_filename(string new_filename) {
    this->filename = new_filename;
    ofstream file_creator(new_filename);
}


string FileRepository::get_watchlist_filename() {
    return watchlist_filename;
}


void FileRepository::set_watchlist_filename(string new_filename) {
    watchlist_filename = new_filename;
}


void FileRepository::update_watchlist_html_file() {
    ofstream file_creator(watchlist_filename);
    vector<string> filename_tokens = StringFunctions::tokenize(watchlist_filename, '.');

    file_creator << "<!DOCTYPE html>\n";
    file_creator << "<html>\n";
    file_creator << "\t<head><title>" << filename_tokens[0] << "</title></head>\n";
    file_creator << "\t<body>\n\t\t<table border=\"1\">\n";
    file_creator << "\t\t<tr>\n";
    file_creator << "\t\t\t<td>Title</td>\n";
    file_creator << "\t\t\t<td>Location</td>\n";
    file_creator << "\t\t\t<td>Time of creation</td>\n";
    file_creator << "\t\t\t<td>Times accessed</td>\n";
    file_creator << "\t\t\t<td>Footage preview</td>\n";
    file_creator << "\t\t</tr>\n";

    for (auto element: watch_list) {
        file_creator << "\t\t<tr>\n";
        file_creator << "\t\t\t<td>" << element.get_title() << "</td>\n";
        file_creator << "\t\t\t<td>" << element.get_location() << "</td>\n";
        file_creator << "\t\t\t<td>" << element.get_time_of_creation() << "</td>\n";
        file_creator << "\t\t\t<td>" << element.get_times_accessed() << "</td>\n";
        file_creator << "\t\t\t<td>" << element.get_footage_preview() << "</td>\n";
        file_creator << "\t\t</tr>\n";
    }

    file_creator << "\t\t</table>\n";
    file_creator << "\t</body>\n";
    file_creator << "</html>";
}


void FileRepository::update_watchlist_csv_file() {
    ofstream file_creator(watchlist_filename);

    for (auto element: watch_list) {
        file_creator << element;
    }
}
