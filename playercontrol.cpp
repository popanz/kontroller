#include "client.h"
#include "playercontrol.h"
#include "kodisettingsmanager.h"
#include "kodiplayerservice.h"

PlayerControl::PlayerControl(QObject *parent) :
    QObject(parent)
{
    // forward event
    connect(&KodiPlayerService::instance(), &KodiPlayerService::playersChanged, this, &PlayerControl::updatePlayers_);
}

void PlayerControl::refreshPlayerInfo()
{
    KodiPlayerService::instance().refreshPlayerInfo();
}

void PlayerControl::playPause(int playerId)
{
    KodiPlayerService::instance().playPause(playerId);
}

void PlayerControl::next(int playerId)
{
    QJsonObject parameters;
    parameters["playerid"] = playerId;
    parameters["to"] = QLatin1String("next");
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.GoTo", parameters);
    Client::current().send(message);
}

void PlayerControl::previous(int playerId)
{
    QJsonObject parameters;
    parameters["playerid"] = playerId;
    parameters["to"] = QLatin1String("previous");
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.GoTo", parameters);
    Client::current().send(message);
}

void PlayerControl::moveToFirst(int playerId)
{
    QJsonObject parameters;
    parameters["playerid"] = playerId;
    parameters["to"] = 0;
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.GoTo", parameters);
    Client::current().send(message);
}

void PlayerControl::stop(int playerId)
{
    QJsonObject parameters;
    parameters["playerid"] = playerId;
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.Stop", parameters);
    Client::current().send(message);
}

void PlayerControl::seekBackward(int playerId)
{
    QJsonObject parameters;
    parameters.insert("playerid", playerId);
    parameters.insert("value", QLatin1String("smallbackward"));
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.Seek", parameters);
    Client::current().send(message);
}

void PlayerControl::seekForward(int playerId)
{
    QJsonObject parameters;
    parameters.insert("playerid", playerId);
    parameters.insert("value", QLatin1String("smallforward"));
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.Seek", parameters);
    Client::current().send(message);
}

void PlayerControl::seekToPercentage(int playerId, int percentage)
{
    QJsonObject parameters;
    parameters.insert("playerid", playerId);
    parameters.insert("value", percentage);
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.Seek", parameters);
    Client::current().send(message);
}

void PlayerControl::setShuffle(int playerId, bool shuffle)
{
    QJsonObject parameters;
    parameters.insert("playerid", playerId);
    parameters.insert("shuffle", shuffle);
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.SetShuffle", parameters);
    auto reply = Client::current().send(message);
    connect(reply, &QJsonRpcServiceReply::finished, this,
            [this, playerId, shuffle]() {this->handleShuffleResult_(playerId, shuffle);});
}

void PlayerControl::switchSubtitle(int playerId, int subtitleIndex)
{
    QJsonObject parameters;
    parameters.insert("playerid", playerId);
    if(subtitleIndex == -1)
    {
        parameters.insert("enable", false);
        parameters.insert("subtitle", "off");
    }
    else
    {
        parameters.insert("enable", true);
        parameters.insert("subtitle", subtitleIndex);
    }
    QJsonRpcMessage message = QJsonRpcMessage::createRequest("Player.SetSubtitle", parameters);
    auto reply = Client::current().send(message);
    connect(reply, &QJsonRpcServiceReply::finished, this,
            [this, playerId, subtitleIndex]() {
        for(auto player : KodiPlayerService::instance().players())
        {
            if(player->playerId() == playerId)
            {
                player->setCurrentSubtitleIndex(subtitleIndex);
            }
        }
    });
}

void PlayerControl::updatePlayers_()
{
    players_.clear();
    for(KodiPlayer* player : KodiPlayerService::instance().players())
        players_.push_back(player);
    emit playersChanged();
}

void PlayerControl::handleShuffleResult_(int playerId, bool shuffle)
{
    auto reply = dynamic_cast<QJsonRpcServiceReply*>(sender());
    if(reply)
    {
        for(auto player : KodiPlayerService::instance().players())
        {
            if(player->playerId() == playerId)
                player->setShuffled(shuffle);
        }
    }
}

namespace
{
int playersPropCount(QQmlListProperty<KodiPlayer>* list)
{
    return static_cast<QList<KodiPlayer*>*>(list->data)->count();
}

KodiPlayer* playersPropAt(QQmlListProperty<KodiPlayer>* list, int index)
{
    auto l = static_cast<QList<KodiPlayer*>*>(list->data);
    if(index < l->size())
        return (*l)[index];
    return nullptr;
}
}

QQmlListProperty<KodiPlayer> PlayerControl::players()
{
    return QQmlListProperty<KodiPlayer>(this, &players_, &playersPropCount, &playersPropAt);
}

