#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QFile>
#include <QTextStream>

class File : public QFile
{
public:
    File();
    ~File();

public:
    QString read();
    void write(QString data);
    void changeFileName(QString name);

    void createDefaultConfig(const QString& filePath);
    void readConfig();
    void saveConfig(const QString& filePath);
private:
    QFile _file;
    QString _name;

    QFile _config;
};

#endif // FILE_H
