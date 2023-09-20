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
#include "ConfigurationPropCtrl.h"
#include "MainDocument.h"

IMPLEMENT_DYNAMIC(CConfigurationPropCtrl, CMFCPropertyGridCtrl)

CConfigurationPropCtrl::CConfigurationPropCtrl()
   : m_pSizeX(NULL)
   , m_pSizeY(NULL)
   , m_pNoiseScale(NULL)
   , m_pOctaveCount(NULL)
   , m_pPersistance(NULL)
   , m_pLacunarity(NULL)
{
}

CConfigurationPropCtrl::~CConfigurationPropCtrl()
{
}

BEGIN_MESSAGE_MAP(CConfigurationPropCtrl, CMFCPropertyGridCtrl)
ON_WM_CREATE()
ON_MESSAGE(WM_NEW_OPEN_DOCUMENT, &CConfigurationPropCtrl::OnNewOpenDocument)
END_MESSAGE_MAP()

int CConfigurationPropCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CMFCPropertyGridCtrl::OnCreate(lpCreateStruct) == -1)
   {
      return -1;
   }

   // TODO:  Ajoutez ici votre code de création spécialisé
   EnableHeaderCtrl(TRUE);
   EnableDescriptionArea(TRUE);
   SetVSDotNetLook(TRUE);
   MarkModifiedProperties(TRUE);

   RetroVisualManager::Apply(this);

   SetFont(&afxGlobalData.fontRegular);

   CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(I18N(IDS_PROP_GROUP_LABEL));
   if (!pGroup)
   {
      return -1;
   }

   COleVariant NullVar;

   CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(I18N(IDS_PROP_SIZE_LABEL), 0, TRUE);
   m_pSizeX = new CMFCPropertyGridProperty(_T("X"), NullVar, I18N(IDS_PROP_SIZE_X_DESC));
   m_pSizeX->SetData(CMainDocument::EProperty_Size_X);
   m_pSizeY = new CMFCPropertyGridProperty(_T("Y"), NullVar, I18N(IDS_PROP_SIZE_Y_DESC));
   m_pSizeY->SetData(CMainDocument::EProperty_Size_Y);
   pSize->Enable(FALSE);
   pSize->AddSubItem(m_pSizeX);
   pSize->AddSubItem(m_pSizeY);

   m_pNoiseScale = new CMFCPropertyGridProperty(I18N(IDS_PROP_SCALE_LABEL), NullVar, I18N(IDS_PROP_SCALE_DESC));
   m_pNoiseScale->SetData(CMainDocument::EProperty_Scale);
   m_pOctaveCount = new CMFCPropertyGridProperty(I18N(IDS_PROP_OCTAVECOUNT_LABEL), NullVar, I18N(IDS_PROP_OCTAVECOUNT_DESC));
   m_pOctaveCount->SetData(CMainDocument::EProperty_OctaveCount);
   m_pPersistance = new CMFCPropertyGridProperty(I18N(IDS_PROP_PERSISTANCE_LABEL), NullVar, I18N(IDS_PROP_PERSISTANCE_DESC));
   m_pPersistance->SetData(CMainDocument::EProperty_Persistance);
   m_pLacunarity = new CMFCPropertyGridProperty(I18N(IDS_PROP_LACUNARITY_LABEL), NullVar, I18N(IDS_PROP_LACUNARITY_DESC));
   m_pLacunarity->SetData(CMainDocument::EProperty_Lacunarity);

   pGroup->AddSubItem(pSize);
   pGroup->AddSubItem(m_pNoiseScale);
   pGroup->AddSubItem(m_pOctaveCount);
   pGroup->AddSubItem(m_pPersistance);
   pGroup->AddSubItem(m_pLacunarity);

   AddProperty(pGroup);

   return 0;
}

afx_msg LRESULT CConfigurationPropCtrl::OnNewOpenDocument(WPARAM, LPARAM lParam)
{
   CMainDocument* pDocument = reinterpret_cast<CMainDocument*>(lParam);

   ASSERT(pDocument);
   ASSERT_VALID(pDocument);

   m_pSizeX->SetValue((_variant_t)pDocument->GetWidth());
   m_pSizeY->SetValue((_variant_t)pDocument->GetHeight());
   m_pNoiseScale->SetValue((_variant_t)pDocument->GetScale());
   m_pOctaveCount->SetValue((_variant_t)pDocument->GetOctaveCount());
   m_pPersistance->SetValue((_variant_t)pDocument->GetPersistance());
   m_pLacunarity->SetValue((_variant_t)pDocument->GetLacunarity());

   return 0;
}

void CConfigurationPropCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
   ASSERT(pProp);
   ASSERT_VALID(pProp);

   CFrameWnd* pFrameWnd = GetTopLevelFrame();
   ASSERT(pFrameWnd);
   ASSERT_VALID(pFrameWnd);

   ASSERT_KINDOF(CMainDocument, pFrameWnd->GetActiveDocument());
   CMainDocument* pDocument = STATIC_DOWNCAST(CMainDocument, pFrameWnd->GetActiveDocument());
   ASSERT(pDocument);
   ASSERT_VALID(pDocument);

   const DWORD_PTR uData = pProp->GetData();

   pDocument->SetProperty(uData, pProp->GetValue());
}
