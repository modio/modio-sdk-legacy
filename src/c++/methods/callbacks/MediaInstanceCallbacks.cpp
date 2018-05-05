#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, AddModLogoCall *> add_mod_logo_calls;
std::map<u32, AddModImagesCall *> add_mod_images_calls;
std::map<u32, AddModYoutubeLinksCall *> add_mod_youtube_links_calls;
std::map<u32, AddModSketchfabLinksCall *> add_mod_sketchfab_links_calls;

void onAddModLogo(void *object, ModioResponse modio_response)
{
    u32 call_id = *((u32 *)object);

    modio::Response response;
    response.initialize(modio_response);

    add_mod_logo_calls[call_id]->callback(response);

    delete (u32 *)object;
    delete add_mod_logo_calls[call_id];
    add_mod_logo_calls.erase(call_id);
}

void onAddModImages(void *object, ModioResponse modio_response)
{
    u32 call_id = *((u32 *)object);

    modio::Response response;
    response.initialize(modio_response);

    add_mod_images_calls[call_id]->callback(response);

    delete (u32 *)object;
    delete add_mod_images_calls[call_id];
    add_mod_images_calls.erase(call_id);
}

void onAddModYoutubeLinks(void *object, ModioResponse modio_response)
{
    u32 call_id = *((u32 *)object);

    modio::Response response;
    response.initialize(modio_response);

    add_mod_youtube_links_calls[call_id]->callback(response);

    delete (u32 *)object;
    delete add_mod_youtube_links_calls[call_id];
    add_mod_youtube_links_calls.erase(call_id);
}

void onAddModSketchfabLinks(void *object, ModioResponse modio_response)
{
    u32 call_id = *((u32 *)object);

    modio::Response response;
    response.initialize(modio_response);

    add_mod_sketchfab_links_calls[call_id]->callback(response);

    delete (u32 *)object;
    delete add_mod_sketchfab_links_calls[call_id];
    add_mod_sketchfab_links_calls.erase(call_id);
}
}
