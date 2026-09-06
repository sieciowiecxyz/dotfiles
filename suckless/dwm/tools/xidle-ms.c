#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>

int
main(void)
{
	Display *display;
	XScreenSaverInfo *info;

	display = XOpenDisplay(NULL);
	if (!display) {
		fputs("xidle-ms: cannot open display\n", stderr);
		return 1;
	}

	info = XScreenSaverAllocInfo();
	if (!info) {
		fputs("xidle-ms: cannot allocate XScreenSaverInfo\n", stderr);
		XCloseDisplay(display);
		return 1;
	}

	if (!XScreenSaverQueryInfo(display, DefaultRootWindow(display), info)) {
		fputs("xidle-ms: XScreenSaverQueryInfo failed\n", stderr);
		XFree(info);
		XCloseDisplay(display);
		return 1;
	}

	printf("%lu\n", info->idle);

	XFree(info);
	XCloseDisplay(display);
	return 0;
}
