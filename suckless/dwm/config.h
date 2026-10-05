/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "brave"

/* appearance */
static unsigned int borderpx  = 2;
static unsigned int snap      = 32;
static int gappih             = 0;
static int gappiv             = 0;
static int gappoh             = 0;
static int gappov             = 0;
static int smartgaps          = 0;
static int showbar            = 1;
static int topbar             = 1;
static char fontmain[128]     = "Atkinson Hyperlegible Mono:size=12";
static char fontemoji[128]    = "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true";
static char fontnerd[128]     = "JetBrainsMonoNL Nerd Font:size=12";
static char fontsymbols[128]  = "Noto Sans Symbols 2:size=12";
static const char *fonts[]    = { fontmain, fontemoji, fontnerd, fontsymbols };
static char dmenufont[128]    = "Atkinson Hyperlegible Mono:size=12";

static char normbgcolor[32]     = "#000000";
static char normbordercolor[32] = "#1f1f1f";
static char normfgcolor[32]     = "#8a8a8a";
static char selbgcolor[32]      = "#000000";
static char selbordercolor[32]  = "#5a5a5a";
static char selfgcolor[32]      = "#d0d0d0";
static char stickybordercolor[32] = "#ff00ff";

static char statusfgcolor[32]   = "#8a8a8a";
static char statusbgcolor[32]   = "#000000";
static char tagsnormfgcolor[32] = "#8a8a8a";
static char tagsnormbgcolor[32] = "#000000";
static char tagsselfgcolor[32]  = "#c0c0c0";
static char tagsselbgcolor[32]  = "#000000";
static char infonormfgcolor[32] = "#8a8a8a";
static char infonormbgcolor[32] = "#000000";
static char infoselfgcolor[32]  = "#ffffff";
static char infoselbgcolor[32]  = "#000000";

static const char *colors[][3] = {
	/*               fg              bg              border */
	[SchemeNorm]      = { normfgcolor,     normbgcolor,     normbordercolor },
	[SchemeSel]       = { selfgcolor,      selbgcolor,      selbordercolor },
	[SchemeStatusLow] = { "#eeeeee", statusbgcolor, normbordercolor },
	[SchemeStatusMedium] = { "#a3d977", statusbgcolor, normbordercolor },
	[SchemeStatusWarn] = { "#ffd75f", statusbgcolor, normbordercolor },
	[SchemeStatusHot]  = { "#ff784f", statusbgcolor, normbordercolor },
	[SchemeStatus]    = { statusfgcolor,   statusbgcolor,   normbordercolor },
	[SchemeTagsNorm]  = { tagsnormfgcolor, tagsnormbgcolor, normbordercolor },
	[SchemeTagsSel]   = { tagsselfgcolor,  tagsselbgcolor,  selbordercolor },
	[SchemeInfoNorm]  = { infonormfgcolor, infonormbgcolor, normbordercolor },
	[SchemeInfoSel]   = { infoselfgcolor,  infoselbgcolor,  selbordercolor },
	[SchemeSticky]    = { normfgcolor,     normbgcolor,     stickybordercolor },
	[SchemeStickySel] = { selfgcolor,      selbgcolor,      stickybordercolor },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

static const char *sptermcmd[] = {
	TERMINAL, "-n", "spterm", "-g", "120x34", NULL
};
static const char *spcalccmd[] = {
	TERMINAL, "-n", "spcalc", "-f", "Atkinson Hyperlegible Mono:size=16",
	"-g", "50x20", "-e", "bc", "-lq", NULL
};
static Sp scratchpads[] = {
	{ "spterm", sptermcmd },
	{ "spcalc", spcalccmd },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ TERMCLASS,  "spterm",   NULL,       SPTAG(0),     1,           -1 },
	{ TERMCLASS,  "spcalc",   NULL,       SPTAG(1),     1,           -1 },
};

/* layout(s) */
static float mfact             = 0.55;
static int nmaster             = 1;
static int resizehints         = 0;
static const int lockfullscreen = 1;
static const int refreshrate   = 120;

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "[tile]",   tile },
	{ "[cols]",   columns },
	{ "[center]", centeredmaster },
	{ "[rows]",   bstack },
	{ "[float]",  NULL },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,             KEY,      view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask, KEY,      toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,   KEY,      tag,        {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j, ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k, ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_v, ACTION##stack, {.i = 0 } },

#define SHCMD(cmd) { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = {
	"dmenu_run", "-m", dmenumon, "-fn", dmenufont,
	"-nb", normbgcolor, "-nf", normfgcolor,
	"-sb", selbgcolor, "-sf", selfgcolor, NULL
};
static const char *termcmd[]    = { TERMINAL, NULL };
static const char *browsercmd[] = { BROWSER, NULL };
static const char *filescmd[]   = { "thunar", NULL };
static const char *sysactcmd[]  = { "sysact", NULL };
static const char *unicodecmd[] = { "dmenuunicode", NULL };
static const char *layouthelpcmd[] = {
	"/bin/sh", "-c",
	"notify-send 'dwm layouts' 'Super+t tile\nSuper+y cols\nSuper+i center\nSuper+u rows\nSuper+o float\nSuper+p/+Shift+p master count\nSuper+f fullscreen window'",
	NULL
};

#define XRES_STRING(name, var) { name, STRING, var, sizeof var }
#define XRES_VALUE(name, type, var) { name, type, var, 0 }
ResourcePref resources[] = {
	XRES_STRING("normbgcolor",     normbgcolor),
	XRES_STRING("font",            fontmain),
	XRES_STRING("fontemoji",       fontemoji),
	XRES_STRING("fontnerd",        fontnerd),
	XRES_STRING("fontsymbols",     fontsymbols),
	XRES_STRING("dmenufont",       dmenufont),
	XRES_STRING("normbordercolor", normbordercolor),
	XRES_STRING("normfgcolor",     normfgcolor),
	XRES_STRING("selbgcolor",      selbgcolor),
	XRES_STRING("selbordercolor",  selbordercolor),
	XRES_STRING("selfgcolor",      selfgcolor),
	XRES_STRING("statusfgcolor",   statusfgcolor),
	XRES_STRING("statusbgcolor",   statusbgcolor),
	XRES_STRING("tagsnormfgcolor", tagsnormfgcolor),
	XRES_STRING("tagsnormbgcolor", tagsnormbgcolor),
	XRES_STRING("tagsselfgcolor",  tagsselfgcolor),
	XRES_STRING("tagsselbgcolor",  tagsselbgcolor),
	XRES_STRING("infonormfgcolor", infonormfgcolor),
	XRES_STRING("infonormbgcolor", infonormbgcolor),
	XRES_STRING("infoselfgcolor",  infoselfgcolor),
	XRES_STRING("infoselbgcolor",  infoselbgcolor),
	XRES_STRING("color13",         stickybordercolor),
	XRES_VALUE("borderpx",         INTEGER, &borderpx),
	XRES_VALUE("snap",             INTEGER, &snap),
	XRES_VALUE("showbar",          INTEGER, &showbar),
	XRES_VALUE("topbar",           INTEGER, &topbar),
	XRES_VALUE("nmaster",          INTEGER, &nmaster),
	XRES_VALUE("resizehints",      INTEGER, &resizehints),
	XRES_VALUE("mfact",            FLOAT,   &mfact),
	XRES_VALUE("gappih",           INTEGER, &gappih),
	XRES_VALUE("gappiv",           INTEGER, &gappiv),
	XRES_VALUE("gappoh",           INTEGER, &gappoh),
	XRES_VALUE("gappov",           INTEGER, &gappov),
	XRES_VALUE("smartgaps",        INTEGER, &smartgaps),
};

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key            function          argument */
	STACKKEYS(MODKEY,                              focus)
	STACKKEYS(MODKEY|ShiftMask,                    push)
	{ MODKEY,                       XK_grave,       spawn,          {.v = unicodecmd } },
	TAGKEYS(                        XK_1,                          0)
	TAGKEYS(                        XK_2,                          1)
	TAGKEYS(                        XK_3,                          2)
	TAGKEYS(                        XK_4,                          3)
	TAGKEYS(                        XK_5,                          4)
	TAGKEYS(                        XK_6,                          5)
	TAGKEYS(                        XK_7,                          6)
	TAGKEYS(                        XK_8,                          7)
	TAGKEYS(                        XK_9,                          8)
	{ MODKEY,                       XK_BackSpace,   spawn,          {.v = sysactcmd } },
	{ MODKEY|ShiftMask,             XK_q,           spawn,          {.v = sysactcmd } },
	{ MODKEY,                       XK_Tab,         view,           {0} },
	{ MODKEY,                       XK_q,           killclient,     {0} },
	{ MODKEY,                       XK_w,           spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_r,           spawn,          {.v = filescmd } },
	{ MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_i,           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,           setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,           setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_p,           incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_p,           incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_a,           togglegaps,     {0} },
	{ MODKEY,                       XK_s,           togglesticky,   {0} },
	{ MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_f,           togglefullscr,  {0} },
	{ MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_comma,       spawn,          SHCMD("playerctl previous; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ MODKEY,                       XK_period,      spawn,          SHCMD("playerctl play-pause; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ MODKEY,                       XK_slash,       spawn,          SHCMD("playerctl next; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ MODKEY,                       XK_minus,       spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; pkill -RTMIN+10 ${STATUSBAR:-dwmblocks}") },
	{ MODKEY,                       XK_equal,       spawn,          SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 3%+; pkill -RTMIN+10 ${STATUSBAR:-dwmblocks}") },
	{ MODKEY,                       XK_m,           spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; pkill -RTMIN+10 ${STATUSBAR:-dwmblocks}") },
	{ MODKEY|ShiftMask,             XK_m,           spawn,          SHCMD("mic-kill-switch") },
	{ MODKEY,                       XK_apostrophe,  togglescratch,  {.ui = 1} },
	{ MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,      togglescratch,  {.ui = 0} },
	{ MODKEY,                       XK_b,           togglebar,      {0} },
	{ MODKEY,                       XK_Left,        focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,        tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,       tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_space,       setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
	{ MODKEY,                       XK_F5,          xrdb,           {0} },
	{ 0,                            XK_Print,       spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,                    XK_Print,       spawn,          SHCMD("maim -s pic-area-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY|ShiftMask,             XK_s,           spawn,          SHCMD("screenshot-select") },
	{ 0, XF86XK_AudioMute,          spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; pkill -RTMIN+10 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,          SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 3%+; pkill -RTMIN+10 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; pkill -RTMIN+10 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioPrev,          spawn,          SHCMD("playerctl previous; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioNext,          spawn,          SHCMD("playerctl next; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioPause,         spawn,          SHCMD("playerctl play-pause; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioPlay,          spawn,          SHCMD("playerctl play-pause; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioStop,          spawn,          SHCMD("playerctl stop; pkill -RTMIN+11 ${STATUSBAR:-dwmblocks}") },
	{ 0, XF86XK_AudioMicMute,       spawn,          SHCMD("mic-kill-switch") },
	{ 0, XF86XK_Calculator,         spawn,          SHCMD(TERMINAL " -e bc -lq") },
	{ 0, XF86XK_WWW,                spawn,          {.v = browsercmd } },
	{ 0, XF86XK_DOS,                spawn,          {.v = termcmd } },
	{ 0, XF86XK_MonBrightnessUp,    spawn,          SHCMD("brightnessctl set +1%") },
	{ 0, XF86XK_MonBrightnessDown,  spawn,          SHCMD("brightnessctl set 1%-") },
};

static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {0} },
	{ ClkLtSymbol,          0,              Button3,        spawn,          {.v = layouthelpcmd } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,    {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        incrgaps,       {.i = +1} },
	{ ClkClientWin,         MODKEY,         Button5,        incrgaps,       {.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkRootWin,           0,              Button2,        togglebar,      {0} },
};
