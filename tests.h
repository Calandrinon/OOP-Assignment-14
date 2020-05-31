#ifndef __TESTS_H__
#define __TESTS_H__
#include "repository.h"
#include "service.h"
#include "myexceptions.h"

class Tests {
	public:
		Tests();
		void test_recording_getters();
		void test_recording_setters();
		void test_repository_add();
		void test_service_add();
		void test_repository_delete();
		void test_service_delete();
		void test_repository_search();
		void test_service_update();
        void testRepositoryAdd__duplicateElement__doesntAddElement();
        void testRepositorySearch__searchingNonexistentElement__fails();
        void testRepositoryNext__averageCase__incrementsToNextElement();
        void testRepositorySave__averageCase__elementAddedToWatchlist();
        void testFileRepository__addingAnElement__success();
        void testFileRepository__addingADuplicateElement__success();
        void testFileRepository__removingAnElement__success();
        void testFileRepository__removingANonexistingElement__fails();
        void testFileRepository__searchingAnElement__success();
        void testFileRepository__searchingAnNonexistentElement__returnsFalse();
        void testFileRepository__getNextElement__success();
        void testFileRepository__saveElement__success();
        void testFileRepository__getFilename__success();
        void testServiceGetFileRepoFilename__getsFilename__success();
        void testServiceSetFileRepoFilename__setsFilename__success();
        void testRepositorySetFileRepoFilename__setsFilename__success();
        void testRepositoryGetFileRepoFilename__getsFilename__success();
        void testCommandFormatException();
        void testFileRepoExistenceInService();
        void testStrip();
        void testTimeOfCreationValidation__incorrectFormatting__throwsException();
        void testTimeOfCreationValidation__invalidDate__throwsException();
        void testServiceGetMemoryRepositoryContainer__serviceHasFileRepo__failure();
        void testServiceGetFileRepoFilename__serviceHasNoFileRepo__success();
        void testServiceSearchWithMemoryRepo__existentItem__success();
        void testServiceSearchWithFileRepo__existentItem__success();
        void testServiceRemoveWithFileRepo__existentItem__itemRemoved();
        void testServiceUpdateWithMemoryRepo__inexistentItem__exceptionThrown();
        void testServiceUpdateWithFileRepo__inexistentItem__exceptionThrown();
        void testServiceUpdateWithFileRepo__existentItem__updatedItem();
        void testServiceNext__withMemoryRepo__success();
        void testServiceNext__withFileRepo__success();
        void testServiceSave__withFileRepo__success();
        void testServiceSave__withMemoryRepo__success();
        void test_getter_and_setter_for_watchlist_filename();
        void test_update_watchlist_html_file();
};

#endif
