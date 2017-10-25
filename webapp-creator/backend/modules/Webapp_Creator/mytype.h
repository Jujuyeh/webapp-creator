#ifndef MYTYPE_H
#define MYTYPE_H

#include <QObject>
#include <QProcess>
#include <QString>

#define SHORT 128
#define LONG 640
#define LONGER 1024


class MyType : public QObject
{
    Q_OBJECT

public:
    explicit MyType(QObject *parent = 0);
    ~MyType();

    // The function inserts [name], [desc], [title], [version] and [maint] into
    // the corresponding field of manifest.json.
    Q_INVOKABLE void insertManifest(QString qname, QString qdesc, QString qtitle, QString qversion, QString qalias,
                         QString qmaint, bool ogra);

    // The function inserts the corresponding policy groups into the apparmor file.
    Q_INVOKABLE void insertApparmor(QString qgroups, QString qname, bool ogra);

    // The function inserts the URLs and settings of the webapp into a desktop file.
    Q_INVOKABLE void insertDesktop(QString qname, QString qcom, QString qtitle, QString qurl, QString qarg,
                       QString qsubUrl1, QString qsubUrl2, QString qsubUrl3, QString qurls,
                       QString qPROVIDER, QString qUSER_AGENT, bool https, bool ogra, bool png, QString qhex);

    // This function sets the config.js file of Ogra's alternate webapp container
    Q_INVOKABLE void insertConfig (QString qname, QString qalias, QString qurl, QString qsubUrl1,
                       QString qsubUrl2, QString qsubUrl3, QString qurls, bool hapticLinks,
                       QString qUSER_AGENT, bool https, bool UA, bool audibleLinks);

    // This function sets the qml files of Ogra's alternate webapp container
    Q_INVOKABLE void insertQML (QString qname, QString qalias);

    // This function creates the Webapp files and folders
    Q_INVOKABLE void createFiles(QString qname, bool ogra, bool png, bool selIcon, QString iconSource);

    // This function generates the click package
    Q_INVOKABLE void genClick();

    // This function deletes al generated data in /tmp by Webapp Creator
    Q_INVOKABLE void cleanTmp();

    //It returns true if [word] contains only lowercase characters.
    Q_INVOKABLE bool lowercase(QString qword);

    //It returns false if [word] contains non-numeric characters other than dots.
    Q_INVOKABLE bool interger(QString qword);

    //It returns true if [word] contains one '@' and at least one dot.
    Q_INVOKABLE bool email(QString qword);

    //It returns true if [word] contains at least one dot.
    Q_INVOKABLE bool URL(QString qword);

    //It returns false if [word] starts with "http"
    Q_INVOKABLE bool noHttp (QString qword);

    ///It returns true if word is at least two characters long
    Q_INVOKABLE bool validName (QString qword);

    //It returns true if word is valid SVG or PNG image file
    Q_INVOKABLE bool validImage (QString qword);

    //Return red
    Q_INVOKABLE int getRed(const QColor &color);

    //Return green
    Q_INVOKABLE int getGreen(const QColor &color);

    //Return blue
    Q_INVOKABLE int getBlue(const QColor &color);


    //double
    Q_INVOKABLE double colorToDouble (QString s);

    //valid color
    Q_INVOKABLE bool validColor (QString word);




Q_SIGNALS:
    void helloWorldChanged();

protected:
    QProcess *m_process;

};

#endif // MYTYPE_H
