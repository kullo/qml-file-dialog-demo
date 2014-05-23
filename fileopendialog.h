#ifndef FILEOPENDIALOG_H
#define FILEOPENDIALOG_H

#include <QQuickItem>
#include <QFileDialog>
#include <QUrl>
#include <private/qguiapplication_p.h>
#include <QtGui/qpa/qplatformdialoghelper.h>
#include <QtGui/qpa/qplatformtheme.h>

class FileOpenDialog : public QQuickItem
{
    Q_OBJECT
public:
    explicit FileOpenDialog(QQuickItem *parent = 0);
    ~FileOpenDialog();

    Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
    QUrl fileUrl() const;

    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    QString filename() const;
    void setFilename(QString filename);

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    QString title() const;
    void setTitle(QString title);

    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

signals:
    void fileUrlChanged();
    void filenameChanged();
    void titleChanged();
    void accepted();
    void rejected();

protected:
    QPlatformFileDialogHelper* init_helper();

protected:
    QPlatformFileDialogHelper *m_dlgHelper;
    QQuickWindow *m_parentWindow;
    Qt::WindowModality m_modality;
    bool m_visible;
    QSharedPointer<QFileDialogOptions> m_options;

protected Q_SLOTS:
    virtual void accept();
    virtual void reject();

private:
    void setFileUrl(QUrl fileUrl);

    QFileDialog *dialog_;
    QUrl fileUrl_;
    QString filename_;
    QString title_;

    Q_DISABLE_COPY(FileOpenDialog)
};

#endif // FILEOPENDIALOG_H
