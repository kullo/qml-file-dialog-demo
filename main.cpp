#include "qtquick2controlsapplicationviewer.h"

#include <QApplication>

#include "fileopendialog.h"
#include "filesavedialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<FileOpenDialog>("MyModules", 1, 0, "FileOpenDialog");
    qmlRegisterType<FileSaveDialog>("MyModules", 1, 0, "FileSaveDialog");

    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/file-dialog-demo/main.qml"));
    viewer.show();

    return app.exec();
}
