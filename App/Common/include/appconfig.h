#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QVariant>

class AppConfig
{
public:
    static QString m_strSettingsFile;
    static void SaveSetting(const QString &group, const QString &name, const QVariant &value);
    static QVariant ReadSetting(const QString &group, const QString &name, const QVariant &value = QVariant());
    static bool m_bMouseInsert;
    static bool m_bPlayVideo;
    static QSize GetDesktopSize();
};

#endif // APPCONFIG_H
