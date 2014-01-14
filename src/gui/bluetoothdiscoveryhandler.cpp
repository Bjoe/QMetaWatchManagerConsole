#include "bluetoothdiscoveryhandler.h"

namespace qmwm {
namespace gui {

BluetoothDiscoveryHandler::BluetoothDiscoveryHandler(QObject *parent) :
    QObject(parent),
    m_error(BluetoothDiscoveryHandler::NoError),
    m_model(new BluetoothDiscoveryModel(parent)),
    m_agent(new QBluetoothServiceDiscoveryAgent(parent)),
    m_running(false)
{
    connect(m_agent, SIGNAL(serviceDiscovered(const QBluetoothServiceInfo&)), m_model, SLOT(add(const QBluetoothServiceInfo&)));
    connect(m_agent, SIGNAL(finished()), this, SLOT(finishedDiscovery()));
    connect(m_agent, SIGNAL(canceled()), this, SLOT(finishedDiscovery()));
    connect(m_agent, SIGNAL(error(QBluetoothServiceDiscoveryAgent::Error)), this, SLOT(errorDiscovery(QBluetoothServiceDiscoveryAgent::Error)));
}

BluetoothDiscoveryHandler::Error BluetoothDiscoveryHandler::error() const
{
    return m_error;
}

bool BluetoothDiscoveryHandler::running() const
{
    return m_running;
}

void BluetoothDiscoveryHandler::setRunning(bool running)
{
    m_running = running;
    emit runningChanged();
}

BluetoothDiscoveryModel *BluetoothDiscoveryHandler::model() const
{
    return m_model;
}

void BluetoothDiscoveryHandler::setModel(BluetoothDiscoveryModel *model)
{
    m_model = model;
    emit modelChanged();
}

void BluetoothDiscoveryHandler::discover()
{
    if(m_running == true) {
        m_agent->stop();
    }
    m_model->clearModel();

    setRunning(true);
    m_agent->start();
}

void BluetoothDiscoveryHandler::finishedDiscovery()
{
    setRunning(false);
}

void BluetoothDiscoveryHandler::errorDiscovery(QBluetoothServiceDiscoveryAgent::Error error)
{
    m_error = static_cast<BluetoothDiscoveryHandler::Error>(error);
    emit errorChanged();
}

} // namespace gui
} // namespace qmwm
