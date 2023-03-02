#ifndef CITYBOOK_H
#define CITYBOOK_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include "json.h"

//"id": 37,
//"pid": 3400,
//"city_code": "101220105",
//"city_name": "巢湖市",
//"post_code": "238000",
//"area_code": "0551",
class City {
public:
    City(QtJson::JsonObject jsonObj);

    int m_nId;
    int m_nPid;
    QString m_strCityCode;
    QString m_strCityName;
    QString m_strPostCode;
    QString m_strrAreaCode;
};

class CityBook
{

public:
    CityBook();
    ~CityBook();

    static CityBook *Instance();
    QString GetCityId(const QString &cityName);
    void LoadConfig(const QString &fileName);
    QStringList searchCitys(const QString &name);

signals:

private:
    static CityBook *self;
    QMap<int, City> m_cityBook;

private:

};

#endif // CITYBOOK_H
