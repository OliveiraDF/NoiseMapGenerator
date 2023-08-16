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

#pragma once

#include "ConfigurationPane.h"
#include "LogPane.h"

class CMainFrame : public CFrameWndEx
{
protected:

   // création à partir de la sérialisation uniquement
   CMainFrame() noexcept;
   DECLARE_DYNCREATE(CMainFrame)

// Attributs

public:

// Opérations

public:

// Substitutions

public:

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);

// Implémentation

public:

   virtual ~CMainFrame();
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

protected:

   // membres incorporés de la barre de contrôle
   CMFCMenuBar m_wndMenuBar;
   CMFCStatusBar m_wndStatusBar;
   CLogPane m_wndLogPane;
   CConfigurationPane m_wndConfigurationPane;

// Fonctions générées de la table des messages

protected:

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

   DECLARE_MESSAGE_MAP()

public:

   afx_msg void OnViewConfiguration();
   afx_msg void OnUpdateViewConfiguration(CCmdUI* pCmdUI);
   afx_msg void OnViewLog();
   afx_msg void OnUpdateViewLog(CCmdUI* pCmdUI);
   afx_msg void OnViewFullscreen();
   afx_msg void OnUpdateViewFullscreen(CCmdUI* pCmdUI);

protected:

   afx_msg LRESULT OnNewOpenDocument(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnUpdateProperty(WPARAM wParam, LPARAM lParam);
};
