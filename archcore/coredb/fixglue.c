
main()
{
	int i;
	int block=0;
	while ((i = getchar()) != -1) {
		if(i == '>') block=1;
		if(i == '=') block=1;
		if(i == '"') block=0;
		if(!block) putchar(i);
	}
}

