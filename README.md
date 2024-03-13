# sshconnector 
Small ncurses SSH bookmark tool. Let you select hosts via a config file and connect them via the ssh command.

## Usage
If you have installed the ncurses5 libraries, just type
```bash
./sshconnector «static host file» «user defined host file» «manual»
```

- `<<static host file>>` is basically a system wide `hosts.conf` for multi user environments.
- `<<user defined host file>>` is a per user `hosts.conf` that is appended to the main first hosts list.
- `<<manual>>` is a custom manual files that will be displayed in the application with the `h` key.

> Note that the the first `hosts.conf` parameter is mandatory, the rest are optional paratmeters.

## Development
### Requirements
- make
- gcc `min std=c++11`
- libncurses5-dev

### Build
```bash
make
```

# Credits
> Beardman Studios (c) 2024