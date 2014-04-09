#ifndef QMWM_GUI_METAWATCHSCREENHANDLER_H
#define QMWM_GUI_METAWATCHSCREENHANDLER_H

#include <QObject>

#include "core/protocoldispatcher.h"
#include "screen.h"

namespace qmwm {
namespace gui {

class MetaWatchScreenHandler : public QObject
{
    Q_OBJECT
public:
    explicit MetaWatchScreenHandler(QObject *parent = 0);

signals:

public slots:
    void onSendSetWidgetList(const qmwp::core::ProtocolDispatcher* dispatcher) const;

private:
    qmwp::Screen m_screen{};
};

} // namespace gui
} // namespace qmwm

#endif // QMWM_GUI_METAWATCHSCREENHANDLER_H
