# Yoctopus MIDI

Reads values from a Yocto-3D-V2 and sends them out as MIDI CC messages.  Mac
only.

## Usage:

No dependencies beyond the compiler; just run:

```
$ make run
```

This will build it and start it running.  It will present as a midi device
labeled "yocto 3d v2 controller" which sends CC values.

