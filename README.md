# hideaway

A plugin for [_Interception Tools_][interception-tools] to move the mouse
pointer out of sight after a couple of seconds. The expected parameters are like
follows:

```
hideaway <seconds> <away x> <away y> <back x> <back y>
```

For example, this is to move the mouse away after four seconds, and back from
the bottom right corner to the center of the screen when there's interaction
with the mouse:

```
hideaway 4 10000 10000 -512 -256
```

The `-512 -256` is mouse specific and it's what works for me to put the mouse
pointer back on the screen's center.

## Dependencies

- [Interception Tools][interception-tools]

## Building

```
$ git clone git@gitlab.com:interception/linux/plugins/hideaway.git
$ cd hideaway
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Execution

`hideaway` is an [_Interception Tools_][interception-tools] plugin. A possible
`udevmon` job configuration is:

```yaml
- JOB: "intercept $DEVNODE | hideaway 4 10000 10000 -512 -256 | uinput -d $DEVNODE"
  DEVICE:
    EVENTS:
      EV_REL: [REL_X, REL_Y]

```

For more information about the [_Interception Tools_][interception-tools], check
the project's website.

## Installation

I'm maintaining an Archlinux package on AUR:

- <https://aur.archlinux.org/packages/interception-hideaway>

I don't use Ubuntu and recommend Archlinux instead, as it provides the AUR, so I
don't maintain PPAs. For more information on Ubuntu/Debian installation check
this:

- <https://askubuntu.com/questions/979359/how-do-i-install-caps2esc>

## License

<a href="https://gitlab.com/interception/linux/plugins/caps2esc/blob/master/LICENSE.md">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/License_icon-mit-2.svg/120px-License_icon-mit-2.svg.png" alt="MIT">
</a>

Copyright © 2017 Francisco Lopes da Silva

[interception-tools]: https://gitlab.com/interception/linux/tools
