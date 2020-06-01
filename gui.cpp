#include "gui.h"
#include <iostream>
#include <vector>
#include "playlistvisualization.h"
using namespace std;

GUI::GUI(Service* _service, QWidget *parent) :
    QWidget(parent),
  service(_service)
{
    this->initGUI();
    this->connect_signals_and_slots();

    /// The 10 items used for debugging
    service->add("1", "1", "01-01-2001", "1", "1.mp1");
    service->add("2", "2", "02-02-2002", "2", "2.mp2");
    service->add("3", "3", "03-03-2003", "3", "3.mp3");
    service->add("4", "4", "04-04-2004", "4", "4.mp4");
    service->add("5", "5", "04-04-2005", "5", "5.mp4");
    service->add("6", "6", "04-04-2006", "6", "6.mp4");
    service->add("7", "7", "04-04-2007", "7", "7.mp4");
    service->add("8", "8", "04-04-2008", "8", "8.mp4");
    service->add("9", "9", "04-04-2009", "9", "9.mp4");
    service->add("10", "10", "04-04-2010", "10", "10.mp4");
    this->add_recordings_to_list_widget();

    if (service->does_service_have_file_repository()) {
        service->set_watchlist_filename("myhtml.html");
    }
}


void GUI::initGUI() {
    QHBoxLayout* main_layout = new QHBoxLayout(this);
    QVBoxLayout* element_addition_layout = new QVBoxLayout();
    QVBoxLayout* queue_button_layout = new QVBoxLayout();
    QVBoxLayout* playlist_layout = new QVBoxLayout();
    QFormLayout* element_addition_form = new QFormLayout();
    QGridLayout* buttons_layout = new QGridLayout();
    QString visualization_text("Visualize playlist in a table view");
    this->playlist_visualization_button = new QPushButton(visualization_text);


    QLabel* playlist_label = new QLabel("Playlist:");
    this->playlist_widget = new QListWidget();
    playlist_layout->addWidget(playlist_visualization_button);
    playlist_layout->addWidget(playlist_label);
    playlist_layout->addWidget(playlist_widget);

    QString next_text("Next");
    this->next_button = new QPushButton(next_text);
    playlist_layout->addWidget(next_button);

    QString play_text("Play");
    this->play_button = new QPushButton(play_text);
    playlist_layout->addWidget(play_button);


    QString add_text("Add");
    this->add_button = new QPushButton(add_text);
    buttons_layout->addWidget(add_button, 1, 1);

    QString update_text("Update");
    this->update_button = new QPushButton(update_text);
    buttons_layout->addWidget(update_button, 1, 2);

    QString delete_text("Delete");
    this->delete_button = new QPushButton(delete_text);
    buttons_layout->addWidget(delete_button, 1, 3);

    QString undo_text("Undo");
    this->undo_button = new QPushButton(undo_text);
    buttons_layout->addWidget(undo_button, 2, 1);

    QString redo_text("Redo");
    this->redo_button= new QPushButton(redo_text);
    buttons_layout->addWidget(redo_button, 2, 3);

    QString add_to_playlist_text(">> Save >>");
    this->add_to_playlist_button = new QPushButton(add_to_playlist_text);
    queue_button_layout->addWidget(add_to_playlist_button);




    QLabel* elements = new QLabel("Recordings:");
    element_addition_layout->addWidget(elements);

    this->recordings_list = new QListWidget;
    element_addition_layout->addWidget(this->recordings_list);

    QLabel* title_label = new QLabel("Title: ");
    this->title_edit = new QLineEdit();
    element_addition_form->addRow(title_label, this->title_edit);

    QLabel* location_label = new QLabel("Location: ");
    this->location_edit = new QLineEdit();
    element_addition_form->addRow(location_label, this->location_edit);

    QLabel* time_of_creation_label = new QLabel("Time of creation: ");
    this->time_of_creation_edit = new QLineEdit();
    element_addition_form->addRow(time_of_creation_label, this->time_of_creation_edit);

    QLabel* times_accessed_label = new QLabel("Times accessed: ");
    this->times_accessed_edit = new QLineEdit();
    element_addition_form->addRow(times_accessed_label, this->times_accessed_edit);

    QLabel* footage_preview_label = new QLabel("Footage preview: ");
    this->footage_preview_edit = new QLineEdit();
    element_addition_form->addRow(footage_preview_label, this->footage_preview_edit);


    element_addition_layout->addLayout(element_addition_form);
    element_addition_layout->addLayout(buttons_layout);
    main_layout->addLayout(element_addition_layout);
    main_layout->addLayout(queue_button_layout);
    main_layout->addLayout(playlist_layout);
}


void GUI::connect_signals_and_slots() {
    /// Connects the add button to its corresponding handler
    QObject::connect(this->add_button, &QPushButton::clicked, this, &GUI::add_recording_button_handler);

    /// Changes the text in the line edits whenever a list widget item is selected
    QObject::connect(this->recordings_list, &QListWidget::itemSelectionChanged, this, &GUI::update_line_edits);

    QObject::connect(this->update_button, &QPushButton::clicked, this, &GUI::update_recording_button_handler);

    QObject::connect(this->delete_button, &QPushButton::clicked, this, &GUI::delete_recording_button_handler);

    QObject::connect(this->add_to_playlist_button, &QPushButton::clicked, this, &GUI::save_recording_button_handler);

    QObject::connect(this->playlist_widget, &QListWidget::itemSelectionChanged, this, &GUI::update_current_recording);

    QObject::connect(this->next_button, &QPushButton::clicked, this, &GUI::next_recording_button_handler);

    QObject::connect(this->play_button, &QPushButton::clicked, this, &GUI::play_recording_button_handler);

    QObject::connect(this->undo_button, &QPushButton::clicked, this, &GUI::undo_button_handler);

    QObject::connect(this->redo_button, &QPushButton::clicked, this, &GUI::redo_button_handler);

    QObject::connect(this->playlist_visualization_button, &QPushButton::clicked, this, &GUI::playlist_visualization_button_handler);
}


void GUI::add_recording_button_handler() {
    string title = this->title_edit->text().toStdString();
    string location = this->location_edit->text().toStdString();
    string time_of_creation = this->time_of_creation_edit->text().toStdString();
    string times_accessed = this->times_accessed_edit->text().toStdString();
    string footage_preview = this->footage_preview_edit->text().toStdString();

    vector<string> operation = {"delete", title, location, time_of_creation, times_accessed, footage_preview};

    try {
        string message =  title + " " + location + " " + time_of_creation + " " + times_accessed + " " +footage_preview;
        service->add(title, location, time_of_creation, times_accessed, footage_preview);
        service->push_to_undo_stack(operation);
    } catch (...) {

    }

    this->add_recordings_to_list_widget();
}


void GUI::update_recording_button_handler() {
    string title = this->title_edit->text().toStdString();
    string location = this->location_edit->text().toStdString();
    string time_of_creation = this->time_of_creation_edit->text().toStdString();
    string times_accessed = this->times_accessed_edit->text().toStdString();
    string footage_preview = this->footage_preview_edit->text().toStdString();
    vector<Recording> container = service->get_repository_container();

    Recording searched_recording;
    for (auto recording: container) {
        if (recording.get_title() == title) {
            searched_recording = recording;
        }
    }

    vector<string> operation = {"update", searched_recording.get_title(),
                               searched_recording.get_location(),
                               searched_recording.get_time_of_creation(),
                               std::to_string(searched_recording.get_times_accessed()),
                               searched_recording.get_footage_preview()};
    for (auto token: operation) {
        qDebug() << QString::fromStdString(token);
    }

    try {
        string message =  title + " " + location + " " + time_of_creation + " " + times_accessed + " " +footage_preview;
        service->update(title, location, time_of_creation, times_accessed, footage_preview);
        service->push_to_undo_stack(operation);
    } catch (...) {

    }

    this->add_recordings_to_list_widget();
}


void GUI::delete_recording_button_handler() {
    string title = this->title_edit->text().toStdString();
    string location = this->location_edit->text().toStdString();
    string time_of_creation = this->time_of_creation_edit->text().toStdString();
    string times_accessed = this->times_accessed_edit->text().toStdString();
    string footage_preview = this->footage_preview_edit->text().toStdString();

    vector<string> operation = {"add", title, location, time_of_creation, times_accessed, footage_preview};

    try {
        string message =  title + " " + location + " " + time_of_creation + " " + times_accessed + " " +footage_preview;
        service->remove(title);
        service->push_to_undo_stack(operation);
    } catch (...) {

    }

    this->add_recordings_to_list_widget();
}


void GUI::save_recording_button_handler() {
    string title = this->title_edit->text().toStdString();
    string location = this->location_edit->text().toStdString();
    string time_of_creation = this->time_of_creation_edit->text().toStdString();
    string times_accessed = this->times_accessed_edit->text().toStdString();
    string footage_preview = this->footage_preview_edit->text().toStdString();
    try {
        string message =  title + " " + location + " " + time_of_creation + " " + times_accessed + " " +footage_preview;
        service->save(title);
    } catch (...) {

    }

    this->add_recordings_to_playlist();
}


void GUI::add_recordings_to_list_widget() {
    if (this->recordings_list->count() > 0) {
        this->recordings_list->clear();
    }

    vector<Recording> container = service->get_repository_container();

    for (auto recording: container) {
        string recording_as_string = recording.get_title() + "; " + recording.get_location() + "; " + recording.get_time_of_creation() + "; " + std::to_string(recording.get_times_accessed()) + "; " + recording.get_footage_preview();
        QString item_in_list = QString::fromStdString(recording_as_string);
        QListWidgetItem* recording_list_item = new QListWidgetItem(item_in_list);
        this->recordings_list->addItem(recording_list_item);
    }

    if (this->recordings_list->count() > 0) {
        this->recordings_list->setCurrentRow(0);
    }
}


void GUI::add_recordings_to_playlist() {
    if (this->playlist_widget->count() > 0) {
        this->playlist_widget->clear();
    }

    vector<Recording> watchlist = service->get_watchlist();

    for (auto recording: watchlist) {
        string recording_as_string = recording.get_title() + "; " + recording.get_location() + "; " + recording.get_time_of_creation() + "; " + std::to_string(recording.get_times_accessed()) + "; " + recording.get_footage_preview();
        QString item_in_list = QString::fromStdString(recording_as_string);
        QListWidgetItem* playlist_item= new QListWidgetItem(item_in_list);
        this->playlist_widget->addItem(playlist_item);
    }

    if (this->playlist_widget->count() > 0) {
        this->playlist_widget->setCurrentRow(service->get_selected_recording_index());
    }
}



int GUI::get_current_index()
{
    if (this->recordings_list->count() == 0)
        return -1;

    // get selected index
    QModelIndexList index = this->recordings_list->selectionModel()->selectedIndexes();
    if (index.size() == 0)
    {
        this->title_edit->clear();
        this->location_edit->clear();
        this->time_of_creation_edit->clear();
        this->times_accessed_edit->clear();
        this->footage_preview_edit->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}


int GUI::get_current_playlist_index()
{
    if (this->playlist_widget->count() == 0)
        return -1;

    // get selected index
    QModelIndexList index = this->playlist_widget->selectionModel()->selectedIndexes();
    if (index.size() == 0)
    {
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}


void GUI::update_line_edits() {
    vector<Recording> container = service->get_repository_container();
    int item_index = this->get_current_index();

    if (item_index == -1) {
        return;
    }

    if (item_index >= container.size()) {
        return;
    }

    Recording recording = container[item_index];
    this->title_edit->setText(QString::fromStdString(recording.get_title()));
    this->location_edit->setText(QString::fromStdString(recording.get_location()));
    this->time_of_creation_edit->setText(QString::fromStdString(recording.get_time_of_creation()));
    this->times_accessed_edit->setText(QString::fromStdString(std::to_string(recording.get_times_accessed())));
    this->footage_preview_edit->setText(QString::fromStdString(recording.get_footage_preview()));
}


void GUI::update_current_recording() {
    vector<Recording> watchlist = service->get_watchlist();
    int current_index = this->get_current_playlist_index();

    try {
        if (current_index < 0) {
            qDebug() << "current index less than 0";
            return;
        }
        service->set_current_recording(current_index);
    } catch (...) {

    }
}


void GUI::next_recording_button_handler() { 
    int current_index = this->get_current_playlist_index();

    if (playlist_widget->count() == 0) {
        return;
    }

    service->next();
    if (playlist_widget->count() == current_index + 1) {
        playlist_widget->setCurrentRow(0);
    } else {
        playlist_widget->setCurrentRow(current_index+1);
    }
}


void GUI::play_recording_button_handler() {
    if (this->playlist_widget->count() == 0) {
        return;
    }

    int current_index = service->get_selected_recording_index();
    if (current_index == this->playlist_widget->count() - 1 && current_index != 0) {
        service->set_selected_recording_index(current_index-1);
    }

    current_index = this->get_current_playlist_index();
    qDebug() << current_index;
    vector<Recording> watchlist = service->get_watchlist();
    service->remove_from_watchlist(current_index);
    add_recordings_to_playlist();
}


void GUI::undo_button_handler() {
    service->undo();
    this->add_recordings_to_list_widget();
}


void GUI::redo_button_handler() {
    service->redo();
    this->add_recordings_to_list_widget();
}


void GUI::playlist_visualization_button_handler() {
    vector<Recording> container = service->get_repository_container();
    qDebug() << "From playlist_visualization handler";
    for (auto object: container) {
        qDebug() << QString::fromStdString(object.get_as_string());
    }

    PlaylistVisualization visualization(container);
    visualization.setModal(true);
    visualization.exec();
}


GUI::~GUI()
{
    delete playlist_widget;
    delete next_button;
    delete play_button;
    delete add_button;
    delete update_button;
    delete delete_button;
    delete add_to_playlist_button;
    delete recordings_list;
    delete title_edit;
    delete location_edit;
    delete time_of_creation_edit;
    delete times_accessed_edit;
    delete footage_preview_edit;
}
