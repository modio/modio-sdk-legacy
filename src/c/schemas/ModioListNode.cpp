#include "c/schemas/ModioListNode.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload

extern "C"
{
  void modioInitNode(ModioListNode* node)
  {
    node->value = NULL;
    node->next = NULL;
  }

  void modioFreeNodeList(ModioListNode* node)
  {
    if(node)
    {
      ModioListNode* next = node->next;
      if(node->value)
        delete[] node->value;
      delete node;

      modioFreeNodeList(next);
    }
  }
}
