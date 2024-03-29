//
//  menu.cpp
//  macOS base - remade
//

#include "menu.h"
#include "Config.h"


cMenu* menu = new cMenu();
Config cfg;

// Colours

Color Red             = Color(255, 0, 57, 255);
Color inactive          = Color(82, 82, 82, 255);
Color MainColor         = Red;
Color Pink              = Color(255, 105, 180, 255);

Color FontColor         = Color(250, 250, 250, 250);
Color background        = Color(18, 18, 18, 255);
Color border1           = Color(60, 60, 60, 255);
Color border2           = Color(40, 40, 40, 255);
Color black             = Color(0, 0, 0, 255);
Color Avoz              = Color(201, 201, 201, 255);


bool WasPressed, WasReleased;
auto Pressed (ButtonCode_t code) -> void {
    
    if (pInputSystem->IsButtonDown(code)) {
        
        WasPressed = true;
        
    } else if (!(pInputSystem->IsButtonDown(code))) {
        
        if (WasPressed) {
            
            WasReleased = true;
            
        } else {
            
            WasReleased = false;
            
        }
        
        WasPressed = false;
        
    }
    
}

// Menu components

void cMenu::renderCheckbox(int x, int y, const char* str, bool* var) {
    
    int size = 10;
    Color col = Color(193, 232, 85, 255);
    
    draw->RectOutlined(x, y, size - 1, size - 1, 1, background, col); // Outside box
    
    if (*var)
        draw->fillrgba(x + 1, y + 1, size - 3, size - 3, col);
    
    if (draw->inArea(x, y, size + 40, size)) {
        
        if (WasReleased)
            *var = !*var;
    }
    
    draw->drawstring(x + 14, y - 3, FontColor, mFont, str);
    
}

// The sliders are kinda broken, if you click past the ends itll still move
// for ints
void cMenu::renderSlider(int x, int y, int w, const char* szString, int& value, int max, int min) {
    
    int h = 8;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - w / 2 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + w / 2 && draw->GetMouse().y < y + h + 2) {
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    draw->fillrgba(x, y + 5, w + 2, h, Color(9, 9, 9, 255));
    draw->fillrgba(x, y + 5, curValue, h, Color(193, 232, 85, 255));
    
    draw->drawstring(x + curValue - 5, y + 3, FontColor, mFont, to_string(value).c_str());
    
}

// for floats
void cMenu::renderSlider(int x, int y, int w, const char* szString, float& value, int max, int min) {
    
    int h = 8;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - w / 2 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + w / 2 && draw->GetMouse().y < y + h + 2) {
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    draw->fillrgba(x, y + 5, w + 2, h, Color(9, 9, 9, 255));
    draw->fillrgba(x, y + 5, curValue, h, Avoz);
    
    draw->drawstring(x + curValue - 5, y + 3, FontColor, mFont, to_string(value).c_str());
    
}

void cMenu::renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend) {
    
    int Y = y + h;
    
    Color col1  = Color(12, 12, 12, 255);
    Color col2  = Color(18, 18, 18, 255);
    
    if(draw->inArea(x, y, w, h)) {
        if(WasReleased) {
            *bOpend = !*bOpend;
        }
    }
    
    if (*bOpend) {
        
        for ( int i = 0; i < szValue.size(); i++ ) {
            
            auto bHover = draw->inArea(x, Y + 2 + (i * h), w, 18);
            draw->fillrgba(x, Y + (i * h), w, h, bHover ? col1 : col2 );
            draw->drawstring(x + 10, Y + 3 + (i * h), Color(250, 250, 250, 255), mFont, szValue[i].c_str());
            
            
            if (draw->inArea(x, Y + 2 + ( i * h ), w, 18)) {
                
                if(WasPressed){
                    currValue = i;
                    *bOpend = false;
                }
                
            }
            
        }
        
    }
    
    if(currValue == 0)
        szString = szString;
    else
        szString = szValue[currValue].c_str();
    
    // Draws the box
    draw->fillrgba(x, y, w, h, Color(18, 18, 18, 255));
    draw->drawstring(x + 10, y + (h / 2) - 7, Color(255, 255, 255, 255), mFont, szString);
    
    
    if (!*bOpend)
    {
        // draw arrow pointing down
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 0, 0, 0, 255 ) );
    }
    else
    {
        // draw arrow pointing up
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 0, 0, 0, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 0, 0, 0, 255 ) );
    }
    
}

void cMenu::renderButton(int x, int y, const char* szString, bool* var) {
    
    int w = 60;
    int h = 20;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasPressed) {
            *var = true;
        }
    } else {
        *var = false;
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(37, 52, 60, 255) : Color(25, 25, 25, 255), Color(25, 25, 25, 255));
    draw->drawbox(x + 1, y + 1, w - 2, h - 2, bHovering ? Color(64, 91, 106, 255) : Color(67, 67, 67, 255));
    draw->drawbox(x, y, w, h, bHovering ? Color(25, 35, 40, 255) : Color(9, 9, 9, 255));
    
    draw->drawstring(x + w / 2, y + h / 2, FontColor, framefont, szString, true);
    
}

void cMenu::playerbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString)
{
    y += index * 24;
    
    if(draw->inArea(x, y, w, h))
    {
        if(WasReleased)
        {
            playercount = index;
        }
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(12, 12, 12, 255), FontColor : Color(22, 22, 22, 255), Color(16, 16, 16, 255));
    draw->drawbox(x, y, w, h, Color(18, 18, 18, 255));
    draw->drawstring(x + w / 2, y + h / 2, Color::Avoz(), mFont, szString, true);
}
// Made by ViKiNG
void cMenu::drawcolorpicker(int x, int y, const char *szString, Color &col) {
    
    int oner = 6;
    float flRnbw = 0.0005f;
    int currPosX, currPosY;
    
    for(int i = 0 ; i < 21; i++) {
        flRnbw += 0.045f;
        
        Color col1 = Color::GetFromHSB(flRnbw, 1.0f, 1.0f);
        Color col2 = Color::GetFromHSB(flRnbw, 0.90f, 0.90f);
        Color col3 = Color::GetFromHSB(flRnbw, 0.80f, 0.80f);
        Color col4 = Color::GetFromHSB(flRnbw, 0.70f, 0.70f);
        Color col5 = Color::GetFromHSB(flRnbw, 0.60f, 0.60f);
        Color col6 = Color::GetFromHSB(flRnbw, 0.50f, 0.50f);
        Color col7 = Color::GetFromHSB(flRnbw, 0.40f, 0.40f);
        Color col8 = Color::GetFromHSB(flRnbw, 0.30f, 0.30f);
        Color col9 = Color::GetFromHSB(flRnbw, 0.20f, 0.20f);
        Color col10 = Color::GetFromHSB(flRnbw, 0.15f, 0.15f);
        Color col11 = Color::GetFromHSB(flRnbw, 0.10f, 0.10f);
        
        draw->fillrgba(x + i * oner, y, oner, oner, Color(col1.r(), col1.g(), col1.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 1, oner, oner, Color(col2.r(), col2.g(), col2.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 2, oner, oner, Color(col3.r(), col3.g(), col3.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 3, oner, oner, Color(col4.r(), col4.g(), col4.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 4, oner, oner, Color(col5.r(), col5.g(), col5.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 5, oner, oner, Color(col6.r(), col6.g(), col6.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 6, oner, oner, Color(col7.r(), col7.g(), col7.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 7, oner, oner, Color(col8.r(), col8.g(), col8.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 8, oner, oner, Color(col9.r(), col9.g(), col9.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 9, oner, oner, Color(col10.r(), col10.g(), col10.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 10, oner, oner, Color(col11.r(), col11.g(), col11.b(), 255));
        
        int x1 = x + i * oner;
        int y2 = y + oner * 1;
        int y3 = y + oner * 2;
        int y4 = y + oner * 3;
        int y5 = y + oner * 4;
        int y6 = y + oner * 5;
        int y7 = y + oner * 6;
        int y8 = y + oner * 7;
        int y9 = y + oner * 8;
        int y10 = y + oner * 9;
        int y11 = y + oner * 10;
        
        if(draw->inArea(x1, y, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col1;
                draw->drawbox(x1, y, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y;
            }
        } else if(draw->inArea(x1, y2, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col2;
                draw->drawbox(x1, y2, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y2;
            }
        } else if(draw->inArea(x1, y3, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col3;
                draw->drawbox(x1, y3, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y3;
            }
        } else if(draw->inArea(x1, y4, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col4;
                draw->drawbox(x1, y4, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y4;
            }
        } else if(draw->inArea(x1, y5, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col5;
                draw->drawbox(x1, y5, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y5;
            }
        } else if(draw->inArea(x1, y6, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col6;
                draw->drawbox(x1, y6, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y6;
            }
        }
        else if(draw->inArea(x1, y7, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col7;
                draw->drawbox(x1, y7, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y7;
            }
        }
        else if(draw->inArea(x1, y8, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col8;
                draw->drawbox(x1, y8, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y8;
            }
        }
        else if(draw->inArea(x1, y9, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col9;
                draw->drawbox(x1, y9, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y9;
            }
        }
        else if(draw->inArea(x1, y10, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col10;
                draw->drawbox(x1, y10, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y10;
            }
        }
        else if(draw->inArea(x1, y11, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col11;
                draw->drawbox(x1, y11, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y11;
            }
        }
    }
    
    draw->fillrgba(x, y + 73, 5, 20, Color(col.r(), col.g(), col.b(), 255));
    draw->drawbox(x, y + 73, 5, 20, Color::Black());
    
    string strPalette;
    
    strPalette.append("R: ");
    strPalette.append(to_string(col.r()));
    
    strPalette.append(" G: ");
    strPalette.append(to_string(col.g()));
    
    strPalette.append(" B: ");
    strPalette.append(to_string(col.b()));
    
    draw->drawstring(x, y - 20, Color::White(), mFont, szString);
    draw->drawstring(x + 10, y + 78, Color::White(), mFont, strPalette.c_str());
}

// Tabs

void cMenu::renderAim(int x, int y) {
    
    this->renderCheckbox(x, y + 6, "Enabled", &vars.aimbot.enabled);
    this->renderCheckbox(x, y + 23, "SilentAim", &vars.aimbot.silent);
    draw->drawstring(x, y + 34, FontColor, mFont, "FOV");
    this->renderSlider(x, y + 43, 180, "", vars.aimbot.FovToPlayer, 180, 0);
    draw->drawstring(x, y + 63, FontColor, mFont, "Hitbox");
    this->renderSlider(x, y + 73, 180, "Hitbox", vars.aimbot.hitbox, 7, 0);
    this->renderCheckbox(x, y + 93, "Auto Wall", &vars.aimbot.autowall);
    this->renderSlider(x, y + 103, 180, "", vars.aimbot.mindmg, 100, 0);
    draw->drawstring(x, y + 123, FontColor, mFont, "Hitchance");
    this->renderSlider(x, y + 133, 180, "", vars.aimbot.accuracyhithcance, 100, 0);
    draw->drawstring(x, y + 153, FontColor, mFont, "Pointscale");
    this->renderSlider(x, y + 163, 180, "", vars.aimbot.pointscale, 100, 0);
    this->renderCheckbox(x + 200, y + 173, "Backtrack", &vars.aimbot.backtrack);
    //this->renderSlider(x + 200, y + 193, 90, "", vars.aimbot.backtracking, 12, 0);
    
    
    vector<string> Resolve;  // Resolver
    
    
    Resolve.push_back("Test");
    Resolve.push_back("Simple");
    Resolve.push_back("gaycents");
    Resolve.push_back("Brute");
    
    
    this->renderCombo(x, y + 200, 110, 20, "Off", Resolve, vars.aimbot.yresolve, &vars.resolver_opend); // 150
    
    //Middle
    this->renderCheckbox(x + 200, y + 6, "Auto Scope", &vars.aimbot.autoscope);
    this->renderCheckbox(x + 200, y + 23, "Auto Pistol", &vars.aimbot.autopistol);
    this->renderCheckbox(x + 200, y + 43, "Auto Crouch", &vars.aimbot.autocrouch);
    this->renderCheckbox(x + 200, y + 63, "Auto Shoot", &vars.aimbot.autoshoot);
    this->renderCheckbox(x + 200, y + 83, "Anti Resolver", &vars.misc.antiResolverFlip);
    this->renderCheckbox(x + 200, y + 103, "Auto Zeus", &vars.aimbot.autozeus);
    
    vector<string> hitscan;
    // X
    hitscan.push_back("off");
    hitscan.push_back("gay");//xanax moving
    hitscan.push_back("$$$");//supremacy $
    hitscan.push_back("skeet");//gamesense
    hitscan.push_back("extreme");
    hitscan.push_back("rage quit");
    hitscan.push_back("random");
    hitscan.push_back("stop it");
    
    vector<string> fakewalk;  // Fake types
    fakewalk.push_back("Off");
    fakewalk.push_back("v1");
    fakewalk.push_back("v2");
    fakewalk.push_back("v3");
    
    
    this->renderCheckbox(x + 200, y + 123, "Hitscan", &vars.aimbot.hitscan);
    //this->renderCheckbox(x + 300, y + 163, "Fakewalk", &vars.aimbot.fakewalk);
    this->renderCombo(x + 200, y + 143, 100, 20, "Hitscan", hitscan, vars.aimbot.hitscantype, &vars.hitscan_opend);
    //this->renderCombo(x + 300, y + 189, 100, 20, "Fakewalk", fakewalk, vars.aimbot.fakewalktype, &vars.fakewalk_opend);
    
    vector<string> X;  // Real Pitch
    vector<string> Y;  // Real Yaw
    vector<string> FY; // Fake Yaw
    vector<string> MY; // Ground Yaw
    vector<string> AY; // Air Yaw
    // Pitch
    X.push_back("Off");
    X.push_back("Emotion");
    X.push_back("Dance");
    if(!vars.misc.antiuntrust)
    {
        X.push_back("FakeDown");
        X.push_back("FakeUp");
    }
    // Yaw
    Y.push_back("Off");
    Y.push_back("Backwards");
    Y.push_back("LowerYaw");
    Y.push_back("Manual Edge");
    Y.push_back("LBY Breaker");
    // Fake Yaw
    FY.push_back("Off");
    FY.push_back("Rand");
    FY.push_back("Rand2");
    FY.push_back("Rand3");
    FY.push_back("180");
    FY.push_back("180 Rotation");
    //Moving Yaw
    MY.push_back("Off");
    MY.push_back("LowerYaw");
    MY.push_back("Backwards Jitter");
    MY.push_back("Rotate");
    // Air Yaw
    AY.push_back("Off");
    AY.push_back("Rotate");
    
    this->renderCheckbox(x + 300, y + 6, "AntiAim Enabled", &vars.misc.antiaim);
    this->renderCheckbox(x + 300, y + 23, "Show Real Angles", &vars.misc.thirdpersonmode);
    this->renderCheckbox(x + 300, y + 43, "Fake", &vars.misc.fakeaa); // 60
    //draw->drawstring(x + 300, y + 63, FontColor, mFont, "LBY Delta");
    //this->renderSlider(x + 300, y + 83, 180, "", vars.misc.delta, 180, 0);
    this->renderCheckbox(x + 300, y + 173, "Freestanding", &vars.misc.edge);
    
    
    this->renderCombo(x + 300, y + 63, 125, 20, "Pitch", X, vars.misc.aaX, &vars.aaX_opend); // 80
    if(!vars.aaX_opend)
        
        this->renderCombo(x + 300, y + 83, 125, 20, "Yaw", Y, vars.misc.aaY, &vars.aaY_opend);
    if((!vars.aaX_opend) && !vars.aaY_opend)
        
        this->renderCombo(x + 300, y + 103, 125, 20, "Fake Yaw", FY, vars.misc.FaaY, &vars.FaaY_opend); // 100*/
    if((!vars.aaX_opend) && !vars.aaY_opend && !vars.FaaY_opend)
        
        this->renderCombo(x + 300, y + 123, 125, 20, "Moving Yaw", MY, vars.misc.MaaY, &vars.MaaY_opend); // 120
    if((!vars.aaX_opend) && !vars.aaY_opend && !vars.FaaY_opend && !vars.misc.MaaY)
        
        this->renderCombo(x + 300, y + 143, 125, 20, "Air Yaw", AY, vars.misc.AaaY, &vars.AaaY_opend); // 140
}


void cMenu::renderPlayer(int x, int y)
{
    draw->drawstring(x + 15, y + 18, FontColor, mFont, "Players List");
    
    if(!pEngine->IsInGame())
        draw->drawstring(x + 15, y + 43, Color::White(), mFont, "Not in game");
    
    
    std::vector<std::string> PitchResolver;
    
    PitchResolver.push_back("Auto");
    PitchResolver.push_back("Down");
    PitchResolver.push_back("Up");
    
    
    int bPadding = 0;
    char plinfo[255];
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    for(int i = 1; i < 64; i++) {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
            continue;
        
        player_info_t info;
        pEngine->GetPlayerInfo(i, &info);
        
        this->playerbutton(x + 15, y + 43, 120, 20, bPadding, vars.playerTab, info.name);
        
        
        if(bPadding == vars.playerTab)
        {
            sprintf(plinfo, "Player info for : %s", info.name);
            
            draw->drawstring(x + 265, y + 28, FontColor, mFont, plinfo);
            this->renderCheckbox(x + 265, y + 48, "Resolve", &gCorrections[entity->GetIndex()].resolved);
            this->renderCheckbox(x + 265, y + 68, "Whitelist", &gCorrections[entity->GetIndex()].whitelist);
            this->renderCheckbox(x + 265, y + 88, "BAim", &gCorrections[entity->GetIndex()].baim);
            
            //Draw Pitch Resolver
            
            draw->drawstring(x + 265, y + 108, FontColor, mFont, "Pitch");
            this->renderCombo(x + 265, y + 128, 125, 20, "Auto", PitchResolver, gCorrections[entity->GetIndex()].dropdown_x, &vars.playerlist_opend_x[entity->GetIndex()]);
            
            bPadding++;
        }
    }
}


void cMenu::renderVis(int x, int y) {
    
    this->renderCheckbox(x, y + 6, "Enabled", &vars.visuals.enabled);
    this->renderCheckbox(x, y + 23, "Enemy only", &vars.visuals.enemyonly);
    this->renderCheckbox(x, y + 43, "Vis Only", &vars.visuals.visonly);
    this->renderCheckbox(x, y + 63, "Box", &vars.visuals.box);
    this->renderCheckbox(x, y + 83, "Name", &vars.visuals.name);
    this->renderCheckbox(x, y + 103, "Health", &vars.visuals.health);
    this->renderCheckbox(x, y + 123, "Armour", &vars.visuals.armour);
    this->renderCheckbox(x, y + 143, "Heath text", &vars.visuals.healthtext);
    this->renderCheckbox(x, y + 163, "Skeleton", &vars.visuals.skeleton);
    this->renderCheckbox(x, y + 183, "Snaplines", &vars.visuals.snapline);
    this->renderCheckbox(x, y + 203, "Grenade ESP", &vars.visuals.grenade);
    this->renderCheckbox(x, y + 223, "Weapon ESP", &vars.visuals.active);
    
    //Middle
    this->renderCheckbox(x + 150, y + 6, "SkinChanger", & vars.visuals.skinc);
    this->renderCheckbox(x + 150, y + 23, "Dropped Weapons", & vars.visuals.weapons);
    this->renderCheckbox(x + 150, y + 43, "Bomb Timer", & vars.visuals.bombtimer);
    this->renderCheckbox(x + 150, y + 63, "Defusing", & vars.visuals.defusing);
    this->renderCheckbox(x + 150, y + 83, "Rescuing", & vars.visuals.rescuing);
    this->renderCheckbox(x + 150, y + 103, "No Flash", & vars.misc.noflash);
    this->renderCheckbox(x + 150, y + 123, "Recoil Crosshair", & vars.visuals.rcrosshair);
    this->renderCheckbox(x + 150, y + 193, "AA Indicators", & vars.visuals.antiaim_indicator);
    std::vector<std::string> Indicator;
    
    Indicator.push_back("Off");
    Indicator.push_back("Words");
    Indicator.push_back("Arrows");
    
    this->renderCombo(x + 150, y + 213, 125, 20, "Lit", Indicator, vars.visuals.indicatorAA_types, &vars.indicatorAA_opend);
    
    this->renderCheckbox(x + 150, y + 143, "Night Mode", & vars.misc.nightmode);
    
    
    // Left side
    vector<string> Players;
    vector<string> Hands;
    vector<string> Weapons;
    
    Players.push_back("Lit");
    Players.push_back("Texture");
    Players.push_back("WireFrame");
    Hands.push_back("Lit");
    Hands.push_back("Texture");
    Hands.push_back("Wireframe");
    Weapons.push_back("Lit");
    Weapons.push_back("Texture");
    Weapons.push_back("Wireframe");
    
    this->renderCheckbox(x + 300, y + 6, "Player Chams", &vars.visuals.chams);
    this->renderSlider(x + 300, y + 23, 180, "", vars.visuals.playerchams_alpha, 255, 0);
    this->renderCheckbox(x + 300, y + 43, "Hand Chams", &vars.visuals.handchams);
    this->renderSlider(x + 300, y + 63, 180, "", vars.visuals.handchams_alpha, 255, 0);
    this->renderCheckbox(x + 300, y + 83, "Weapon Chams", &vars.visuals.weaponchams);
    this->renderSlider(x + 300, y + 103, 180, "", vars.visuals.weaponchams_alpha, 255, 0);
    if(vars.visuals.chams) {
        this->renderCombo(x + 300, y + 143, 125, 20, "Lit", Players, vars.visuals.playersType, &vars.players_opend);
    }
    if(vars.visuals.handchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 300, y + 163, 125, 20, "Lit", Hands, vars.visuals.handsType, &vars.hands_opend);
    }
    if(vars.visuals.weaponchams) {
        if((!vars.players_opend) && !vars.hands_opend)
            this->renderCombo(x + 300, y + 183, 125, 20, "Lit", Weapons, vars.visuals.weaponType, &vars.weapons_opend);
    }
    
}

// Configs
/*
 void cMenu::renderConfigs(int x, int y) {
 vector<string> conf;
 
 conf.push_back("HvH");
 conf.push_back("HvH 2");
 conf.push_back("HvH 3");
 
 this->renderCombo(x, y, 125, 20, "HvH", conf, cfg.cfgcombo, &vars.cfg_opend);
 if(!vars.cfg_opend) {
 this->renderButton(x, y + 22, "Save", &cfg.saveconfig);
 this->renderButton(x + 65, y + 22, "Load", &cfg.loadconfig);
 }
 }
 */

void cMenu::renderMisc(int x, int y) {
    
    vector<string> CT;
    // X
    CT.push_back("off");
    CT.push_back("stxrmhook");//xanax moving
    CT.push_back("supremacy $");//supremacy $
    CT.push_back("gaysense");//gamesense
    CT.push_back("getze.us");
    //CT.push_back("Test");
    //CT.push_back("Test 2");
    //CT.push_back("Mixed");
    
    this->renderCheckbox(x, y + 6, "Bhop", &vars.misc.bhop);
    this->renderCheckbox(x, y + 23, "Auto strafe", &vars.misc.autostrafe);
    this->renderCheckbox(x, y + 43, "Circle Strafe", &vars.misc.cstrafe);
    this->renderCheckbox(x, y +  63, "FOV Changer", &vars.misc.fovt);
    this->renderSlider(x, y + 73, 180, "FOV", vars.misc.fov, 70, 0);
    this->renderCheckbox(x, y + 93, "No recoil", &vars.misc.norecoil);
    this->renderCheckbox(x, y + 113, "No visual recoil", &vars.misc.novisual);
    this->renderCheckbox(x, y + 133, "Spammer", &vars.misc.spammer);
    //clan tags
    this->renderCheckbox(x, y + 173, "Clan Tag", &vars.misc.vangeme);
    //this->renderCheckbox(x, y + 150, "skeet.cc", &vars.misc.gamesense);
    //this->renderCheckbox(x, y + 170, "aimware.net", &vars.misc.aimware);
    //this->renderCheckbox(x, y + 153, "Clantag", &vars.misc.clantag);
    this->renderCombo(x, y + 193, 125, 20, "off", CT, vars.misc.clantagtype, &vars.clantag_opend);
    this->renderCheckbox(x, y + 153, "Watermark", &vars.misc.watermark);
    
    
    vector<string> FakeLag;
    
    FakeLag.push_back("Off");
    FakeLag.push_back("Adaptive");
    FakeLag.push_back("Fake");
    
    // Fake Lag
    this->renderCheckbox(x + 300, y + 6, "WorldPaint", &vars.misc.worldpaint);
    this->renderCheckbox(x + 300, y + 23, "Spec List", &vars.misc.showspectators);
    this->renderCheckbox(x + 300, y + 43, "Antiscreenshot", &vars.misc.antiscreenshot);
    this->renderCheckbox(x + 300, y + 63, "Anti untrust", &vars.misc.antiuntrust);
    this->renderCheckbox(x + 300, y + 83, "Asuswall", &vars.misc.asuswalls);
    this->renderSlider(x + 300, y + 103, 180, "", vars.misc.asusalpha, 1.f, 0.f);
    this->renderCheckbox(x + 300, y + 123, "FakeLag", &vars.misc.fakelag);
    this->renderCombo(x + 300, y + 143, 125, 20, "Off", FakeLag, vars.misc.fakelagtype, &vars.fakelag_opend);
    if(!vars.fakelag_opend)
        this->renderSlider(x + 300, y + 168, 125, "", vars.misc.fakelagfactor, 16, 0);
    
}

void cMenu::renderColors(int x, int y) {
    
    vector<string> Colors;
    
    Colors.push_back("CT Colours");
    Colors.push_back("T Colours");
    Colors.push_back("Hand/Weapon Colours");
    Colors.push_back("World Colours");
    
    this->renderCombo(x + 200, y + 2 + 14, 125, 20, "CT Colours", Colors, vars.colors.combo, &vars.colors_opend);
    
    
    if(vars.colors.combo == 0) {
        this->drawcolorpicker(x, y + 22, "CT Box", vars.colors.ctbox);
        this->drawcolorpicker(x, y + 150, "CT BoxIgn", vars.colors.ctbox_ign);
        this->drawcolorpicker(x + 350, y + 22, "CT Chams", vars.colors.ctchams);
        this->drawcolorpicker(x + 350, y + 150, "CT ChamIgn", vars.colors.ctchams_ign);
    }
    if(vars.colors.combo == 1) {
        this->drawcolorpicker(x, y + 22, "T Box", vars.colors.tbox);
        this->drawcolorpicker(x, y + 150, "T BoxIgn", vars.colors.tbox_ign);
        this->drawcolorpicker(x + 350, y + 22, "T Chams", vars.colors.tchams);
        this->drawcolorpicker(x + 350, y + 150, "T ChamIgn", vars.colors.tchams_ign);
    }
    if(vars.colors.combo == 2) {
        this->drawcolorpicker(x, y + 22, "Hands", vars.colors.hands);
        this->drawcolorpicker(x + 350, y + 20, "Weapon", vars.colors.weapon);
    }
    if(vars.colors.combo == 3) {
        this->drawcolorpicker(x, y + 22, "World", vars.colors.world);
        this->drawcolorpicker(x + 350, y + 20, "Sky", vars.colors.sky);
    }
    
}

// Menu tabs
enum mTab
{
    Main    = 0,
    RageTab  = 1,
    PlayerTab   = 2,
    VisTab  = 3,
    MiscTab = 4,
    ColorsTab = 5
};

static int curTab = mTab::RageTab;

// This is where the menu is "put together"
void cMenu::renderMenu() {
    
    static int x = 100;
    static int y = 100;
    int w = 500;
    int h = 300;
    int hh = 22; // The height of the dragable area
    
    
    
    draw->RectOutlined(x, y, w, h, 1, Color(18, 18, 18, 255), Color(20, 20, 20, 255));
    draw->drawgradient(x + 2.5, y + 19, w - 4, 3, Color(35, 7, 77,255), Color(204, 83, 51, 255));
    draw->drawstring(x + ( ( w - 4 ) / 2 ) + 2, y + 10, Color::White(), mFont, "$TXRMHOOK", true);
    
    // Draws tabs
    draw->RectOutlined(x + 2, y + 20 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color::Black());
    draw->RectOutlined(x + 102, y + 20 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color::Black());
    draw->RectOutlined(x + 202, y + 20 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color::Black());
    draw->RectOutlined(x + 302, y + 20 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color::Black());
    draw->RectOutlined(x + 402, y + 20 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color::Black());
    
    
    // Handles tabs
    if(draw->inArea(x + 2, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 2, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color::Black());
        
        if(WasReleased)
            curTab = mTab::RageTab;
        
    } else if(draw->inArea(x + 102, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 102, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color::Black());
        
        if(WasReleased)
            curTab = mTab::PlayerTab;
        
    } else if(draw->inArea(x + 202, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 202, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color::Black());
        
        if(WasReleased)
            curTab = mTab::VisTab;
        
    } else if(draw->inArea(x + 302, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 302, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color::Black());
        
        if(WasReleased)
            curTab = mTab::MiscTab;
        
    } else if(draw->inArea(x + 402, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 402, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color::Black());
        
        if(WasReleased)
            curTab = mTab::ColorsTab;
        
    }
    
    
    switch (curTab) {
            
        case mTab::RageTab:
            draw->RectOutlined(x + 2, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color(201, 201, 201, 255));
            this->renderAim(x + 2 + 5, y + 27 + 20 + 5);
            break;
            
        case mTab::PlayerTab:
            draw->RectOutlined(x + 102, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color(201, 201, 201, 255));
            this->renderPlayer(x + 2 + 5, y + 27 + 20 + 5);
            break;
            
        case mTab::VisTab:
            draw->RectOutlined(x + 202, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color(201, 201, 201, 255));
            this->renderVis(x + 2 + 5, y + 27 + 20 + 5);
            break;
            
        case mTab::MiscTab:
            draw->RectOutlined(x + 302, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color(201, 201, 201, 255));
            this->renderMisc(x + 2 + 5, y + 27 + 20 + 5);
            break;
            
        case mTab::ColorsTab:
            draw->RectOutlined(x + 402, y + 22 + 5, 96, 25, 1, Color(12, 12, 12, 255), Color(201, 201, 201, 255));
            this->renderColors(x + 2 + 5, y + 27 + 20 + 5);
            break;
            
        default:
            break;
            
    }
    
    //this->renderConfigs(x + 25, y + h - 56);
    
    config->getConfig(cfg.cfgcombo);
    
    if(!vars.cfgInit) {
        skins_cfg->LoadSkins();
        config->LoadConfig();
        vars.cfgInit = true;
    }
    
    /*
     if(cfg.loadconfig) {
     skins_cfg->LoadSkins();
     config->LoadConfig();
     }
     
     if(cfg.saveconfig) {
     config->SaveConfig();
     }
     */
    
    // Render strings last so they're on top
    draw->drawstring(x + 50, y + 22 + 16, Avoz, osFont, "1", true);
    draw->drawstring(x + 150, y + 22 + 17, Avoz, osFont, "2", true);
    draw->drawstring(x + 250, y + 22 + 16, Avoz, osFont, "3", true);
    draw->drawstring(x + 350, y + 22 + 17, Avoz, osFont, "4", true);
    draw->drawstring(x + 450, y + 22 + 15, Avoz, osFont, "5", true);
    
    
    Pressed(MOUSE_LEFT);
    draw->MoveMenu(x, y, w, hh, 1);
    
}

