#ifndef STRAVAEXPORTER_H
#define STRAVAEXPORTER_H

#include "iactivityexporter.h"
#include <QNetworkAccessManager>


class StravaExporter : public IActivityExporter
{
    Q_OBJECT

public:
    explicit StravaExporter(QObject *parent = 0);

    virtual QString name() const;
    virtual bool loadConfig( const WatchPreferences & preferences, QDomElement element );
    virtual bool isEnabled( ) const;
    virtual void setEnabled(bool enabled);
    virtual bool isOnline() const;
    virtual bool autoOpen() const;
    virtual void setAutoOpen( bool autoOpen );
    virtual QIcon icon() const;
    virtual void reset();
    virtual bool hasSetup() const;
    virtual void setup( QWidget * parent );
    virtual void saveConfig( const WatchPreferences & preferences, QDomDocument & document, QDomElement & element );

signals:

public slots:
    virtual void exportActivity( ActivityPtr activity );
private slots:
    void requestFinished( QNetworkReply * reply );

private:
    bool m_Enabled;
    QByteArray m_AuthToken;
    QNetworkAccessManager m_Manager;
    bool m_AutoOpen;
    QIcon m_Icon;

    void getActivityStatus(int activityId , int retry);
    void activitySubmitted( QJsonDocument & d, int httpCode );
    void activityStatus(QJsonDocument &d, int httpCode , QNetworkReply *reply);
    void authCodeAnswer( QJsonDocument & d, int httpCode );
};
typedef QSharedPointer<StravaExporter>StravaExporterPtr;

#endif // STRAVAEXPORTER_H
