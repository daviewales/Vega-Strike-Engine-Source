#include "vs_globals.h"
#include "vegastrike.h"
#include "sprite.h"
#include "cockpit.h"
#include "universe.h"
#include "star_system.h"
Cockpit::Cockpit (const char * file): Pit(NULL),Crosshairs(NULL),cockpit_offset(0), viewport_offset(0) {
  LoadXML(file);
  if (Crosshairs)
    Crosshairs->SetPosition (0,viewport_offset);  
}
void Cockpit::Draw() {
  GFXHudMode (true);
  GFXColor4f (1,1,1,1);
  GFXBlendMode (ONE,ONE);
  if (Crosshairs)
    Crosshairs->Draw();
  GFXBlendMode (ONE,ZERO);
  GFXAlphaTest (GREATER,.1);
  RestoreViewPort();
  if (Pit)
    Pit->Draw();
  GFXHudMode (false);
  GFXAlphaTest (ALWAYS,0);
}
Cockpit::~Cockpit () {
  if (Pit)
    delete Pit;
  if (Crosshairs)
    delete Crosshairs;
}
void Cockpit::RestoreViewPort() {
  GFXViewPort (0, 0, g_game.x_resolution,g_game.y_resolution);
}
void Cockpit::SetupViewPort () {
    GFXViewPort (0,(int)(viewport_offset*g_game.y_resolution), g_game.x_resolution,g_game.y_resolution);
  _Universe->activeStarSystem()->AccessCamera()->setCockpitOffset (cockpit_offset);
}
