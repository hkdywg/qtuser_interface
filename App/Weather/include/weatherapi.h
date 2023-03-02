#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeatherApi : public QObject
{
    Q_OBJECT

public:
    WeatherApi(QObject *parent = 0);
    ~WeatherApi();

    void QueryCityWeather(const QString &cityCode);
signals:
    void signalResult(const QByteArray &jsonData);

private:
    QString GetSignText(QString text);
    QNetworkAccessManager *manager;

private slots:
    void replyFinished(QNetworkReply* reply);
};

#endif // WEATHERAPI_H
