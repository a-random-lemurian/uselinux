# Completion for uselinux <https://github.com/a-random-lemurian/uselinux>

_uselinux()
{
    local cur prev opts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    opts="
        --arch-btw
        --bash-macos
        --bash-windows
        --break-userspace
        --compile-everything
        --distro
        --desk
        --get-yold
        --hackerman
        --no-bloatware
        --segfault
        --snap-at-snaps
        --year-of-linux-desktop
        --no-typewriter
        --help
        --usage
        --version"
    if [[ ${cur} == -* ]] ; then
        COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
        return 0
    fi
}

complete -F _uselinux uselinux
