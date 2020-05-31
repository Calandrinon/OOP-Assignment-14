#include <iostream>
#include <vector>
#include "tests.h"
#include "ui.h"
//#include <crtdbg.h>
#include "gui.h"
#include "dialog.h"
#include <memory>
#include <QApplication>
#include <fstream>
#include "string_functions.h"
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    //Tests();
    QApplication a(argc, argv);

    Dialog dialog;
    dialog.exec();

    ifstream in("config.txt");
    string line, repo_type="MemoryRepository";

    while (getline(in, line)) {
        qDebug() << QString::fromStdString(line);
        if (line[0] == '#') {
            continue;
        } else {
            line = StringFunctions::strip(line);
            vector<string> tokens = StringFunctions::tokenize(line, '=');

            for (auto token: tokens) {
                token = StringFunctions::strip(token);
            }

            if (tokens[0] == "repo_type") {
                repo_type = tokens[1];
            }

            qDebug() << QString::fromStdString(line);
        }
    }


    Repository* repository;
    if (repo_type == "FileRepository") {
        repository = new FileRepository("in.in");
    } else {
        repository = new MemoryRepository();
    }

    Service service(repository);
    GUI gui(&service);
    gui.show();

    //_CrtDumpMemoryLeaks();
    return a.exec();
}
