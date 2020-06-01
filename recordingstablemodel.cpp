#include "recordingstablemodel.h"
#include <QDebug>

RecordingsTableModel::RecordingsTableModel(vector<Recording> container, QObject* parent): QAbstractTableModel(parent) {
    this->container = container;
}
RecordingsTableModel::~RecordingsTableModel() {}


int RecordingsTableModel::rowCount(const QModelIndex &parent) const {
    unsigned int number_of_recordings = container.size();
    return number_of_recordings;
}


int RecordingsTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}


QVariant RecordingsTableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column(); 

    if (row == container.size()) {
        return QVariant();
    }

    Recording recording = container[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
            case 0:
                return QString::fromStdString(recording.get_title());

            case 1:
                return QString::fromStdString(recording.get_location());

            case 2:
                return QString::fromStdString(recording.get_time_of_creation());

            case 3:
                return QString::fromStdString(std::to_string(recording.get_times_accessed()));

            case 4:
                return QString::fromStdString(recording.get_footage_preview());
        }
    }
}
