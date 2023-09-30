/**
 *
 * Noise Map Generator
 *
 * MIT License
 *
 * Copyright (c) 2023 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "NoiseMapGenerator.h"
#include "MainFrm.h"

#include "MainDocument.h"
#include "MainTabView.h"

#ifdef _DEBUG
#define new    DEBUG_NEW
#endif


// CNoiseMapGeneratorApp

BEGIN_MESSAGE_MAP(CNoiseMapGeneratorApp, CWinAppEx)
ON_COMMAND(ID_APP_ABOUT, &CNoiseMapGeneratorApp::OnAppAbout)
// Commandes de document de fichier standard
ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// Construction de CNoiseMapGeneratorApp

CNoiseMapGeneratorApp::CNoiseMapGeneratorApp() noexcept
	: m_pWICFactory(NULL)
{
	m_bHiColorIcons = TRUE;


	// TODO: remplacer la chaîne d'ID de l'application ci-dessous par une chaîne ID unique ; le format recommandé
	// pour la chaîne est CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("NoiseMapGenerator.AppID.NoVersion"));

	// TODO: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}

// Le seul et unique objet CNoiseMapGeneratorApp

CNoiseMapGeneratorApp theApp;


// Initialisation de CNoiseMapGeneratorApp

BOOL CNoiseMapGeneratorApp::InitInstance()
{
	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() est obligatoire pour utiliser un contrôle RichEdit
	// AfxInitRichEdit2();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO: modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("Retro Technique"));
	LoadStdProfileSettings(4);         // Charge les options de fichier INI standard (y compris les derniers fichiers utilisés)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
																RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Inscrire les modèles de document de l'application.  Ces modèles
	//  lient les documents, fenêtres frame et vues entre eux
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMainDocument),
		RUNTIME_CLASS(CMainFrame),                     // fenêtre frame SDI principale
		RUNTIME_CLASS(CMainTabView));
	if (!pDocTemplate)
	{
		return FALSE;
	}
	AddDocTemplate(pDocTemplate);


	// Analyser la ligne de commande pour les commandes shell standard, DDE, ouverture de fichiers
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Activer les ouvertures d'exécution DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

#ifndef __WINRT__
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (hr == RPC_E_CHANGED_MODE)
	{
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		UNREFERENCED_PARAMETER(hr);
	}
#endif

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	if (FAILED(hr))
	{
		return FALSE;
	}

	// Commandes de dispatch spécifiées sur la ligne de commande.  Retournent FALSE si
	// l'application a été lancée avec /RegServer, /Register, /Unregserver ou /Unregister.
	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	// La seule fenêtre a été initialisée et peut donc être affichée et mise à jour
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// appelle DragAcceptFiles uniquement s'il y a un suffixe
	//  Dans une application SDI, cet appel doit avoir lieu juste après ProcessShellCommand
	// Activer les ouvertures via glisser-déplacer
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

BOOL CNoiseMapGeneratorApp::ExitInstance()
{
	if (m_pWICFactory)
	{
		m_pWICFactory->Release();
		m_pWICFactory = NULL;
	}

#ifndef __WINRT__
	CoUninitialize();
#endif

	return TRUE;
}

IWICImagingFactory* CNoiseMapGeneratorApp::GetWICFactory() const
{
	return m_pWICFactory;
}

CString CNoiseMapGeneratorApp::GetVersion() const
{
	// TODO: Ajoutez ici votre code d'implémentation..
	CString strVersion;

	TCHAR lpszFullPath[1024];

	GetModuleFileName(NULL, lpszFullPath, ARRAYSIZE(lpszFullPath));

	DWORD       uVerHnd       = 0;
	const DWORD dwVerInfoSize = GetFileVersionInfoSize(lpszFullPath, &uVerHnd);
	if (dwVerInfoSize)
	{
		if (uVerHnd != 0)
		{
			return strVersion;
		}

		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
		if (!hMem)
		{
			return strVersion;
		}

		LPSTR lpszVffInfo = reinterpret_cast <CHAR*>(GlobalLock(hMem));
		if (!lpszVffInfo)
		{
			GlobalFree(hMem);
			return strVersion;
		}

		GetFileVersionInfo(lpszFullPath, uVerHnd, dwVerInfoSize, lpszVffInfo);

		struct LANGANDCODEPAGE
		{
			WORD uLanguage;
			WORD uCodePage;
		}* pTranslate;

		UINT uTranslate = 0;

		BOOL bRet = VerQueryValue(lpszVffInfo,
										  _T("\\VarFileInfo\\Translation"),
										  reinterpret_cast <LPVOID*>(&pTranslate),
										  &uTranslate);
		if (!bRet)
		{
			uTranslate = 0;
		}

		struct
		{
			LPCTSTR lpszSubBlock;
			LPCTSTR lpszBuffer;
			UINT    nBufferLen;
		} Queries[] =
		{
			{ _T("ProductVersion"), NULL, 0 },
			{ _T("ProductName"),    NULL, 0 }
		};
		constexpr const UINT uQueryCount = ARRAYSIZE(Queries);

		for (UINT i = 0; i < uQueryCount; i++)
		{
			for (UINT j = 0; j < (uTranslate / sizeof(LANGANDCODEPAGE)); j++)
			{
				CString strSubBlock;
				strSubBlock.Format(_T("\\StringFileInfo\\%04x%04x\\%s"),
										 pTranslate[j].uLanguage,
										 pTranslate[j].uCodePage,
										 Queries[i].lpszSubBlock);

				bRet = VerQueryValue(reinterpret_cast <LPVOID>(lpszVffInfo),
											strSubBlock.GetString(),
											(LPVOID*)&Queries[i].lpszBuffer,
											&Queries[i].nBufferLen);
				if (bRet)
				{
					break;
				}
			}

			if (!bRet)
			{
				Queries[i].lpszBuffer = _T("???");
			}
		}

		strVersion.Format(_T("%s v%s"), Queries[1].lpszBuffer, Queries[0].lpszBuffer);

		GlobalUnlock(hMem);
		GlobalFree(hMem);
	}

#ifdef _DEBUG
	strVersion += _T(" DEBUG");
#endif

	return strVersion;
}

// gestionnaires de messages de CNoiseMapGeneratorApp


// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:

	CAboutDlg() noexcept;

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_ABOUTBOX
	};
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);       // Prise en charge de DDX/DDV

// Implémentation

protected:

	DECLARE_MESSAGE_MAP()

public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

private:

	CString m_strProduct;
};

CAboutDlg::CAboutDlg() noexcept
	: CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_ABOUT_PRODUCT, m_strProduct);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
ON_WM_CTLCOLOR()
ON_WM_CREATE()
END_MESSAGE_MAP()

// Commande App pour exécuter la boîte de dialogue
void CNoiseMapGeneratorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;

	aboutDlg.DoModal();
}

// méthodes de chargement/d'enregistrement de la personnalisation de CNoiseMapGeneratorApp

void CNoiseMapGeneratorApp::PreLoadState()
{
	BOOL    bNameValid;
	CString strName;

	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CNoiseMapGeneratorApp::LoadCustomState()
{
}

void CNoiseMapGeneratorApp::SaveCustomState()
{
}

// gestionnaires de messages de CNoiseMapGeneratorApp


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT uCtlColor)
{
	// TODO:  Modifier ici les attributs du DC

	// TODO:  Retourner un autre pinceau si le pinceau par défaut n'est pas souhaité
	return RetroVisualManager::OnCtlColor(pDC, pWnd, uCtlColor);
}

int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// TODO:  Ajoutez ici votre code de création spécialisé
	RetroVisualManager::SetWindowDarkAttribute(this);

	return 0;
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Ajoutez ici une initialisation supplémentaire
	m_strProduct = theApp.GetVersion();

	UpdateData(FALSE);

	return TRUE;            // return TRUE unless you set the focus to a control
	// EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}
