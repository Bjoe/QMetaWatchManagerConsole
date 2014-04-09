#include "metawatchscreenhandler.h"

#include <QList>

#include "widget.h"
#include "clockwidget.h"
#include "page.h"
#include "setwidgetlistmessage.h"

namespace qmwm {
namespace gui {

MetaWatchScreenHandler::MetaWatchScreenHandler(QObject *parent) :
    QObject(parent)
{
    qmwp::ClockWidget_t clockWidget1 = qmwp::ClockWidget::create(qmwp::ClockWidget::LOGO);
    qmwp::ClockWidget_t clockWidget2 = qmwp::ClockWidget::create(qmwp::ClockWidget::BIG);
    qmwp::ClockWidget_t clockWidget3 = qmwp::ClockWidget::create(qmwp::ClockWidget::FISH);
    qmwp::ClockWidget_t clockWidget4 = qmwp::ClockWidget::create(qmwp::ClockWidget::UP_HORIZONTAL);
    qmwp::ClockWidget_t clockWidget5 = qmwp::ClockWidget::create(qmwp::ClockWidget::BOTTOM_RIGHT);

    qmwp::Page_t page1 = qmwp::Page_t(new qmwp::Page(qmwp::Page::FIRST));
    page1->addWidget(clockWidget4);
    page1->addWidget(clockWidget5);

    qmwp::Page_t page2 = qmwp::Page_t(new qmwp::Page(qmwp::Page::SECOND));
    page2->addWidget(clockWidget1);

    qmwp::Page_t page3 = qmwp::Page_t(new qmwp::Page(qmwp::Page::THIRD));
    page3->addWidget(clockWidget2);

    qmwp::Page_t page4 = qmwp::Page_t(new qmwp::Page(qmwp::Page::FOURTH));
    page4->addWidget(clockWidget3);

    m_screen.addPage(page1);
    m_screen.addPage(page2);
    m_screen.addPage(page3);
    m_screen.addPage(page4);
}

void MetaWatchScreenHandler::onSendSetWidgetList(const qmwp::core::ProtocolDispatcher* dispatcher) const
{
    QList<qmwp::SetWidgetListMessage_t> messages = m_screen.createMessages();

    for(qmwp::SetWidgetListMessage_t message : messages) {
        dispatcher->send(message.data());
    }
}

} // namespace gui
} // namespace qmwm
