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
#include "NoiseMapGenerator.h"
#include "LogPane.h"

IMPLEMENT_DYNAMIC(CLogPane, CDockablePane)

CLogPane::CLogPane()
{
}

CLogPane::~CLogPane()
{
}

BEGIN_MESSAGE_MAP(CLogPane, CDockablePane)
ON_WM_CREATE()
ON_WM_SIZE()
ON_COMMAND(ID_LOG_CLEAR, &CLogPane::OnLogClear)
END_MESSAGE_MAP()


int CLogPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (!m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, AFX_IDW_TOOLBAR + 1) ||
		 !m_wndToolBar.LoadToolBar(IDR_TOOLBAR_LOG, 0, 0, TRUE))
	{
		return -1;
	}

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// TODO:  Ajoutez ici votre code de création spécialisé
	if (!m_ctrlLogList.Create(LBS_NOINTEGRALHEIGHT | LBS_NOSEL | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, { 0, 0, 0, 0 }, this, 1))
	{
		return -1;
	}

	return 0;
}

void CLogPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: ajoutez ici le code de votre gestionnaire de messages
	const INT cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, 0, 0, cx, cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrlLogList.SetWindowPos(NULL, 0, cyTlb, cx, cy - cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CLogPane::OnMessage(const CTime& dtDate, scion::core::ELogLevel eLogLevel, LPCTSTR lpszMessage)
{
	const CString strISO8601 = dtDate.Format(_T("%FT%T%z"));
	const CString strLevel   = scion::core::LogLevelToString(eLogLevel);

	CString strLog;

	strLog.Format(_T("[%s] [%s] %s"), strISO8601.GetString(), strLevel.GetString(), lpszMessage);

	const INT nIndex = m_ctrlLogList.AddString(strLog.GetString());
	if (nIndex >= 0)
	{
		m_ctrlLogList.SetItemData(nIndex, eLogLevel);
	}
}

void CLogPane::OnLogClear()
{
	// TODO: ajoutez ici le code de votre gestionnaire de commande
	m_ctrlLogList.ResetContent();
}
