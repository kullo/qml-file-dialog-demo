#pragma once

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

    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
    bool valid() const;

    Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
    QUrl fileUrl() const;

    Q_PROPERTY(QList<QUrl> fileUrls READ fileUrls NOTIFY fileUrlsChanged)
    QList<QUrl> fileUrls() const;

    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    QString filename() const;
    void setFilename(QString filename);

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    QString title() const;
    void setTitle(QString title);

    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
    QStringList nameFilters() const;
    void setNameFilters(QStringList nameFilters);

    Q_PROPERTY(bool selectMultiple READ selectMultiple WRITE setSelectMultiple NOTIFY selectMultipleChanged)
    bool selectMultiple() const;
    void setSelectMultiple(bool selectMultiple);

    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

signals:
    void fileUrlChanged();
    void fileUrlsChanged();
    void filenameChanged();
    void titleChanged();
    void nameFiltersChanged();
    void accepted();
    void rejected();
    void selectMultipleChanged();

    // unused
    void validChanged();

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
    void setFileUrl(QUrl fileUrl = QUrl());
    void setFileUrls(QList<QUrl> fileUrls = QList<QUrl>());

    QUrl fileUrl_;
    QList<QUrl> fileUrls_;
    QString filename_;
    QString title_;
    QStringList nameFilters_;
    bool selectMultiple_;

    Q_DISABLE_COPY(FileOpenDialog)
};
