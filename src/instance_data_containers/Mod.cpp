#include "instance_data_containers/Mod.h"

namespace modio
{
  void Mod::initialize(ModioMod modio_mod)
  {
    this->id = modio_mod.id;
    this->game_id = modio_mod.game_id;
    this->price = modio_mod.price;
    this->date_added = modio_mod.date_added;
    this->date_live = modio_mod.date_live;
    this->date_updated = modio_mod.date_updated;
    if(modio_mod.homepage)
      this->homepage = modio_mod.homepage;
    if(modio_mod.name)
      this->name = modio_mod.name;
    if(modio_mod.name_id)
      this->name_id = modio_mod.name_id;
    if(modio_mod.summary)
      this->summary = modio_mod.summary;
    if(modio_mod.description)
      this->description = modio_mod.description;
    if(modio_mod.metadata_blob)
      this->metadata_blob = modio_mod.metadata_blob;
    if(modio_mod.url)
      this->url = modio_mod.url;
    this->logo.initialize(modio_mod.logo);
    this->submitted_by.initialize(modio_mod.submitted_by);
    this->media.initialize(modio_mod.media);
    this->modfile.initialize(modio_mod.modfile);
    this->ratings.initialize(modio_mod.ratings);

    this->tags.resize(modio_mod.tags_array_size);
    for(int i = 0; i < modio_mod.tags_array_size; i++)
    {
      this->tags[i].initialize(modio_mod.tags_array[i]);
    }
  }
}
