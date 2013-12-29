#include <QQuickWindow>

#include "myfilesavedialog.h"

MyFileSaveDialog::MyFileSaveDialog(QQuickItem *parent) :
    QQuickItem(parent)
  , m_modality(Qt::WindowModal)
  , m_options(QSharedPointer<QFileDialogOptions>(new QFileDialogOptions()))
{
    m_dlgHelper = init_helper();

    connect(m_dlgHelper, SIGNAL(accept()), this, SLOT(accept()));
    connect(m_dlgHelper, SIGNAL(reject()), this, SLOT(reject()));
}

MyFileSaveDialog::~MyFileSaveDialog()
{
    if (m_dlgHelper)
        m_dlgHelper->hide();
    delete m_dlgHelper;
}

QUrl MyFileSaveDialog::fileUrl() const
{
    return fileUrl_;
}

void MyFileSaveDialog::setFileUrl(QUrl fileUrl)
{
    if (fileUrl_ != fileUrl)
    {
        fileUrl_ = fileUrl;
        emit fileUrlChanged();
    }
}

QString MyFileSaveDialog::filename() const
{
    return filename_;
}

void MyFileSaveDialog::setFilename(QString filename)
{
    if (filename_ != filename)
    {
        filename_ = filename;
        emit filenameChanged();
    }
}

QString MyFileSaveDialog::title() const
{
    return title_;
}

void MyFileSaveDialog::setTitle(QString title)
{
    if (title_ != title)
    {
        title_ = title;
        emit titleChanged();
    }
}

QPlatformFileDialogHelper* MyFileSaveDialog::init_helper()
{
    m_dlgHelper = static_cast<QPlatformFileDialogHelper*>(QGuiApplicationPrivate::platformTheme()->createPlatformDialogHelper(QPlatformTheme::FileDialog));
    if (!m_dlgHelper)
        return NULL;

    return m_dlgHelper;
}

void MyFileSaveDialog::open()
{
    QQuickItem *me = this;
    Q_ASSERT(me);

    QQuickItem *parent = me->parentItem();
    Q_ASSERT(parent);

    QQuickWindow *window = parent->window();
    Q_ASSERT(window);

    m_parentWindow = window;

    m_options->setFileMode(QFileDialogOptions::AnyFile);
    m_options->setAcceptMode(QFileDialogOptions::AcceptSave);
    m_options->setWindowTitle(title());

    QString homePath = QDir::homePath();
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QUrl homeUrl = QUrl::fromLocalFile(homePath);
    m_dlgHelper->setDirectory(homeUrl);
#else
    m_dlgHelper->setDirectory(homePath);
#endif

#ifndef Q_OS_LINUX
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
        m_dlgHelper->selectFile(QUrl(filename()));
    #else
        m_dlgHelper->selectFile(filename());
    #endif
#endif

    m_dlgHelper->setOptions(m_options);
    m_dlgHelper->setFilter(); // applyOptions();

    Qt::WindowFlags flags = Qt::Dialog;
    if (!title().isEmpty()) flags |= Qt::WindowTitleHint;

    m_visible = m_dlgHelper->show(flags, m_modality, m_parentWindow);
}

void MyFileSaveDialog::close()
{
    m_dlgHelper->hide();
    m_visible = false;
}

void MyFileSaveDialog::accept()
{
    m_dlgHelper->hide();

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QList<QUrl> selectedUrls = m_dlgHelper->selectedFiles();
    if ( selectedUrls.count() )
    {
        setFileUrl(selectedUrls.at(0));
    }
#else
    QStringList selectedFiles = m_dlgHelper->selectedFiles();
    if ( selectedFiles.count() )
    {
        setFileUrl(QUrl::fromLocalFile(selectedFiles.at(0)));
    }
#endif

    emit accepted();
}

void MyFileSaveDialog::reject()
{
    m_dlgHelper->hide();
    emit rejected();
}
