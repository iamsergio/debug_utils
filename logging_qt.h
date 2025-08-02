// SPDX-FileCopyrightText: 2025 Sergio Martins
// SPDX-License-Identifier: MIT

#pragma once

#include <QFile>
#include <QDate>
#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>

namespace debug_utils {

inline QString defaultFile()
{
    QString appName = QCoreApplication::applicationName();
    QString dateString = QDate::currentDate().toString("yyyyMMdd");
    QString fileName = QStringLiteral("log-%1-%2.log").arg(appName, dateString);

    return QDir::cleanPath(QDir::tempPath() + QDir::separator() + fileName);
}

inline void log_to_file(const QString &message)
{
    static bool first_logging = true;
    static QMutex mutex;

    QMutexLocker<QMutex> guard(&mutex);

    QFile file(defaultFile());
    if (first_logging) {
        if (file.exists()) {
            file.remove();
        }
        first_logging = false;
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
        out << QStringLiteral("[%1] %2").arg(timestamp, message) << Qt::endl;
        file.close();
    }
}

}
