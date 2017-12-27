#include "extern_c/schemas/ModioListNode.h"

extern "C"
{
  void modioInitNode(ModioListNode* node)
  {
    node->value = NULL;
    node->next = NULL;
  }

  void modioFreeNodeList(ModioListNode* node)
  {
    if(node->value)
      delete node->value;

    if(node->next)
      modioFreeNodeList(node->next);
  }
}
