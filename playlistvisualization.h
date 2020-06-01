#ifndef PLAYLISTVISUALIZATION_H
#define PLAYLISTVISUALIZATION_H
#include "recordingstablemodel.h"

#include <QDialog>

namespace Ui {
class PlaylistVisualization;
}

class PlaylistVisualization : public QDialog
{
    Q_OBJECT

public:
    explicit PlaylistVisualization(Repository* _repository, QWidget *parent = nullptr);
    ~PlaylistVisualization();

private:
    void setup_table_view();

private:
    RecordingsTableModel* table_model;
    Repository* repository;
    Ui::PlaylistVisualization *ui;
};

#endif // PLAYLISTVISUALIZATION_H
