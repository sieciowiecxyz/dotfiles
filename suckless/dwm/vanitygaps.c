static void bstack(Monitor *m);
static void columns(Monitor *m);
static void centeredmaster(Monitor *m);
static void defaultgaps(const Arg *arg);
static void getfacts(Monitor *m, int msize, int ssize, float *mf, float *sf, int *mr, int *sr);
static void getgaps(Monitor *m, int *oh, int *ov, int *ih, int *iv, unsigned int *nc);
static void incrgaps(const Arg *arg);
static void setgaps(int oh, int ov, int ih, int iv);
static void togglegaps(const Arg *arg);

static void
setgaps(int oh, int ov, int ih, int iv)
{
	Pertag *pt = selmon->pertag;
	unsigned int tag = pt->curtag;

	if (oh < 0)
		oh = 0;
	if (ov < 0)
		ov = 0;
	if (ih < 0)
		ih = 0;
	if (iv < 0)
		iv = 0;

	selmon->gappoh = pt->gappoh[tag] = oh;
	selmon->gappov = pt->gappov[tag] = ov;
	selmon->gappih = pt->gappih[tag] = ih;
	selmon->gappiv = pt->gappiv[tag] = iv;
	arrange(selmon);
}

static void
togglegaps(const Arg *arg)
{
	selmon->pertag->enablegaps[selmon->pertag->curtag] ^= 1;
	arrange(selmon);
}

static void
defaultgaps(const Arg *arg)
{
	selmon->pertag->enablegaps[selmon->pertag->curtag] = 0;
	setgaps(gappoh, gappov, gappih, gappiv);
}

static void
incrgaps(const Arg *arg)
{
	setgaps(
		selmon->gappoh + arg->i,
		selmon->gappov + arg->i,
		selmon->gappih + arg->i,
		selmon->gappiv + arg->i
	);
}

static void
getgaps(Monitor *m, int *oh, int *ov, int *ih, int *iv, unsigned int *nc)
{
	unsigned int n;
	int oe, ie;
	Client *c;

	oe = ie = m->pertag->enablegaps[m->pertag->curtag];
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
		;
	if (smartgaps && n == 1)
		oe = 0;

	*oh = m->gappoh * oe;
	*ov = m->gappov * oe;
	*ih = m->gappih * ie;
	*iv = m->gappiv * ie;
	*nc = n;
}

static void
getfacts(Monitor *m, int msize, int ssize, float *mf, float *sf, int *mr, int *sr)
{
	unsigned int n;
	float mfacts, sfacts;
	int mtotal = 0, stotal = 0;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
		;
	mfacts = MIN(n, m->nmaster);
	sfacts = n - m->nmaster;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) {
		if (n < m->nmaster)
			mtotal += msize / mfacts;
		else
			stotal += ssize / sfacts;
	}

	*mf = mfacts;
	*sf = sfacts;
	*mr = msize - mtotal;
	*sr = ssize - stotal;
}

static void
bstack(Monitor *m)
{
	unsigned int i, n;
	int mx, my, mh, mw;
	int sx, sy, sh, sw;
	float mfacts, sfacts;
	int mrest, srest;
	Client *c;
	int oh, ov, ih, iv;

	getgaps(m, &oh, &ov, &ih, &iv, &n);
	if (n == 0)
		return;

	sx = mx = m->wx + ov;
	sy = my = m->wy + oh;
	sh = mh = m->wh - 2 * oh;
	mw = m->ww - 2 * ov - iv * (MIN(n, m->nmaster) - 1);
	sw = m->ww - 2 * ov - iv * (n - m->nmaster - 1);

	if (m->nmaster && n > m->nmaster) {
		sh = (mh - ih) * (1 - m->mfact);
		mh = (mh - ih) * m->mfact;
		sy = my + mh + ih;
	}

	getfacts(m, mw, sw, &mfacts, &sfacts, &mrest, &srest);

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			resize(c, mx, my,
				(mw / mfacts) + (i < mrest ? 1 : 0) - (2 * c->bw),
				mh - (2 * c->bw), 0);
			mx += WIDTH(c) + iv;
		} else {
			resize(c, sx, sy,
				(sw / sfacts) + ((i - m->nmaster) < srest ? 1 : 0) - (2 * c->bw),
				sh - (2 * c->bw), 0);
			sx += WIDTH(c) + iv;
		}
	}
}

static void
columns(Monitor *m)
{
	unsigned int i, n;
	int x, y, h, w;
	Client *c;
	int oh, ov, ih, iv;

	getgaps(m, &oh, &ov, &ih, &iv, &n);
	if (n == 0)
		return;

	x = m->wx + ov;
	y = m->wy + oh;
	h = m->wh - 2 * oh;
	w = (m->ww - 2 * ov - iv * (n - 1)) / n;

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		int cw = w;
		if (i == n - 1)
			cw = m->wx + m->ww - ov - x;
		resize(c, x, y, cw - (2 * c->bw), h - (2 * c->bw), 0);
		x += cw + iv;
	}
}

static void
centeredmaster(Monitor *m)
{
	unsigned int i, n;
	float mfacts = 0, lfacts = 0, rfacts = 0;
	int mw, mx, my, mh;
	int lw, lx, ly, lh;
	int rw, rx, ry, rh;
	int mrest, lrest, rrest;
	Client *c;
	int oh, ov, ih, iv;

	getgaps(m, &oh, &ov, &ih, &iv, &n);
	if (n == 0)
		return;

	mx = lx = rx = m->wx + ov;
	my = ly = ry = m->wy + oh;
	mh = m->wh - 2 * oh - ih * ((!m->nmaster ? n : MIN(n, m->nmaster)) - 1);
	lh = m->wh - 2 * oh - ih * (((n - m->nmaster) / 2) - 1);
	rh = m->wh - 2 * oh - ih * (((n - m->nmaster) / 2) - ((n - m->nmaster) % 2 ? 0 : 1));
	mw = m->ww - 2 * ov;
	lw = rw = (mw - iv) / 2;

	if (m->nmaster && n > m->nmaster) {
		if (n - m->nmaster > 1) {
			mw = (m->ww - 2 * ov - 2 * iv) * m->mfact;
			lw = (m->ww - mw - 2 * ov - 2 * iv) / 2;
			rw = (m->ww - mw - 2 * ov - 2 * iv) - lw;
			mx += lw + iv;
			rx = mx + mw + iv;
		} else {
			mw = (mw - iv) * m->mfact;
			lw = rw = (m->ww - mw - 2 * ov - iv) / 2;
			mx += lw + iv;
			rx = mx + mw + iv;
		}
	}

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (!m->nmaster || i < m->nmaster)
			mfacts += 1;
		else if ((n - m->nmaster) % 2) {
			if ((i - m->nmaster) % 2)
				lfacts += 1;
			else
				rfacts += 1;
		} else {
			if ((i - m->nmaster) % 2)
				rfacts += 1;
			else
				lfacts += 1;
		}
	}

	for (i = 0, mrest = 0, lrest = 0, rrest = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (!m->nmaster || i < m->nmaster)
			mrest += mh / mfacts;
		else if ((n - m->nmaster) % 2) {
			if ((i - m->nmaster) % 2)
				lrest += lh / lfacts;
			else
				rrest += rh / rfacts;
		} else {
			if ((i - m->nmaster) % 2)
				rrest += rh / rfacts;
			else
				lrest += lh / lfacts;
		}
	}
	mrest = mh - mrest;
	lrest = lh - lrest;
	rrest = rh - rrest;

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (!m->nmaster || i < m->nmaster) {
			resize(c, mx, my, mw - (2 * c->bw),
				(mh / mfacts) + (i < mrest ? 1 : 0) - (2 * c->bw), 0);
			my += HEIGHT(c) + ih;
		} else if ((n - m->nmaster) % 2) {
			if ((i - m->nmaster) % 2) {
				resize(c, lx, ly, lw - (2 * c->bw),
					(lh / lfacts) + ((i - 2 * m->nmaster) < 2 * lrest ? 1 : 0) - (2 * c->bw), 0);
				ly += HEIGHT(c) + ih;
			} else {
				resize(c, rx, ry, rw - (2 * c->bw),
					(rh / rfacts) + ((i - 2 * m->nmaster) < 2 * rrest ? 1 : 0) - (2 * c->bw), 0);
				ry += HEIGHT(c) + ih;
			}
		} else {
			if ((i - m->nmaster) % 2) {
				resize(c, rx, ry, rw - (2 * c->bw),
					(rh / rfacts) + ((i - 2 * m->nmaster) < 2 * rrest ? 1 : 0) - (2 * c->bw), 0);
				ry += HEIGHT(c) + ih;
			} else {
				resize(c, lx, ly, lw - (2 * c->bw),
					(lh / lfacts) + ((i - 2 * m->nmaster) < 2 * lrest ? 1 : 0) - (2 * c->bw), 0);
				ly += HEIGHT(c) + ih;
			}
		}
	}
}
