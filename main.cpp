#include <QCoreApplication>
#include <QDebug>
#include <QVariant>
#include <QVariantMap>
#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>
#include <QDomElement>
#include <QDate>
#include <QDebug>
//#include
QString tangVersion(const QString version){
    QString newVersion =  version;
    qDebug() << newVersion.replace(".","");//tach cac dau cham
    int num = newVersion.toInt();
    num = num+1;
    newVersion = QString::number(num);
    newVersion = newVersion.insert(newVersion.length()-2,".");
    newVersion = newVersion.insert(newVersion.length()-1,".");
    return newVersion;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fileName = argv[1];

    QFile file(fileName);
    if(file.open(QFile::ReadWrite))
    {
        QDomDocument doc;
        doc.setContent(&file);
        QDomElement docTag = doc.documentElement();
        QDomElement versionTag = docTag.firstChildElement("Version");
        QDomElement releaseDateTag = docTag.firstChildElement("ReleaseDate");

        //TAO DOMTEXT MOI cho  ReleaseDate
        QDomElement newReleaseDateTag = doc.createElement("ReleaseDate");//tao tag moi tu root doc
        QDomText currentDate = doc.createTextNode(QDate::currentDate().toString("yyyy-MM-dd"));
        newReleaseDateTag.appendChild(currentDate);//set text cho node moi
        docTag.replaceChild(newReleaseDateTag,releaseDateTag);//thay the tag
        // tang version va gan cho tag version
        QDomElement newVersionTag = doc.createElement("Version");
        QDomText currentVersionText = doc.createTextNode(tangVersion(versionTag.text()));
        newVersionTag.appendChild(currentVersionText);
        docTag.replaceChild(newVersionTag,versionTag);
        //qDebug() << versionTag.text(); //lay gia tri
        //versionTag.setAttribute("database","db");
        file.resize(0);
        QTextStream stream;
        stream.setDevice(&file);
        doc.save(stream,4);
        file.close();
        return 0;
    }
    else
    {
        qDebug()<<"Can't access file";
        return -1;
    }
    return a.exec();
}

