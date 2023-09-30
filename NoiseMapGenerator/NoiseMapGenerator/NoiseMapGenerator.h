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

#ifndef __AFXWIN_H__
#error "incluez 'pch.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"       

class CNoiseMapGeneratorApp : public CWinAppEx
{
#pragma region Constructors

public:

	CNoiseMapGeneratorApp() noexcept;

#pragma endregion
#pragma region Attributes

private:

	IWICImagingFactory* m_pWICFactory;
	BOOL m_bHiColorIcons;

public:

	IWICImagingFactory* GetWICFactory() const;

#pragma endregion
#pragma region Operations

public:

	CString GetVersion() const;

#pragma endregion
#pragma region Overridables

public:

	BOOL InitInstance() override;
	BOOL ExitInstance() override;
	void PreLoadState() override;
	void LoadCustomState() override;
	void SaveCustomState() override;

#pragma endregion
#pragma region Messages

	DECLARE_MESSAGE_MAP()

	afx_msg void OnAppAbout();

#pragma endregion

};

extern CNoiseMapGeneratorApp theApp;
