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

