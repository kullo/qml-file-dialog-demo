#include "qtquick2controlsapplicationviewer.h"

#include "myfilesavedialog.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    qmlRegisterType<MyFileSaveDialog>("MyModules", 1, 0, "MyFileSaveDialog");

    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/file-dialog-demo/main.qml"));
    viewer.show();

    return app.exec();
}
