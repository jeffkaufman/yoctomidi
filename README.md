# Yoctopus MIDI

Reads values from a Yocto-3D-V2 and sends them out as MIDI CC messages.  Mac
only.

## Usage:

No dependencies beyond the compiler; just run:

```
$ (cd yoctolib/Examples/Doc-GettingStarted-Yocto-3D/ && make)
$ make
```

Then when you're ready to run it, run:

```
make run
```

It will present as a midi device labeled "yocto 3d v2 controller" which sends
CC values.

