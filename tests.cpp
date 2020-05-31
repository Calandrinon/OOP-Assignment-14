#include "tests.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include "string_functions.h"
using namespace std;

/**
Tests::Tests() {
	test_recording_getters();
	test_recording_setters();
	test_repository_add();
	test_service_add();
	test_repository_delete();
	test_service_delete();
	test_repository_search();
	test_service_update();
    testRepositoryAdd__duplicateElement__doesntAddElement();
    testRepositoryNext__averageCase__incrementsToNextElement();
    testRepositorySave__averageCase__elementAddedToWatchlist();
    testFileRepository__addingAnElement__success();
    testFileRepository__addingADuplicateElement__success();
    testFileRepository__removingAnElement__success();
    testFileRepository__searchingAnElement__success();
    testFileRepository__searchingAnNonexistentElement__returnsFalse();
    testFileRepository__removingANonexistingElement__fails();
    testFileRepository__getNextElement__success();
    testFileRepository__saveElement__success();
    testFileRepository__getFilename__success();
    testRepositorySearch__searchingNonexistentElement__fails();
    testServiceGetFileRepoFilename__getsFilename__success();
    testRepositorySetFileRepoFilename__setsFilename__success();
    testServiceSetFileRepoFilename__setsFilename__success();
    testRepositoryGetFileRepoFilename__getsFilename__success();
    testCommandFormatException();
    testFileRepoExistenceInService();
    testStrip();
    testTimeOfCreationValidation__incorrectFormatting__throwsException();
    testTimeOfCreationValidation__invalidDate__throwsException();
    testServiceGetMemoryRepositoryContainer__serviceHasFileRepo__failure();
    testServiceGetFileRepoFilename__serviceHasNoFileRepo__success();
    testServiceSearchWithMemoryRepo__existentItem__success();
    testServiceSearchWithFileRepo__existentItem__success();
    testServiceRemoveWithFileRepo__existentItem__itemRemoved();
    testServiceUpdateWithMemoryRepo__inexistentItem__exceptionThrown();
    testServiceUpdateWithFileRepo__inexistentItem__exceptionThrown();
    testServiceNext__withMemoryRepo__success();
    testServiceNext__withFileRepo__success();
    testServiceSave__withFileRepo__success();
    testServiceSave__withMemoryRepo__success();
    test_getter_and_setter_for_watchlist_filename();
    test_update_watchlist_html_file();
    testServiceUpdateWithFileRepo__existentItem__updatedItem();
}


void Tests::testRepositorySave__averageCase__elementAddedToWatchlist() {
    MemoryRepository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly2","1","01-13-3248",5,"prev124.mp15");
    repository.add(recording2);
    repository.save();

    vector<Recording> watchlist = repository.get_watchlist();
    Recording watchlist_element = watchlist[0];
    assert(watchlist_element.get_title() == recording.get_title());

    cout << "MemoryRepository save operation test passed!\n";
}


void Tests::testRepositoryNext__averageCase__incrementsToNextElement() {
    MemoryRepository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly2","1","01-13-3248",5,"prev124.mp15");
    repository.add(recording2);
    string element = repository.next();

    assert(element == "anomaly2, 1, 01-13-3248, 5, prev124.mp15");

    cout << "MemoryRepository next operation test passed!\n";
}


void Tests::testRepositoryAdd__duplicateElement__doesntAddElement() {
    MemoryRepository repository;

    Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    repository.add(recording);
    Recording recording2("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15");
    try {
        repository.add(recording);
    } catch(RepositoryException& re) {

    }

    vector<Recording> container = repository.get_container();
    assert(container.size() == 1);

    cout << "MemoryRepository duplicate element test passed!\n";
}




void Tests::test_recording_getters() {
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	

	assert(recording.get_title() == "anomaly");	
	assert(recording.get_location() == "deck D sector X1423");
	assert(recording.get_time_of_creation() == "01-13-3248");
	assert(recording.get_times_accessed() == 5);
	assert(recording.get_footage_preview() == "prev123.mp15");

	std::cout << "Recording getters tests passed!\n";
}


void Tests::test_recording_setters() {
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	

	recording.set_title("sometitle");
	assert(recording.get_title() == "sometitle");	

	std::cout << "Recording setters tests passed!\n";
}


void Tests::test_repository_add() {
	MemoryRepository repository;		

	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);

	vector<Recording> container = repository.get_container();
	assert(container[0].get_title() == recording.get_title());

	cout << "MemoryRepository add operation test passed!\n";
}


void Tests::test_service_add() {
	MemoryRepository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");

	vector<Recording> container = repository.get_container();
	assert(container.size() == 1);

	cout << "Service add operation test passed!\n";
}


void Tests::test_repository_delete() {
	MemoryRepository repository;
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);
	assert(repository.get_container().size() == 1);

	repository.remove("anomaly");
	assert(repository.get_container().size() == 0);

	cout << "MemoryRepository delete operation test passed!\n";
}


void Tests::test_service_delete() {
	MemoryRepository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");
	assert(repository.get_container().size() == 1);

	service.remove("anomaly");
	assert(repository.get_container().size() == 0);
	
	cout << "Service delete operation test passed!\n";
}


void Tests::test_repository_search() {
	MemoryRepository repository;
	Recording recording("anomaly","deck D sector X1423","01-13-3248",5,"prev123.mp15"); 	
	repository.add(recording);

	assert(repository.search("anomaly"));

	cout << "MemoryRepository search operation test passed!\n";
}


void Tests::test_service_update() {
	MemoryRepository repository;
	Service service(&repository);

	service.add("anomaly","deck D sector X1423","01-13-3248","5","prev123.mp15");
	assert(repository.get_container().size() == 1);

	service.update("anomaly", "deck X sector X200","01-13-3500","1","abc.mp4");
	vector<Recording> container = repository.get_container();
	assert(container[0].get_footage_preview() == "abc.mp4");
	cout << "Service update operation test passed!\n";
}


void Tests::testFileRepository__searchingAnElement__success() {
    FileRepository* repository = new FileRepository("test.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    repository->add(recording);

    assert(repository->search("1") == true);

    delete repository;
    cout << "File repository searching operation test passed!\n";
}


void Tests::testFileRepository__addingAnElement__success() {
    FileRepository* repository = new FileRepository("test1.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    repository->add(recording);

    assert(repository->search("1") == true);

    delete repository;
    cout << "File repository add operation test passed!\n";
}


void Tests::testFileRepository__removingAnElement__success() {
    FileRepository* repository = new FileRepository("test2.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");
    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    repository->remove("1");
    assert(repository->get_number_of_elements() == 1);

    delete repository;
    cout << "File repository remove operation test passed!\n";
}


void Tests::testFileRepository__addingADuplicateElement__success() {
    FileRepository* repository = new FileRepository("test3.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("1", "1", "01-01-2001", 1, "1.mp1");
    repository->add(recording);

    try {
        repository->add(recording2);
    } catch (std::exception& exc) {

    }

    assert(repository->search("1") == true);

    delete repository;
    cout << "File repository duplicate element addition test passed!\n";
}



void Tests::testFileRepository__searchingAnNonexistentElement__returnsFalse() {
    FileRepository* repository = new FileRepository("test4.in");

    assert(repository->search("5") == false);

    delete repository;
    cout << "File repository unexistent searched element test passed!\n";
}


void Tests::testFileRepository__removingANonexistingElement__fails() {
    FileRepository* repository = new FileRepository("test5.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");
    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    repository->remove("abc");
    assert(repository->get_number_of_elements() == 2);

    delete repository;
    cout << "File repository unexisting element removal test passed!\n";
}


void Tests::testFileRepository__getNextElement__success() {
    FileRepository* repository = new FileRepository("test6.in");

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");
    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    assert(repository->next() == "2, 2, 02-02-2002, 2, 2.mp1");
    assert(repository->next() == "1, 1, 01-01-2001, 1, 1.mp1");
    assert(repository->next() == "2, 2, 02-02-2002, 2, 2.mp1");

    delete repository;
    cout << "File repository next operation test passed!\n";
}


void Tests::testFileRepository__saveElement__success() {
    FileRepository* repository = new FileRepository("test7.in");

    try {
        repository->save();
    } catch (std::exception& exc) {}

    Recording recording("1", "1", "01-01-2001", 1, "1.mp1");
    Recording recording2("2", "2", "02-02-2002", 2, "2.mp1");

    repository->add(recording);
    repository->add(recording2);
    assert(repository->get_number_of_elements() == 2);

    repository->save();
    vector<Recording> watchlist = repository->get_watchlist();
    assert(watchlist.size() == 1);

    delete repository;
    cout << "File repository save operation test passed!\n";
}


void Tests::testFileRepository__getFilename__success() {
    FileRepository* repository = new FileRepository("test8.in");

    assert(repository->get_filename() == "test8.in");

    delete repository;
    cout << "File repository save operation test passed!\n";
}


void Tests::testRepositorySearch__searchingNonexistentElement__fails() {
    MemoryRepository* repository = new MemoryRepository();

    assert(repository->search("abc") == false);

    delete repository;
    cout << "File repository nonexistent element search test passed!\n";
}


void Tests::testServiceGetFileRepoFilename__getsFilename__success() {
    FileRepository* repository = new FileRepository("test9.in");
    Service* service = new Service(repository);

    assert(service->get_file_repository_filename() == "test9.in");

    delete repository;
    delete service;
    cout << "Service&fileRepo get filename test passed!\n";
}


void Tests::testServiceSetFileRepoFilename__setsFilename__success() {
    FileRepository* repository = new FileRepository("test10.in");
    Service* service = new Service(repository);

    assert(service->get_file_repository_filename() == "test10.in");
    service->set_file_repository_filename("test2.in");
    assert(service->get_file_repository_filename() == "test2.in");

    delete repository;
    delete service;
    cout << "Service&fileRepo set filename test passed!\n";
}


void Tests::testRepositorySetFileRepoFilename__setsFilename__success() {
    FileRepository* repository = new FileRepository("test11.in");

    repository->set_filename("test12.in");
    assert(repository->get_filename() == "test12.in");

    delete repository;
    cout << "FileRepo set filename test passed!\n";
}


void Tests::testRepositoryGetFileRepoFilename__getsFilename__success() {
    FileRepository* repository = new FileRepository("test13.in");

    assert(repository->get_filename() == "test13.in");

    delete repository;
    cout << "FileRepo get filename test passed!\n";
}


void Tests::testCommandFormatException() {
    try {
        throw CommandFormatException("Incorrect formatting!\n");
    } catch (CommandFormatException& exc) {

    }
}


void Tests::testFileRepoExistenceInService() {
    MemoryRepository repository;
    Service service(&repository);

    assert(service.does_service_have_file_repository() == false);
}


void Tests::testStrip() {
    MemoryRepository repository;
    Service service(&repository);
    string test_string = "   abc  \n";

    assert(StringFunctions::strip(test_string) == "abc");
}


void Tests::testTimeOfCreationValidation__incorrectFormatting__throwsException() {
    MemoryRepository repository;
    Service service(&repository);

    try {
        service.add("1", "1", "01-20", "5", "file.mp3");
    } catch (CommandFormatException& cfe) {

    }
}


void Tests::testTimeOfCreationValidation__invalidDate__throwsException() {
    MemoryRepository repository;
    Service service(&repository);

    try {
        service.add("1", "1", "32-50-2250", "5", "file.mp3");
    } catch (CommandFormatException& cfe) {

    }
}


void Tests::testServiceGetMemoryRepositoryContainer__serviceHasFileRepo__failure() {
    FileRepository repository("test16.txt");
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");
    vector<Recording> my_container = service.get_repository_container();

    assert(my_container.size() == 0);
}


void Tests::testServiceGetFileRepoFilename__serviceHasNoFileRepo__success() {
    MemoryRepository repository;
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");
    vector<Recording> my_container = service.get_repository_container();

    assert(my_container.size() == 1);
}


void Tests::testServiceSearchWithMemoryRepo__existentItem__success() {
    MemoryRepository repository;
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");

    assert(service.search("1") == true);
}


void Tests::testServiceSearchWithFileRepo__existentItem__success() {
    FileRepository repository("test17.txt");
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");

    assert(service.search("1") == true);
}


void Tests::testServiceRemoveWithFileRepo__existentItem__itemRemoved() {
    FileRepository repository("test17.txt");
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");
    service.remove("1");

    ifstream in(repository.get_filename());
    assert(in.peek() == std::ifstream::traits_type::eof());
}


void Tests::testServiceUpdateWithMemoryRepo__inexistentItem__exceptionThrown() {
    MemoryRepository repository;
    Service service(&repository);
    try {
        service.update("1", "1", "01-01-2001", "15", "file.mp4");
        assert(false);
    } catch (...) {
        assert(true);
    }
}


void Tests::testServiceUpdateWithFileRepo__inexistentItem__exceptionThrown() {
    FileRepository repository("test18.txt");
    Service service(&repository);

    try {
        service.update("1", "1", "01-01-2001", "15", "file.mp4");
        assert(false);
    } catch (...) {
        assert(true);
    }
}


void Tests::testServiceNext__withMemoryRepo__success() {
    MemoryRepository repository;
    Service service(&repository);
    service.add("1", "1", "01-01-2001", "15", "file.mp4");
    service.add("2", "2", "01-01-2001", "16", "file2.mp4");

    assert(service.next() == "2, 2, 01-01-2001, 16, file2.mp4");
}


void Tests::testServiceNext__withFileRepo__success() {
    FileRepository repository("test18.txt");
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");
    service.add("2", "2", "01-01-2001", "16", "file2.mp4");

    assert(service.next() == "2, 2, 01-01-2001, 16, file2.mp4");
}


void Tests::testServiceSave__withFileRepo__success() {
    FileRepository repository("test18.txt");
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");
    service.add("2", "2", "01-01-2001", "16", "file2.mp4");
    service.save();
    service.save();
    service.save();

    vector<Recording> container = service.get_watchlist();

    assert(container.size() == 3);
}


void Tests::testServiceSave__withMemoryRepo__success() {
    MemoryRepository repository;
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "15", "file.mp4");
    service.add("2", "2", "01-01-2001", "16", "file2.mp4");
    service.save();
    service.save();
    service.save();

    vector<Recording> container = service.get_watchlist();

    assert(container.size() == 3);
}


void Tests::test_getter_and_setter_for_watchlist_filename() {
    FileRepository repository("test19.txt");
    Service service(&repository);

    service.set_watchlist_filename("test_watchlist.csv");
    assert(repository.get_watchlist_filename() == "test_watchlist.csv");
}


void Tests::test_update_watchlist_html_file() {
    FileRepository repository("test20.txt");
    Service service(&repository);

    service.set_watchlist_filename("test_watchlist2.html");

    service.add("1", "1", "01-01-2001", "1", "test.mp1");
    service.add("2", "2", "02-02-2002", "2", "test2.mp2");

    service.next();
    service.save();

    vector<Recording> watchlist = repository.get_watchlist();

    assert(watchlist[0].get_as_string() == "2, 2, 02-02-2002, 2, test2.mp2");
}


void Tests::testServiceUpdateWithFileRepo__existentItem__updatedItem() {
    FileRepository repository("test20.txt");
    Service service(&repository);

    service.add("1", "1", "01-01-2001", "1", "test.mp1");
    service.update("1", "a", "01-01-2001", "1", "test2.mp1");

    ifstream in(repository.get_filename());
    string updated_element;
    getline(in, updated_element);

    assert(updated_element == "1, a, 01-01-2001, 1, test2.mp1");
}

**/
