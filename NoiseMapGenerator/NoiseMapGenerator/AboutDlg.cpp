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
#include "AboutDlg.h"
#include "NoiseMapGenerator.h"

#pragma region Constructors

CAboutDlg::CAboutDlg() noexcept
	: CDialogEx(IDD_ABOUTBOX)
{
}

#pragma endregion
#pragma region Overridables

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_ABOUT_PRODUCT, m_strProduct);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_strProduct = theApp.GetVersion();

	UpdateData(FALSE);

	return TRUE; 
}

#pragma endregion
#pragma region Messages

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT uCtlColor)
{
	return RetroVisualManager::OnCtlColor(pDC, pWnd, uCtlColor);
}

int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	RetroVisualManager::SetWindowDarkAttribute(this);

	return 0;
}

#pragma endregion