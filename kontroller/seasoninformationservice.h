#ifndef EU_TGCM_KONTROLLER_SEASONINFORMATIONSERVICE_H
#define EU_TGCM_KONTROLLER_SEASONINFORMATIONSERVICE_H

#include "client.h"

#include "file.h"

#include <QObject>
#include <QQmlListProperty>

namespace eu
{
namespace tgcm
{
namespace kontroller
{

class SeasonInformationService : public QObject
{
	Q_OBJECT
	QString seasonId_; // contains both tvshowid and season, separated by |

	QString showTitle_;
	QString thumbnail_;
	double rating_;
	int nbEpisodes_;
	int nbWatchedEpisodes_;
	QString fanart_;
	QString art_;

	QVector<File> episodes_;

	eu::tgcm::kontroller::Client* client_;

  public:
	explicit SeasonInformationService(QObject* parent = nullptr);
	Q_PROPERTY(eu::tgcm::kontroller::Client* client READ client WRITE setClient NOTIFY clientChanged)
	Q_PROPERTY(QString seasonId READ seasonId WRITE setSeasonId NOTIFY seasonIdChanged)
	Q_PROPERTY(QString showTitle READ showTitle WRITE setShowTitle NOTIFY showTitleChanged)
	Q_PROPERTY(QString thumbnail READ thumbnail WRITE setThumbnail NOTIFY thumbnailChanged)
	Q_PROPERTY(int nbEpisodes READ nbEpisodes WRITE setNbEpisodes NOTIFY nbEpisodesChanged)
	Q_PROPERTY(int nbWatchedEpisodes READ nbWatchedEpisodes WRITE setNbWatchedEpisodes NOTIFY nbWatchedEpisodesChanged)
	Q_PROPERTY(QString fanart READ fanart WRITE setFanart NOTIFY fanartChanged)
	Q_PROPERTY(QString art READ art WRITE setArt NOTIFY artChanged)
	Q_PROPERTY(QVariantList episodes READ episodesList NOTIFY episodesChanged)
	Q_PROPERTY(QString season READ season NOTIFY seasonIdChanged)

	QString seasonId() const;
	void setSeasonId(const QString& seasonId);

	QString showTitle() const;
	void setShowTitle(const QString& title);

	int nbEpisodes() const;
	void setNbEpisodes(int nbEpisodes);

	int nbWatchedEpisodes() const;
	void setNbWatchedEpisodes(int nbWatchedEpisodes);

	QString fanart() const;
	void setFanart(const QString& fanart);

	QString art() const;
	void setArt(const QString& art);

	QVector<File> episodes() const;
	QVariantList episodesList() const;

	QString thumbnail() const;
	void setThumbnail(const QString& thumbnail);

	QString season() const;

	eu::tgcm::kontroller::Client* client() const;

  signals:
	void seasonIdChanged();
	void showTitleChanged();
	void thumbnailChanged();
	void nbEpisodesChanged();
	void nbWatchedEpisodesChanged();
	void fanartChanged();
	void artChanged();
	void episodesChanged();

	void clientChanged(eu::tgcm::kontroller::Client* client);

  public slots:
	void refresh();

	void setClient(eu::tgcm::kontroller::Client* client);

  private slots:
	void refreshEpisodes_();
	void handleRefresh_();
	void handleRefreshEpisodes_();
};

} // namespace kontroller
} // namespace tgcm
} // namespace eu
#endif // EU_TGCM_KONTROLLER_SEASONINFORMATIONSERVICE_H
