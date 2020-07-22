#include"common.h"

QDir directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());
//    qDebug()<<dir.path();
#if defined(Q_OS_WIN)
    if (dir.dirName().startsWith( "build")
            || dir.dirName().startsWith( "release")//.toLower() == "release"
            || dir.dirName().startsWith("bin"))
    dir.cdUp();
    dir.cdUp();
//    qDebug()<<dir.path();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}
