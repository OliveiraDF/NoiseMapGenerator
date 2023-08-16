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
#include "LogListCtrl.h"


// CLogListCtrl

IMPLEMENT_DYNAMIC(CLogListCtrl, CListBox)

CLogListCtrl::CLogListCtrl()
{
}

CLogListCtrl::~CLogListCtrl()
{
}

BEGIN_MESSAGE_MAP(CLogListCtrl, CListBox)
ON_WM_CREATE()
ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// gestionnaires de messages de CLogListCtrl



int CLogListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CListBox::OnCreate(lpCreateStruct) == -1)
   {
      return -1;
   }

   // TODO:  Ajoutez ici votre code de création spécialisé
   SetFont(&afxGlobalData.fontRegular);

   return 0;
}

HBRUSH CLogListCtrl::CtlColor(CDC* pDC, UINT nCtlColor)
{
   // TODO:  Modifier ici les attributs du DC
   if (nCtlColor == CTLCOLOR_LISTBOX)
   {
      pDC->SetBkColor(RGB(83, 83, 83));
      pDC->SetTextColor(RGB(245, 245, 245));
      return CreateSolidBrush(RGB(83, 83, 83));
   }

   // TODO:  Retourner un pinceau non NULL si le gestionnaire du parent ne doit pas être appelé
   return NULL;
}
