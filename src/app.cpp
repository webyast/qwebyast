#include <app.h>


App::App ( int & argc, char ** argv ) 
: QApplication( argc, argv )
{
}

void App::saveState( QSessionManager & manager )
{
    manager.setRestartHint( QSessionManager::RestartNever );
}

#include "app.moc"
