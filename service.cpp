#include <sstream>
#include "myexceptions.h"
#include "recording.h"
#include "service.h"
#include <QDebug>
using namespace std;

Service::Service(Repository* repository) {
    auto memory_repository = dynamic_cast<MemoryRepository*>(repository);

    if (memory_repository) {
        this->repository = memory_repository;
        this->has_file_repository = false;
        qDebug() << "It is a memory repository!";
    } else {
        this->file_repository = dynamic_cast<FileRepository*>(repository);
        this->has_file_repository = true;
    }

}


bool Service::does_service_have_file_repository() {
    return has_file_repository;
}


string Service::get_file_repository_filename() {
    return file_repository->get_filename();
}


void Service::add(string title, string location, string time_of_creation, string times_accessed, string footage_preview) {
	/**
	 * 
	 * Adds a new recording to the repository.
	 * 
	 * Input:
	 * 		- title, location, time_of_creation, times_accessed, footage_preview: strings
	 **/
	validator.validate_time_of_creation(time_of_creation);
	validator.validate_times_accessed(times_accessed);

	Recording recording(title, location, time_of_creation, stoi(times_accessed), footage_preview);
    if (!has_file_repository) {
        repository->add(recording);
    } else {
        file_repository->add(recording);
    }
}


vector<Recording> Service::get_repository_container() {
	/**
	 * Gets the contents of the custom-made std::vector from the repository.
	 * 
	 **/
    if (!has_file_repository) {
        return repository->get_container();
    } else {
        return file_repository->get_container();
    }
}


bool Service::search(string title) {
    if (!has_file_repository) {
        return repository->search(title);
    } else {
        return file_repository->search(title);
    }
}


void Service::remove(string title) {
	/**
	 * 
	 * Removes a recording from the repository by its title.
	 * 
	 * Input:
	 * 		- title: string
	 **/
	if (!has_file_repository) {
        repository->remove(title);
    } else {
	    file_repository->remove(title);
	}
}


void Service::update(string title, string location, string time_of_creation, string times_accessed, string footage_preview) {
    /**
     *
     * Updates the details of a recording in the repository.
     * In case the recording with the specified title does not exist, the method throws
     * a RepositoryException.
     *
     * Input:
     * 		- title, location, time_of_creation, times_accessed, footage_preview: strings
     * Throws:
     * 		- RepositoryException: in case the recording with the given title doesn't exist
     **/
    validator.validate_time_of_creation(time_of_creation);
    validator.validate_times_accessed(times_accessed);

    if (!has_file_repository && !repository->search(title)) {
        RepositoryException re("RepositoryException: The element cannot be updated because it doesn't exist!\n");
        throw re;
    } else if (has_file_repository && !file_repository->search(title)) {
        RepositoryException re("RepositoryException: The element cannot be updated because it doesn't exist!\n");
        throw re;
    }

    if (!has_file_repository) {
        repository->remove(title);
    } else {
        file_repository->remove(title);
    }

	Recording recording(title, location, time_of_creation, stoi(times_accessed), footage_preview);
	if (!has_file_repository)
	    repository->add(recording);
    else
        file_repository->add(recording);
}



void Service::set_selected_recording_index(int new_index) {
    if (!has_file_repository) {
        repository->set_selected_recording_index(new_index);
    } else {
        file_repository->set_selected_recording_index(new_index);
    }
}


int Service::get_selected_recording_index() {
    if (!has_file_repository) {
        return repository->get_selected_recording_index();
    } else {
        return file_repository->get_selected_recording_index();
    }
}


string Service::next() {
    if (!has_file_repository)
	    return repository->next();
    else
        return file_repository->next();
}


void Service::save(string title) {
    if (!has_file_repository)
        repository->save(title);
    else
        file_repository->save(title);  /// has to be fixed
}


void Service::set_current_recording(int position) {
    if (!has_file_repository) {
        repository->set_current_recording(position);
    } else {
        file_repository->set_current_recording(position);
    }
}


vector<Recording> Service::get_watchlist() {
    if (!has_file_repository)
	    return repository->get_watchlist();
    else
        return file_repository->get_watchlist();
}


Service::~Service() {
}


void Service::set_file_repository_filename(string new_filename) {
    file_repository->set_filename(new_filename);
}


void Service::set_watchlist_filename(string file_path) {
    file_repository->set_watchlist_filename(file_path);

    if (file_path.find(".html") != std::string::npos) {
        file_repository->update_watchlist_html_file();
    } else {
        file_repository->update_watchlist_csv_file();
    }
}


void Service::remove_from_watchlist(int element_index) {
    if (!has_file_repository) {
        repository->remove_from_watchlist(element_index);
    } else {
        file_repository->remove_from_watchlist(element_index);
    }
}


void Service::push_to_undo_stack(vector<string> operation) {
    undo_stack.push(operation);
}


vector<string> Service::pop_from_undo_stack() {
    vector<string> operation = undo_stack.top();
    undo_stack.pop();
    return operation;
}
