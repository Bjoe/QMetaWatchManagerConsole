#include "portinfomodel.h"

#include <QDebug>

namespace qmwm {
namespace gui {

PortInfoModel::PortInfoModel(QObject *parent) :
    QAbstractListModel(parent), m_roles(), m_portInfo()
{
    m_portInfo = QSerialPortInfo::availablePorts();

    qDebug() << m_portInfo.size();

    m_roles[Qt::UserRole + 1] = QString("portName").toUtf8();
    m_roles[Qt::UserRole + 2] = QString("systemLocation").toUtf8();
    m_roles[Qt::UserRole + 3] = QString("description").toUtf8();
    m_roles[Qt::UserRole + 4] = QString("manufacturer").toUtf8();
}

int PortInfoModel::rowCount(const QModelIndex &parent) const
{
    return m_portInfo.size();
}

QVariant PortInfoModel::data(const QModelIndex &index, int role) const
{
    QSerialPortInfo portInfo = m_portInfo.at(index.row());

    switch(role - Qt::UserRole) {

    case 1:
        return QVariant(portInfo.portName());

    case 2:
        return QVariant(portInfo.systemLocation());

    case 3:
        return QVariant(portInfo.description());

    case 4:
        return QVariant(portInfo.manufacturer());
    }
    return QVariant("--");
}

QHash<int, QByteArray> PortInfoModel::roleNames() const
{
    return m_roles;
}

QSerialPortInfo PortInfoModel::at(int index)
{
    return m_portInfo.at(index);
}

} // namespace gui
} // namespace qmwm
