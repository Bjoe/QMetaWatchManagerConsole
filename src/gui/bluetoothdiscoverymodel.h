#ifndef QMWM_GUI_BLUETOOTHDISCOVERYMODEL_H
#define QMWM_GUI_BLUETOOTHDISCOVERYMODEL_H

#include <QObject>
#include <QVariant>
#include <QModelIndex>
#include <QAbstractListModel>
#include <QtBluetooth/QBluetoothServiceInfo>

namespace qmwm {
namespace gui {

class BluetoothDiscoveryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit BluetoothDiscoveryModel(QObject *parent = 0);
    virtual ~BluetoothDiscoveryModel();

    enum {
        Name = Qt::UserRole + 1,
        DeviceName,
        RemoteAddress
    };

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void clearModel();

    const QBluetoothServiceInfo *get(int row) const;

public slots:
    void add(const QBluetoothServiceInfo& service);

private:
    QList<const QBluetoothServiceInfo *> m_services;
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_BLUETOOTHDISCOVERYMODEL_H
