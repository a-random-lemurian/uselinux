#compdef _uselinux uselinux

# Completion for uselinux <https://github.com/a-random-lemurian/uselinux>

function _uselinux {
  local -a commands

  _arguments \
   "--arch-btw[I use arch btw]" \
   "--bash-macos[macOS is spyware]" \
   "--bash-windows[Windows is spyware]" \
   "--break-userspace[Make Linus Torvalds angry by breaking userspace with Linux kernel patches]" \
   "--compile-everything[Compile everything (Gentoo)]" \
   '(-d --distro)'{-d,--distro}"[Specify a Linux distribution]" \
   '(-e --desk)'{-e,--desk}"[Specify a desktop environment]" \
   "--get-yold[Print the year of the Linux desktop]" \
   "--hackerman[Be a hackerman (requires Kali)]" \
   "--segfault[Trigger a segmentation fault]" \
   "--snap-at-snaps[Get annoyed at constant Ubuntu snap updates]" \
   "--year-of-linux-desktop[Specify the year of the Linux desktop]" \
   "--family-friendly[Use with --break-userspace, for strict parents]"
}

compdef _uselinux uselinux 
