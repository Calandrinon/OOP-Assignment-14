#include "recordingstablemodel.h"

RecordingsTableModel::RecordingsTableModel(Repository* _repository, QObject* parent): QAbstractTableModel(parent), repository(_repository){}
RecordingsTableModel::~RecordingsTableModel() {}


int RecordingsTableModel::rowCount(const QModelIndex &parent) const {
    unsigned int number_of_recordings = repository->get_container().size();
    return number_of_recordings;
}


int RecordingsTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}


QVariant RecordingsTableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();

    vector<Recording> recordings = repository->get_container();

    if (row == recordings.size()) {
        return QVariant();
    }

    Recording recording = recordings[row];

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
