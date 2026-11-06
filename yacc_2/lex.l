
%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
[0-9]+       { sscanf(yytext, "%d", &yylval); return NUM; }
[+\-*/()]    { return yytext[0]; }
\n           { return '\n'; }
.            { return other; }
%% 
