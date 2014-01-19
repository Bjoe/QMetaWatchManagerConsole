#ifndef QMWP_WATCHPROPERTYOPERATIONMESSAGE_H
#define QMWP_WATCHPROPERTYOPERATIONMESSAGE_H

#include <memory>
#include <QObject>

#include "core/metawatchmessage.h"

namespace qmwp {

class WatchPropertyOperationMessage : public QObject, public core::Message
{
    Q_OBJECT

    Q_ENUMS(ClockFormat)
    Q_ENUMS(Seconds)
    Q_ENUMS(DateFormat)
    Q_ENUMS(Separation)
    Q_ENUMS(Backlight)
    Q_ENUMS(Operation)

    Q_PROPERTY(qmwp::WatchPropertyOperationMessage::ClockFormat clockFormat READ clockFormat WRITE setClockFormat NOTIFY clockFormatChanged)
    Q_PROPERTY(bool clockFormatChecked READ clockFormatChecked WRITE setClockFormatChecked NOTIFY clockFormatChanged)
    Q_PROPERTY(qmwp::WatchPropertyOperationMessage::Seconds showSeconds READ showSeconds WRITE setShowSeconds NOTIFY showSecondsChanged)
    Q_PROPERTY(bool showSecondsChecked READ showSecondsChecked WRITE setShowSecondsChecked NOTIFY showSecondsChanged)
    Q_PROPERTY(qmwp::WatchPropertyOperationMessage::DateFormat dateFormat READ dateFormat WRITE setDateFormat NOTIFY dateFormatChanged)
    Q_PROPERTY(bool dateFormatChecked READ dateFormatChecked WRITE setDateFormatChecked NOTIFY dateFormatChanged)
    Q_PROPERTY(qmwp::WatchPropertyOperationMessage::Separation showSeparationLine READ showSeparationLine WRITE setShowSeparationLine NOTIFY showSeparationLineChanged)
    Q_PROPERTY(bool showSeparationLineChecked READ showSeparationLineChecked WRITE setShowSeparationLineChecked NOTIFY showSeparationLineChanged)
    Q_PROPERTY(qmwp::WatchPropertyOperationMessage::Backlight autoBacklight READ autoBacklight WRITE setAutoBacklight NOTIFY autoBacklightChanged)
    Q_PROPERTY(bool autoBacklightChecked READ autoBacklightChecked WRITE setAutoBacklightChecked NOTIFY autoBacklightChanged)
    Q_PROPERTY(qmwp::WatchPropertyOperationMessage::Operation operation READ operation WRITE setOperation NOTIFY operationChanged)
    Q_PROPERTY(bool operationChecked READ operationChecked WRITE setOperationChecked NOTIFY operationChanged)

public:
    WatchPropertyOperationMessage();
    virtual ~WatchPropertyOperationMessage();

    enum class ClockFormat { H24, H12 };
    enum class Seconds { ON, OFF };
    enum class DateFormat { DDMM, MMDD };
    enum class Separation { ON, OFF };
    enum class Backlight { ENABLE, DISABLE };
    enum class Operation { READ, WRITE };

    void setClockFormat(ClockFormat format);
    ClockFormat clockFormat() const;
    void setClockFormatChecked(bool checked);
    bool clockFormatChecked() const;

    void setShowSeconds(Seconds show);
    Seconds showSeconds() const;
    void setShowSecondsChecked(bool checked);
    bool showSecondsChecked() const;

    void setDateFormat(DateFormat format);
    DateFormat dateFormat() const;
    void setDateFormatChecked(bool checked);
    bool dateFormatChecked() const;

    void setShowSeparationLine(Separation show);
    Separation showSeparationLine() const;
    void setShowSeparationLineChecked(bool checked);
    bool showSeparationLineChecked() const;

    void setAutoBacklight(Backlight light);
    Backlight autoBacklight() const;
    void setAutoBacklightChecked(bool checked);
    bool autoBacklightChecked() const;

    void setOperation(Operation rw);
    Operation operation() const;
    void setOperationChecked(bool checked);
    bool operationChecked() const;

signals:
    void clockFormatChanged();
    void showSecondsChanged();
    void dateFormatChanged();
    void showSeparationLineChanged();
    void autoBacklightChanged();
    void operationChanged();

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

} // namespace qmwp

#endif // QMWP_WATCHPROPERTYOPERATIONMESSAGE_H
