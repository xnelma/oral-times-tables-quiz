#ifndef OTTQ_20260519_1934_INCLUDE
#define OTTQ_20260519_1934_INCLUDE

#include <QObject>
#include <qqml.h>
#include <QStringListModel>

class LanguageListModel : public QStringListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    LanguageListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
};

#endif // OTTQ_20260519_1934_INCLUDE
