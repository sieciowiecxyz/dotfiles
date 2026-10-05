//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
/*	{"⌨", "sb-kbselect", 0, 30},*/ 
/*	{"",	"sb-tasks",	10,	26},*/
	{"",	"sb-media",	1,	11},
	{"",	"sb-mic",	0,	12},
	{"",	"sb-volume",	0,	10},
	{"",	"sb-idle",	10,	13},
	{"",	"sb-pacpackages",	1800,	8},
	{"",	"sb-cpu-simple",	2,	18},
	{"",	"sb-gpu-simple",	2,	27},
	{"",	"sb-power-mode",	2,	20},
	{"",	"sb-power",	2,	19},
	{"", "sb-codex", 900, 28},
	{"",	"sb-forecast",	9000,	5},
	{"",	"sb-clock",	1,	1},
/*	{"",	"sb-cpu",		10,	18}, */
/*	{"",	"sb-brightness",	0,	15},*/
/*	{"",	"sb-mailbox",	300,	24},*/
/* {"",	"sb-price xmr-btc \"Monero to Bitcoin\" 🔒 25",	9000,	25}, */
	/* {"",	"sb-price xmr Monero 🔒 24",			9000,	24}, */
	/* {"",	"sb-price eth Ethereum 🍸 23",			9000,	23}, */
/*	{"",	"sb-nettraf",	1,	16},*/
/*	{"",	"sb-internet",	5,	4},*/
/*	{"",	"sb-battery",	5,	3},*/ 
};

//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = " | ";

// Have dwmblocks automatically recompile and run when you edit this file in
// vim with the following line in your vimrc/init.vim:

// autocmd BufWritePost ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; sudo make install && { killall -q dwmblocks;setsid dwmblocks & }
