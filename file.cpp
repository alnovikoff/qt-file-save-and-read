#include "file.h"
#include <QTextStream>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

File::File()
{
    _config.setFileName("config.json");

    if(_config.exists())
    {
        readConfig();
    }
    else
    {
        createDefaultConfig("config.json");
    }
}

File::~File(){}

QString File::read() {
    QTextStream in(&_file);
    _file.setFileName(_name);
    _file.open(QIODevice::ReadWrite | QIODevice::Text);
    QString content = in.readAll();
    _file.close();
    return content;
}

void File::write(QString data) {
    QTextStream out(&_file);
    _file.setFileName(_name);
    _file.open(QIODevice::ReadWrite | QIODevice::Text);
    out << data;
    _file.close();
}

void File::changeFileName(QString name)
{
    QString oldFileName = _name;
    if (oldFileName != name + ".txt")
    {
         _name = name + ".txt";
        _file.rename(oldFileName, _name);

        saveConfig("config.json");
    }
}

void File::createDefaultConfig(const QString& filePath)
{
    QJsonObject configObject;
    configObject["filename"] = "def.txt"; // Set your default filename here

    QJsonDocument configDoc(configObject);
    QByteArray configData = configDoc.toJson();


    _name = configObject.value("filename").toString();
    _file.setFileName(_name);

    if (_config.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        _config.write(configData);
        _config.close();
        qDebug() << "Created default config file:" << filePath;
    }
    else
    {
        qDebug() << "Error creating config file:" << _file.errorString();
    }
}

void File::readConfig()
{
    if (_config.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray configData = _config.readAll();
        QJsonDocument configDoc = QJsonDocument::fromJson(configData);
        QJsonObject configObject = configDoc.object();

        _name = configObject.value("filename").toString();
        _file.setFileName(_name);

        _config.close();
    }
    else
    {
        qDebug() << "Error opening config file for reading:" << _file.errorString();
    }
}

void File::saveConfig(const QString& filePath)
{
    QJsonObject configObject;
    configObject["filename"] = _name;

    QJsonDocument configDoc(configObject);
    QByteArray configData = configDoc.toJson();

    if (_config.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        _config.write(configData);
        _config.close();
        qDebug() << "Saved config file:" << filePath;
    }
    else
    {
        qDebug() << "Error saving config file:" << _file.errorString();
    }
}
