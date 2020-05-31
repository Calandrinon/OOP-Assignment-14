#pragma once
#include <iostream>
#include <string>
using namespace std;

class Recording {
	private:
		std::string title;
		std::string location;
		std::string time_of_creation;
		int times_accessed;
		std::string footage_preview;

	public:
		Recording();
		Recording(std::string title, std::string location, std::string time_of_creation, int times_accessed, std::string footage_preview);
		std::string get_title();
		std::string get_location();
		std::string get_time_of_creation();
		int get_times_accessed();
		std::string get_footage_preview();
		void set_title(std::string new_title);
		void set_location(std::string new_location);
		void set_time_of_creation(std::string new_time);
		void set_times_accessed(int new_times_accessed);
		void set_footage_preview(std::string new_footage_preview);
		std::string get_as_string();
};
