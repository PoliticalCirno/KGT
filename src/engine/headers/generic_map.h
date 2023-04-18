#include "generics.h"
#include "generic_models.h"
#ifndef GENERIC_MAP_H
#define GENERIC_MAP_H
/**********************************\
Map Loader/editor codenamed: AWOO  *
Developed by: Tapc(politicalcirno) *
Features (planned and included):   *
-Map editing                       *
-Map load/unload/import/export     *
-props loading                     *
-automatic occlusion culling       *
-Makes Caprese salad               *
\**********************************/
struct MapProperties
{
    Model brush;
    Model Props;
};

void LoadMap(char* mapLoc);
void LoadProps(char* propLoc, int propAmt, Vector3 modelPosition, Vector3 modelRotation);

//btw, if any of u nerds are mad about me not using PascalCase on variables, haha nerd cry harder lolololol.
//camelCase supremacy!!!!!!!!!!!!!!!
#endif // GENERIC_MAP_H

//Automatic world object organizer
