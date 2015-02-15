#include"doms.h"
#include"common.h" 
main()
{
      ClientInfo test;
      test.PostSpace=(char *)malloc(100);
      strcpy(test.PostSpace,"ccccccccccccc");
      WebInterface inter("anotherpage.exe");
      inter.webmain(&test,0);
        cout<<test.PageSpace;
      getchar();
}
