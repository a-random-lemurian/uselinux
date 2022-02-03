@test "hackerman with kali" {
  result="$(../bin/uselinux --hackerman -d kali)"
}

@test "hackerman, no distro" {
  run ../bin/uselinux --hackerman
  [ "$status" -eq 1 ]
  [ "$output" = "fatal: distro not specified" ]
}

@test "hackerman, wrong distro" {
  run ../bin/uselinux --hackerman -d debian
  [ "$status" -eq 1 ]
  [ "$output" = "fatal: --hackerman requires Kali Linux (use -d kali)" ]
}

@test "pass --segfault" {
    run ../bin/uselinux --segfault
}

@test "snap at snaps, not using ubuntu or mint" {
    run ../bin/uselinux --snap-at-snaps -d arch
    [ "$output" = "No more snaps!" ]
}

@test "snap at snaps, using mint" {
    run ../bin/uselinux --snap-at-snaps -d mint
    [ "$output" = "Well, Linux Mint doesn't have snaps, yes?" ]
}
