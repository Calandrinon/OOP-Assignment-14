#include "playlistvisualization.h"
#include "ui_playlistvisualization.h"

PlaylistVisualization::PlaylistVisualization(vector<Recording> container, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaylistVisualization)
{
    ui->setupUi(this);
    this->table_model = new RecordingsTableModel(container);
    this->setup_table_view();
}


void PlaylistVisualization::setup_table_view() {
    ui->tableView->setModel(table_model);
}



PlaylistVisualization::~PlaylistVisualization()
{
    delete table_model;
    delete ui;
}
