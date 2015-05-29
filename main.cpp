#include <QApplication>
#include "webcam.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebCam w;
    w.show();
    
    return a.exec();
}
