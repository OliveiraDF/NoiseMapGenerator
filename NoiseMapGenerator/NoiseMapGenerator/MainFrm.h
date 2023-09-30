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

class CMainDocument;

class CMainFrame : public CFrameWndEx
{
#pragma region Constructors

protected:

	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

public:

	virtual ~CMainFrame();

#pragma endregion
#pragma region Attributes

protected:

	CMFCMenuBar m_wndMenuBar;
	CMFCStatusBar m_wndStatusBar;
	retro::mfc::CLogPane m_wndLogPane;
	CConfigurationPane m_wndConfigurationPane;

#pragma endregion
#pragma region Overridables

public:

	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL) override;
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

#pragma endregion
#pragma region Implementations

private:

	const CMainDocument* OnFileExportMap(LPCTSTR lpszMap, CString& strFullPath);

#pragma endregion
#pragma region Messages

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:

	afx_msg void OnViewConfiguration();
	afx_msg void OnUpdateViewConfiguration(CCmdUI* pCmdUI);
	afx_msg void OnViewLog();
	afx_msg void OnUpdateViewLog(CCmdUI* pCmdUI);
	afx_msg void OnViewFullscreen();
	afx_msg void OnUpdateViewFullscreen(CCmdUI* pCmdUI);
	afx_msg void OnFileExportColourMap();
	afx_msg void OnFileExportHeightMap();

#pragma endregion

};
