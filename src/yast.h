#ifndef YAST_H
#define YAST_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QProcess>


class Yast : public QDialog
{
	Q_OBJECT
public:
	Yast();

private:
	QSystemTrayIcon *tray;
	QAction *enableYastAction;
	QAction *runBrowserAction;

	bool isYastRunning();
	bool isFirefoxAvailable();


private slots:
	void slotEnableYast();
	void slotRunBrowser();
	void slotHelperFinished( int exitCode, QProcess::ExitStatus exitStatus );
	void slotHelperError( QProcess::ProcessError error );
	void slotUpdateStatus();

};


#endif
