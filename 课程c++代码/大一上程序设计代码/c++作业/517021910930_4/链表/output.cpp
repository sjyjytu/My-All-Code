#include "head.h"

void output(link *c)
{
    if (c->next==NULL) cout<<c->data;
    else {output(c->next);cout<<' '<<c->data;}

}
