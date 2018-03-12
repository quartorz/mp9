#ifndef UTILITY_H
#define UTILITY_H

#include <QString>

inline QString formatTime(qint64 time)
{
    auto s = time / 1000;
    return QString("%1:%2:%3.%4")
            .arg(QString::number(s / 3600), 2, '0').arg(QString::number((s / 60) % 60), 2, '0')
            .arg(QString::number(s % 60, 10), 2, '0').arg(QString::number(time % 1000), 3, '0');
}

#endif // UTILITY_H
