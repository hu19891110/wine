/*
 *  Notepad
 *
 *  Copyright 1997,98 Marcel Baur <mbaur@g26.ethz.ch>
 *  Copyright 1998 Karl Backstrm <karl_b@geocities.com>
 *  Copyright 2002 Sylvain Petreolle <spetreolle@yahoo.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include "windows.h"
#include "main.h"
#include "language.h"

CHAR STRING_MENU_Xx[]      = "MENU_Xx";
CHAR STRING_PAGESETUP_Xx[] = "DIALOG_PAGESETUP_Xx";

void LANGUAGE_UpdateWindowCaption(void) {
  /* Sets the caption of the main window according to Globals.szFileName:
      Notepad - (untitled)      if no file is open
      Notepad - [filename]      if a file is given
  */
  
  CHAR szCaption[MAX_STRING_LEN];
  CHAR szUntitled[MAX_STRING_LEN];

  LoadString(Globals.hInstance, STRING_NOTEPAD, szCaption, sizeof(szCaption));
  
  if (strlen(Globals.szFileName)>0) {
      lstrcat(szCaption, " - [");
      lstrcat(szCaption, Globals.szFileName);
      lstrcat(szCaption, "]");
  }
  else
  {
      LoadString(Globals.hInstance, STRING_UNTITLED, szUntitled, sizeof(szUntitled));
      lstrcat(szCaption, " - ");
      lstrcat(szCaption, szUntitled);
  }
    
  SetWindowText(Globals.hMainWnd, szCaption);
  
}



static BOOL LANGUAGE_LoadStringOther(UINT num, UINT ids, LPSTR str, UINT len)
{
  BOOL bOk;

  ids -= Globals.wStringTableOffset;
  ids += num * 0x100;

  bOk = LoadString(Globals.hInstance, ids, str, len);

  return(bOk);
}

VOID LANGUAGE_LoadMenus(VOID)
{
  HMENU  hMainMenu;

  /* Set frame caption */
  LANGUAGE_UpdateWindowCaption();
  
  /* Change Resource names */
//  lstrcpyn(STRING_MENU_Xx      + sizeof(STRING_MENU_Xx)      - 3, lang, 3);
//  lstrcpyn(STRING_PAGESETUP_Xx + sizeof(STRING_PAGESETUP_Xx) - 3, lang, 3);

  /* Create menu */
  hMainMenu = LoadMenu(Globals.hInstance, MAIN_MENU);
    Globals.hFileMenu     = GetSubMenu(hMainMenu, 0);
    Globals.hEditMenu     = GetSubMenu(hMainMenu, 1);
    Globals.hSearchMenu   = GetSubMenu(hMainMenu, 2);
    Globals.hLanguageMenu = GetSubMenu(hMainMenu, 3);
    Globals.hHelpMenu     = GetSubMenu(hMainMenu, 4);

  SetMenu(Globals.hMainWnd, hMainMenu);

  /* Destroy old menu */
  if (Globals.hMainMenu) DestroyMenu(Globals.hMainMenu);
  Globals.hMainMenu = hMainMenu;
}

//VOID LANGUAGE_DefaultHandle(WPARAM wParam)
//{
//  if ((wParam >=NP_FIRST_LANGUAGE) && (wParam<=NP_LAST_LANGUAGE))
//          LANGUAGE_SelectByNumber(wParam - NP_FIRST_LANGUAGE);
//     else printf("Unimplemented menu command %i\n", wParam);
//}
