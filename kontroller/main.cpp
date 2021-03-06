#ifdef SAILFISH_TARGET
#include <sailfishapp.h>
#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#else
#include <QApplication>
#endif
#include <QtQml>
#include <QScopedPointer>

#include "musicservice.h"
#include <cassert>
#include "downloadservice.h"
#include "remote.h"
#include "client.h"
#include "statusservice.h"
#include "player.h"
#include "playerservice.h"
#include "playlistitem.h"
#include "videoservice.h"
#include "applicationsettings.h"
#include "deviceinformation.h"
#include "artistinformationservice.h"
#include "albuminformationservice.h"
#include "musiccontrol.h"
#include "videocontrol.h"
#include "movieinformationservice.h"
#include "tvshowinformationservice.h"
#include "seasoninformationservice.h"
#include "episodeinformationservice.h"
#include "playinginformation.h"
#include "server.h"
#include "downloadlocation.h"

#include <QScreen>
#ifndef SAILFISH_TARGET
#include "themeinformation.h"
#endif

void registerTypes()
{
    using namespace eu::tgcm::kontroller;
#ifdef SAILFISH_TARGET
    auto qmlprefix = "harbour.eu.tgcm";
#else
    auto qmlprefix = "eu.tgcm";
#endif
	qRegisterMetaType<File>("File");
	qRegisterMetaTypeStreamOperators<File>("File");
	qRegisterMetaType<PlaylistItem>();
	qRegisterMetaTypeStreamOperators<PlaylistItem>("PlaylistItem");
	int ret = qmlRegisterType<File>();
	assert(ret);
	qRegisterMetaType<QVector<File>>("QFileVector");
//	ret = qmlRegisterType<QVector<File>>();
	assert(ret);
    ret = qmlRegisterType<Subtitle>();
    assert(ret);
    ret = qmlRegisterType<AudioStream>();
    assert(ret);
	ret = qmlRegisterUncreatableType<Server>(qmlprefix, 1, 0, "Server",
	                                         QString::fromUtf8("Server not creatable from qml"));
	assert(ret);
	ret = qmlRegisterUncreatableType<Client>(qmlprefix, 1, 0, "Client",
	                                         QString::fromUtf8("Client not creatable from qml"));
	assert(ret);
	ret = qmlRegisterUncreatableType<ApplicationSettings>(
	          qmlprefix, 1, 0, "ApplicationSettings",
	          QString::fromUtf8("ApplicationSettings must be created in C++ and exposed as a property"));
	assert(ret);
	ret = qmlRegisterType<MusicService>(qmlprefix, 1, 0, "MusicService");
	assert(ret);
	ret = qmlRegisterType<Remote>(qmlprefix, 1, 0, "Remote");
	assert(ret);
	ret = qmlRegisterUncreatableType<PlayerService>(qmlprefix, 1, 0, "PlayerService",
	                                                QString::fromUtf8("PlayerService is not creatable from qml"));
	assert(ret);
	ret = qmlRegisterType<StatusService>(qmlprefix, 1, 0, "StatusService");
	assert(ret);
	ret = qmlRegisterUncreatableType<Player>(qmlprefix, 1, 0, "Player",
	                                         QString::fromUtf8("Player is not creatable from qml"));
	assert(ret);
	ret = qmlRegisterUncreatableType<PlaylistService>(qmlprefix, 1, 0, "PlaylistService",
	                                                  "PlaylistService is not creatable from qml");
    assert(ret);
    ret = qmlRegisterType<VideoService>(qmlprefix, 1, 0, "VideoService");
    assert(ret);
    ret = qmlRegisterType<DeviceInformation>(qmlprefix, 1, 0, "DeviceInformation");
    assert(ret);
    ret = qmlRegisterType<ArtistInformationService>(qmlprefix, 1, 0, "ArtistInformationService");
    assert(ret);
    ret = qmlRegisterType<AlbumInformationService>(qmlprefix, 1, 0, "AlbumInformationService");
    assert(ret);
    ret = qmlRegisterType<MusicControl>(qmlprefix, 1, 0, "MusicControl");
    assert(ret);
    ret = qmlRegisterType<VideoControl>(qmlprefix, 1, 0, "VideoControl");
    assert(ret);
    ret = qmlRegisterType<MovieInformationService>(qmlprefix, 1, 0, "MovieInformationService");
    assert(ret);
    ret = qmlRegisterType<TvShowInformationService>(qmlprefix, 1, 0, "TvShowInformationService");
    assert(ret);
    ret = qmlRegisterType<SeasonInformationService>(qmlprefix, 1, 0, "SeasonInformationService");
    assert(ret);
    ret = qmlRegisterType<EpisodeInformationService>(qmlprefix, 1, 0, "EpisodeInformationService");
    assert(ret);
	ret = qmlRegisterUncreatableType<PlayingInformation>(qmlprefix, 1, 0, "PlayingInformation",
	                                                     "PlayingInformation cannot be created form qml");
    assert(ret);
	ret = qmlRegisterUncreatableType<DownloadService>(
	          qmlprefix, 1, 0, "DownloadService",
	          QString::fromUtf8("Download service cannot be created, must use client.downloadService property"));
	assert(ret);
	qRegisterMetaType<DownloadLocation>();
	qRegisterMetaTypeStreamOperators<DownloadLocation>("DownloadLocation");
	ret = qmlRegisterUncreatableType<DownloadLocation>(qmlprefix, 1, 0, "DownloadLocation",
	                                                   "DownloadLocation cannot be created from qml");
	assert(ret);
#ifndef SAILFISH_TARGET
    ret = qmlRegisterType<ThemeInformation>(qmlprefix, 1, 0, "ThemeInformation");
    assert(ret);
#endif
}


int main(int argc, char *argv[])
{
#ifdef SAILFISH_TARGET
	QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
	QScopedPointer<QQuickView> view(SailfishApp::createView());
	registerTypes();
	eu::tgcm::kontroller::ApplicationSettings applicationSettings;
	auto client = new eu::tgcm::kontroller::Client(&applicationSettings, app.data());
	view->rootContext()->setContextProperty(QString::fromUtf8("appSettings"), &applicationSettings);
	view->rootContext()->setContextProperty(QString::fromUtf8("appClient"), client);
	view->setSource(SailfishApp::pathTo("qml/sailfish/kontroller.qml"));
	view->show();
#else
	QApplication* app = new QApplication(argc, argv);
	QQmlApplicationEngine engine;
	registerTypes();

	eu::tgcm::kontroller::DeviceInformation inf;
	inf.setup(*app);

	//QQmlComponent component(&engine);
	engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
#endif

	return app->exec();
}
