#include "Registry.hpp"
#include "Systems.hpp"

void System::kill_system(Registry &r,
                         SparseArray<Component::Mortal> &mortals)
{
  for (auto &&[mtl] : containers::Zipper(mortals))
  {
    if (mtl.health_points == 0)
      r.kill_entity(r.entity_from_index(mtl.entity_id));
  }
}