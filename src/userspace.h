// WE DO NOT BREAK USERSPACE!
// Typos have been preserved for accuracy.

/**
 * @brief WE DO NOT BREAK USERSPACE! This variable contains a message sent by Linus Torvalds
 * to a Linux kernel developer named "Mauro", roasting him
 * for breaking userspace.
 */

const char* WE_DO_NOT_BREAK_USERSPACE =
"From	Linus Torvalds <>\n"
"Date	Sun, 23 Dec 2012 09:36:15 -0800\n"
"Subject	Re: [Regression w/ patch] Media commit causes user space to misbahave (was: Re: Linux 3.8-rc1)\n"
"On Sun, Dec 23, 2012 at 6:08 AM, Mauro Carvalho Chehab\n"
"<mchehab@redhat.com> wrote:\n"
">\n"
"> Are you saying that pulseaudio is entering on some weird loop if the\n"
"> returned value is not -EINVAL? That seems a bug at pulseaudio.\n"
"\n"
#ifdef FAMILY_FRIENDLY
"Mauro, SHUT UP!\n"
#else
"Mauro, SHUT THE FUCK UP!\n"
#endif
"\n"
"It's a bug alright - in the kernel. How long have you been a\n"
"maintainer? And you *still* haven't learnt the first rule of kernel\n"
"maintenance?\n"
"\n"
"If a change results in user programs breaking, it's a bug in the\n"
"kernel. We never EVER blame the user programs. How hard can this be to\n"
"understand?\n"
"\n"
"To make matters worse, commit f0ed2ce840b3 is clearly total and utter\n"
#ifdef FAMILY_FRIENDLY
"GARBAGE even if it didn't break applications. ENOENT is not a valid error\n"
#else
"CRAP even if it didn't break applications. ENOENT is not a valid error\n"
#endif
"return from an ioctl. Never has been, never will be. ENOENT means \"No\n"
"such file and directory\", and is for path operations. ioctl's are done\n"
"on files that have already been opened, there's no way in hell that\n"
"ENOENT would ever be valid.\n"
"\n"
"> So, on a first glance, this doesn't sound like a regression,\n"
"> but, instead, it looks tha pulseaudio/tumbleweed has some serious\n"
"> bugs and/or regressions.\n"
"\n"
"Shut up, Mauro. And I don't _ever_ want to hear that kind of obvious\n"
#ifdef FAMILY_FRIENDLY
"garbage and nonsense from a kernel maintainer again. Seriously.\n"
#else
"garbage and idiocy from a kernel maintainer again. Seriously.\n"
#endif
"\n"
"I'd wait for Rafael's patch to go through you, but I have another\n"
"error report in my mailbox of all KDE media applications being broken\n"
"by v3.8-rc1, and I bet it's the same kernel bug. And you've shown\n"
"yourself to not be competent in this issue, so I'll apply it directly\n"
"and immediately myself.\n"
"\n"
"WE DO NOT BREAK USERSPACE!\n"
"\n"
"Seriously. How hard is this rule to understand? We particularly don't\n"
#ifdef FAMILY_FRIENDLY
"break user space with TOTAL GARBAGE. I'm angry, because your whole email\n"
#else
"break user space with TOTAL CRAP. I'm angry, because your whole email\n"
#endif
"was so _horribly_ wrong, and the patch that broke things was so\n"
"obviously crap. The whole patch is incredibly broken shit. It adds an\n"
"insane error code (ENOENT), and then because it's so insane, it adds a\n"
"few places to fix it up (\"ret == -ENOENT ? -EINVAL : ret\").\n"
"\n"
"The fact that you then try to make *excuses* for breaking user space,\n"
"and blaming some external program that *used* to work, is just\n"
"shameful. It's not how we work.\n"
"\n"
#ifdef FAMILY_FRIENDLY
"Fix your \"compliance tool\", because it is obviously broken.\n"
#else
"Fix your f*cking \"compliance tool\", because it is obviously broken.\n"
#endif
"And fix your approach to kernel programming.\n"
"\n"
"               Linus\n";