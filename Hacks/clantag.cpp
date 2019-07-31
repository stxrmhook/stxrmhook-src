#include "clantag.h"

// Thanks @pwned

void clantag()

{
    if(vars.misc.clantag > 0)
    {
        if (vars.misc.clantagtype == CLAN_TAG::xanax)
        {
            
            static int Tick;
            Tick++;
            
            if (Tick > 0 && Tick < 15)
            {
                SetClanTag("s            ", "stxrm.pw");
            }
            else if (Tick > 30 && Tick < 45)
            {
                SetClanTag("st           ", "stxrm.pw");
            }
            else if (Tick > 60 && Tick < 75)
            {
                SetClanTag("stx          ", "stxrm.pw");
            }
            else if (Tick > 90 && Tick < 105)
            {
                SetClanTag("stxr         ", "stxrm.pw");
            }
            else if (Tick > 120 && Tick < 135)
            {
                SetClanTag("stxrm.pw         ", "stxrm.pw");
            }
            else if (Tick > 150 && Tick < 165)
            {
                SetClanTag(" stxrm.pw        ", "stxrm.pw");
            }
            else if (Tick > 180 && Tick < 195)
            {
                SetClanTag("  stxrm.pw       ", "stxrm.pw");
            }
            else if  (Tick > 210 && Tick < 225)
            {
                SetClanTag("   stxrm.pw      ", "stxrm.pw");
            }
            else if (Tick > 240 && Tick < 255)
            {
                SetClanTag("    stxrm.pw     ", "stxrm.pw");
            }
            else if (Tick > 270 && Tick < 285)
            {
                SetClanTag("     stxrm.pw    ", "stxrm.pw");
            }
            else if (Tick > 300 && Tick < 315)
            {
                SetClanTag("      stxrm.pw   ", "stxrm.pw");
            }
            else if (Tick > 330 && Tick < 345)
            {
                
                SetClanTag("       stxrm.pw  ", "stxrm.pw");
            }
            else if (Tick > 360 && Tick < 375)
            {
                SetClanTag("        stxrm.pw  ", "stxrm.pw");
            }
            else if (Tick > 390 && Tick < 405)
            {
                SetClanTag("         stxrm.pw ", "stxrm.pw");
            }
            else if (Tick > 420 && Tick < 435)
            {
                SetClanTag("          stxrm.pw", "stxrm.pw");
            }
            else if (Tick > 450 && Tick < 465)
            {
                SetClanTag("           stxrm.p", "stxrm.pw");
            }
            else if (Tick > 480 && Tick < 495)
            {
                SetClanTag("            stxrm.", "stxrm.pw");
            }
            else if (Tick > 510 && Tick < 525)
            {
                SetClanTag("             stxrm", "stxrm.pw");
            }
            else if (Tick > 540 && Tick < 555)
            {
                SetClanTag("              stxr", "stxrm.pw");
            }
            else if (Tick > 570 && Tick < 585)
            {
                SetClanTag("               st", "stxrm.pw");
            }
            
            
            // Reset
            if(Tick > 585)
            {
                Tick = 0;
            }
        }
        
        //
        //
        
        if (vars.misc.clantagtype == CLAN_TAG::supremacy)
        {
            
            static int Tick;
            Tick++;
            
            if (Tick > 0 && Tick < 15)
            {
                SetClanTag("SUPREMACY $", "SUPREMACY $");
            }
            
            
            
            // Reset
            if(Tick > 15)
            {
                Tick = 0;
            }
        }
        
        
        if (vars.misc.clantagtype == CLAN_TAG::gamesense)
        {
            
            
            //skeet
            {
                switch (int(pGlobals->curtime * 2.4) % 27)
                {
                    case 0: SetClanTag("                    ga", "gamesense.pub"); break;
                    case 1: SetClanTag("                   gam", "gamesense.pub"); break;
                    case 2: SetClanTag("                  game", "gamesense.pub"); break;
                    case 3: SetClanTag("                 games", "gamesense.pub"); break;
                    case 4: SetClanTag("                gamese", "gamesense.pub"); break;
                    case 5: SetClanTag("               gamesen", "gamesense.pub"); break;
                    case 6: SetClanTag("              gamesens", "gamesense.pub"); break;
                    case 7: SetClanTag("             gamesense", "gamesense.pub"); break;
                    case 8: SetClanTag("            gamesense.", "gamesense.pub"); break;
                    case 9: SetClanTag("         gamesense.pub", "gamesense.pub"); break;
                    case 10:SetClanTag("        gamesense.pub ", "gamesense.pub"); break;
                    case 11:SetClanTag("       gamesense.pub  ", "gamesense.pub"); break;
                    case 12:SetClanTag("      gamesense.pub   ", "gamesense.pub"); break;
                    case 13:SetClanTag("      gamesense.pub   ", "gamesense.pub"); break;
                    case 14:SetClanTag("    gamesense.pub     ", "gamesense.pub"); break;
                    case 15:SetClanTag("   gamesense.pub      ", "gamesense.pub"); break;
                    case 16:SetClanTag("  gamesense.pub       ", "gamesense.pub"); break;
                    case 17:SetClanTag(" gamesense.pub        ", "gamesense.pub"); break;
                    case 18:SetClanTag(" gamesense.pub        ", "gamesense.pub"); break;
                    case 19:SetClanTag(" gamesense.pub        ", "gamesense.pub"); break;
                    case 20:SetClanTag("gamesense.pub         ", "gamesense.pub"); break;
                    case 21:SetClanTag("amesense.pub          ", "gamesense.pub"); break;
                    case 22:SetClanTag("mesense.pub           ", "gamesense.pub"); break;
                    case 23:SetClanTag("esense.pub            ", "gamesense.pub"); break;
                    case 24:SetClanTag("sense.pub             ", "gamesense.pub"); break;
                    case 25:SetClanTag("ense.pub              ", "gamesense.pub"); break;
                    case 26:SetClanTag("nse.pub               ", "gamesense.pub"); break;
                    case 27:SetClanTag("se.pub                ", "gamesense.pub"); break;
                    case 28:SetClanTag("e.pub                 ", "gamesense.pub"); break;
                        
                }
            }
        }
        
        
        if (vars.misc.clantagtype == CLAN_TAG::getzeus)
        {
            static int Tick;
            Tick++;
            
            if (Tick > 0 && Tick < 15)
            {
                SetClanTag("getze.us ", "getze.us");
            }
            else if (Tick > 30 && Tick < 45)
            {
                SetClanTag("etze.us g", "getze.us");
            }
            else if (Tick > 60 && Tick < 75)
            {
                SetClanTag("tze.us ge", "getze.us");
            }
            else if (Tick > 90 && Tick < 105)
            {
                SetClanTag("ze.us get", "getze.us");
            }
            else if (Tick > 120 && Tick < 135)
            {
                SetClanTag("e.us getz", "getze.us");
            }
            else if (Tick > 150 && Tick < 165)
            {
                SetClanTag(".us getze", "getze.us");
            }
            else if (Tick > 180 && Tick < 195)
            {
                SetClanTag("us getze.", "getze.us");
            }
            else if  (Tick > 210 && Tick < 225)
            {
                SetClanTag("s getze.u", "getze.us");
            }
            else if  (Tick > 240 && Tick < 255)
            {
                SetClanTag(" getze.us", "getze.us");
            }
            else if  (Tick > 270 && Tick < 285)
            {
                SetClanTag("getze.us ", "getze.us");
            }
            else if  (Tick > 300 && Tick < 315)
            {
                SetClanTag("getze.us ", "getze.us");
            }
            
            
            // Reset
            if(Tick > 315)
            {
                Tick = 0;
            }
        }
        
        
        
        
    }
}

