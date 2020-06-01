#include "playlistvisualization.h"
#include "ui_playlistvisualization.h"

PlaylistVisualization::PlaylistVisualization(Repository* _repository, QWidget *parent) :
    QDialog(parent),
    repository(_repository),
    ui(new Ui::PlaylistVisualization)
{
    ui->setupUi(this);
    this->table_model = new RecordingsTableModel(repository);
    this->setup_table_view();
}


void PlaylistVisualization::setup_table_view() {
    ui->tableView->setModel(table_model);
}



PlaylistVisualization::~PlaylistVisualization()
{
    delete ui;
}
