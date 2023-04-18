#include "../headers/generic_models.h"

void SetFilterModel(Model model, int filter)
{
    for(int i = 0; model.materialCount > i; i++)
    {
      SetTextureFilter(model.materials[i].maps[MATERIAL_MAP_ALBEDO].texture, filter);
    }
}
