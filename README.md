# sshconnector 

Small ncurses SSH bookmark tool. Let you select hosts via a config file and connect them via the ssh command.
## What is it?

### Which systems?
Only tested on linux/debian so far.

### How to run?
If you have installed the ncurses5 libraries, just type
```bash
./sshconnector «static host file» «user defined host file» «manual»
```

### License?
sshconnector, distributed under the GNU GPL v2. For full terms see the included COPYING file on the GitHub reposity.

### Pro tip?
sshconnector works perfectly in a terminal multiplexer like tmux.

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