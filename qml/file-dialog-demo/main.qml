import QtQuick 2.1
import QtQuick.Controls 1.0
import MyModules 1.0

ApplicationWindow {
    title: "Hello World"
    width: 600
    height: 300

    FileOpenDialog {
        id: openFile
        title: "Open file"

        onAccepted: outputOpenFile.text = "File selected: " + openFile.fileUrl
        onRejected: outputOpenFile.text = "File selected: –"
    }

    FileSaveDialog {
        id: saveFile
        title: "Save file"
        filename: "download.png"

        onAccepted: outputSaveFile.text = "File selected: " + saveFile.fileUrl
        onRejected: outputSaveFile.text = "File selected: –"
    }

    Column {
        spacing: 20

        Button {
            text: "Open File"
            onClicked: { openFile.open(); }
        }
        Text { id: outputOpenFile }

        Button {
            text: "Save File"
            onClicked: { saveFile.open(); }
        }
        Text { id: outputSaveFile }
    }
}
