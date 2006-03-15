#pragma once

#include "resource.h"

#include <msxml.h>

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct SettingsBase {

	virtual bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot) = 0;
	virtual bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot) = 0;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct ConsoleSettings : public SettingsBase {

	ConsoleSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	wstring		strShell;
	wstring		strInitialDir;

	DWORD		dwRefreshInterval;
	DWORD		dwChangeRefreshInterval;
	DWORD		dwRows;
	DWORD		dwColumns;
	DWORD		dwBufferRows;
	DWORD		dwBufferColumns;

	COLORREF	defaultConsoleColors[16];
	COLORREF	consoleColors[16];
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct FontSettings : public SettingsBase {

	FontSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	wstring		strName;
	DWORD		dwSize;
	bool		bBold;
	bool		bItalic;

	bool		bUseColor;
	COLORREF	crFontColor;
};

//////////////////////////////////////////////////////////////////////////////

enum DockPosition {

	dockNone	= -1,
	dockTL		= 0,
	dockTR		= 1,
	dockBL		= 2,
	dockBR		= 3,
};

//////////////////////////////////////////////////////////////////////////////

enum ZOrder {
	zorderNormal	= 0,
	zorderOnTop		= 1,
	zorderOnBottom	= 2
};

//////////////////////////////////////////////////////////////////////////////

struct WindowSettings : public SettingsBase {

	WindowSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	wstring			strTitle;
	wstring			strIcon;
	bool			bUseTabIcon;
	bool			bShowCommand;
	bool			bShowCommandInTabs;
	bool			bUseTabTitles;

	bool			bShowMenu;
	bool			bShowToolbar;
	bool			bShowTabs;
	bool			bShowStatusbar;

	bool			bCaption;
	bool			bResizable;
	bool			bTaskbarButton;
	bool			bBorder;
	DWORD			dwInsideBoder;

	int				nX;
	int				nY;
	ZOrder			zOrder;
	DockPosition	dockPosition;
	int				nSnapDistance;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

enum TransparencyType {

	transNone		= 0,
	transAlpha		= 1,
	transColorKey	= 2
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct TransparencySettings : public SettingsBase {

	TransparencySettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	TransparencyType	transType;
	BYTE				byActiveAlpha;
	BYTE				byInactiveAlpha;
	COLORREF			crColorKey;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct AppearanceSettings : public SettingsBase {

	AppearanceSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	FontSettings			fontSettings;
	WindowSettings			windowSettings;
	TransparencySettings	transparencySettings;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct CopyPasteSettings : public SettingsBase {

	CopyPasteSettings();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	bool	bCopyOnSelect;
	bool	bNoWrap;
	bool	bTrimSpaces;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct BehaviorSettings : public SettingsBase {

	BehaviorSettings ();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	CopyPasteSettings	copyPasteSettings;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct HotKeys : public SettingsBase {

	HotKeys();

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	struct CommandData {
		
		CommandData(const wchar_t* pszCommand, const wchar_t* pszDescription, WORD commandID)
		: strCommand(pszCommand)
		, strDescription(pszDescription)
		, wCommandID(commandID)
		{}
		
		wstring	strCommand;
		wstring	strDescription;
		WORD	wCommandID;
	};

	struct HotkeyData {

		HotkeyData(DWORD commandID, ACCEL accel, bool extended)
		: dwCommandID(commandID)
		, accelHotkey(accel)
		, bExtended(extended)
		{
		}

		DWORD	dwCommandID;
		ACCEL	accelHotkey;
		bool	bExtended;
	};

	typedef vector<shared_ptr<CommandData> >		CommandsVector;
	typedef map<DWORD, shared_ptr<HotkeyData> >		HotKeysMap;

	HotKeysMap		mapHotKeys;
	CommandsVector	vecCommands;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

enum BackgroundImageType {

	bktypeNone		= 0,
	bktypeImage		= 1,
	bktypeDesktop	= 2,
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

struct TabData {

	TabData(const ConsoleSettings& conSettings)
	: strShell(conSettings.strShell)
	, strInitialDir(conSettings.strInitialDir)
	, strName(L"Console")
	, dwCursorStyle(0)
	, crCursorColor(RGB(255, 255, 255))
	, backgroundImageType(bktypeNone)
	, crBackgroundColor(RGB(0, 0, 0))
	, tabIcon()
	, tabSmallIcon()
	, tabBackground()
	, consoleSettings(conSettings)
	{
	}

	bool IsBackgroundRelative() const {
		if (tabBackground.get() == NULL) return false;
		return tabBackground->bRelative;
	}

	// custom shell settings
	wstring							strShell;
	wstring							strInitialDir;

	wstring							strName;
	DWORD							dwCursorStyle;
	COLORREF						crCursorColor;

	BackgroundImageType				backgroundImageType;
	COLORREF						crBackgroundColor;

	CIcon							tabIcon;
	CIcon							tabSmallIcon;
	shared_ptr<ImageData>			tabBackground;

private:
	const ConsoleSettings&			consoleSettings;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

typedef vector<shared_ptr<TabData> >	TabDataVector;

struct TabSettings : public SettingsBase {

	TabSettings(const ConsoleSettings& conSettings);

	bool Load(const CComPtr<IXMLDOMElement>& pOptionsRoot);
	bool Save(const CComPtr<IXMLDOMElement>& pOptionsRoot);

	TabDataVector	tabDataVector;

private:
	const ConsoleSettings&			consoleSettings;
};

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

class SettingsHandler {

	public:
		SettingsHandler();
		~SettingsHandler();

	public:

		bool LoadSettings(const wstring& strSettingsFileName);

		wstring	GetSettingsFileName() const { return m_strSettingsFileName; }

		ConsoleSettings& GetConsoleSettings() { return m_consoleSettings; }
		AppearanceSettings& GetAppearanceSettings() { return m_appearanceSettings; }
		BehaviorSettings& GetBehaviorSettings() { return m_behaviorSettings; }
		HotKeys& GetHotKeys() { return m_hotKeys; }
		TabSettings& GetTabSettings() { return m_tabSettings; }

	private:

		CComPtr<IXMLDOMDocument>	m_pOptionsDocument;
		CComPtr<IXMLDOMElement>		m_pOptionsRoot;

	private:

		wstring				m_strSettingsFileName;

		ConsoleSettings		m_consoleSettings;
		AppearanceSettings	m_appearanceSettings;
		BehaviorSettings	m_behaviorSettings;
		HotKeys				m_hotKeys;

		TabSettings			m_tabSettings;
};

//////////////////////////////////////////////////////////////////////////////