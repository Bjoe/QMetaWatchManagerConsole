#include "bluetoothdiscoverymodel.h"

#include <QByteArray>
#include <QHash>
#include <QAbstractItemModel>
#include <QtBluetooth/QBluetoothDeviceInfo>

namespace qmwm {
namespace gui {

BluetoothDiscoveryModel::BluetoothDiscoveryModel(QObject *parent) :
    QAbstractListModel(parent), m_services{}
{
}

BluetoothDiscoveryModel::~BluetoothDiscoveryModel()
{
    qDeleteAll(m_services);
    m_services.clear();
}

int BluetoothDiscoveryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_services.count();
}

QVariant BluetoothDiscoveryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0)
        return QVariant();

    if (index.row() >= m_services.count()){
        qWarning() << "index out of bounds";
        return QVariant();
    }

    const QBluetoothServiceInfo *service = m_services.value(index.row());
    const QBluetoothDeviceInfo deviceInfo = service->device();
    switch (role) {
    case Name: {
        QString label = deviceInfo.name();
        if (label.isEmpty())
            label += deviceInfo.address().toString();
        else
            label+= QStringLiteral(":");
        label += QStringLiteral(" ") + service->serviceName();
        return label;
    }
    case DeviceName:
        return deviceInfo.name();
    case RemoteAddress:
        return deviceInfo.address().toString();
    }
    return QVariant();
}

QHash<int, QByteArray> BluetoothDiscoveryModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames = QAbstractItemModel::roleNames();
    roleNames.insert(Name, "name");
    roleNames.insert(RemoteAddress, "remoteAddress");
    roleNames.insert(DeviceName, "deviceName");
    return roleNames;
}

void BluetoothDiscoveryModel::clearModel()
{
    beginResetModel();
    qDeleteAll(m_services);
    m_services.clear();
    endResetModel();
}

void BluetoothDiscoveryModel::add(const QBluetoothServiceInfo &service)
{
    const QBluetoothServiceInfo* current = nullptr;
    for(int i = 0; i < m_services.count(); ++i) {
        current = m_services.at(i);
        if(current->serviceName() == service.serviceName() &&
                current->device().address() == service.device().address()) {
            return;
        }
    }

    beginInsertRows(QModelIndex(), m_services.count(), m_services.count());
    m_services.append(new QBluetoothServiceInfo(service));
    endInsertRows();
}

const QBluetoothServiceInfo *BluetoothDiscoveryModel::get(int row) const
{
    return m_services.at(row);
}

} // namespace gui
} // namespace qmwm
