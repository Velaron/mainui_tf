#pragma once

#include "BaseClientWindow.h"
#include "Action.h"
#include "EventSystem.h"

class CClientWindow : public CMenuBaseClientWindow
{
public:
	typedef CMenuBaseClientWindow BaseClass;
	CClientWindow( const char *name = "CClientWindow" ) : BaseClass( name )
	{
		// SetCharSize( QM_DEFAULTFONT );
		m_iNumBtns = 0;
	}
	~CClientWindow()
	{
		for( int i = 0; i < m_iNumBtns; i++ )
		{
			delete buttons[i];
		}
	}

	void Show() override
	{
		EngFuncs::KEY_SetDest( KEY_MENU );
		EngFuncs::ClientCmd( TRUE, "touch_setclientonly 1");
		BaseClass::Show();
	}

	void Hide() override
	{
		uiStatic.client.Clean();
		
		BaseClass::Hide();
		EngFuncs::KEY_SetDest( KEY_GAME );
		EngFuncs::ClientCmd( FALSE, "touch_setclientonly 0");
	}

	CEventCallback ExecAndHide( const char *szCmd )
	{
		return CEventCallback( []( CMenuBaseItem *pSelf, void *pExtra )
		{
			pSelf->Parent()->Hide();
			EngFuncs::ClientCmd( FALSE, (const char*)pExtra );
		}, (void *)szCmd );
	}

	CMenuAction *AddButton( int key, const char *name, Point pos, CEventCallback callback );

	bool KeyDown( int key );
	void VidInit() override;
	void Draw() override;
	CEventCallback keys[10];

protected:
	CMenuAction *buttons[16];
	int m_iNumBtns;
};