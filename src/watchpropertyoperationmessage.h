#ifndef QMWP_WATCHPROPERTYOPERATIONMESSAGE_H
#define QMWP_WATCHPROPERTYOPERATIONMESSAGE_H

#include <memory>

#include "core/metawatchmessage.h"

namespace qmwp {

class WatchPropertyOperationMessage : public core::Message
{
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

    void setShowSeconds(Seconds show);
    Seconds showSeconds() const;

    void setDateFormat(DateFormat format);
    DateFormat dateFormat() const;

    void setShowSeparationLine(Separation show);
    Separation showSeparationLine() const;

    void setAutoBacklight(Backlight light);
    Backlight autoBacklight() const;

    void setOperation(Operation rw);
    Operation operation() const;

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

} // namespace qmwp

#endif // QMWP_WATCHPROPERTYOPERATIONMESSAGE_H
