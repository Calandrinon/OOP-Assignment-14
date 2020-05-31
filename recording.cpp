#include "recording.h"


Recording::Recording() {}


Recording::Recording(std::string title, std::string location, std::string time_of_creation, int times_accessed, std::string footage_preview) {
	this->title = title;
	this->location = location;
	this->time_of_creation = time_of_creation;
	this->times_accessed = times_accessed;
	this->footage_preview = footage_preview;
}


std::string Recording::get_title() {
	return title;
}


std::string Recording::get_location() {
	return location;
}


std::string Recording::get_time_of_creation() {
	return time_of_creation;
}	


int Recording::get_times_accessed() {
	return times_accessed;
}


std::string Recording::get_footage_preview() {
	return footage_preview;
}


void Recording::set_title(std::string new_title) {
	title = new_title;
}


std::string Recording::get_as_string() {
	return title + ", " + location + ", " + time_of_creation + ", " + to_string(times_accessed) + ", " + footage_preview;
}
