
/* 
 * remove newlines that occur within ().
 * does not support nested parens.
 */
main()
{
	int i;
	int killnl=0;
	while(( (i = getchar())  )  != -1) {
            if(i == '(') killnl=1;
            if(i == ')') killnl=0;
	    if(killnl && (i == '\n')) {
                putchar(' ');
                
 	    } else {
		putchar(i);
	    }
	}
}
