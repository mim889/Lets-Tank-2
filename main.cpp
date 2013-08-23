#include <QApplication>
#include <QMessageBox>
#include "glwidget.h"
#include "errorlog.h"

#define ERRORLOG 0
#if ERRORLOG == 1
void myMessageOutput(QtMsgType type, const char *msg)
 {
     switch (type) {
     case QtDebugMsg:
         ErrorLOG::getSingleton() << "Debug: " << msg;
         break;
     case QtWarningMsg:
         ErrorLOG::getSingleton() << "Warning: " << msg;
         break;
     case QtCriticalMsg:
         ErrorLOG::getSingleton() << "Critical: " << msg;
         break;
     case QtFatalMsg:
         ErrorLOG::getSingleton() << "Fatal: " << msg;
         break;
     default: break;
     }
 }
#endif


int main(int argc, char *argv[])
{
    #if ERRORLOG == 1
        qInstallMsgHandler (myMessageOutput);
    #endif
    QApplication app(argc, argv);
    GlWidget window;
    window.show();

    return app.exec();
}
