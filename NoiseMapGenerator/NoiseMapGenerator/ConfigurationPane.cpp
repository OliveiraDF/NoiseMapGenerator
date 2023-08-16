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
#include "ConfigurationPane.h"


// CConfigurationPane

IMPLEMENT_DYNAMIC(CConfigurationPane, CDockablePane)

CConfigurationPane::CConfigurationPane()
{
}

CConfigurationPane::~CConfigurationPane()
{
}

BEGIN_MESSAGE_MAP(CConfigurationPane, CDockablePane)
ON_WM_CREATE()
ON_WM_SIZE()
END_MESSAGE_MAP()


int CConfigurationPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CDockablePane::OnCreate(lpCreateStruct) == -1)
   {
      return -1;
   }

   // TODO:  Ajoutez ici votre code de création spécialisé
   if (!m_ctrlConfiguration.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, { 0, 0, 0, 0 }, this, 1))
   {
      return -1;
   }

   return 0;
}

void CConfigurationPane::OnSize(UINT nType, int cx, int cy)
{
   CDockablePane::OnSize(nType, cx, cy);

   // TODO: ajoutez ici le code de votre gestionnaire de messages
   m_ctrlConfiguration.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
}
