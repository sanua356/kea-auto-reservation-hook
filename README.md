# KEA Auto reservation hook

## Introduction

This repository provides a hook for KEA that allows automatic reservation of addresses for clients in subnets by MAC address when they request them for the first time.

## Service Info
The hook is implemented only for `kea-dhcp4` service.

## Parameters
### Optional
`runtime-logging` - Boolean type (by default: false). Determines whether to log save and reservation error events for each client to a log file.

### Required
`enabled` - Boolean type. Determines the hook's operating status. False - disabled. True - enabled.

`subnets` - Array of strings. Determines for which subnets automatic address reservation should be performed. Value format: IPv4/netmask (Example: "192.168.0.0/24").

## Example configuration
```json
{
  "enabled": true,
  "subnets": ["192.168.0.0/24"],
  "runtime-logging": true
}
```

## Example work
<img width="409" height="286" alt="image" src="https://github.com/user-attachments/assets/c8b61120-662a-49cc-bb05-2d6af72a54e5" />


## Build

### Build with G++
1. Install kea-dev package (In Arch it is part of the KEA package, in other distributions it may be a separate package).
2. Clone this repository `git clone https://github.com/sanua356/kea-auto-reservation-hook.git`.
3. Go to the repository directory `cd ./kea-auto-reservation-hook`.
4. Make the build script executable `chmod +x ./build.sh`.
5. Run build script `./build.sh` (sudo rights may be required).
6. Find ".so" library in current directory.

### Build with Meson
1. Clone KEA official repository: `git clone https://gitlab.isc.org/isc-projects/kea.git`.
2. Clone current repository in KEA repository path `/src/hooks/dhcp/`.
3. In file `meson.build` by path `/src/hooks/dhcp` paste new line `subdir('kea-auto-reservation-hook')` .
4. Run `meson compile -C build` in terminal.
5. After compilation the library file is located at the path `/build/src/hooks/dhcp/kea-auto-reservation-hook`.

## License

MIT
