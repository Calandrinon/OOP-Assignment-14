#ifndef RECORDINGSTABLEMODEL_H
#define RECORDINGSTABLEMODEL_H
#include <QAbstractTableModel>
#include "repository.h"

class RecordingsTableModel: public QAbstractTableModel {
private:
    Repository* repository;

public:
    RecordingsTableModel(Repository* repository, QObject* parent = NULL);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    ~RecordingsTableModel();
};

#endif // RECORDINGSTABLEMODEL_H
