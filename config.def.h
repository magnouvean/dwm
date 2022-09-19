/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#bfbfbf";
static const char col_gray3[]       = "#ff79c6";
static const char col_gray4[]       = "#f8f8f2";
static const char col_cyan[]        = "#282a36";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_gray1, col_cyan },
	[SchemeSel]  = { col_gray4, col_gray3,  col_gray3  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "st-256color",              NULL, NULL, 1 << 0, 0, -1 },
	{ "Emacs",                    NULL, NULL, 1 << 0, 0, -1 },
	{ "Luakit",                   NULL, NULL, 1 << 1, 0, -1 },
	{ "firefox",                  NULL, NULL, 1 << 1, 0, -1 },
	{ "Nyxt",                     NULL, NULL, 1 << 1, 0, -1 },
	{ "Chromium-browser",         NULL, NULL, 1 << 1, 0, -1 },
	{ "Zathura",                  NULL, NULL, 1 << 3, 0, -1 },
	{ "sioyek",                   NULL, NULL, 1 << 3, 0, -1 },
	{ "Soffice",                  NULL, NULL, 1 << 3, 0, -1 },
	{ "libreoffice-writer",       NULL, NULL, 1 << 3, 0, -1 },
	{ "libreoffice-impress",      NULL, NULL, 1 << 3, 0, -1 },
	{ "libreoffice-startcenter",  NULL, NULL, 1 << 3, 0, -1 },
	{ "libreoffice-writer",       NULL, NULL, 1 << 3, 0, -1 },
	{ "GNU Octave",               NULL, NULL, 1 << 4, 0, -1 },
	{ "GeoGebra",                 NULL, NULL, 1 << 4, 0, -1 },
	{ "Matplotlib",               NULL, NULL, 1 << 4, 0, -1 },
	{ "libreoffice-calc",         NULL, NULL, 1 << 4, 0, -1 },
	{ "libreoffice-math",         NULL, NULL, 1 << 4, 0, -1 },
	{ "Ferdi",                    NULL, NULL, 1 << 5, 0, -1 },
	{ "thunderbird",              NULL, NULL, 1 << 6, 0, -1 },
	{ "tiled",                    NULL, NULL, 1 << 7, 0, -1 },
	{ "LDtk",                     NULL, NULL, 1 << 7, 0, -1 },
	{ "Gimp-2.10",                NULL, NULL, 1 << 7, 0, -1 },
	{ "mpv",                      NULL, NULL, 1 << 8, 0, -1 },
	{ "Virt-manager",             NULL, NULL, 1 << 9, 0, -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

void tagandview(const Arg *arg) {
	tag(arg);
	view(arg);
}
void montagandview(const Arg *arg) {
	tagmon(arg);
	focusmon(arg);
}
void togglefullscreen(const Arg *arg) {
	if (!selmon->sel)
		return;
	if (!selmon->sel->isfullscreen)
		setfullscreen(selmon->sel, 1);
	else if (selmon->sel->isfullscreen)
		setfullscreen(selmon->sel, 0);
}

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{Mod4Mask, KEY, view, {.ui = 1 << TAG}}, \
	{Mod4Mask | ShiftMask, KEY, tagandview, {.ui = 1 << TAG}},
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *roficmd[]  = { "rofi", "-show", "drun", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY | Mod4Mask,        XK_r,         spawn,             {.v = roficmd} },
	{ MODKEY,                   XK_Return,    spawn,             {.v = termcmd} },
	{ Mod4Mask,                 XK_j,         focusstack,        {.i = +1} },
	{ Mod4Mask,                 XK_k,         focusstack,        {.i = -1} },
	{ Mod4Mask | ShiftMask,     XK_j,         movestack,         {.i = +1} },
	{ Mod4Mask | ShiftMask,     XK_k,         movestack,         {.i = -1} },
	{ MODKEY,                   XK_q,         killclient,        {0} },
	{ MODKEY,                   XK_s,         togglefloating,    {0} },
	{ MODKEY,                   XK_f,         togglefullscreen,  {0} },
	{ MODKEY,                   XK_l,         focusmon,          {.i = -1} },
	{ MODKEY,                   XK_h,         focusmon,          {.i = +1} },
	{ MODKEY | ShiftMask,       XK_l,         montagandview,     {.i = -1} },
	{ MODKEY | ShiftMask,       XK_h,         montagandview,     {.i = +1} },
	{ MODKEY | ShiftMask,       XK_s,         spawn,             SHCMD("$HOME/.dwm/screenlock.sh") },
	{ MODKEY | Mod4Mask,        XK_Escape,    spawn,             SHCMD("rofi -show power-menu -modi power-menu:rofi-power-menu") },
	{ MODKEY | Mod4Mask,        XK_F1,        spawn,             SHCMD("rofi-mpc") },
	{ MODKEY | Mod4Mask,        XK_F11,       spawn,             SHCMD("tessen") },
	{ MODKEY|ShiftMask,         XK_e,         quit,              {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,     0,        Button1, view,           {0} },
	{ ClkClientWin,  Mod4Mask, Button1, movemouse,      {0} },
	{ ClkClientWin,  Mod4Mask, Button2, togglefloating, {0} },
	{ ClkClientWin,  Mod4Mask, Button3, resizemouse,    {0} },
};

