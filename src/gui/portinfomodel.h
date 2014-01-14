#ifndef QMWM_GUI_PORTINFOMODEL_H
#define QMWM_GUI_PORTINFOMODEL_H

#include <QObject>
#include <QByteArray>
#include <QModelIndex>
#include <QHash>
#include <QList>
#include <QVariant>
#include <QAbstractListModel>
#include <QtSerialPort/QSerialPortInfo>

namespace qmwm {
namespace gui {

class PortInfoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PortInfoModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int,QByteArray> roleNames() const;

    QSerialPortInfo at(int index);

private:
    QHash<int, QByteArray> m_roles;
    QList<QSerialPortInfo> m_portInfo;
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_PORTINFOMODEL_H
