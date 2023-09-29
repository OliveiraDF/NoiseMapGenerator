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
#include "NoiseMapGenerator.h"

#include "MainFrm.h"
#include "MainDocument.h"

#ifdef _DEBUG
#define new    DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
ON_WM_CREATE()
ON_COMMAND(ID_VIEW_CONFIGURATION, &CMainFrame::OnViewConfiguration)
ON_UPDATE_COMMAND_UI(ID_VIEW_CONFIGURATION, &CMainFrame::OnUpdateViewConfiguration)
ON_COMMAND(ID_VIEW_LOG, &CMainFrame::OnViewLog)
ON_UPDATE_COMMAND_UI(ID_VIEW_LOG, &CMainFrame::OnUpdateViewLog)
ON_COMMAND(ID_VIEW_FULLSCREEN, &CMainFrame::OnViewFullscreen)
ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, &CMainFrame::OnUpdateViewFullscreen)
ON_COMMAND(ID_FILE_EXPORT_COLOURMAP, &CMainFrame::OnFileExportColourMap)
ON_COMMAND(ID_FILE_EXPORT_HEIGHTMAP, &CMainFrame::OnFileExportHeightMap)
END_MESSAGE_MAP()

static UINT indicators[] =
{
   ID_SEPARATOR,
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame() noexcept
{
   // TODO: ajoutez ici le code d'une initialisation de membre
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
   {
      return -1;
   }

   if (!m_wndMenuBar.Create(this))
   {
      TRACE0("Impossible de créer la barre de menus\n");
      return -1;                // échec de la création
   }

   m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

   // empêche la barre de menus de prendre le focus lors de l'activation
   CMFCPopupMenu::SetForceMenuFocus(FALSE);

   if (!m_wndStatusBar.Create(this))
   {
      TRACE0("Impossible de créer la barre d'état\n");
      return -1;                // échec de la création
   }
   m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

   if (!m_wndLogPane.Create(_T("Log"), this, { 0, 0, 200, 200 }, TRUE, ID_VIEW_LOG,
                            WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
   {
      return -1;
   }

   if (!m_wndConfigurationPane.Create(_T("Configuration"), this, { 0, 0, 300, 200 }, TRUE, ID_VIEW_CONFIGURATION,
                                      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
   {
      return -1;
   }

   retro::core::RegisterLogObserver(&m_wndLogPane);

   // TODO: supprimez ces cinq lignes si vous ne souhaitez pas que la barre d'outils et la barre de menus soient ancrables
   m_wndConfigurationPane.EnableDocking(CBRS_ALIGN_ANY);
   m_wndLogPane.EnableDocking(CBRS_ALIGN_ANY);
   m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
   EnableDocking(CBRS_ALIGN_ANY);
   DockPane(&m_wndMenuBar);
   DockPane(&m_wndConfigurationPane);
   DockPane(&m_wndLogPane);

   // définir le gestionnaire visuel utilisé pour dessiner tous les éléments d'interface utilisateur
   CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(retro::mfc::CRetroVisualManager));

   RetroVisualManager::SetWindowDarkAttribute(this);

   // activer le comportement de la fenêtre d'ancrage de style Visual Studio 2005
   CDockingManager::SetDockingMode(DT_SMART);
   // activer le comportement de masquage automatique de la fenêtre d'ancrage de style Visual Studio 2005
   EnableAutoHidePanes(CBRS_ALIGN_ANY);

   EnableFullScreenMode(ID_VIEW_FULLSCREEN);
   EnableFullScreenMainMenu(FALSE);

   return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   if (!CFrameWndEx::PreCreateWindow(cs))
   {
      return FALSE;
   }
   // TODO: changez ici la classe ou les styles Window en modifiant
   //  CREATESTRUCT cs

   return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
   CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
   CFrameWndEx::Dump(dc);
}

#endif //_DEBUG

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
   if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
   {
      return FALSE;
   }

   return TRUE;
}

void CMainFrame::OnViewConfiguration()
{
   // TODO: ajoutez ici le code de votre gestionnaire de commande
   ShowPane(&m_wndConfigurationPane, !(m_wndConfigurationPane.IsVisible()), FALSE, TRUE);
   RecalcLayout();

   retro::core::Log(m_wndConfigurationPane.IsVisible() ?
                    I18N(IDS_LOG_CONFIGURATION_PANE_ON) :
                    I18N(IDS_LOG_CONFIGURATION_PANE_OFF));
}

void CMainFrame::OnUpdateViewConfiguration(CCmdUI* pCmdUI)
{
   // TODO: ajoutez ici le code du gestionnaire d'interface utilisateur de mise à jour des commandes
   pCmdUI->SetCheck(m_wndConfigurationPane.IsVisible());
}

void CMainFrame::OnViewLog()
{
   // TODO: ajoutez ici le code de votre gestionnaire de commande
   ShowPane(&m_wndLogPane, !(m_wndLogPane.IsVisible()), FALSE, TRUE);
   RecalcLayout();

   retro::core::Log(m_wndConfigurationPane.IsVisible() ?
                    I18N(IDS_LOG_LOG_PANE_ON) :
                    I18N(IDS_LOG_LOG_PANE_OFF));
}

void CMainFrame::OnUpdateViewLog(CCmdUI* pCmdUI)
{
   // TODO: ajoutez ici le code du gestionnaire d'interface utilisateur de mise à jour des commandes
   pCmdUI->SetCheck(m_wndLogPane.IsVisible());
}

void CMainFrame::OnViewFullscreen()
{
   // TODO: ajoutez ici le code de votre gestionnaire de commande
   ShowFullScreen();

   retro::core::Log(IsFullScreen() ?
                    I18N(IDS_LOG_FULL_SCREEN_ON) :
                    I18N(IDS_LOG_FULL_SCREEN_OFF));
}

void CMainFrame::OnUpdateViewFullscreen(CCmdUI* pCmdUI)
{
   // TODO: ajoutez ici le code du gestionnaire d'interface utilisateur de mise à jour des commandes
   pCmdUI->SetCheck(IsFullScreen());
}

void CMainFrame::OnFileExportColourMap()
{
   // TODO: ajoutez ici le code de votre gestionnaire de commande
   CString strFullPath;
   const CMainDocument* pDocument = OnFileExportMap(_T("ColourMap"), strFullPath);

   if (pDocument)
   {
      pDocument->ExportColourMap(strFullPath.GetString());
   }
}

void CMainFrame::OnFileExportHeightMap()
{
   // TODO: ajoutez ici le code de votre gestionnaire de commande
   CString strFullPath;
   const CMainDocument* pDocument = OnFileExportMap(_T("HeightMap"), strFullPath);

   if (pDocument)
   {
      pDocument->ExportHeightMap(strFullPath.GetString());
   }
}

const CMainDocument* CMainFrame::OnFileExportMap(LPCTSTR lpszMap, CString& strFullPath)
{
   CFileDialog FileDialog(FALSE, _T("png"), lpszMap, 6UL, _T("PNG File (*.png)|*.png|"), this);

   const INT_PTR nRet = FileDialog.DoModal();

   if (nRet == IDOK)
   {
      const CString strFolderPath = FileDialog.GetFolderPath();
      const CString strFileName   = FileDialog.GetFileName();

      strFullPath.Format(_T("%s\\%s"), strFolderPath.GetString(), strFileName.GetString());

      ASSERT_KINDOF(CMainDocument, GetActiveDocument());
      CMainDocument* pDocument = STATIC_DOWNCAST(CMainDocument, GetActiveDocument());
      ASSERT(pDocument);
      ASSERT_VALID(pDocument);

      return pDocument;
   }

   return NULL;
}
