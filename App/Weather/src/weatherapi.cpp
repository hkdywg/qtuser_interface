#include "weatherapi.h"
#include "citybook.h"
#include "json.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>

#define CITY_API    "https://service-is751ged-1257101137.ap-shanghai.apigateway.myqcloud.com/release/weather/city"
#define WEATHER_API "https://service-is751ged-1257101137.ap-shanghai.apigateway.myqcloud.com/release/weather/query"
#define SECRET_ID   "AKIDjhq2vss1D6c2n5la2cknpwnOm8h4cytAx9qw"
#define SECRET_KEY  "2mxu64tbrn25r1bk6vgwioobhyduqh22q4353qlw"
#define FREE_WEATHER_API "http://t.weather.sojson.com/api/weather/city/"

WeatherApi::WeatherApi(QObject *parent) : QObject(parent)
{
    manager= new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

WeatherApi::~WeatherApi()
{

}

void WeatherApi::QueryCityWeather(const QString &cityCode)
{
    QString url = QString("http://t.weather.sojson.com/api/weather/city/%1").arg(cityCode);
    QNetworkRequest requset;
    requset.setUrl(QUrl(url));

    manager->get(requset);
}

void WeatherApi::replyFinished(QNetworkReply *reply)
{
    emit signalResult(reply->readAll());
}
