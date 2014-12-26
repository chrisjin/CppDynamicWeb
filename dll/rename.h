#include"fileptrs.h"
#include"domptrs.h"
#define Rename(type) typedef type##Ptr type 

Rename(WebObject);
Rename(Html);
Rename(Button);
Rename(Div);
Rename(Form);
Rename(Frame);
Rename(Frameset);
Rename(JavaScript);
Rename(JSFunc);
Rename(Script);
//Rename(CSS);
Rename(Img);
Rename(Input);
Rename(Image);
Rename(BinFile);
Rename(TxtFile);


