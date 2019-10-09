#include "BaseMenu.h"
#include "Action.h"
#include "ScrollView.h"
#include "ClientWindow.h"

static class CClientClassMenu : public CClientWindow
{
public:
	typedef CClientWindow BaseClass;
	CClientClassMenu() : BaseClass( "CClientClassMenu" ) {}

	void _Init();
	void Reload();
	void Draw();

	CEventCallback MakeCb( const char *cmd )
	{
		return CEventCallback( MenuCb( &CClientClassMenu::cb ), (void*)cmd );
	}

private:
	const char *command;
	char textbuffer[1024];

	void cb( void *pExtra )
	{
		command = (const char*)pExtra;
		EngFuncs::ClientCmd( FALSE, command );
		Hide();
	}

} uiClassMenu;

void CClientClassMenu::_Init()
{
	int iYOffset = 80;

	const char *szCommands[] = { "scout", "sniper", "soldier", "demoman", "medic", "hwguy", "pyro", "spy", "engineer" };
	const char *szLabels[] = { "#Scout", "#Sniper", "#Soldier", "#Demoman", "#Medic", "#HWGuy", "#Pyro", "#Spy", "#Engineer" };

	for ( int i = 0; i < 9; i++ )
	{
		AddButton( ( i + 1 ) + '0', L( szLabels[i] ),
			Point( 40, iYOffset ), MakeCb( szCommands[i] ) );
		iYOffset += 32;
	}

	AddButton( '5', L( "#Random" ),
		Point( 40, iYOffset ), MakeCb( szLabels[g_pClient->GetRandomClass() - 1] ));

	szName = L( "#Title_SelectYourClass" );
}

void CClientClassMenu::Reload()
{
}

void CClientClassMenu::Draw()
{
	BaseClass::Draw();
}

void UI_ClassMenu_Show( void )
{
	EngFuncs::KEY_SetDest( KEY_MENU );
	uiClassMenu.Show();
}