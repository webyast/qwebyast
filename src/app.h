#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QSessionManager>



class App : public QApplication
{
	Q_OBJECT
public:
	App ( int & argc, char ** argv );
	void saveState( QSessionManager & manager );


};


#endif
