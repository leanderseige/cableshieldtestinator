# CABLESHIELDTESTINATOR

A post be [AudioPilz](https://www.youtube.com/@AudioPilz) from a while ago challanged me to build a device that non-invasively detects whether a cable is actually shielded or not. 

Cheap audio patch cables today often come unshielded. That means, that the second conductor (ground, the shield) is not actually a mesh of wires wrapped around the signal conductor (as I would expect it from cables for audio. Instead there are just two wires lying next to each other inside the coating.

So I was eager to find out whether a cable is shielded or not without cutting it.

The final outcome of my product is some sort of proof-of-concept. In my opinion it does work. However, ist was not too easy to make it work...

## The Idea

The idea was to lay the cable through a coil, run a signal through to both of the conductors alternating and measure the response that gets induced in the coil. 

A cable with two equal conductors (unshielded) should behave different from a cable where one conductor is wrapped around the other one (shielded).

It turned out that this approach oviously was good enough to separate shielded cables from unshielded ones.

![Block  diagram](images/blockdiagram.png)

## Circuit Diagram

The Cicruit uses a TL084 as an oscillator to generate a triangular waveform at about 250 Hz. An ATMEGA328p microcontroller uses two relays to pass this signal through this or that wire. The cable under test is placed inside a coil. The coil itself is connected to another TL084 to amplify and smooth the signal. Finally, the microcontroller reads the analog signal and evaluates it.

![Block  diagram](images/schematic.png)








