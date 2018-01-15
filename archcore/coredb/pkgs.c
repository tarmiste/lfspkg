

struct pkgdeps {
char *names[100];
char *depends[200];
char *optdepends[100];
char *makedepends[100];
char *checkdepends[100];
} ;
	
struct pkgdeps pkgs[20000] = {
#include "glue"
#include "../extradb/glue"
#include "../communitydb/glue"
};
	
#if	0
struct pkgdeps moo = {
{ "zlib", "", },
{ "glibc", "", },
{ "", },
{ "", },
{ "", },
};
#endif

main()
{
	int i,j;
	for(i = 0; i < 20000; i++) {
		if(pkgs[i].names[0] == 0) break;
		printf("%s: ", pkgs[i].names[0]);
		printf("deps=");
		for(j = 0; j < 200; j++) {
			if(pkgs[i].depends[j] == 0) break;
			printf("%s ", pkgs[i].depends[j]);
		}
		printf("\n");
	}
	printf("numpkgs= %d\n", i);
}
