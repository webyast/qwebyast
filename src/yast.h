#ifndef YAST_H
#define YAST_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QProcess>
#include <QtWebKit>



class Yast : public QDialog
{
	Q_OBJECT
public:
	Yast();

private:
	QSystemTrayIcon *tray;
	QAction *enableYastAction;
	QAction *runBrowserAction;
	QWebView *web;

	bool isYastRunning();
	bool isFirefoxAvailable();


private slots:
	void slotEnableYast();
	void slotRunBrowser();
	void slotHelperFinished( int exitCode, QProcess::ExitStatus exitStatus );
	void slotHelperError( QProcess::ProcessError error );
	void slotUpdateStatus();
        void slotSslErrorHandler( QNetworkReply *  reply,const QList<QSslError> &  errorList);
	void slotTrayActivated ( QSystemTrayIcon::ActivationReason reason );


};


#endif
