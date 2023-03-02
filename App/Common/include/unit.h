#ifndef UNIT_H
#define UNIT_H

#include <QApplication>
#include <QDateTime>

/**
 * 版本更新：更新录音功能、温湿度采集功能  2019年10月11日22:23:51
 */
#define APP_VERSION         0x01020004
#define APP_STR_VERSION     "1.2.0.4"

#define STATUSBAR_HEIGHT    80

#define APP_BUILD_DATE      QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace(\
                            "  ", " 0" ), "MMM dd yyyy").toString("yyyy-MM-dd")
#define APP_FONT_FAMILY     "思源黑体 CN Normal"

#endif // UNIT_H
