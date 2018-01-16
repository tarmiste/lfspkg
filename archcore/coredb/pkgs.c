

struct pkgdeps {
char *names[100];
char *provides[200];
char *depends[200];
char *optdepends[200];
char *makedepends[200];
char *checkdepends[200];
} ;

char *dependslist[200];
char *makedependslist[200];
	
#include "basepkgs.c"
#include "basedevelpkgs.c"

struct pkgdeps pkgs[20000] = {
#include "glue"
#include "../extradb/glue"
#include "../communitydb/glue" 
};
	

char *installedpkgs[20000];
int installedcount=0;

int
addifunique(char *pkg)
{
	unsigned int i;
	for(i = 0; i < 20000; i++) {
		if(installedpkgs[i] == 0 ) {
			installedpkgs[i] = pkg;
			installedcount++;
			printf("adding %s\n", pkg);
			return(1);
		}
		if(!strcmp(installedpkgs[i], pkg)) {
			/*printf("duplicate %s %s\n", installedpkgs[i], pkg); */
			break;
		}
	}
	return(0);
}

getdepends(char *pkg)
{
	int i,j;
	int foundit=0;
	int len;

	dependslist[0] = 0;
	makedependslist[0] = 0;
	for(i = 0; i < 20000; i++) {
		if(pkgs[i].names[0] == 0) { 
			printf("Error: Can't find %s in pkglist\n", pkg);
			return;
		}
		if(!strcmp(pkgs[i].names[0], pkg)) {
			foundit=1;
		}
		for(j =0; j < 100; j++) {
			if(pkgs[i].provides[j] == 0) break;
			len=strlen(pkgs[i].provides[j]);
			if(len != 0)  {
#if	0
				if(!strcmp(".so", pkgs[i].provides[j]+(len-3)) {
				if(!strncmp(pkgs[i].provides[j], pkg, len-3)) {
printf("Truncate match .so\n");
					foundit=1;
				}
				}
#endif
			}
			if(!strcmp(pkgs[i].provides[j], pkg)) {
				foundit=1;
				break;
			}
		}
		if(foundit) {
			for(j=0; j < 200; j++) {
				dependslist[j] = pkgs[i].depends[j];
				if(dependslist[j] == 0) break;	
			}
			for(j=0; j < 200; j++) {
				makedependslist[j] = pkgs[i].makedepends[j];
				if(makedependslist[j] == 0) break;	
			}
			return;
		}
	}
}

int
getdeplength(char *depstring)
{
	int len=0;
	if(depstring == 0) return (0);
	if(*depstring == 0) return (0);
	return(strlen(depstring));
	while(*depstring != 0) {
		if(*depstring == '>'){
			return(len);
		}
		if(*depstring == '='){
			return(len);
		}
		len++;
		depstring++;
	}
	return(len);
}

killdepgarbage(char *depstring)
{
	if(depstring == 0) return;
	if(*depstring == 0) return;
	while(*depstring != 0) {
		if(*depstring == '>'){
#if	0
			 *depstring=0;
#endif
			return;
		}
		if(*depstring == '='){
#if	0
			 *depstring=0;
#endif
			return;
		}
		depstring++;
	}
}

main()
{
	int i,j;
	char *list[200];
	char *pkg;
	int loop=0;
	char depstr[100];

	for(i = 0; i < 20000; i++) {
		if(basepkgs[i] == 0) { break; }
		installedpkgs[i] = basepkgs[i];
		installedcount++;
	}

	for(i = 0; i < 20000; i++) {
		if(basedevelpkgs[i] == 0) { break; }
		(void)addifunique(basedevelpkgs[i]);
	}


#if	0
printf("=====initial package list = \n");
for(i = 0; i < 20000; i++) {
	if(installedpkgs[i] == 0) break;
	printf("%s\n", installedpkgs[i]);
}
printf("=====end of initial package list = \n");
#endif

printf("adding first set\n");

	for(loop=0; loop < 20; loop++){
		printf("loop= %d\n", loop);

		for(i = 0; i < 20000; i++) {
			if(installedpkgs[i] == 0) break;

			pkg=installedpkgs[i];
			getdepends(pkg);
#if	0
printf("deps for %s\n", pkg);
#endif

			for(j = 0; j < 200; j++){
				if(dependslist[j] == 0) {
					break;
				}
#if	0
				memset(&depstr[0], 0, 100);
				strcpy(&depstr[0], dependslist[j]);
				depstr[getdeplength(&depstr[0])] = 0;
				addifunique(&depstr[0]);
#endif
				addifunique(dependslist[j]);
			}
			for(j = 0; j < 200; j++){
				if(makedependslist[j] == 0) {
					break;
				}
#if	0
				memset(&depstr[0], 0, 100);
				strcpy(&depstr[0], makedependslist[j]);
				depstr[getdeplength(&depstr[0])] = 0;
				addifunique(&depstr[0]);
#endif
				addifunique(makedependslist[j]);
			}

		}
	}


#if	0
printf("=====final package list = \n");
for(i = 0; i < 20000; i++) {
	if(installedpkgs[i] == 0) break;
	printf("%s\n", installedpkgs[i]);
}
printf("=====end of initial package list = \n");
#endif
	printf("installedpkgs= %d\n", installedcount);
}
