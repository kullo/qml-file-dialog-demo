# Add more folders to ship with the application, here
folder_01.source = qml/file-dialog-demo
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QT += core-private
QT += gui-private
QT += widgets

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    fileopendialog.cpp \
    filesavedialog.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    fileopendialog.h \
    filesavedialog.h
