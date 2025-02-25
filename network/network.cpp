#include "network.h"
#include <QMessageBox>

Network::Network()
{
    // http init
    net_manager = new QNetworkAccessManager();
    net_request = new QNetworkRequest();
    network_manager2 = new QNetworkAccessManager();
    network_request2 = new QNetworkRequest();
    network_manager3 = new QNetworkAccessManager();
    network_request3 = new QNetworkRequest();
    network_manager4 = new QNetworkAccessManager();
    net_request4 = new QNetworkRequest();

    // 关于http 网络歌曲的 json 解析 和相应播放
    connect(net_manager, &QNetworkAccessManager::finished, this, &Network::reply);
    connect(network_manager2, &QNetworkAccessManager::finished, this, &Network::reply2);
    connect(network_manager3, &QNetworkAccessManager::finished, this, &Network::reply3);
    connect(network_manager4, &QNetworkAccessManager::finished, this, &Network::RankReply);
}

// net_manager finish 响应reply 开始在tableWidget 上显示
void Network::reply(QNetworkReply* re) {
    //获取Cookies
    QVariant v = re->header(QNetworkRequest::CookieHeader);

    QVariant status_code = re->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (re ->error() == QNetworkReply::NoError) {
        QByteArray bytes = re->readAll();
        QString res(bytes);
        parseJson(res, idx);
        idx += 20;
    } else {
        qDebug() << "error!";
    }
}

// 解析 json 显示到 tablewidget上
void Network::parseJson(QString json, int idx) {
        QString songname_original;   //歌曲名
        QString singername;        //歌手
        QString hashStr;           //hash
        QString id;
        QString album_name;        //专辑
        int duration;          	   //时间
        QByteArray byte_array;
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json.toUtf8()), &json_error);
        if (json_error.error == QJsonParseError::NoError)
        {
            if (parse_doucment.isObject())
            {
                QJsonObject rootObj = parse_doucment.object();
                if (rootObj.contains("data"))
                {
                    QJsonValue valuedata = rootObj.value("data");
                    if (valuedata.isObject())
                    {
                        QJsonObject valuedataObject = valuedata.toObject();
                        if (valuedataObject.contains("info"))
                        {
                            QJsonValue valueArray = valuedataObject.value("info");
                            if (valueArray.isArray())
                            {
                                QJsonArray array = valueArray.toArray();
                                int size = array.size();
                                for (int i = idx, j = 0; i < size + idx && j < size; i++, ++j)
                                {
                                    QJsonValue value = array.at(j);
                                   if (value.isObject())
                                   {
                                        QJsonObject object = value.toObject();
                                        if (object.contains("songname_original"))//歌曲名
                                        {
                                            QJsonValue AlbumID_value = object.take("songname_original");
                                            if (AlbumID_value.isString())
                                            {
                                                songname_original = AlbumID_value.toString();
                                            }
                                        }
                                        if (object.contains("singername"))//歌手
                                        {
                                            QJsonValue AlbumID_value = object.take("singername");
                                            if (AlbumID_value.isString())
                                            {
                                                singername = AlbumID_value.toString();
                                            }
                                        }
                                        if (object.contains("album_name"))//专辑
                                        {
                                            QJsonValue AlbumID_value = object.take("album_name");
                                            if (AlbumID_value.isString())
                                            {
                                                album_name = AlbumID_value.toString();
                                            }
                                        }
                                        if (object.contains("hash")) //hash
                                        {
                                            QJsonValue FileHash_value = object.take("hash");
                                            if (FileHash_value.isString())
                                            {
                                                hashStr = FileHash_value.toString();
                                            }
                                        }
                                        if (object.contains("album_id"))
                                        {
                                            QJsonValue FileHash_value = object.take("album_id");
                                            if (FileHash_value.isString())
                                            {
                                                //用Vector保存每首歌曲的album_id
                                                id = FileHash_value.toString();
                                            }
                                        }
                                        if (object.contains("duration"))//时长
                                        {
                                           QJsonValue AlbumID_value = object.take("duration").toInt();
                                           duration = AlbumID_value.toInt();
                                        }
                                    }
                                    mst buffer;
                                    QString time = QString("%1:%2").arg(duration/60).arg(duration%60);
                                    buffer.hashStr = hashStr;
                                    buffer.id = id;
                                    buffer.name = songname_original;
                                    buffer.singerName = singername;
                                    buffer.albumName = album_name;
                                    buffer.time = time;
                                    infoArray.push_back(buffer);
                            }
                        }
                    }
                }
            }
        }
    }
    if (idx == 1) {
        this->idx = 0;
        emit SearchIsFinished(infoArray);
    }
}

void Network::reply2(QNetworkReply *re)  // 如果net_messageer finish  判断是否载入 然后进行js
{
    //获取响应的信息，状态码为200表示正常
     QVariant status_code = re->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //无错误返回
    if(re->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = re->readAll();  //获取字节
        QString result(bytes);  //转化为字符串
        New_parseJson2(result);
        //parseJson2(result);//解析json
    }
    else
    {
        //处理错误
        qDebug()<<"歌曲播放失败";
    }
}

//图片 url 处理
QString Network::ImageUrlProcessing(QString img, QString size)
{
    QString front, back;
    bool isfront = false, ismid = true, isback = false;
    for (int i = 0; i < img.size(); ++i)
    {
         if (img[i] == '}')
         {
            ismid = true;
            continue;
         }
         if (!ismid) continue;
         if (img[i] == '{')
         {
             isfront = true;
             ismid = false;
             continue;
         }

         if (!isfront) front += img[i];
         else if (!isback) back += img[i];
    }
    return front + size + back;
}

//新的接口 播放音乐解析Json
void Network::New_parseJson2(QString json)
{
    QString audio_name;//歌手-歌名
    QString play_url;//播放地址
    QString img;
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json.toUtf8()), &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
       if(parse_doucment.isObject())
       {
           QJsonObject rootObj = parse_doucment.object();
           if (rootObj.contains("url") && rootObj["url"].isString()) // 歌曲url
           {
                if(rootObj["url"].toString().size() > 0)
                {
                    infoArray[TargetRow].url = rootObj["url"].toString();
                    //qDebug() << rootObj;
                }
                else
                {
                    QMessageBox::warning(this, "Error", "收费音乐暂时无法播放！", QMessageBox::Ok);
                    return;
                }
           }

           if (rootObj.contains("songName") && rootObj["songName"].isString()) // 歌曲名字
           {
               if(rootObj["songName"].toString().size() > 0)
               {
                   infoArray[TargetRow].name = rootObj["songName"].toString();
               }
           }

           if ((rootObj.contains("imgUrl") && rootObj["imgUrl"].isString()) ||
                   (rootObj.contains("album_img") && rootObj["album_img"].isString())) // 歌曲图片
           {
               if(rootObj["imgUrl"].toString().size() > 0 || rootObj["album_img"].toString().size() > 0)
               {
                   QString img = rootObj["imgUrl"].toString().size() > 0 ?
                               rootObj["imgUrl"].toString() : rootObj["album_img"].toString();
                   QString img_res = ImageUrlProcessing(img, "100");
                   infoArray[TargetRow].img = img_res;
                   //qDebug() << "IMG MUSIC: " << infoArray[TargetRow].img;
               }
           }

           if (rootObj.contains("lrc") && rootObj["lrc"].isString()) // 歌词
           {
               if(rootObj["lrc"].toString().size() > 0)
               {
                    infoArray[TargetRow].lrcStr = ""; //rootObj["lrc"].toString();
               }
           }
           emit GetMusicFinished();
       }
    }
}

//解析 json
void Network::parseJson2(QString json) {
    //qDebug() << json;
    QString audio_name;//歌手-歌名
    QString play_url;//播放地址
    QString img;
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json.toUtf8()), &json_error);
    if(json_error.error == QJsonParseError::NoError) {
       if(parse_doucment.isObject())
       {
           QJsonObject rootObj = parse_doucment.object();
           if(rootObj.contains("data"))
           {
               QJsonValue valuedata = rootObj.value("data");
               if(valuedata.isObject())
               {
                   QJsonObject valuedataObject = valuedata.toObject();
                   QString play_urlStr("");
                   if(valuedataObject.contains("play_url"))
                   {
                       QJsonValue play_url_value = valuedataObject.take("play_url");
                       if(play_url_value.isString())
                       {
                           play_urlStr = play_url_value.toString();      //歌曲的url
                           if(play_urlStr !="")
                           {
                               MusicUrl = play_urlStr;
                               infoArray[TargetRow].url = MusicUrl;
                           }
                       }
                   }
                   if(valuedataObject.contains("audio_name"))
                   {
                       QJsonValue play_name_value = valuedataObject.take("audio_name");
                       if(play_name_value.isString())
                       {
                           QString audio_name = play_name_value.toString();    //歌曲名字
                           if(audio_name!="")
                           {
                               //显示
                               infoArray[TargetRow].name = audio_name;
                               //qDebug() << audio_name;
                           }
                       }
                   }

                   // 获得该首歌的图片
                   if (valuedataObject.contains("img"))
                   {
                       QJsonValue play_name_value = valuedataObject.take("img");
                       if (play_name_value.isString())
                       {
                           QString img_name = play_name_value.toString();
                           if (img_name != "")
                           {
                               infoArray[TargetRow].img = img_name;
                               //network_request3->setUrl(QUrl(audio_name));
                               //network_manager3->get(*network_request3);  // 反馈信号 准备解析json
                           }
                       }
                   }
                   // 歌词显示
                   //idd = 0; // 初始化 lrc_itm 的索引
                if (valuedataObject.contains("lyrics")) //lrc
                {
                       QJsonValue play_url_value = valuedataObject.take("lyrics");
                       if (play_url_value.isString())
                       {
                           QString play_lrcStr = play_url_value.toString();
                           if (play_urlStr != "")
                           {
                               QString lrc = play_lrcStr;
                               infoArray[TargetRow].lrcStr = lrc;
                           }
                           else
                           {
                               //没有歌词;
                           }
                       }
                  }
                  emit GetMusicFinished();
              }
                    //下一篇的歌词获取也是在这里添加代码
            else {
                   qDebug()<<"出错";
                }
            }
        }
    }
    else
    {
        qDebug() << "json 解析出错";
    }
}

// 图片获取 触发信号开始解析
void Network::reply3(QNetworkReply *reply)
{
    //获取响应的信息，状态码为200表示正常
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //无错误返回
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  //获取字节
        //由于获取的图片像素过大，而我们显示的图片很小，所以我们需要压缩图片的像素，我们label的大小为45*45，所以我们把图片压缩为45*45
        imgPix = QPixmap();
        imgPix.loadFromData(bytes);
        emit GetNetworkImgFinished();
    }
    else
    {
        //处理错误
        qDebug()<<"NET_图片显示错误";
    }
}

void Network::RankReply(QNetworkReply *re) {
    //获取Cookies
    QVariant v = re->header(QNetworkRequest::CookieHeader);

    QVariant status_code = re->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (re ->error() == QNetworkReply::NoError) {
        QByteArray bytes = re->readAll();
        QString res(bytes);

        RankParseJson(res, idx);
        idx += 20;
    } else {
        qDebug() << "error!";
    }
}

void Network::RankParseJson(QString json, int idx) {
    QString songname_original;   //歌曲名
    QString singername;        //歌手
    QString hashStr;           //hash
    QString album_name;        //专辑
    int duration;          	   //时间
    QString id;
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json.toUtf8()), &json_error);
    if (json_error.error == QJsonParseError::NoError)
    {
        if (parse_doucment.isObject())
        {
            QJsonObject rootObj = parse_doucment.object();
            if (rootObj.contains("songs"))
            {
                QJsonValue valuedata = rootObj.value("songs");
                if (valuedata.isObject())
                {
                    QJsonObject valuedataObject = valuedata.toObject();
                    if (valuedataObject.contains("list"))
                    {
                        QJsonValue valueArray = valuedataObject.value("list");
                        if (valueArray.isArray())
                        {
                            QJsonArray array = valueArray.toArray();
                            int size = array.size();
                            for (int i = idx, j = 0; i < size + idx && j < size; i++, ++j)
                            {
                                QJsonValue value = array.at(j);
                               if (value.isObject())
                               {
                                    QJsonObject object = value.toObject();
                                    if (object.contains("filename"))//歌曲名
                                    {
                                        QJsonValue AlbumID_value = object.take("filename");
                                        if (AlbumID_value.isString())
                                        {
                                            QString filename_ = AlbumID_value.toString();
                                            if(filename_.size() == 0) continue;
                                            ParseSingerAndSong(songname_original, singername, AlbumID_value.toString());
                                        }
                                    }
                                    if (object.contains("remark"))//专辑
                                    {
                                        QJsonValue AlbumID_value = object.take("remark");
                                        if (AlbumID_value.isString())
                                        {
                                            album_name = AlbumID_value.toString();
                                        }
                                    }
                                    if (object.contains("hash")) //hash
                                    {
                                        QJsonValue FileHash_value = object.take("hash");
                                        if (FileHash_value.isString())
                                        {
                                            hashStr = FileHash_value.toString();
                                            //用Vector保存每首歌曲的hash
                                            //hash.push_back(FileHash_value.toString());
                                        }
                                    }
                                    if (object.contains("album_id"))
                                    {
                                        QJsonValue FileHash_value = object.take("album_id");
                                        if (FileHash_value.isString())
                                        {
                                            id = FileHash_value.toString();
                                            //用Vector保存每首歌曲的album_id
                                            //id.push_back(FileHash_value.toString());
                                        }
                                    }
                                    if (object.contains("duration"))//时长
                                    {
                                       QJsonValue AlbumID_value = object.take("duration").toInt();
                                       duration = AlbumID_value.toInt();
                                    }
                                }

                               mst buffer;
                               QString time = QString("%1:%2").arg(duration/60).arg(duration%60);
                               buffer.hashStr = hashStr;
                               buffer.id = id;
                               buffer.name = songname_original;
                               buffer.singerName = singername;
                               buffer.albumName = album_name;
                               buffer.time = time;
                               infoArray.push_back(buffer);
                            }
                        }
                    }
                }
            }
        }
    }
    if (idx == 1) {
        this->idx = 0;
        emit SearchIsFinished(infoArray);
    }
}


// 搜索 text 通过 http网络, 给予finish 相应
void Network::search(QString text, int idx) {
    ClearNetworkVector();
    for (int i = 1; i <= idx; ++i) {
        QString net_search = QString("http://mobilecdn.kugou.com/api/v3/search/song?format=json&keyword=%1&page=%2&pagesize=18a").arg(text).arg(i);
        net_request->setUrl(QUrl(net_search));
        net_manager->get(*net_request);
    }
}

void Network::SelectNetworkMusic(int row) {
    TargetRow = row;
    //歌曲请求 row 是行号
    //QString KGAPISTR1 =QString("https://www.kugou.com/yy/index.php?r=play/getdata"
    //"&hash=%1&album_id=%2&_=1497972864535").arg(infoArray.at(row).hashStr) .arg(infoArray.at(row).id);
    QString KGAPISTR1 =QString("https://m.kugou.com/app/i/getSongInfo.php?cmd=playInfo"
    "&hash=%1&album_id=%2&_=1497972864535").arg(infoArray.at(row).hashStr) .arg(infoArray.at(row).id);
    network_request2->setUrl(QUrl(KGAPISTR1));
    qDebug() << KGAPISTR1;
    //这句话很重要，我们手动复制url放到浏览器可以获取json，但是通过代码不行，必须加上下面这句才可以
    network_request2->setRawHeader("Cookie","kg_mid=2333");
    //network_request2->setHeader(QNetworkRequest::CookieHeader, 2333);
    network_manager2->get(*network_request2);
}

void Network::ClearNetworkVector() {
    this->idx = 0;
    infoArray.clear();
}

void Network::StartRequestNetImg(QString url) {
    network_request3->setUrl(QUrl(url));
    network_manager3->get(*network_request3);  // 反馈信号 准备解析json
}

void Network::ParseSingerAndSong(QString &singer, QString &song, QString name) {
    singer.clear();
    song.clear();

    bool skip = false;
    for(auto c: name) {
        if (skip == false && c != '-') {
            song += c;
        }
        else if (skip == true && c != '-') {
            singer += c;
        }
        else if (c == ' ') continue;
        else {
            skip = true;
            continue;
        }
    }
}
